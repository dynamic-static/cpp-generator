
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

#include <string>
#include <string_view>

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
    CppDeclaration::Collection cppCompileGuards;
    SECTION("TODO")
    {
        cppCompileGuards = {
            "using a = b;",
            "using x = y;",
        };
    }
    SECTION("TODO")
    {
        cppCompileGuards = {
            "",
            "using a = b;",
            std::string(),
            { },
            "using x = y;",
            std::string_view(),
        };
    }
        CHECK(to_string(cppCompileGuards, Declaration) ==
R"(using a = b;
using x = y;
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
