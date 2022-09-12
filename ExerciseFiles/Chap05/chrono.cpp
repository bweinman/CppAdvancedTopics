// chrono.cpp by Bill Weinman [bw.org]
// as of 2022-09-12
#include <format>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

constexpr auto newline = []{ print("\n"); };

using std::chrono::duration;

using seconds = duration<double>;
using milliseconds = duration<double, std::milli>;
using microseconds = duration<double, std::micro>;
using fps24 = duration<unsigned long, std::ratio<1, 24>>;

constexpr uint64_t MAX_PRIME{ 0x1FFFF };

std::string make_commas(const uint64_t& num) {
    auto s = std::to_string(num);
    for (auto l = static_cast<int>(s.length()) - 3; l > 0; l -= 3) {
        s.insert(l, ",");
        }
    return s;
}

// Callable concept
template<typename T>
concept Callable = requires(T f) { f(); };

seconds timer(const Callable auto& f) {
    using timer_clock = std::chrono::steady_clock;
    auto t1 = timer_clock::now();
    auto count = f();
    auto t2 = timer_clock::now();
    seconds secs {t2 - t1};
    print("found {} primes in range\n", make_commas(count));
    return secs;
}

uint64_t count_primes() {
    constexpr auto isprime = [](const uint64_t n) {
        for(uint64_t i {2}; i < n / 2; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    };

    uint64_t count {0};
    uint64_t start {2};
    uint64_t end {MAX_PRIME};
    for (uint64_t i {start}; i <= end ; ++i) {
        if (isprime(i)) ++count;
   }
   return count;
}

int main() {
    auto t = std::chrono::system_clock::now();
    print("system_clock::now is {:%F %T %Z}\n", t);
    newline();

    print("counting primes up to {}\n", make_commas(MAX_PRIME));
    auto secs {timer(count_primes)};
    newline();

    print("time elapsed: {:.3f} sec\n", secs.count());
    print("time elapsed: {:.3f} ms\n", milliseconds(secs).count());
    print("time elapsed: {:.3e} μs\n", microseconds(secs).count());
    print("time elapsed: {} frames at 24 fps\n", floor<fps24>(secs).count());
    newline();

    print("time elapsed: {:.3}\n", secs);
    print("time elapsed: {:.3}\n", milliseconds(secs));
    print("time elapsed: {:.3}\n", microseconds(secs));
    newline();
}
