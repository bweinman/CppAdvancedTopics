// lambda-hello.cpp by Bill Weinman [bw.org]
// updated 2022-09-09
#include <format>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

int main() {
    auto x = []{ print("Hello, earthlings\n"); };
    x();
}
