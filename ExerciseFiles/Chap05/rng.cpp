// rng.cpp by Bill Weinman [bw.org]
// as of 2022-09-02
#include <format>
#include <string_view>
#include <vector>
#include <random>
#include <algorithm>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

constexpr size_t n_samples {1000};
constexpr size_t n_partitions {10};
constexpr size_t n_max {50};

template <typename RNG>
void histogram(const std::string_view& rng_name) {
    auto p_ratio = static_cast<double>(RNG::max() / n_partitions);

    RNG rng{};
    std::vector<size_t> v(n_partitions);
    for (size_t i{}; i < n_samples; ++i) {
        ++v[static_cast<size_t>(rng() / p_ratio)];
    }
    
    auto max_el = std::max_element(v.begin(), v.end());
    auto v_ratio = *max_el / n_max;
    if (v_ratio < 1) v_ratio = 1;

    print("engine: {}\n", rng_name);
    for (size_t i{}; i < n_partitions; ++i) {
        print("{:02}:{:*<{}}\n", i + 1, ' ', v[i] / v_ratio);
    }
    print("\n");
}

int main() {
    histogram<std::random_device>("random_device");
    histogram<std::default_random_engine>("default_random_engine");

//    histogram<std::minstd_rand0>("minstd_rand0");
//    histogram<std::minstd_rand>("minstd_rand");
//
//    histogram<std::mt19937>("mt19937");
//    histogram<std::mt19937_64>("mt19937_64");
//
//    histogram<std::ranlux24_base>("ranlux24_base");
//    histogram<std::ranlux48_base>("ranlux48_base");
//
//    histogram<std::ranlux24>("ranlux24");
//    histogram<std::ranlux48>("ranlux48");
//
//    histogram<std::knuth_b>("knuth_b");
}
