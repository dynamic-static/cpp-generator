
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-enum.hpp"

#include "catch.hpp"

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Empty CppEnum", "[CppEnum]")
{
    CppEnum cppEnum;
    CHECK(to_string(cppEnum, Declaration) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum without CppEnumerators", "[CppEnum]")
{
    CppEnum cppEnum {
        "WidgetType"
    };
    CHECK(to_string(cppEnum, Declaration) ==
R"(enum WidgetType
{
};
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum with CppEnumerators", "[CppEnum]")
{
    CppEnum cppEnum;
    SECTION("TODO")
    {
        cppEnum = {
            "WidgetType",
            CppEnumerators {
                { "Foo", "1" },
                { "Bar", "2" },
                { "Baz", "3" },
            }
        };
    }
    SECTION("TODO")
    {
        cppEnum = {
            "WidgetType",
            CppEnumerators {
                { "Foo", "1" },
                { "Bar", "2" },
            },
            CppEnumerator {
                "Baz", "3"
            },
        };
    }
    CHECK(to_string(cppEnum, Declaration) ==
R"(enum WidgetType
{
    Foo = 1,
    Bar = 2,
    Baz = 3,
};
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum with CppEnumerators with CppCompileGuards", "[CppEnum]")
{
    CppEnum cppEnum;
    SECTION("TODO")
    {
        cppEnum = {
            "WidgetType",
            CppEnumerators {
                {
                    CppCompileGuards { "DYNAMIC_STATIC_FOO_ENABLED" },
                    "Foo", "1"
                },
                {
                    "Bar", "2"
                },
                {
                    CppCompileGuards {
                        "DYNAMIC_STATIC_PLATFORM",
                        "DYNAMIC_STATIC_BAZ_ENABLED",
                    },
                    "Baz", "3"
                },
            }
        };
    }
    SECTION("TODO")
    {
        cppEnum = {
            "WidgetType",
            CppEnumerator {
                CppCompileGuards { "DYNAMIC_STATIC_FOO_ENABLED" },
                "Foo", "1"
            },
            CppEnumerators {
                {
                    "Bar", "2"
                },
                {
                    CppCompileGuards {
                        "DYNAMIC_STATIC_PLATFORM",
                        "DYNAMIC_STATIC_BAZ_ENABLED",
                    },
                    "Baz", "3"
                },
            },
        };
    }
    CHECK(to_string(cppEnum, Declaration) ==
R"(enum WidgetType
{
    #ifdef DYNAMIC_STATIC_FOO_ENABLED
    Foo = 1,
    #endif // DYNAMIC_STATIC_FOO_ENABLED
    Bar = 2,
    #ifdef DYNAMIC_STATIC_PLATFORM
    #ifdef DYNAMIC_STATIC_BAZ_ENABLED
    Baz = 3,
    #endif // DYNAMIC_STATIC_BAZ_ENABLED
    #endif // DYNAMIC_STATIC_PLATFORM
};
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum with CppCompileGuards", "[CppEnum]")
{
    CppEnum cppEnum;
    SECTION("TODO")
    {
        cppEnum = {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_WIDGETS_ENABLED",
            },
            "WidgetType",
            CppEnumerators {
                { "Foo", "1" },
                { "Bar", "2" },
                { "Baz", "3" },
            }
        };
    }
    CHECK(to_string(cppEnum, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_WIDGETS_ENABLED
enum WidgetType
{
    Foo = 1,
    Bar = 2,
    Baz = 3,
};
#endif // DYNAMIC_STATIC_WIDGETS_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum typedef", "[CppEnum]")
{
    CppEnum cppEnum;
    SECTION("TODO")
    {
        cppEnum = {
            Typedef, "WidgetType",
            CppEnumerators {
                { "Foo", "1" },
                { "Bar", "2" },
                { "Baz", "3" },
            }
        };
    }
    CHECK(to_string(cppEnum, Declaration) ==
R"(typedef enum WidgetType
{
    Foo = 1,
    Bar = 2,
    Baz = 3,
} WidgetType;
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum class with base type", "[CppEnum]")
{
    CppEnum cppEnum;
    SECTION("TODO")
    {
        cppEnum = {
            "WidgetType", Class, "uint32_t",
            CppEnumerators {
                { "Foo", "1" },
                { "Bar", "2" },
                { "Baz", "3" },
            }
        };
    }
    CHECK(to_string(cppEnum, Declaration) ==
R"(enum class WidgetType : uint32_t
{
    Foo = 1,
    Bar = 2,
    Baz = 3,
};
)");
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppEnum::Collection", "[CppEnum]")
{
    CppEnum::Collection cppEnums;
    CHECK(to_string(cppEnums, Declaration) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum::Collection single CppEnum", "[CppEnum]")
{
    CppEnum::Collection cppEnums {
        {
            "e0",
            CppEnumerators {
                { "v0", "0" },
                { "v1", "1" },
                { "v2", "2" },
            }
        }
    };
    CHECK(to_string(cppEnums, Declaration) ==
R"(enum e0
{
    v0 = 0,
    v1 = 1,
    v2 = 2,
};
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum::Collection multiple CppEnums", "[CppEnum]")
{
    CppEnum::Collection cppEnums {
        {
            "e0",
            CppEnumerators {
                { "v0", "0" },
                { "v1", "1" },
                { "v2", "2" },
            }
        },
        {
            "e1",
            CppEnumerators {
                { "v0", "0" },
                { "v1", "1" },
                { "v2", "2" },
            }
        },
    };
    CHECK(to_string(cppEnums, Declaration) ==
R"(enum e0
{
    v0 = 0,
    v1 = 1,
    v2 = 2,
};

enum e1
{
    v0 = 0,
    v1 = 1,
    v2 = 2,
};
)");
}

/**
TODO : Documentation
*/
TEST_CASE("CppEnum::Collection multiple CppEnums with CppCompileGuards", "[CppEnum]")
{
    CppEnum::Collection cppEnums {
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_E0_ENABLED",
            },
            "e0",
            CppEnumerators {
                { "v0", "0" },
                { "v1", "1" },
                { "v2", "2" },
            }
        },
        {
            CppCompileGuards {
                "DYNAMIC_STATIC_PLATFORM",
                "DYNAMIC_STATIC_E1_ENABLED",
            },
            "e1",
            CppEnumerators {
                { "v0", "0" },
                { "v1", "1" },
                { "v2", "2" },
            }
        },
    };
    CHECK(to_string(cppEnums, Declaration) ==
R"(#ifdef DYNAMIC_STATIC_E0_ENABLED
enum e0
{
    v0 = 0,
    v1 = 1,
    v2 = 2,
};
#endif // DYNAMIC_STATIC_E0_ENABLED

#ifdef DYNAMIC_STATIC_PLATFORM
#ifdef DYNAMIC_STATIC_E1_ENABLED
enum e1
{
    v0 = 0,
    v1 = 1,
    v2 = 2,
};
#endif // DYNAMIC_STATIC_E1_ENABLED
#endif // DYNAMIC_STATIC_PLATFORM
)");
}

} // namespace tests
} // namespace cppgen
} // namespace dst
