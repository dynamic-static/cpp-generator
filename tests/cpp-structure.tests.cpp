
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-structure.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
static std::string to_padded_string(
    const CppStructure& cppStructure,
    CppGenerationFlags cppGenerationFlags,
    std::string_view cppEnclosingType
)
{
    auto str = to_string(cppStructure, cppGenerationFlags, cppEnclosingType);
    return !str.empty() ? "\n\n" + str + '\n' : str;
}

/**
TODO : Documentation
*/
static void validate_cpp_structure(
    const CppStructure& cppStructure,
    std::string_view cppEnclosingType,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    CHECK(to_padded_string(cppStructure, Declaration, cppEnclosingType) == expectedDeclaration);
    CHECK(to_padded_string(cppStructure, Definition, cppEnclosingType) == expectedDefinition);
    CHECK(to_padded_string(cppStructure, Declaration | Definition, cppEnclosingType) == expectedInlineDefinition);
}

/**
TODO : Documentation
*/
static void validate_cpp_structure(
    const CppStructure& cppStructure,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    validate_cpp_structure(cppStructure, { }, expectedDeclaration, expectedDefinition, expectedInlineDefinition);
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppStructure", "[CppStructure]")
{
    CppStructure cppStructure;
    validate_cpp_structure(cppStructure, { }, { }, { });
}

/**
TODO : Documentation
*/
TEST_CASE("CppStructure", "[CppStructure]")
{
    CppStructure cppStructure {
        Class, "Widget", Final,
        Public,
            CppFunction {
                "Widget", Default
            },
            CppFunction {
                "const std::string&", "get_name", Const,
                CppSourceBlock {R"(
                    return mName;
                )"}
            },
            CppFunction {
                "void", "set_name", CppParameter { "std::string_view", "name" },
                CppSourceBlock {R"(
                    mName = name;
                )"}
            },
        Private,
            3.14f
            // CppVariable { "std::string", "mName", "\"Widget\"" }
    };
    validate_cpp_structure(cppStructure,
R"(

class Widget final
{
public:
    Widget() = default;
    const std::string& get_name() const;
    void set_name(std::string_view name);

private:
    std::string mName { "Widget" };
};

)",
R"(

const std::string& Widget::get_name() const
{
    return mName;
}

void Widget::set_name(std::string_view name)
{
    mName = name;
}

)",
R"(

class Widget final
{
public:
    Widget() = default;

    inline const std::string& get_name() const
    {
        return mName;
    }

    inline void set_name(std::string_view name)
    {
        mName = name;
    }

private:
    std::string mName { "Widget" };
};

)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
