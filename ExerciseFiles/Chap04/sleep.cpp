// sleep.cpp by Bill Weinman [bw.org]
// as of 2022-09-10
#include <format>
#include <chrono>
#include <thread>

using std::chrono::steady_clock;
using std::chrono::duration;
using std::this_thread::sleep_for;
using std::this_thread::sleep_until;

using namespace std::chrono_literals;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    print("let's wait a bit...\n");

    auto t1 = steady_clock::now();
    print("sleep for 2.5 seconds\n");
    sleep_for(2s + 500ms);

    print("sleep for 3 seconds\n");
    sleep_until(steady_clock::now() + 3s);

    duration<double> dur1 = steady_clock::now() - t1;
    print("total duration: {:.5}\n", dur1);
}
