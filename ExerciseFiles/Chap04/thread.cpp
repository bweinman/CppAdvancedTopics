// thread.cpp by Bill Weinman [bw.org]
// as of 2022-09-10
#include <format>
#include <chrono>
#include <thread>

using std::thread;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void sleepms(const unsigned ms) {
    using millis = std::chrono::milliseconds;
    std::this_thread::sleep_for(millis(ms));
}

void thread_func(const int n) {
    print("This is t{}\n", n);
    auto slp_dur = 100 * n;

    for(auto i = 0; i < 5; ++i) {
        sleepms(slp_dur);
        print("t{} ({}ms): loop {}\n", n, slp_dur, i + 1);
    }
    print("Finishing t{}\n", n);
}

int main() {
    thread t1(thread_func, 1);
    thread t2(thread_func, 2);
    t1.detach();
    t2.detach();

    print("main() sleep 2 sec\n");
    sleepms(2000);   // give the threads time

    print("end of main()\n");
}
