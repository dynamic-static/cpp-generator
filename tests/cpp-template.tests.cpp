
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-template.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
static void validate_cpp_template(
    const CppTemplate& cppTemplate,
    std::string_view expectedTemplateDeclaration,
    std::string_view expectedSpecializationDeclaration
)
{
    CHECK(to_string(cppTemplate, Declaration) == expectedTemplateDeclaration);
    CHECK(to_string(cppTemplate, Declaration | Definition) == expectedTemplateDeclaration);
    CHECK(to_string(cppTemplate, Specialization | Declaration) == expectedSpecializationDeclaration);
    CHECK(to_string(cppTemplate, Specialization | Declaration | Definition) == expectedSpecializationDeclaration);
    if (!cppTemplate.cppParameters.empty()) {
        CHECK(to_string(cppTemplate, Definition) == std::string());
        CHECK(to_string(cppTemplate, Specialization | Definition) == std::string());
    } else {
        if (!cppTemplate.cppSpecializations.empty()) {
            CHECK(to_string(cppTemplate, Definition) == "template <>\n");
        } else {
            CHECK(to_string(cppTemplate, Definition) == std::string());
        }
        CHECK(to_string(cppTemplate, Specialization | Definition) == expectedSpecializationDeclaration);
    }
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppTemplate", "[CppTemplate]")
{
    CppTemplate cppTemplate;
    validate_cpp_template(cppTemplate, { }, { });
}

/**
TODO : Documentation
*/
TEST_CASE("CppTemplate single CppParameter", "[CppTemplate]")
{
    CppTemplate cppTemplate {
        CppParameters {{ "typename", "T" }}
    };
    validate_cpp_template(cppTemplate, "template <typename T>\n", { });
}

/**
TODO : Documentation
*/
TEST_CASE("CppTemplate multiple CppParameters", "[CppTemplate]")
{
    CppTemplate cppTemplate {
        CppParameters {{ "typename", "T" }, { "size_t", "Count", "4" }}
    };
    validate_cpp_template(cppTemplate, "template <typename T, size_t Count = 4>\n", { });
}

/**
TODO : Documentation
*/
TEST_CASE("CppTemplate specialization", "[CppTemplate]")
{
    CppTemplate cppTemplate {
        CppSpecializations { "Widget", "8" },
    };
    validate_cpp_template(cppTemplate, "template <>\n", "<Widget, 8>");
}

/**
TODO : Documentation
*/
TEST_CASE("CppTemplate partial specialization", "[CppTemplate]")
{
    CppTemplate cppTemplate {
        CppParameters {{ "size_t", "Count" }},
        CppSpecializations { "Widget" },
    };
    validate_cpp_template(cppTemplate, "template <size_t Count>\n", "<Widget>");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
