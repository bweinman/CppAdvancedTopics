//  format.cpp by Bill Weinman [bw.org]
//  as of 2022-09-12
#include <format>
#include <iostream>
#include <string_view>
#include <numbers>

using std::numbers::pi;

template<typename T>
struct Frac {
    T n;
    T d;
};

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// format specialization
template <typename T>
struct std::formatter<Frac<T>> : std::formatter<int> {
    template <typename Context>
    auto format(const Frac<T>& f, Context& ctx) const {
        return format_to(ctx.out(), "{}/{}", f.n, f.d);
    }
};

// ostream specialization
template <typename T>
std::ostream& operator<<(std::ostream& os, const Frac<T>& f) {
    os << f.n << '/' << f.d;
    return os;
}

int main() {
    const int inta {47};
    const char * human {"earthlings"};
    const std::string_view alien {"vulcans"};
    const double df_pi {pi};

    std::cout << "inta is " << inta << '\n'
        << "hello, " << human << '\n'
        << "All " << alien << " are welcome here\n"
        << "π is " << df_pi << '\n';


    print("Hello {}\n", human);
    print("Hello {} we are {}\n", human, alien);
    print("Hello {1} we are {0}\n", human, alien);

    print("π is {}\n", df_pi);
    print("π is {:.5}\n", df_pi);
    print("inta is {1:}, π is {0:.5}\n", df_pi, inta);

    print("inta is [{:*<10}]\n", inta);
    print("inta is [{:0>10}]\n", inta);
    print("inta is [{:^10}]\n", inta);
    print("inta is [{:_^10}]\n", inta);

    print("{:>8}: [{:04X}]\n", "Hex", inta);
    print("{:>8}: [{:4o}]\n", "Octal", inta);
    print("{:>8}: [{:4d}]\n", "Decimal", inta);

    Frac<long> n {3, 5};
    std::cout << "Frac: " << n << '\n';
    print("Frac: {}\n", n);
}
