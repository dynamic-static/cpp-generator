
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

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
static std::string to_padded_string(
    const CppFunction::Collection& cppFunctions,
    CppGenerationFlags cppGenerationFlags,
    std::string_view cppEnclosingType
)
{
    auto str = to_string(cppFunctions, cppGenerationFlags, cppEnclosingType);
    return !str.empty() ? "\n\n" + str + '\n' : str;
}

/**
TODO : Documentation
*/
static void validate_cpp_function_collection(
    const CppFunction::Collection& cppFunctions,
    std::string_view cppEnclosingType,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    CHECK(to_padded_string(cppFunctions, Declaration, cppEnclosingType) == expectedDeclaration);
    CHECK(to_padded_string(cppFunctions, Definition, cppEnclosingType) == expectedDefinition);
    CHECK(to_padded_string(cppFunctions, Declaration | Definition, cppEnclosingType) == expectedInlineDefinition);
}

/**
TODO : Documentation
*/
static void validate_cpp_function_collection(
    const CppFunction::Collection& cppFunctions,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    validate_cpp_function_collection(cppFunctions, { }, expectedDeclaration, expectedDefinition, expectedInlineDefinition);
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppFunction::Collection", "[CppFunction::Collection]")
{
    CppFunction::Collection cppFunctions;
    validate_cpp_function_collection(cppFunctions, { }, { }, { });
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction::Collection", "[CppFunction::Collection]")
{
    CppFunction::Collection cppFunctions {
        {
            "void", "fn0",
            CppSourceBlock {
                "// CppSourceBlock"
            }
        },
        {
            "void", "fn1",
            CppSourceBlock {
                "// CppSourceBlock"
            }
        },
        {
            "void", "fn2",
            CppSourceBlock {
                "// CppSourceBlock"
            }
        }
    };
    validate_cpp_function_collection(cppFunctions,
R"(

void fn0();
void fn1();
void fn2();

)",
R"(

void fn0()
{
    // CppSourceBlock
}

void fn1()
{
    // CppSourceBlock
}

void fn2()
{
    // CppSourceBlock
}

)",
R"(

inline void fn0()
{
    // CppSourceBlock
}

inline void fn1()
{
    // CppSourceBlock
}

inline void fn2()
{
    // CppSourceBlock
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction::Collection with CppCompileGuards", "[CppFunction::Collection]")
{
    CppFunction::Collection cppFunctions {
        {
            "void", "fn0",
            CppSourceBlock {
                "// CppSourceBlock"
            }
        },
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_FEATURE_FN1_ENABLED",
            },
            "void", "fn1",
            CppSourceBlock {
                "// CppSourceBlock"
            }
        },
        {
            CppCompileGuard {
                "DYNAMIC_STATIC_FEATURE_FN2_ENABLED"
            },
            "void", "fn2",
            CppSourceBlock {
                "// CppSourceBlock"
            }
        }
    };
    validate_cpp_function_collection(cppFunctions,
R"(

void fn0();
#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_FN1_ENABLED
void fn1();
#endif // DYNAMIC_STATIC_FEATURE_FN1_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_FN2_ENABLED
void fn2();
#endif // DYNAMIC_STATIC_FEATURE_FN2_ENABLED

)",
R"(

void fn0()
{
    // CppSourceBlock
}

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_FN1_ENABLED
void fn1()
{
    // CppSourceBlock
}
#endif // DYNAMIC_STATIC_FEATURE_FN1_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

#ifdef DYNAMIC_STATIC_FEATURE_FN2_ENABLED
void fn2()
{
    // CppSourceBlock
}
#endif // DYNAMIC_STATIC_FEATURE_FN2_ENABLED

)",
R"(

inline void fn0()
{
    // CppSourceBlock
}

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_FN1_ENABLED
inline void fn1()
{
    // CppSourceBlock
}
#endif // DYNAMIC_STATIC_FEATURE_FN1_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

#ifdef DYNAMIC_STATIC_FEATURE_FN2_ENABLED
inline void fn2()
{
    // CppSourceBlock
}
#endif // DYNAMIC_STATIC_FEATURE_FN2_ENABLED

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction::Collection with CppTemplates and CppCompileGuards", "[CppFunction::Collection]")
{
    CppFunction::Collection cppFunctions {
        {
            CppTemplate { CppParameters {{ "typename", "T" }}},
            "void", "fn0",
        },
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_FEATURE_FN1_ENABLED",
            },
            CppTemplate { CppParameter { "typename", "T" }},
            "void", "fn1",
        },
        {
            CppCompileGuard {
                "DYNAMIC_STATIC_FEATURE_FN2_ENABLED"
            },
            CppTemplate { CppParameter { "typename", "T" }},
            "void", "fn2",
        }
    };
    validate_cpp_function_collection(cppFunctions,
R"(

template <typename T>
void fn0()
{
}

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_FN1_ENABLED
template <typename T>
void fn1()
{
}
#endif // DYNAMIC_STATIC_FEATURE_FN1_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

#ifdef DYNAMIC_STATIC_FEATURE_FN2_ENABLED
template <typename T>
void fn2()
{
}
#endif // DYNAMIC_STATIC_FEATURE_FN2_ENABLED

)",
{ },
R"(

template <typename T>
inline void fn0()
{
}

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_FEATURE_FN1_ENABLED
template <typename T>
inline void fn1()
{
}
#endif // DYNAMIC_STATIC_FEATURE_FN1_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM

#ifdef DYNAMIC_STATIC_FEATURE_FN2_ENABLED
template <typename T>
inline void fn2()
{
}
#endif // DYNAMIC_STATIC_FEATURE_FN2_ENABLED

)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst

#if 0
/**
TODO : Documentation
*/
TEST_CASE("CppFunction::Collection", "[CppFunction::Collection]")
{
    CppFunction::Collection cppFunctions;
    validate_cpp_function_collection(cppFunctions,
        R"(
)",
R"(
)",
R"(
)");
}
#endif
