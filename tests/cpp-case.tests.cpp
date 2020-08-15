
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-case.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppCase", "[CppCase]")
{
    CppCase cppCase;
    CHECK(to_string(cppCase, Definition) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppCase", "[CppCase]")
{
    CppCase cppCase {
        "Foo",
        CppSourceBlock {
            "// CppSourceBlock"
        }, Break
    };
    CHECK(to_string(cppCase, Definition) ==
R"(case Foo: {
    // CppSourceBlock
} break;
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppCase default", "[CppCase]")
{
    CppCase cppCase {
        Default,
        CppSourceBlock {
            "// CppSourceBlock"
        }, Break
    };
    CHECK(to_string(cppCase, Definition) ==
R"(default: {
    // CppSourceBlock
} break;
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppCase with CppCompileGuards", "[CppCase]")
{
    CppCase cppCase {
        CppCompileGuards {
            "DYNAMIC_STATIC_PLATFORM",
            "DYNAMIC_STATIC_FOO_ENABLED",
        },
        "Foo",
        CppSourceBlock {
            "// CppSourceBlock"
        }, Break
    };
    CHECK(to_string(cppCase, Definition) ==
R"(#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FOO_ENABLED
case Foo: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_FOO_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
