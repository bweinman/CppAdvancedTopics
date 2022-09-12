// spaceship-frac.cpp by Bill Weinman [bw.org]
// updated 2022-09-02
#include <format>
#include <compare>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

class frac {
    long n;
    long d;
public:
    frac() = delete;
    constexpr frac(int a, int b) : n{a}, d{b} {}

    constexpr double dbl() const {
        return static_cast<double>(n) / static_cast<double>(d);
    }
   
    constexpr auto operator <=> (const frac& rhs) const {
        return dbl() <=> rhs.dbl();
    };

    constexpr auto operator == (const frac& rhs) const {
        return dbl() <=> rhs.dbl() == 0;
    };
};

int main() {
    constexpr frac a(10, 15);
    constexpr frac b(2, 3);
    constexpr frac c(5, 3);

    print("The frac a is {:.3f}\n", a.dbl());
    print("The frac a is {:.3f}\n", b.dbl());
    print("The frac a is {:.3f}\n", c.dbl());
    
    static_assert(a < c);
    static_assert(c > a);
    static_assert(a == b);
    static_assert(a <= b);
    static_assert(a <= c);
    static_assert(c >= a);
    static_assert(a != c);

    print("done.\n");
}
