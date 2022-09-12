//  span.cpp by Bill Weinman [bw.org]
//  as of 2022-09-12
#include <format>
#include <span>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

template<typename T>
void pspan(const std::span<T> view) {
    print("number of elements: {}\n", view.size());
    print("size of span: {}\n", view.size_bytes());
    for(auto e : view) print("{} ", e);
    print("\n");
}

int main() {
    int ca1[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    pspan<int>(ca1);
}
