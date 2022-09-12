// any.cpp by Bill Weinman [bw.org]
// updated 2022-09-10
#include <format>
#include <string>
#include <any>
#include <vector>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

void print_any(const std::any& o) {
    if (!o.has_value()) print("None\n");
    else if (o.type() == typeid(int)) {
        auto x = std::any_cast<int>(o);
        print("int {}\n", x);
    }
    else if (o.type() == typeid(std::string)) {
        auto x = std::any_cast<const std::string&>(o);
        print("string {}\n", x);
    }
    else if (o.type() == typeid(std::vector<int>)) {
        auto v = std::any_cast<const std::vector<int>&>(o);
        print("vector of int, {} elements: ", v.size());
        for (const auto& e : v) print("{} ", e);
        print("\n");
    }
    else print("other type (compiler type string: {})\n", o.type().name());
}

int main() {
    print_any(47);
    print_any(std::string{"47"});
    print_any(std::vector{1, 2, 3, 4, 5});
    print_any(std::vector{1.0, 2.0, 3.0, 4.0, 5.0});
    print("\n");
}
