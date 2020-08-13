
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

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("CppCompileGuard", "[CppCompileGuard]")
{
    SECTION("TODO")
    {
        CppCompileGuard cppCompileGuard;
        CHECK(to_string(cppCompileGuard, Open) == std::string());
        CHECK(to_string(cppCompileGuard, Close) == std::string());
    }
    SECTION("TODO")
    {
        CppCompileGuard cppCompileGuard { "ENABLE_FEATURE" };
        CHECK(to_string(cppCompileGuard, Open) == "#ifdef ENABLE_FEATURE\n");
        CHECK(to_string(cppCompileGuard, Close) == "#endif // ENABLE_FEATURE\n");
    }
}

/**
TODO : Documentation
*/
TEST_CASE("CppCompileGuard::Collection", "[CppCompileGuard::Collection]")
{
    SECTION("TODO")
    {
        CppCompileGuard::Collection cppCompileGuards;
        CHECK(to_string(cppCompileGuards, Open) == std::string());
        CHECK(to_string(cppCompileGuards, Close) == std::string());
    }
    SECTION("TODO")
    {
        CppCompileGuard::Collection cppCompileGuards { "ENABLE_FEATURE" };
        CHECK(to_string(cppCompileGuards, Open) == "#ifdef ENABLE_FEATURE\n");
        CHECK(to_string(cppCompileGuards, Close) == "#endif // ENABLE_FEATURE\n");
    }
    SECTION("TODO")
    {
        CppCompileGuard::Collection cppCompileGuards {
            "ENABLE_PLATFORM",
            "ENABLE_FEATURE",
        };
        CHECK(to_string(cppCompileGuards, Open) ==
R"(#ifdef ENABLE_PLATFORM
#ifdef ENABLE_FEATURE
)");
        CHECK(to_string(cppCompileGuards, Close) ==
R"(#endif // ENABLE_FEATURE
#endif // ENABLE_PLATFORM
)");
    }
    SECTION("TODO")
    {
        CppCompileGuard::Collection cppCompileGuards {
            { },
            "ENABLE_PLATFORM",
            { },
            "ENABLE_FEATURE",
            { },
        };
        CHECK(to_string(cppCompileGuards, Open) ==
R"(#ifdef ENABLE_PLATFORM
#ifdef ENABLE_FEATURE
)");
        CHECK(to_string(cppCompileGuards, Close) ==
R"(#endif // ENABLE_FEATURE
#endif // ENABLE_PLATFORM
)");
    }
    SECTION("TODO")
    {
        CppCompileGuard::Collection cppCompileGuards {
            "ENABLE_PLATFORM",
            "ENABLE_PLATFORM",
            "ENABLE_FEATURE",
            "ENABLE_FEATURE",
            "ENABLE_FEATURE",
            "ENABLE_PLATFORM",
        };
        CHECK(to_string(cppCompileGuards, Open) ==
R"(#ifdef ENABLE_PLATFORM
#ifdef ENABLE_FEATURE
)");
        CHECK(to_string(cppCompileGuards, Close) ==
R"(#endif // ENABLE_FEATURE
#endif // ENABLE_PLATFORM
)");
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
