
#include "dynamic_static/cpp-generator/cpp-source-block.hpp"

#include "catch.hpp"

#include <array>
#include <string>
#include <vector>

#include "dynamic_static/cpp-generator/ascii-grid.hpp"
#include <fstream>
#include <iostream>

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
    std::vector<std::string> baseTypes;
    std::vector<std::string> usingStatements;
    std::vector<Variable> variables;
    std::vector<std::string> scale;
};

/**
TODO : Documentation
*/
TEST_CASE("dst::cppgen::CppSourceBlock TODO 0", "[CppSourceBlock]")
{
    std::vector<Structure> structures {
        {
            "Foo",
            {
                "BasicWidget<Foo>"
            },
            {
                "using Flags = uint32_t;",
                "using Pool = std::vector<Foo, WidgetAllocator<Foo>>;"
            },
            {
                { "size_t", "dataSize", "0" },
                { "const uint8_t*", "pData", "nullptr" },
                { "std::vector<Controllers>", "controllers" },
            },
            {
                "1.0f", "1.0f", "1.0f"
            }
        },
        {
            "Bar",
            {
                "BasicWidget<Bar>"
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
                "BasicWidget<Baz>"
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
                { "std::vector<Controllers>", "controllers" },
            },
            {
                "1.25f", "1.5f", "1.75f"
            }
        },
    };
    auto cppSource = R"(
    $<STRUCTURES>
    struct ${NAME} final : $<BASE_TYPES>${BASE_TYPE}$</s = ", ">
    {
        using Flags = uint32_t;
        using Storage = std::vector<${NAME}, WidgetAllocator<${NAME}>>;

        Flags flags { 0 };
        $<VARIABLES>
        ${TYPE} ${NAME} ${l = "{ " : VALUE : f = " }"};
        $</>
        std::vector<float> scale { $<SCALE>${VALUE}$</s = ", "> };
    };
    $</s = "\n">
    )";
    std::ofstream("ascii-chart.txt") << dst::get_debug_view(cppSource);
    CppSourceBlock cppSourceBlock(
        cppSource, {
        {
            "STRUCTURES", structures,
            CppSourceBlockLogic(const Structure& structure)
            {
                return {
                    { "NAME", structure.name },
                    {
                        "BASE_TYPES", structure.baseTypes,
                        CppSourceBlockLogic(const std::string& baseType)
                        {
                            return {{ "BASE_TYPE", baseType }};
                        }
                    },
                    {
                        "VARIABLES", structure.variables,
                        CppSourceBlockLogic(const Variable& variable)
                        {
                            return {
                                { "TYPE", variable.type },
                                { "NAME", variable.name },
                                { "VALUE", variable.value },
                            };
                        }
                    },
                    {
                        "SCALE", structure.scale,
                        CppSourceBlockLogic(const std::string& value)
                        {
                            return {{ "VALUE", value }};
                        }
                    }
                };
            }
        }
    });
    std::ofstream("cppSourceBlock1.txt") << cppSourceBlock;
}

} // namespace tests
} // namespace cppgen
} // namespace dst

#if 0
void copy(const ${NAME}& other)
{
    $<VARIABLES>
    ${
            
    ```
    size_t length = other.${NAME} ? strlen(other.${NAME}) : 0;
    ${NAME} = length ? new char[length] : nullptr;
    memcpy(${NAME}, other.${NAME}, length + 1);
    ```:
    ```
            
    ```
    }
    $</>
}
#endif
