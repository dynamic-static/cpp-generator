
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-switch.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppSwitch", "[CppSwitch]")
{
    CppSwitch cppSwitch;
    CHECK(to_string(cppSwitch) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppSwitch with CppCases", "[CppSwitch]")
{
    CppSwitch cppSwitch {
        "widget.type",
        CppCases {
            {
                CppCompileGuards {
                    "DYNAMIC_STATIC_FOO_ENABLED"
                },
                "Foo",
                CppSourceBlock {
                    "// CppSourceBlock"
                }, Break
            },
            {
                CppCompileGuards {
                    "DYNAMIC_STATIC_PLATFORM",
                    "DYNAMIC_STATIC_BAR_ENABLED",
                },
                "Bar",
                CppSourceBlock {
                    "// CppSourceBlock"
                }, Break
            },
            {
                "Baz",
                CppSourceBlock {
                    "// CppSourceBlock"
                }, Break
            },
            {
                Default,
                CppSourceBlock {
                    "assert(false);"
                }
            },
        }
    };
    CHECK(to_string(cppSwitch) ==
R"(switch (widget.type) {
#ifdef DYNAMIC_STATIC_FOO_ENABLED
case Foo: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_FOO_ENABLED
#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_BAR_ENABLED
case Bar: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_BAR_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
case Baz: {
    // CppSourceBlock
} break;
default: {
    assert(false);
}
}
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppSwitch with CppCases and CppCompileGuards", "[CppSwitch]")
{
    CppSwitch cppSwitch {
        CppCompileGuards {
            "DYNAMIC_STATIC_WIDGETS_ENABLED",
        },
        "widget.type",
        CppCases {
            {
                CppCompileGuards {
                    "DYNAMIC_STATIC_FOO_ENABLED"
                },
                "Foo",
                CppSourceBlock {
                    "// CppSourceBlock"
                }, Break
            },
            {
                CppCompileGuards {
                    "DYNAMIC_STATIC_PLATFORM",
                    "DYNAMIC_STATIC_BAR_ENABLED",
                },
                "Bar",
                CppSourceBlock {
                    "// CppSourceBlock"
                }, Break
            },
            {
                "Baz",
                CppSourceBlock {
                    "// CppSourceBlock"
                }, Break
            },
            {
                Default,
                CppSourceBlock {
                    "assert(false);"
                }
            },
        }
    };
    CHECK(to_string(cppSwitch) ==
R"(#ifdef DYNAMIC_STATIC_WIDGETS_ENABLED
switch (widget.type) {
#ifdef DYNAMIC_STATIC_FOO_ENABLED
case Foo: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_FOO_ENABLED
#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_BAR_ENABLED
case Bar: {
    // CppSourceBlock
} break;
#endif // DYNAMIC_STATIC_BAR_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
case Baz: {
    // CppSourceBlock
} break;
default: {
    assert(false);
}
}
#endif // DYNAMIC_STATIC_WIDGETS_ENABLED
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
