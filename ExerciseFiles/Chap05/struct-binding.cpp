// struct-binding.cpp by Bill Weinman [bw.org]
// updated 2022-09-12
#include <format>
#include <tuple>
#include <vector>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

auto newline = []{ print("\n"); };

struct thing {
    int alpha {};
    double bravo {};
    const char* charlie {};
};

int main() {
    thing x1 {42, 73.2, "hello, earthlings!"};
    std::tuple<int, double, const char*> x2 {42, 73.2, "hello, earthlings!"};
    std::pair<int, double> x3 {47, 112.5};

    print("struct:\n");
    const auto [a1, b1, c1] = x1;
    print("a1 {}, b1 {}, c1 {}\n", a1, b1, c1);
    newline();

    print("tuple:\n");
    const auto [a2, b2, c2] = x2;
    print("a2 {}, b2 {}, c2 {}\n", a2, b2, c2);
    newline();

    print("pair:\n");
    auto& [a3, b3] = x3;
    print("a3 {}, b3 {}\n", a3, b3);
    newline();

    print("modified pair:\n");
    a3 = 212;
    b3 = 500.9;
    auto& [a4, b4] = x3;
    print("a4 {}, b4 {}\n", a4, b4);
    newline();

    print("C-array:\n");
    const int x5[] {1, 2, 3, 4, 5};
    auto [a5, b5, c5, d5, e5] = x5;
    print("a5 {}, b5 {}, c5 {}, d5 {}, e5 {}\n", a5, b5, c5, d5, e5);
    newline();

    print("C-string:\n");
    const char x6[] {"four"};
    auto [a6, b6, c6, d6, e6] = x6;
    print("a6 x{:02x}, b6 x{:02x}, c6 x{:02x}, d6 x{:02x}, e6 x{:02x}\n", a6, b6, c6, d6, e6);
    newline();
}
