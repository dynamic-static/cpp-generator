
#include "dynamic_static/cpp-generator/string.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace string {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("TODO 0", "[TODO]")
{
    SECTION("TODO")
    {
        std::string str = "abcABC012!";
        for (auto c : str) {
            CHECK(str.find(c) == find(str, c));
        }
    }
    SECTION("TODO")
    {
        std::string str = "abcA\"BC0\"12!";
        for (auto c : str) {
            if (c != '\"' &&
                c != 'B' &&
                c != 'C' &&
                c != '0') {
                CHECK(str.find(c) == find(str, c));
            } else {
                CHECK(find(str, c) == std::string::npos);
            }
        }
    }
    SECTION("TODO")
    {
        std::string str = R"(abcA"B\"C0\"1"2!)";
        for (auto c : str) {
            if (c != '\\' &&
                c != '\"' &&
                c != 'B' &&
                c != 'C' &&
                c != '0' &&
                c != '1') {
                CHECK(str.find(c) == find(str, c));
                if (str.find(c) != find(str, c)) {
                    int b = 0;
                }
            } else {
                CHECK(find(str, c) == std::string::npos);
            }
        }
    }
    SECTION("TODO")
    {
        std::string str = "abcA`BC0`12!";
        for (auto c : str) {
            if (c != '`' &&
                c != 'B' &&
                c != 'C' &&
                c != '0') {
                CHECK(str.find(c) == find(str, c));
            } else {
                CHECK(find(str, c) == std::string::npos);
            }
        }
    }
    SECTION("TODO")
    {
        std::string str = R"(
            abcA
            ```
            BC0
            123
            ```
            456!
        )";
        for (auto c : str) {
            if (c != '`' &&
                c != 'B' &&
                c != 'C' &&
                c != '0' &&
                c != '1' &&
                c != '2' &&
                c != '3') {
                CHECK(str.find(c) == find(str, c));
            } else {
                CHECK(find(str, c) == std::string::npos);
            }
        }
    }
}

} // namespace tests
} // namespace string
} // namespace cppgen
} // namespace dst

#if 0
int main(int argc, const char* argv[])
{
    std::ofstream file("formatting.txt");
    file << dst::cppgen::format(R"(
        the
            quick
                brown
        fox
            jumps
        over
    the
    lazy
    dog
    )");
    return 0;
}
#endif
