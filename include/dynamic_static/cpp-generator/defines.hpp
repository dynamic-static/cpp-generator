
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

#define dst_cppgen_assert(EXPRESSION) \
assert(EXPRESSION && "dynamic_static.cpp-generator maintenance required")

namespace dst {
namespace cppgen {

} // namespace cppgen
} // namespace dst
