//  promise.cpp by Bill Weinman [bw.org]
//  as of 2022-09-10
#include <format>
#include <list>
#include <chrono>
#include <future>

using std::chrono::steady_clock;

using launch = std::launch;
using secs = std::chrono::duration<double>;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

struct prime_time {
    secs dur{};
    uint64_t count{};
};

void count_primes(const uint64_t& max, std::promise<prime_time> pval) {
    prime_time ret{};
    constexpr auto isprime = [](uint64_t n) {
        for(uint64_t i {2}; i < n / 2; ++i) {
            if(n % i == 0) return false;
        }
        return true;
    };
    uint64_t start {2};
    uint64_t end {max};
    auto t1 = steady_clock::now();
    for(auto i = start; i <= end ; ++i) {
        if(isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - t1;
    pval.set_value(ret);
}

int main() {
    constexpr uint64_t max_prime {0x1FFFF};  // largest uint64_t is 0xFFFFFFFFFFFFFFFF
    constexpr size_t num_threads {15};
    std::list<std::future<prime_time>> swarm;

    print("start parallel primes\n");
    auto t1 = steady_clock::now();
    for(auto i = num_threads; i; --i) {
        std::promise<prime_time> promise_o{};
        auto future_o = promise_o.get_future();
        swarm.emplace_back(std::move(future_o));
        std::thread t(count_primes, max_prime, std::move(promise_o));
        t.detach();
    }

    for(auto& f : swarm) {
        static auto i = 0;
        auto [dur, count] = f.get();    // structured binding (C++17)
        print("thread {:02}: found {} primes in {:.5}\n", ++i, count, dur);
    }

    secs dur_total{ steady_clock::now() - t1 };
    print("total duration: {:.5}s\n", dur_total.count());
}
