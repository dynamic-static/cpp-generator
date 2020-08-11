
#include "dynamic_static/cpp-generator/cpp-source-tag.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("dst::cppgen::CppSourceTag TODO 0", "[TODO]")
{
    SECTION("TODO")
    {
        std::string cppSource = "${TAG}";
        CppSourceTag tag(cppSource, cppSource.find('$'));
        CHECK(tag.get_type() == CppSourceTag::Type::Invidual);
        CHECK(tag.str(cppSource) == "${TAG}");
    }
    SECTION("TODO")
    {
        std::string cppSource = "$<TAG>";
        CppSourceTag tag(cppSource, cppSource.find('$'));
        CHECK(tag.get_type() == CppSourceTag::Type::RegionBegin);
        CHECK(tag.str(cppSource) == "$<TAG>");
    }
    SECTION("TODO")
    {
        std::string cppSource = "$</TAG>";
        CppSourceTag tag(cppSource, cppSource.find('$'));
        CHECK(tag.get_type() == CppSourceTag::Type::RegionEnd);
        CHECK(tag.str(cppSource) == "$</TAG>");
    }
    SECTION("TODO")
    {
        std::string cppSource = "$</>";
        CppSourceTag tag(cppSource, cppSource.find('$'));
        CHECK(tag.get_type() == CppSourceTag::Type::RegionEnd);
        CHECK(tag.str(cppSource) == "$</>");
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
