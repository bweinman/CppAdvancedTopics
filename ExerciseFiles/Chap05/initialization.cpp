// initialization.cpp by Bill Weinman [bw.org]
// updated 2022-09-02
#include <format>
#include <initializer_list>
#include <vector>
#include <string>

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

constexpr auto newline = []{ print("\n"); };

// print the elements of the vector
constexpr void pvec(const auto& v) {
    if (v.empty()) {
        print("[empty]\n");
    } else {
        for (const auto& i : v) print("{} ", i);
        print("\n");
    }
}

// many constructors
template <typename T>
class thing {
    T v {};
    std::string state {"undef"};
public:
    thing() : v(T{}) {
        print("default constructor\n");
        state = "zero";
    }

    thing(const T& p) : v(p) {
        print("copy constructor\n");
        state = "copied value";
    }

    thing(const std::initializer_list<T>& ilist) {
        print("initializer_list: ");
        for (const auto& e : ilist) print("{} ", e);
        print("\n");
        const auto sz = ilist.size();
        auto pt = ilist.begin();
        if(sz > 1) pt += sz / 2;
        v = *pt;
        state = "list constructed";
    }
    
    thing(const size_t p1, const T& p2) {
        print("specific constructor: {}, {}\n", p1, p2);
        if (p1 < 10) return;
        else v = p2;
        state = "specific value";
    }
    
    void status() const {
        print("status: {}, value {}\n", state, v);
    }
};

void initialize_this() {
    print("t1: ");
    thing<int> t1 {};
    t1.status();
    newline();
    
    print("t2: ");
    thing<int> t2 {7};
    t2.status();
    newline();

    print("t3: ");
    thing t3(42);
    t3.status();
    newline();

    print("t4: ");
    thing<int> t4 {1, 2, 3, 4, 5};
    t4.status();
    newline();

    print("t5: ");
    thing<int> t5 {1, 2};
    t5.status();
    newline();

    print("t6: ");
    thing<int> t6(1, 2);
    t6.status();
    newline();
}

int main() {
    int x {};
    print("x is {}\n", x);
}
