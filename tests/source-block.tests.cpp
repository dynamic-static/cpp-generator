
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/source-block.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <vector>

namespace dst {
namespace cppgen {
namespace tests {

class Variable final
{
public:
    std::string type;
    std::string name;
    std::string value;
};

class Structure final
{
public:
    std::string name;
    std::vector<std::string> compileGuards;
    std::vector<std::string> baseTypes;
    std::vector<std::string> usingStatements;
    std::vector<Variable> variables;
    std::vector<std::string> scale;
};

TEST_CASE("SourceBlock TODO 0", "[SourceBlock]")
{
        std::vector<Structure> structures {
        {
            "Foo",
            {
            },
            {
                "BasicWidget<Foo>",
                "IWidget",
            },
            {
                "using Flags = uint32_t;",
                "using Pool = std::vector<Foo, WidgetAllocator<Foo>>;"
            },
            {
                { "size_t", "dataSize", "0" },
                { "const uint8_t*", "pData", "nullptr" },
                { "std::vector<Controller>", "controllers" },
            },
            {
                "1.0f", "1.0f", "1.0f"
            }
        },
        {
            "Bar",
            {
                "ENABLE_BAR"
            },
            {
            },
            {
                "using Pool = std::vector<Bar, WidgetAllocator<Bar>>;"
            },
            {
                { "size_t", "fooCount", "0" },
                { "const Foo*", "pFoo", "nullptr" },
                { "size_t", "dataSize", "0" },
                { "const uint8_t*", "pData", "nullptr" },
            },
            {
                "0.25f", "0.5f", "0.75f"
            }
        },
        {
            "Baz",
            {
                "ENABLE_BAZ",
                "_WIN32"
            },
            {
                "BasicWidget<Baz>",
                "IWidget",
            },
            {
                "using Flags = uint32_t;",
                "using Pool = std::vector<Baz, WidgetAllocator<Baz>>;"
            },
            {
                { "size_t", "barCount", "0" },
                { "const Bar*", "pBars", "nullptr" },
                { "float", "min", "0.0f" },
                { "float", "max", "1.0f" },
                { "std::vector<Controller>", "controllers" },
            },
            {
                "1.25f", "1.5f", "1.75f"
            }
        },
        {
            "Qux"
        },
    };
    std::string source = R"(
    #pragma once
    #ifndef ${HEADER_GUARD}
    #define ${HEADER_GUARD}

    #include <array>
    #include <string>
    #include <vector>

    $<STRUCTURES:"\n">
    $<COMPILE_GUARDS>
    #ifdef ${COMPILE_GUARD}
    $</>
    ${DOCUMENTATION}
    class ${NAME} final
        $<":":BASE_TYPES:","> public ${BASE_TYPE}
        $</>
    {
    public:
        ${NAME}($<MEMBER_VARIABLES:", ">const ${TYPE}& ${NAME}$</reverse="true">)
            $<":":MEMBER_VARIABLES:","> ${NAME} { ${NAME} }
            $</>
        {
        }

        $<condition="GENERATE_NAME_ACCESSORS">
        const std::string& get_name() const
        {
            return mName;
        }

        void set_name(const std::string& name)
        {
            mName = name;
        }

        $</>
        Flags flags { 0 };
        $<MEMBER_VARIABLES>
        ${TYPE} ${NAME}${" { ":VALUE:" }"};
        $</>
        std::array<float, 3> scale {$<" ":SCALE:", ">${VALUE}$</" ">};
    $<condition="GENERATE_NAME_ACCESSORS">

    private:
        std::string mName { "${NAME}" };
        ${UNUSED_TAG_INSIDE_CONDITION:";"}
    $</>
        ${UNUSED_TAG_INSIDE_REGION:";"}
    };
    $<COMPILE_GUARDS:reverse="true">
    #endif // ${COMPILE_GUARD}
    $</>
    $</>

    #endif // ${HEADER_GUARD}
    )";
    SourceBlock sourceBlock(
        source, {
        SourceBlock("HEADER_GUARD", "WIDGETS_HPP"),
        SourceBlock("STRUCTURES", structures,
            [&](const Structure& structure)
            {
                return std::vector<SourceBlock> {
                    SourceBlock("DOCUMENTATION",
                        "/**\n" +
                        structure.name + " documentation\n" +
                        "*/"
                    ),
                    SourceBlock("NAME", structure.name),
                    Condition("GENERATE_NAME_ACCESSORS", structure.name == "Bar"),
                    SourceBlock("COMPILE_GUARDS", structure.compileGuards,
                        [&](const std::string& compileGuard)
                        {
                            return std::vector<SourceBlock> {
                                SourceBlock("COMPILE_GUARD", compileGuard),
                            };
                        }
                    ),
                    SourceBlock("BASE_TYPES", structure.baseTypes,
                        [&](const std::string& baseType)
                        {
                            return std::vector<SourceBlock> {
                                SourceBlock("BASE_TYPE", baseType),
                            };
                        }
                    ),
                    SourceBlock("MEMBER_VARIABLES", structure.variables,
                        [&](const Variable& variable)
                        {
                            return std::vector<SourceBlock> {
                                SourceBlock("TYPE", variable.type),
                                SourceBlock("NAME", variable.name),
                                SourceBlock("VALUE", variable.value),
                            };
                        }
                    ),
                    SourceBlock("SCALE", structure.scale,
                        [&](const std::string& value)
                        {
                            return std::vector<SourceBlock> {
                                SourceBlock("VALUE", value),
                            };
                        }
                    ),
                };
            }
        )
    });
    CHECK((std::string)sourceBlock == R"(
#pragma once
#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include <array>
#include <string>
#include <vector>

/**
Foo documentation
*/
class Foo final
    : public BasicWidget<Foo>
    , public IWidget
{
public:
    Foo(const std::vector<Controller>& controllers, const const uint8_t*& pData, const size_t& dataSize)
        : dataSize { dataSize }
        , pData { pData }
        , controllers { controllers }
    {
    }

    Flags flags { 0 };
    size_t dataSize { 0 };
    const uint8_t* pData { nullptr };
    std::vector<Controller> controllers;
    std::array<float, 3> scale { 1.0f, 1.0f, 1.0f };
};

#ifdef ENABLE_BAR
/**
Bar documentation
*/
class Bar final
{
public:
    Bar(const const uint8_t*& pData, const size_t& dataSize, const const Foo*& pFoo, const size_t& fooCount)
        : fooCount { fooCount }
        , pFoo { pFoo }
        , dataSize { dataSize }
        , pData { pData }
    {
    }

    const std::string& get_name() const
    {
        return mName;
    }

    void set_name(const std::string& name)
    {
        mName = name;
    }

    Flags flags { 0 };
    size_t fooCount { 0 };
    const Foo* pFoo { nullptr };
    size_t dataSize { 0 };
    const uint8_t* pData { nullptr };
    std::array<float, 3> scale { 0.25f, 0.5f, 0.75f };

private:
    std::string mName { "Bar" };
};
#endif // ENABLE_BAR

#ifdef ENABLE_BAZ
#ifdef _WIN32
/**
Baz documentation
*/
class Baz final
    : public BasicWidget<Baz>
    , public IWidget
{
public:
    Baz(const std::vector<Controller>& controllers, const float& max, const float& min, const const Bar*& pBars, const size_t& barCount)
        : barCount { barCount }
        , pBars { pBars }
        , min { min }
        , max { max }
        , controllers { controllers }
    {
    }

    Flags flags { 0 };
    size_t barCount { 0 };
    const Bar* pBars { nullptr };
    float min { 0.0f };
    float max { 1.0f };
    std::vector<Controller> controllers;
    std::array<float, 3> scale { 1.25f, 1.5f, 1.75f };
};
#endif // _WIN32
#endif // ENABLE_BAZ

/**
Qux documentation
*/
class Qux final
{
public:
    Qux()
    {
    }

    Flags flags { 0 };
    std::array<float, 3> scale {};
};

#endif // WIDGETS_HPP
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
