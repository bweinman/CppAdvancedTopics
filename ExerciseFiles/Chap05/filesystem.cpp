// filesystem.cpp by Bill Weinman [bw.org]
// as of 2022-09-12
#include <format>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

// format-style print()
constexpr void print(const std::string_view str_fmt, auto&&... args) {
    fputs(std::vformat(str_fmt, std::make_format_args(args...)).c_str(), stdout);
}

auto newline = []{ print("\n"); };

template<>
struct std::formatter<fs::path>: std::formatter<int> {
    template<typename Context>
    auto format(const fs::path& p, Context& ctx) {
        return format_to(ctx.out(), "{}", p.string());
    }
};

void printdir(const fs::path& p) {
    using de = fs::directory_entry;
    std::vector<de> dir{};

    auto dircmp_lc = [](const de& lhs, const de& rhs) ->bool {
        return lhs.path().string() < rhs.path().string();
    };

    if(!fs::exists(p)) {
        print("{} does not exist\n", fs::absolute(p));
        return;
    }
    if(is_directory(p)) {
        for(const auto& de : fs::directory_iterator{p}) {
            dir.emplace_back(de);
        }
        std::sort(dir.begin(), dir.end(), dircmp_lc);
        for(const auto& e : dir) {
            print("{} ", fs::relative(e, p));
        }
        newline();
    } else {
        print("not a directory: {}\n", p);
    }
}

constexpr const char* fp{ "testdir/foo.txt" };
constexpr const char* homedir {"/Users/billw/Xcode/ExerciseFiles"};

int main() {
    fs::path p{ fp };
    print("p: {}\n", p);
    
    if(!fs::exists(homedir)) {
        print("{} does not exist\n", fs::absolute(homedir));
        return 1;
    }

    try {
        print("current_path: {}\n", fs::current_path());
        print("change current_path to {}\n", homedir);
        fs::current_path(homedir);
        newline();

        print("current_path: {}\n", fs::current_path());
        print("absolute(p): {}\n", fs::absolute(p));
        newline();

        print("concatenate: {}\n", fs::path{ "testdir" } += "foo.txt");
        print("append: {}\n", fs::path{ "testdir" } /= "foo.txt");
        newline();

        print("canonical: {}\n", fs::canonical(fs::path(".")));
        printdir(fs::path(".") /= "chap01");

    } catch (const fs::filesystem_error& e) {
        print("{}\n", e.what());
        print("path1: {}\n", e.path1());
        print("path2: {}\n", e.path2());
    }
}
