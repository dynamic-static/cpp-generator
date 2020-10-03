
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/source-region.hpp"

#include "catch2/catch.hpp"

#include <string>

namespace dst {
namespace cppgen {
namespace tests {

TEST_CASE("TODO 0", "[SourceRegion]")
{
    std::string source = R"(
        $<REGION>
        $</>
    )";
    SourceRegion region(source);
    CHECK(region.get_key().empty());
    CHECK(region.get_begin_index() == 0);
    CHECK(region.get_end_index() == source.size());
    CHECK(region.get_errors().empty());
    REQUIRE(region.get_source_elements().size() == 1);
    auto pElement = region.get_source_elements()[0].get();
    {
        REQUIRE(pElement);
        CHECK(pElement->get_key() == "REGION");
        CHECK(pElement->get_begin_index() == source.find_first_of('$'));
        CHECK(pElement->get_end_index() == source.find_last_of('>') + 1);
        CHECK(pElement->get_errors().empty());
    }
}

TEST_CASE("TODO 1", "[SourceRegion]")
{
    std::string source = R"(
        $<REGION>
            ${TAG}
            $<SUB_REGION>
            ${TAG}
            $</>
        $</>
    )";
    SourceRegion region(source);
    CHECK(region.get_key().empty());
    CHECK(region.get_begin_index() == 0);
    CHECK(region.get_end_index() == source.size());
    CHECK(region.get_errors().empty());
    REQUIRE(region.get_source_elements().size() == 1);
    auto pElement = region.get_source_elements()[0].get();
    {
        REQUIRE(pElement);
        CHECK(pElement->get_key() == "REGION");
        CHECK(pElement->get_begin_index() == source.find_first_of('$'));
        CHECK(pElement->get_end_index() == source.find_last_of('>') + 1);
        CHECK(pElement->get_errors().empty());
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
