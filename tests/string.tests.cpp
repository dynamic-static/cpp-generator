
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/string.hpp"

#include "catch2/catch.hpp"

#include <string>

namespace dst {
namespace cppgen {
namespace tests {

TEST_CASE("find() basic", "[SubString]")
{
    std::string str = "abcABC012!";
    for (auto c : str) {
        CHECK(cppgen::find_unquoted(str, c) == str.find(c));
    }
}

TEST_CASE("find() ignores quote escaped region", "[SubString]")
{
    std::string str = "abcA\"BC0\"12!";
    for (auto c : str) {
        if (c != '\"' && c != 'B' && c != 'C' && c != '0') {
            CHECK(cppgen::find_unquoted(str, c) == str.find(c));
        } else {
            CHECK(cppgen::find_unquoted(str, c) == std::string::npos);
        }
    }
}

TEST_CASE("find() ignores multiple quote escaped regions", "[SubString]")
{
    std::string str = R"(abcA"B\"C0\"1"2!)";
    for (auto c : str) {
        if (c != '\\' && c != '\"' && c != 'B' && c != 'C' && c != '0' && c != '1') {
            CHECK(cppgen::find_unquoted(str, c) == str.find(c));
        } else {
            CHECK(cppgen::find_unquoted(str, c) == std::string::npos);
        }
    }
}

TEST_CASE("find() ignores backtick escaped region", "[SubString]")
{
    std::string str = "abcA`BC0`12!";
    for (auto c : str) {
        if (c != '`' && c != 'B' && c != 'C' && c != '0') {
            CHECK(cppgen::find_unquoted(str, c) == str.find(c));
        } else {
            CHECK(cppgen::find_unquoted(str, c) == std::string::npos);
        }
    }
}

TEST_CASE("find() with multiline backticked region", "[SubString]")
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
        if (c != '`' && c != 'B' && c != 'C' && c != '0' && c != '1' && c != '2' && c != '3') {
            CHECK(cppgen::find_unquoted(str, c) == str.find(c));
        } else {
            CHECK(cppgen::find_unquoted(str, c) == std::string::npos);
        }
    }
}

TEST_CASE("trim_leading_whitespace() with empty string", "[SubString]")
{
    std::string str;
    auto subStr = trim_leading_whitespace(str);
    CHECK(subStr.empty());
}

TEST_CASE("trim_leading_whitespace() with no leading whitespace", "[SubString]")
{
    std::string str = "The quick brown fox    ";
    auto subStr = trim_leading_whitespace(str);
    CHECK(subStr.size() == str.size());
}

TEST_CASE("trim_leading_whitespace() with leading whitespace", "[SubString]")
{
    std::string str = "    The quick brown fox    ";
    auto subStr = trim_leading_whitespace(str);
    CHECK(subStr.size() == str.size() - 4);
    // CHECK(subStr.begin == str.find('T'));
}

TEST_CASE("trim_trailing_whitespace() with empty string", "[SubString]")
{
    std::string str;
    auto subStr = trim_trailing_whitespace(str);
    CHECK(subStr.empty());
}

TEST_CASE("trim_trailing_whitespace() with no trailing whitespace", "[SubString]")
{
    std::string str = "    The quick brown fox";
    auto subStr = trim_trailing_whitespace(str);
    CHECK(subStr.size() == str.size());
}

TEST_CASE("trim_trailing_whitespace() with trailing whitespace", "[SubString]")
{
    std::string str = "    The quick brown fox    ";
    auto subStr = trim_trailing_whitespace(str);
    CHECK(subStr.size() == str.size() - 4);
    // CHECK(subStr.end == str.find('x') + 1);
}

TEST_CASE("trim_whitespace() with empty string", "[SubString]")
{
    std::string str;
    auto subStr = trim_whitespace(str);
    CHECK(subStr.empty());
}

TEST_CASE("trim_whitespace() with no leading or trailing whitespace", "[SubString]")
{
    std::string str = "The quick brown fox";
    auto subStr = trim_whitespace(str);
    CHECK(subStr.size() == str.size());
}

TEST_CASE("trim_whitespace() with leading and trailing whitespace", "[SubString]")
{
    std::string str = "    The quick brown fox    ";
    auto subStr = trim_whitespace(str);
    CHECK(subStr.size() == str.size() - 8);
    // CHECK(subStr.begin == str.find('T'));
    // CHECK(subStr.end == str.find('x') + 1);
}

TEST_CASE("unquote() TODO", "[SubString]")
{
    // TODO :
}

} // namespace tests
} // namespace cppgen
} // namespace dst
