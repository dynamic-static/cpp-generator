
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-parameter.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("CppParameter", "[CppParameter]")
{
    SECTION("TODO")
    {
        CppParameter cppParameter;
        CHECK(cppParameter.generate(Declaration) == std::string());
        CHECK(cppParameter.generate(Definition) == cppParameter.generate(Declaration));
        CHECK(cppParameter.generate(InlineDefinition) == cppParameter.generate(Declaration));
    }
    SECTION("TODO")
    {
        CppParameter cppParameter { "size_t", "count" };
        CHECK(cppParameter.generate(Declaration) == "size_t count");
        CHECK(cppParameter.generate(Definition) == cppParameter.generate(Declaration));
        CHECK(cppParameter.generate(InlineDefinition) == cppParameter.generate(Declaration));
    }
    SECTION("TODO")
    {
        CppParameter cppParameter { "size_t", "count", "1" };
        CHECK(cppParameter.generate(Declaration) == "size_t count = 1");
        CHECK(cppParameter.generate(Definition) == "size_t count");
        CHECK(cppParameter.generate(InlineDefinition) == cppParameter.generate(Declaration));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("CppParameters", "[CppParameters]")
{
    SECTION("TODO")
    {
        CppParameters cppParameters;
        CHECK(cppParameters.generate(Declaration) == std::string());
        CHECK(cppParameters.generate(Definition) == cppParameters.generate(Declaration));
        CHECK(cppParameters.generate(InlineDefinition) == cppParameters.generate(Declaration));
    }
    SECTION("TODO")
    {
        CppParameters cppParameters {{ "size_t", "count" }};
        CHECK(cppParameters.generate(Declaration) == "size_t count");
        CHECK(cppParameters.generate(Definition) == cppParameters.generate(Declaration));
        CHECK(cppParameters.generate(InlineDefinition) == cppParameters.generate(Declaration));
    }
    SECTION("TODO")
    {
        CppParameters cppParameters {{ "size_t", "objCount", "1" }, { "const Obj*", "pObjs", "nullptr" }};
        CHECK(cppParameters.generate(Declaration) == "size_t objCount = 1, const Obj* pObjs = nullptr");
        CHECK(cppParameters.generate(Definition) == "size_t objCount, const Obj* pObjs");
        CHECK(cppParameters.generate(InlineDefinition) == cppParameters.generate(Declaration));
    }

    SECTION("TODO")
    {
        CppParameters cppParameters {{ }, { "size_t", "objCount", "1" }, { }, { "const Obj*", "pObjs", "nullptr" }};
        CHECK(cppParameters.generate(Declaration) == "size_t objCount = 1, const Obj* pObjs = nullptr");
        CHECK(cppParameters.generate(Definition) == "size_t objCount, const Obj* pObjs");
        CHECK(cppParameters.generate(InlineDefinition) == cppParameters.generate(Declaration));
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
