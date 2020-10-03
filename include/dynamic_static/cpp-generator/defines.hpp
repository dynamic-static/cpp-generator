
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

#define dst_cppgen_assert(EXPRESSION) \
assert(EXPRESSION && "dynamic_static.cpp-generator maintenance required")

#define DYNAMIC_STATIC_CPP_GENERATOR_VERSION_MAJOR 0
#define DYNAMIC_STATIC_CPP_GENERATOR_VERSION_MINOR 1
#define DYNAMIC_STATIC_CPP_GENERATOR_VERSION_PATCH 0

namespace dst {
namespace cppgen {

constexpr int VersionMajor { DYNAMIC_STATIC_CPP_GENERATOR_VERSION_MAJOR };
constexpr int VersionMinor { DYNAMIC_STATIC_CPP_GENERATOR_VERSION_MINOR };
constexpr int VersionPatch { DYNAMIC_STATIC_CPP_GENERATOR_VERSION_PATCH };

} // namespace cppgen
} // namespace dst
