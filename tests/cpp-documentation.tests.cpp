
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-documentation.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
static std::string to_string(const CppDocumentation& cppDocumentation, CppGenerationFlags cppGenerationFlags)
{
    return { };
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppDocumentation", "[CppDocumentation]")
{
    CppDocumentation cppDeclaration;
    CHECK(to_string(cppDeclaration, Declaration) == std::string());
}

} // namespace tests
} // namespace cppgen
} // namespace dst
