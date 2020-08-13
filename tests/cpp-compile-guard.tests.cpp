
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"

#include "catch.hpp"

#include <string>
#include <string_view>

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppCompileGuard", "[CppCompileGuard]")
{
    CppCompileGuard cppCompileGuard;
    CHECK(to_string(cppCompileGuard, Open) == std::string());
    CHECK(to_string(cppCompileGuard, Close) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("Populated CppCompileGuard", "[CppCompileGuard]")
{
    CppCompileGuard cppCompileGuard { "DYNAMIC_STATIC_FEATURE_ENABLED" };
    CHECK(to_string(cppCompileGuard, Open) == "#ifdef DYNAMIC_STATIC_FEATURE_ENABLED\n");
    CHECK(to_string(cppCompileGuard, Close) == "#endif // DYNAMIC_STATIC_FEATURE_ENABLED\n");
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppCompileGuard::Collection", "[CppCompileGuard::Collection]")
{
    CppCompileGuard::Collection cppCompileGuards;
    CHECK(to_string(cppCompileGuards, Open) == std::string());
    CHECK(to_string(cppCompileGuards, Close) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppCompileGuard::Collection with single CppCompileGuard", "[CppCompileGuard::Collection]")
{
    CppCompileGuard::Collection cppCompileGuards { "DYNAMIC_STATIC_FEATURE_ENABLED" };
    CHECK(to_string(cppCompileGuards, Open) == "#ifdef DYNAMIC_STATIC_FEATURE_ENABLED\n");
    CHECK(to_string(cppCompileGuards, Close) == "#endif // DYNAMIC_STATIC_FEATURE_ENABLED\n");
}

/**
TODO : Documentation
*/
TEST_CASE("CppCompileGuard::Collection with multiple CppCompileGuards", "[CppCompileGuard::Collection]")
{
    CppCompileGuard::Collection cppCompileGuards;
    SECTION("TODO")
    {
        cppCompileGuards = {
            "DYNAMIC_STATIC_PLATFORM_ENABLED",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
        };
    }
    SECTION("TODO")
    {
        cppCompileGuards = {
            { },
            "DYNAMIC_STATIC_PLATFORM_ENABLED",
            std::string_view(),
            "",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
            std::string(),
        };
    }
    SECTION("TODO")
    {
        cppCompileGuards = {
            "DYNAMIC_STATIC_PLATFORM_ENABLED",
            "DYNAMIC_STATIC_PLATFORM_ENABLED",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
            "DYNAMIC_STATIC_PLATFORM_ENABLED",
        };
    }
        CHECK(to_string(cppCompileGuards, Open) ==
R"(#ifdef DYNAMIC_STATIC_PLATFORM_ENABLED
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
)");
        CHECK(to_string(cppCompileGuards, Close) ==
R"(#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM_ENABLED
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
