// lambda-predicate.cpp by Bill Weinman [bw.org]
// updated 2022-09-09
#include <format>
#include <algorithm>
#include <vector>
#include <string>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

// disp_v: display vector
void disp_v(const auto& v) {
    if(!v.size()) return;
    for(auto e :  v) print("{} ", e);
    print("\n");
}

int main() {
    std::vector<int> v1{ 1, 7, 4, 9, 4, 8, 12, 10, 20 };

    // is_div4 predicate
    auto is_div4 = [](int i) { return i % 4 == 0; };

    // count numbers div by 4
    auto count = std::count_if(v1.begin(), v1.end(), is_div4);
    print("count is {}\n", count);
    
    // copy numbers div by 4s
    std::vector<int> v2{};
    std::copy_if(v1.begin(), v1.end(), std::back_inserter(v2), is_div4);
    disp_v(v2);

    // char_upper operator
    auto char_upper = [](char c) ->char {
        if(c >= 'a' && c <= 'z') return c - ('a' - 'A');
        else return c;
    };

    std::string s1 {"big light in sky slated to appear in east"};
    std::string s2 {};
    std::string s3 {};
    print("\ns1: {}\n", s1);

    // char_upper transform
    std::transform(s1.begin(), s1.end(), std::back_inserter(s2), char_upper);
    print("s2: {}\n", s2);

    // title_case operator
    auto title_case = [&char_upper](char c) {
        static char prev_c {' '};
        char new_c {prev_c == ' ' ? char_upper(c) : c};
        prev_c = c;
        return new_c;
    };

    // title_case transform
    std::transform(s1.begin(), s1.end(), std::back_inserter(s3), title_case);
    print("\ns3: {}\n", s3);
}
