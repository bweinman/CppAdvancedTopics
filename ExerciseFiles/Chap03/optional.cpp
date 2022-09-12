// optional.cpp by Bill Weinman [bw.org]
// updated 2022-08-30
#include <format>
#include <optional>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

struct return_status {
    long value;
    bool have_value;
};

return_status factor(long n) {
    return_status rs {0, false};
    for(long i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            rs.value = i;
            rs.have_value = true;
            return rs;
        }
    }
    return rs;
}

int main() {
    long a {42};
    auto x = factor(a);

    if(x.have_value) print("lowest factor of {} is {}\n", a, x.value);
    else print("{} is prime\n", a);
}
