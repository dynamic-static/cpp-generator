
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-enumerator.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppEnumerator", "[CppEnumerator]")
{
    CppEnumerator cppEnumerator;
    CHECK(to_string(cppEnumerator, Declaration) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator with name", "[CppEnumerator]")
{
    CppEnumerator cppEnumerator { "Foo" };
    CHECK(to_string(cppEnumerator, Declaration) == "Foo,\n");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator with name and value", "[CppEnumerator]")
{
    CppEnumerator cppEnumerator { "Foo", "1 << 1" };
    CHECK(to_string(cppEnumerator, Declaration) == "Foo = 1 << 1,\n");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator with CppCompileGuard", "[CppEnumerator]")
{
    CppEnumerator cppEnumerator {
        CppCompileGuards { "DYNAMIC_STATIC_FEATURE_ENABLED" },
        "Foo", "1 << 1"
    };
    CHECK(to_string(cppEnumerator, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
Foo = 1 << 1,
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator with CppCompileGuard::Collection", "[CppEnumerator]")
{
    CppEnumerator cppEnumerator {
        CppCompileGuards {
            "DYNAMIC_STATIC_PLATFORM",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
        },
        "Foo", "1 << 1"
    };
    CHECK(to_string(cppEnumerator, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
Foo = 1 << 1,
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppEnumerator::Collection", "[CppEnumerator::Collection]")
{
    CppEnumerator::Collection cppEnumerators;
    CHECK(to_string(cppEnumerators, Declaration) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator::Collection single CppEnumerator", "[CppEnumerator::Collection]")
{
    CppEnumerator::Collection cppEnumerators {{ "Foo", "1" }};
    CHECK(to_string(cppEnumerators, Declaration) == "Foo = 1,\n");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator::Collection multiple CppEnumerators", "[CppEnumerator::Collection]")
{
    CppEnumerator::Collection cppEnumerators {
        { "Foo", "1" },
        { "Bar", "2" },
        { "Baz", "3" },
    };
    CHECK(to_string(cppEnumerators, Declaration) ==
R"(Foo = 1,
Bar = 2,
Baz = 3,
)");
}

// TODO : Filter duplicates test...

/**
TODO : Documentation
*/
TEST_CASE("CppEnumerator::Collection multiple CppEnumerators with CppCompileGuards", "[CppEnumerator::Collection]")
{
    CppEnumerator::Collection cppEnumerators {
        {
            CppCompileGuards { "DYNAMIC_STATIC_FOO_ENABLED" },
            "Foo", "1"
        },
        {
            "Bar", "2"
        },
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_BAZ_ENABLED",
            },
            "Baz", "3"
        },
    };
    CHECK(to_string(cppEnumerators, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_FOO_ENABLED
Foo = 1,
#endif // DYNAMIC_STATIC_FOO_ENABLED
Bar = 2,
#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_BAZ_ENABLED
Baz = 3,
#endif // DYNAMIC_STATIC_BAZ_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
