
#include "dynamic_static/cpp-generator/cpp-source-region.hpp"

#include "catch.hpp"

#include <fstream>

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("dst::cppgen::CppSourceRegion TODO 0", "[TODO]")
{
    SECTION("TODO")
    {
        std::string cppSource =
R"(
$<REGION>
${TAG}
$</REGION>
)";
        CppSourceTag tag(cppSource, cppSource.find('$'));
        CppSourceRegion region(cppSource, tag);
        CHECK(region.str(cppSource) ==
R"($<REGION>
${TAG}
$</REGION>)");
    }
}

/**
TODO : Documentation
*/
TEST_CASE("dst::cppgen::CppSourceRegion TODO 1", "[TODO]")
{
    SECTION("TODO")
    {
        std::string cppSource =
R"(
$<REGION>
    $<SUB_REGION_0>
        ${SUB_REGION_0_TAG_0}
        ${SUB_REGION_0_TAG_1}
    $</>
    $<SUB_REGION_1>
        ${SUB_REGION_1_TAG_0}
            $<SUB_SUB_REGION>
                ${SUB_SUB_REGION_TAG_0}
                ${SUB_SUB_REGION_TAG_1}
            $</>
        ${SUB_REGION_1_TAG_1}
    $</>
$</REGION>
)";
        CppSourceTag tag(cppSource, cppSource.find('$'));
        CppSourceRegion region(cppSource, tag);
        std::ofstream("CppSourceRegion.txt") << region.str(cppSource);
        CHECK(region.str(cppSource) ==
R"($<REGION>
$<SUB_REGION_0>
${SUB_REGION_0_TAG_0}
${SUB_REGION_0_TAG_1}
$</>
$<SUB_REGION_1>
${SUB_REGION_1_TAG_0}
$<SUB_SUB_REGION>
${SUB_SUB_REGION_TAG_0}
${SUB_SUB_REGION_TAG_1}
$</>
${SUB_REGION_1_TAG_1}
$</>
$</REGION>)");
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
