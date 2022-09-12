// atomic.cpp by Bill Weinman [bw.org]
// as of 2022-09-12
#include <format>
#include <string>
#include <list>
#include <thread>
#include <atomic>

std::atomic_bool ready {};
std::atomic_uint64_t g_count {};
std::atomic_flag winner {};

constexpr uint64_t max_count {1'000'000};
constexpr int max_threads {100};

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

std::string make_commas(const uint64_t& num) {
    auto s = std::to_string(num);
    for (auto l = static_cast<int>(s.length()) - 3; l > 0; l -= 3) {
        s.insert(l, ",");
        }
    return s;
}

void countem(int id) {
    while (!ready) std::this_thread::yield();
    for (auto i = 0; i < max_count; ++i) {
        if (winner.test()) return;
        ++g_count;
    }
    if (!winner.test_and_set()) {
        print("thread {:02} won!\n", id);
        winner.notify_all();
    }
};

int main() {
    std::list<std::thread> swarm {};
    print("spawn {} threads\n", max_threads);
    for (auto i = 0; i < max_threads; ++i) {
        swarm.emplace_back(countem, i);
    }
    
    print("Go!\n");
    ready = true;

    for (auto& t : swarm) t.join();
    print("global count: {}\n", make_commas(g_count));
}
