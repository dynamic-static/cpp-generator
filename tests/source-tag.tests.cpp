
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/source-tag.hpp"

#include "catch2/catch.hpp"

#include <string>

namespace dst {
namespace cppgen {
namespace tests {

TEST_CASE("SourceTag ctor() Replacement empty", "[SourceTag]")
{
    std::string source = "${}";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() Replacement with key", "[SourceTag]")
{
    std::string source = "${TAG}";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "TAG");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() Replacement multiline with key", "[SourceTag]")
{
    std::string source = R"(
        ${
            TAG
        }
    )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "TAG");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionBegin empty", "[SourceTag]")
{
    std::string source = "$<>";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::RegionBegin);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionBegin with key", "[SourceTag]")
{
    std::string source = "$<TAG>";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "TAG");
    CHECK(tag.get_type() == SourceTag::Type::RegionBegin);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionEnd empty", "[SourceTag]")
{
    std::string source = "$</>";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::RegionEnd);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionEnd with key", "[SourceTag]")
{
    std::string source = "$</TAG>";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "TAG");
    CHECK(tag.get_type() == SourceTag::Type::RegionEnd);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().empty());
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionEnd with single quoted option", "[SourceTag]")
{
    std::string source = R"(  $</reverse="true">  )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::RegionEnd);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().size() == 1);
    CHECK(tag.get_option("reverse") == "true");
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() Replacement with quoted head and tail options", "[SourceTag]")
{
    std::string source = R"(    ${ "int " : TAG : " = 64;" }    )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "TAG");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().size() == 2);
    CHECK(tag.get_option("head") == "int ");
    CHECK(tag.get_option("tail") == " = 64;");
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() Replacement with backticked head and tail options", "[SourceTag]")
{
    std::string source = R"(    ${ `int ` : TAG : ` = 64;` }    )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "TAG");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().size() == 2);
    CHECK(tag.get_option("head") == "int ");
    CHECK(tag.get_option("tail") == " = 64;");
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionBegin with backticked head and seperator options", "[SourceTag]")
{
    std::string source = R"(    $<`: ` : BASE_TYPES : `\n,`>    )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "BASE_TYPES");
    CHECK(tag.get_type() == SourceTag::Type::RegionBegin);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().size() == 2);
    CHECK(tag.get_option("head") == ": ");
    CHECK(tag.get_option("seperator") == "\n,");
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionBegin multiline with backticked head and seperator options", "[SourceTag]")
{
    std::string source = R"(
        $<
                `: `
            : BASE_TYPES
                :
                    `\n,`
            >
    )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "BASE_TYPES");
    CHECK(tag.get_type() == SourceTag::Type::RegionBegin);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().size() == 2);
    CHECK(tag.get_option("head") == ": ");
    CHECK(tag.get_option("seperator") == "\n,");
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() RegionEnd with backticked tail option", "[SourceTag]")
{
    std::string source = R"(    $</`\n}`>    )";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::RegionEnd);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('>') + 1);
    CHECK(tag.get_options().size() == 1);
    CHECK(tag.get_option("tail") == "\n}");
    CHECK(tag.get_errors().empty());
}

TEST_CASE("SourceTag ctor() Replacement with mutltiple key error", "[SourceTag]")
{
    std::string source = "${ KEY_0 : KEY_1 }";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "KEY_0");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    REQUIRE(tag.get_errors().size() == 1);
    CHECK(tag.get_errors()[0] == "tag contains multiple keys [ KEY_0, KEY_1 ]; a tag may only have one key");
}

TEST_CASE("SourceTag ctor() Replacement with mutltiple multiple key errors", "[SourceTag]")
{
    std::string source = "${ KEY_0 : KEY_1 : KEY_2 }";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "KEY_0");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    REQUIRE(tag.get_errors().size() == 2);
    CHECK(tag.get_errors()[0] == "tag contains multiple keys [ KEY_0, KEY_1 ]; a tag may only have one key");
    CHECK(tag.get_errors()[1] == "tag contains multiple keys [ KEY_0, KEY_2 ]; a tag may only have one key");
}

TEST_CASE("SourceTag ctor() Replacement with mutltiple multiple option key errors", "[SourceTag]")
{
    std::string source = "${ \"head_0\" : \"head_1\" : KEY : \"tail_0\" : \"tail_1\" }";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key() == "KEY");
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    REQUIRE(tag.get_options().size() == 2);
    CHECK(tag.get_option("head") == "head_0");
    CHECK(tag.get_option("tail") == "tail_0");
    REQUIRE(tag.get_errors().size() == 2);
    CHECK(tag.get_errors()[0] == "tag contains multiple options with the same key [ head ]; option keys must be unique within a tag");
    CHECK(tag.get_errors()[1] == "tag contains multiple options with the same key [ tail ]; option keys must be unique within a tag");
}

TEST_CASE("SourceTag ctor() Replacement with invalid option key error", "[SourceTag]")
{
    std::string source = "${b@dk#y=\"value\"}";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    REQUIRE(tag.get_errors().size() == 1);
    CHECK(tag.get_errors()[0] == "option key [ b@dk#y ] contains invalid character(s); option keys may contain '_' and alphanumeric characters");
}

TEST_CASE("SourceTag ctor() Replacement with unquoted option value error", "[SourceTag]")
{
    std::string source = "${key=badvalue}";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::Replacement);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.find('}') + 1);
    CHECK(tag.get_options().empty());
    REQUIRE(tag.get_errors().size() == 1);
    CHECK(tag.get_errors()[0] == "option value [ badvalue ] must be enclosed in '\"' or '`' characters");
}

TEST_CASE("SourceTag ctor() Replacement with unmatched '{' and '}' brace error", "[SourceTag]")
{
    std::string source = "${ \"head\" : KEY : \"tail\" ";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::Invalid);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.size());
    CHECK(tag.get_options().empty());
    REQUIRE(tag.get_errors().size() == 1);
    CHECK(tag.get_errors()[0] == "tag open brace '{' encountered without matching close brace '}'; are there unmatched '\"' or '`' characters in the input source?");
}

TEST_CASE("SourceTag ctor() Replacement with unmatched '<' and '>' brace error", "[SourceTag]")
{
    std::string source = "$< \"head\" : KEY : \"tail\" ";
    SourceTag tag(source, source.find('$'));
    CHECK(tag.get_key().empty());
    CHECK(tag.get_type() == SourceTag::Type::Invalid);
    CHECK(tag.get_begin_index() == source.find('$'));
    CHECK(tag.get_end_index() == source.size());
    CHECK(tag.get_options().empty());
    REQUIRE(tag.get_errors().size() == 1);
    CHECK(tag.get_errors()[0] == "tag open brace '<' encountered without matching close brace '>'; are there unmatched '\"' or '`' characters in the input source?");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
