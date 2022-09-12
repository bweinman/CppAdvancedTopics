//  async.cpp by Bill Weinman [bw.org]
//  as of 2022-09-10
#include <format>
#include <list>
#include <chrono>
#include <future>

using std::chrono::steady_clock;
using secs = std::chrono::duration<double>;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

struct prime_time {
    secs dur{};
    uint64_t count{};
};

prime_time count_primes(const uint64_t& max) {
    prime_time ret{};
    constexpr auto isprime = [](uint64_t n) {
        for(uint64_t i {2}; i < n / 2; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    };
    uint64_t start {2};
    uint64_t end {max};
    auto time_thread_start = steady_clock::now();
    for(auto i = start; i <= end ; ++i) {
        if(isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - time_thread_start;
    return ret;
}

int main() {
    constexpr uint64_t max_prime {0x1FFFF};  // largest uint64_t is 0xFFFFFFFFFFFFFFFF
    constexpr size_t num_threads {15};
    std::list<std::future<prime_time>> swarm;

    print("start parallel primes\n");
    auto time_start = steady_clock::now();
    for(auto i = num_threads; i; --i) {
        swarm.emplace_back(std::async(count_primes, max_prime));
    }

    for(auto& f : swarm) {
        static auto i = 0;
        auto [dur, count] = f.get();    // structured binding (C++17)
        print("thread {:02}: found {} primes in {:.5}\n", ++i, count, dur);
    }

    secs dur_total {steady_clock::now() - time_start};
    print("total duration: {:.5}s\n", dur_total.count());
}
