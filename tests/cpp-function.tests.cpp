
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
static std::string to_padded_string(
    const CppFunction& cppFunction,
    CppGenerationFlags cppGenerationFlags,
    std::string_view cppEnclosingType
)
{
    auto str = to_string(cppFunction, cppGenerationFlags, cppEnclosingType);
    return !str.empty() ? "\n\n" + str + '\n' : str;
}

/**
TODO : Documentation
*/
static void validate_cpp_function(
    const CppFunction& cppFunction,
    std::string_view cppEnclosingType,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    CHECK(to_padded_string(cppFunction, Declaration, cppEnclosingType) == expectedDeclaration);
    CHECK(to_padded_string(cppFunction, Definition, cppEnclosingType) == expectedDefinition);
    CHECK(to_padded_string(cppFunction, Declaration | Definition, cppEnclosingType) == expectedInlineDefinition);
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
static void validate_cpp_function(
    const CppFunction& cppFunction,
    std::string_view expectedDeclaration,
    std::string_view expectedDefinition,
    std::string_view expectedInlineDefinition
)
{
    validate_cpp_function(cppFunction, { }, expectedDeclaration, expectedDefinition, expectedInlineDefinition);
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

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with single CppParameter", "[CppFunction]")
{
    CppFunction cppFunction(
        "void", "update", CppParameter { "const Widget*", "pWidget", "nullptr" },
        CppSourceBlock {R"(
            if (pWidget) {
                process(*pWidget);
            }
        )"}
    );
    validate_cpp_function(cppFunction,
R"(

void update(const Widget* pWidget = nullptr);

)",
R"(

void update(const Widget* pWidget)
{
    if (pWidget) {
        process(*pWidget);
    }
}

)",
R"(

inline void update(const Widget* pWidget = nullptr)
{
    if (pWidget) {
        process(*pWidget);
    }
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with multiple CppParameters", "[CppFunction]")
{
    CppFunction cppFunction(
        "void", "update", CppParameters {{ "size_t", "widgetCount", "0" }, { "const Widget*", "pWidgets", "nullptr" }},
        CppSourceBlock { R"(
            if (widgetCount && pWidgets) {
                for (size_t i = 0; i < widgetCount; ++i) {
                    process(pWidgets[i]);
                }
            }
        )" }
    );
    validate_cpp_function(cppFunction,
        R"(

void update(size_t widgetCount = 0, const Widget* pWidgets = nullptr);

)",
R"(

void update(size_t widgetCount, const Widget* pWidgets)
{
    if (widgetCount && pWidgets) {
        for (size_t i = 0; i < widgetCount; ++i) {
            process(pWidgets[i]);
        }
    }
}

)",
R"(

inline void update(size_t widgetCount = 0, const Widget* pWidgets = nullptr)
{
    if (widgetCount && pWidgets) {
        for (size_t i = 0; i < widgetCount; ++i) {
            process(pWidgets[i]);
        }
    }
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with CppTemplate", "[CppFunction]")
{
    CppFunction cppFunction(
        CppTemplate { CppParameters {{ "typename", "WidgetType" }}},
        "void", "update", CppParameters {{ "const WidgetType&", "widget" }}
    );
    validate_cpp_function(cppFunction,
R"(

template <typename WidgetType>
inline void update(const WidgetType& widget)
{
}

)",
{ },
R"(

template <typename WidgetType>
inline void update(const WidgetType& widget)
{
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with CppTemplate and CppCompileGuard", "[CppFunction]")
{
    CppFunction cppFunction(
        CppCompileGuard { "DYNAMIC_STATIC_FEATURE_ENABLED" },
        CppTemplate { CppParameters {{ "typename", "WidgetType" }}},
        "void", "update", CppParameters {{ "const WidgetType&", "widget" }}
    );
    validate_cpp_function(cppFunction,
R"(

#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
template <typename WidgetType>
inline void update(const WidgetType& widget)
{
}
#endif // DYNAMIC_STATIC_FEATURE_ENABLED

)",
{ },
R"(

#ifdef DYNAMIC_STATIC_FEATURE_ENABLED
template <typename WidgetType>
inline void update(const WidgetType& widget)
{
}
#endif // DYNAMIC_STATIC_FEATURE_ENABLED

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with CppTemplate specialization", "[CppFunction]")
{
    CppFunction cppFunction(
        CppTemplate { CppSpecialization { "Widget" }},
        "void", "update", CppParameters {{ "const Widget&", "widget" }}
    );
    validate_cpp_function(cppFunction,
R"(

template <>
void update<Widget>(const Widget& widget);

)",
R"(

template <>
void update<Widget>(const Widget& widget)
{
}

)",
R"(

template <>
inline void update<Widget>(const Widget& widget)
{
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction with CppTemplate partial specialization", "[CppFunction]")
{
    CppFunction cppFunction(
        CppTemplate { CppParameter { "size_t", "Count", "4" }, CppSpecialization { "Widget" } },
        "void", "update", CppParameters {{ "const std::array<Widget, Count>&", "widgets" }}
    );
    validate_cpp_function(cppFunction,
R"(

template <size_t Count = 4>
inline void update<Widget>(const std::array<Widget, Count>& widgets)
{
}

)",
{ },
R"(

template <size_t Count = 4>
inline void update<Widget>(const std::array<Widget, Count>& widgets)
{
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction member", "[CppFunction]")
{
    CppFunction cppFunction(
        "void", "update", Override | Final
    );
    validate_cpp_function(cppFunction, "Widget",
R"(

void update() override final;

)",
R"(

void Widget::update()
{
}

)",
R"(

void Widget::update() override final
{
}

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction abstract member", "[CppFunction]")
{
    CppFunction cppFunction(
        Virtual, "void", "update", Abstract
    );
    validate_cpp_function(cppFunction, "Widget",
R"(

virtual void update() = 0;

)",
R"(

void Widget::update()
{
}

)",
R"(

virtual void Widget::update() = 0;

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction default member", "[CppFunction]")
{
    CppFunction cppFunction(
        Virtual, "void", "update", Abstract
    );
    validate_cpp_function(cppFunction, "Widget",
R"(

virtual void update() = 0;

)",
R"(

void Widget::update()
{
}

)",
R"(

virtual void Widget::update() = 0;

)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppFunction::Collection", "[CppFunction::Collection]")
{
}

} // namespace tests
} // namespace cppgen
} // namespace dst
