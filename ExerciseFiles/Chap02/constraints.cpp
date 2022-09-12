// constraints.cpp by Bill Weinman [bw.org]
// updated 2022-08-23
#include <format>
#include <concepts>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

template<typename T>
requires std::integral<T>
T arg42(const T& arg) {
    return arg + 42;
}

int main() {
    auto n = 7.9;
    print("The answer is [{}]\n", arg42(n));
}
