
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

/**
TODO : Documentation
*/
TEST_CASE("Empty CppCase::Collection", "[CppCase::Collection]")
{
    CppCase::Collection cppCases;
    CHECK(to_string(cppCases, Definition) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppCase::Collection with CppCases", "[CppCase::Collection]")
{
    CppCase::Collection cppCases {
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_FOO_ENABLED"
            },
            "Foo",
            CppSourceBlock {
                "// CppSourceBlock"
            }, Break
        },
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_BAR_ENABLED",
            },
            "Bar",
            CppSourceBlock {
                "// CppSourceBlock"
            }, Break
        },
        {
            "Baz",
            CppSourceBlock {
                "// CppSourceBlock"
            }, Break
        },
        {
            Default,
            CppSourceBlock {
                "assert(false);"
            }
        },
    };
    CHECK(to_string(cppCases, Definition) ==
R"(#ifdef DYNAMIC_STATIC_FOO_ENABLED
case Foo: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_FOO_ENABLED
#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_BAR_ENABLED
case Bar: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_BAR_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
case Baz: {
    // CppSourceBlock
} break;
default: {
    assert(false);
}
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
