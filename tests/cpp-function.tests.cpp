
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-function.hpp"

#include "catch.hpp"

#include <fstream>

#define WRITE_FUNCTIONS                                                               \
std::ofstream("CppFunction.hpp") << to_string(cppFunction, Declaration);              \
std::ofstream("CppFunction.cpp") << to_string(cppFunction, Definition);               \
std::ofstream("CppFunction.inl") << to_string(cppFunction, Declaration | Definition);

namespace dst {
namespace cppgen {
namespace tests {

static bool sWriteCppFunctionFiles;

/**
TODO : Documentation
*/
static void validate_cpp_function(
    const CppFunction& cppFunction,
    CppGenerationFlags cppGenerationFlags,
    std::string_view expected
)
{
    auto actual = to_string(cppFunction, cppGenerationFlags);
    if (!expected.empty()) {
        actual = "\n\n" + actual + '\n';
    }
    CHECK(actual == expected);
}

/**
TODO : Documentation
*/
static void validate_cpp_function(
    const CppFunction& cppFunction,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    validate_cpp_function(cppFunction, Declaration, expectedDeclaration);
    validate_cpp_function(cppFunction, Definition, expectedDefinition);
    validate_cpp_function(cppFunction, Declaration | Definition, expectedInlineDefinition);
    if (sWriteCppFunctionFiles) {
        sWriteCppFunctionFiles = false;
        std::ofstream("CppFunction.hpp") << "\n" << to_string(cppFunction, Declaration);
        std::ofstream("CppFunction.cpp") << "\n" << to_string(cppFunction, Definition);
        std::ofstream("CppFunction.inl") << "\n" << to_string(cppFunction, Declaration | Definition);
    }
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppFunction", "[CppFunction]")
{
    CppFunction cppFunction;
    validate_cpp_function(cppFunction, { }, { }, { });
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction", "[CppFunction]")
{
    CppFunction cppFunction(
        "void", "update",
        CppSourceBlock {
            "// CppSourceBlock"
        }
    );
    validate_cpp_function(cppFunction,
R"(

void update();

)",
R"(

void update()
{
    // CppSourceBlock
}

)",
R"(

inline void update()
{
    // CppSourceBlock
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with CppCompileGuards", "[CppFunction]")
{
    CppFunction cppFunction(
        CppCompileGuards {
            "DYNAMIC_STATIC_PLATFORM",
            "DYNAMIC_STATIC_FEATURE_ENABLED",
        },
        "void", "update",
        CppSourceBlock {
            "// CppSourceBlock"
        }
    );
    sWriteCppFunctionFiles = true;
    validate_cpp_function(cppFunction,
        R"(

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
void update();
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

)",
R"(

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
void update()
{
    // CppSourceBlock
}
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

)",
R"(

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
inline void update()
{
    // CppSourceBlock
}
#endif // DYNAMIC_STATIC_FEATURE_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

)");
}

#if 0
/**
TODO : Documentation
*/
TEST_CASE("CppFunction with CppTemplate", "[CppFunction]")
{
    CppFunction cppFunction(
        CppTemplate {{ "WidgetType" }},
        "void", "update", CppParameters { "const WidgetType&", "widget" },
        CppSourceBlock {
            "// CppSourceBlock"
        }
    );
    validate_cpp_function(cppFunction,
R"(

void update();

)",
R"(

void update()
{
    // CppSourceBlock
}

)",
R"(

inline void update()
{
    // CppSourceBlock
}

)");
}
#endif

/**
TODO : Documentation
*/
TEST_CASE("CppFunction::Collection", "[CppFunction::Collection]")
{
}

} // namespace tests
} // namespace cppgen
} // namespace dst
