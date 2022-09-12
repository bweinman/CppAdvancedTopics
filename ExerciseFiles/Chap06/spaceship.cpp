// spaceship.cpp by Bill Weinman [bw.org]
// updated 2022-09-12
#include <format>
#include <compare>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class num {
    int a;
public:
    num() = delete;
    constexpr num(const int& n) : a(n) {}
    constexpr int get() const { return a; }
    constexpr bool operator == (const num& rhs) const { return a == rhs.a; }
    constexpr bool operator != (const num& rhs) const { return !(a == rhs.a); }
    constexpr bool operator <  (const num& rhs) const { return a < rhs.a; }
    constexpr bool operator >  (const num& rhs) const { return rhs.a < a; }
    constexpr bool operator <= (const num& rhs) const { return !(rhs.a < a); }
    constexpr bool operator >= (const num& rhs) const { return !(a < rhs.a); }
};

int main() {
    num n {42};
    print("The num is {}\n", n.get());

    constexpr num na {7};
    constexpr num nb {7};
    constexpr num nc {42};
    static_assert(na < nc);
    static_assert(nc > na);
    static_assert(na == nb);
    static_assert(na <= nb);
    static_assert(na <= nc);
    static_assert(nc >= na);
    static_assert(na != nc);
    print("done.\n");
}
