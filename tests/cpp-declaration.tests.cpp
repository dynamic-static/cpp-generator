
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-declaration.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppDeclaration", "[CppDeclaration]")
{
    CppDeclaration cppDeclaration;
    CHECK(to_string(cppDeclaration, Declaration) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("Populated CppDeclaration", "[CppDeclaration]")
{
    CppDeclaration cppDeclaration { "using a = b;" };
    CHECK(to_string(cppDeclaration, Declaration) == "using a = b;\n");
}

/**
TODO : Documentation
*/
TEST_CASE("Populated CppDeclaration with a CppCompileGuard", "[CppDeclaration]")
{
    CppDeclaration cppDeclaration {
        "DYNAMIC_STATIC_FEATURE_ENABLED",
        "using a = b;"
    };
    CHECK(to_string(cppDeclaration, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
using a = b;
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
)");
}

/**
TODO : Documentation
*/
TEST_CASE("Populated CppDeclaration with a CppCompileGuard::Collection", "[CppDeclaration]")
{
    CppDeclaration cppDeclaration {
        CppCompileGuards {
            "DYNAMIC_STATIC_PLATFORM",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
        },
        "using a = b;"
    };
    CHECK(to_string(cppDeclaration, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
using a = b;
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppDeclaration::Collection", "[CppDeclaration::Collection]")
{
    CppDeclaration::Collection cppDeclarations;
    CHECK(to_string(cppDeclarations, Declaration) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppDeclaration::Collection with single CppDeclaration", "[CppDeclaration::Collection]")
{
    CppDeclaration::Collection cppDeclarations { "using a = b;" };
    CHECK(to_string(cppDeclarations, Declaration) == "using a = b;\n");
}

/**
TODO : Documentation
*/
TEST_CASE("CppDeclaration::Collection with multiple CppDeclarations", "[CppDeclaration::Collection]")
{
    CppDeclaration::Collection cppDeclarations;
    SECTION("TODO")
    {
        cppDeclarations = {
            "using a = b;",
            "using x = y;",
        };
    }
    SECTION("TODO")
    {
        cppDeclarations = {
            "",
            "using a = b;",
            std::string(),
            { },
            "using x = y;",
            std::string_view(),
        };
    }
        CHECK(to_string(cppDeclarations, Declaration) ==
R"(using a = b;
using x = y;
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppDeclaration::Collection with multiple CppDeclarations with CppCompileGuards", "[CppDeclaration::Collection]")
{
    CppDeclaration::Collection cppDeclarations {
        "using a = b;",
        {
            CppCompileGuard { "DYNAMIC_STATIC_OPTIONS_ENABLED" },
            "using Flags = uint32_t;"
        },
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_FEATURE_ENABLED",
            },
            "using x = y;",
        }
    };
    CHECK(to_string(cppDeclarations, Declaration) ==
R"(using a = b;
#ifdef DYNAMIC_STATIC_OPTIONS_ENABLED
using Flags = uint32_t;
#endif // DYNAMIC_STATIC_OPTIONS_ENABLED
#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
using x = y;
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
