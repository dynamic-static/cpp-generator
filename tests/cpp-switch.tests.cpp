
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-switch.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppSwitch", "[CppSwitch]")
{
    CppSwitch cppSwitch;
    CHECK(to_string(cppSwitch, Declaration) == std::string());
}

} // namespace tests
} // namespace cppgen
} // namespace dst
