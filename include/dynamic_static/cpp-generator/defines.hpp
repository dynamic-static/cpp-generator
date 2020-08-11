
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

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
enum CppGenerationFlagBits
{
    Declaration      = 1,                        //!< TODO : Documentation
    Definition       = 1 << 1,                   //!< TODO : Documentation
    InlineDefinition = Declaration | Definition, //!< TODO : Documentation
};

/**
TODO : Documentation
*/
using CppGenerationFlags = uint32_t;

} // namespace cppgen
} // namespace dst
