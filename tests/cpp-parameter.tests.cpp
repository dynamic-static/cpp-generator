
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

// TODO : Break into individual functions...
/**
TODO : Documentation
*/
TEST_CASE("CppParameter", "[CppParameter]")
{
    SECTION("TODO")
    {
        CppParameter cppParameter;
        CHECK(to_string(cppParameter, Declaration) == std::string());
        CHECK(to_string(cppParameter, Definition) == to_string(cppParameter, Declaration));
        CHECK(to_string(cppParameter, Inline | Definition) == to_string(cppParameter, Declaration));
    }
    SECTION("TODO")
    {
        CppParameter cppParameter { "size_t", "count" };
        CHECK(to_string(cppParameter, Declaration) == "size_t count");
        CHECK(to_string(cppParameter, Definition) == to_string(cppParameter, Declaration));
        CHECK(to_string(cppParameter, Inline | Definition) == to_string(cppParameter, Declaration));
    }
    SECTION("TODO")
    {
        CppParameter cppParameter { "size_t", "count", "1" };
        CHECK(to_string(cppParameter, Declaration) == "size_t count = 1");
        CHECK(to_string(cppParameter, Definition) == "size_t count");
        CHECK(to_string(cppParameter, Inline | Definition) == to_string(cppParameter, Declaration));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("CppParameter::Collection", "[CppParameter::Collection]")
{
    SECTION("TODO")
    {
        CppParameter::Collection cppParameters;
        CHECK(to_string(cppParameters, Declaration) == std::string());
        CHECK(to_string(cppParameters, Definition) == to_string(cppParameters, Declaration));
        CHECK(to_string(cppParameters, Inline | Definition) == to_string(cppParameters, Declaration));
    }
    SECTION("TODO")
    {
        CppParameter::Collection cppParameters {{ "size_t", "count" }};
        CHECK(to_string(cppParameters, Declaration) == "size_t count");
        CHECK(to_string(cppParameters, Definition) == to_string(cppParameters, Declaration));
        CHECK(to_string(cppParameters, Inline | Definition) == to_string(cppParameters, Declaration));
    }
    SECTION("TODO")
    {
        CppParameter::Collection cppParameters {{ "size_t", "objCount", "1" }, { "const Obj*", "pObjs", "nullptr" }};
        CHECK(to_string(cppParameters, Declaration) == "size_t objCount = 1, const Obj* pObjs = nullptr");
        CHECK(to_string(cppParameters, Definition) == "size_t objCount, const Obj* pObjs");
        CHECK(to_string(cppParameters, Inline | Definition) == to_string(cppParameters, Declaration));
    }
    SECTION("TODO")
    {
        CppParameter::Collection cppParameters {{ }, { "size_t", "objCount", "1" }, { }, { "const Obj*", "pObjs", "nullptr" }};
        CHECK(to_string(cppParameters, Declaration) == "size_t objCount = 1, const Obj* pObjs = nullptr");
        CHECK(to_string(cppParameters, Definition) == "size_t objCount, const Obj* pObjs");
        CHECK(to_string(cppParameters, Inline | Definition) == to_string(cppParameters, Declaration));
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
