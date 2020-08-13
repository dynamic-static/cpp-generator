
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-namespace.hpp"

#include "catch.hpp"

#include <string>
#include <string_view>

namespace dst {
namespace cppgen {
namespace tests {

/**
TODO : Documentation
*/
TEST_CASE("Anonymous CppNamespace", "[CppNamespace]")
{
    CppNamespace cppNamespace;
    CHECK(to_string(cppNamespace, Open) == "namespace {\n");
    CHECK(to_string(cppNamespace, Close) == "} // namespace\n");
}

/**
TODO : Documentation
*/
TEST_CASE("Populated CppNamespace", "[CppNamespace]")
{
    CppNamespace cppNamespace { "dst" };
    CHECK(to_string(cppNamespace, Open) == "namespace dst {\n");
    CHECK(to_string(cppNamespace, Close) == "} // namespace dst\n");
}

/**
TODO : Documentation
*/
TEST_CASE("Empty CppNamespace::Collection", "[CppNamespace::Collection]")
{
    CppNamespace::Collection cppNamespaces;
    CHECK(to_string(cppNamespaces, Open) == std::string());
    CHECK(to_string(cppNamespaces, Close) == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("CppNamespace::Collection with single CppNamespace", "[CppNamespace::Collection]")
{
    CppNamespace::Collection cppNamespaces { "dst" };
    CHECK(to_string(cppNamespaces, Open) == "namespace dst {\n");
    CHECK(to_string(cppNamespaces, Close) == "} // namespace dst\n");
}

/**
TODO : Documentation
*/
TEST_CASE("CppNamespace::Collection with multiple CppNamespaces", "[CppNamespace::Collection]")
{
    SECTION("TODO")
    {
        CppNamespace::Collection cppNamespaces {
            "dst",
            "cppgen",
        };
        CHECK(to_string(cppNamespaces, Open) ==
R"(namespace dst {
namespace cppgen {
)");
        CHECK(to_string(cppNamespaces, Close) ==
R"(} // namespace cppgen
} // namespace dst
)");
    }
    SECTION("TODO")
    {
        CppNamespace::Collection cppNamespaces {
            std::string(),
            "dst",
            { },
            std::string_view(),
            "cppgen",
            "",
        };
        CHECK(to_string(cppNamespaces, Open) ==
R"(namespace {
namespace dst {
namespace {
namespace {
namespace cppgen {
namespace {
)");
        CHECK(to_string(cppNamespaces, Close) ==
R"(} // namespace
} // namespace cppgen
} // namespace
} // namespace
} // namespace dst
} // namespace
)");
    }
    SECTION("TODO")
    {
        CppNamespace::Collection cppNamespaces {
            "ns0",
            "ns1",
            "ns2",
            "ns3",
            "ns4",
            "ns5",
        };
        CHECK(to_string(cppNamespaces, Open) ==
R"(namespace ns0 {
namespace ns1 {
namespace ns2 {
namespace ns3 {
namespace ns4 {
namespace ns5 {
)");
        CHECK(to_string(cppNamespaces, Close) ==
R"(} // namespace ns5
} // namespace ns4
} // namespace ns3
} // namespace ns2
} // namespace ns1
} // namespace ns0
)");
    }
}

} // namespace tests
} // namespace cppgen
} // namespace dst
