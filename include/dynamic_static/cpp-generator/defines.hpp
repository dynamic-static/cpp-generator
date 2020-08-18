
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

/**
TODO : Documentation
*/
enum CppGenerationFlagBits
{
    Declaration     = 1,      //!< TODO : Documentation
    Definition      = 1 << 1, //!< TODO : Documentation
    Specialization  = 1 << 2, //!< TODO : Documentation
    Open            = 1 << 3, //!< TODO : Documentation
    Close           = 1 << 4, //!< TODO : Documentation
};

/**
TODO : Documentation
*/
using CppGenerationFlags = uint32_t;

/**
TODO : Documentation
*/
enum CppFlagBits
{
    Static   = 1,       //!< TODO : Documentation
    Extern   = 1 << 1,  //!< TODO : Documentation
    Virtual  = 1 << 2,  //!< TODO : Documentation
    Const    = 1 << 3,  //!< TODO : Documentation
    Abstract = 1 << 4,  //!< TODO : Documentation
    Override = 1 << 5,  //!< TODO : Documentation
    Final    = 1 << 6,  //!< TODO : Documentation
    Default  = 1 << 7,  //!< TODO : Documentation
    Delete   = 1 << 8,  //!< TODO : Documentation
    Friend   = 1 << 9,  //!< TODO : Documentation
    Typedef  = 1 << 10, //!< TODO : Documentation
    Class    = 1 << 11, //!< TODO : Documentation
    Struct   = 1 << 12, //!< TODO : Documentation
    Break    = 1 << 13, //!< TODO : Documentation
};

/**
TODO : Documentation
*/
using CppFlags = uint32_t;

/**
TODO : Documentation
*/
enum CppAccessSpecifier
{
    Unspecified, //!< TODO : Documentation
    Public,      //!< TODO : Documentation
    Protected,   //!< TODO : Documentation
    Private,     //!< TODO : Documentation
};

constexpr int VersionMajor { DYNAMIC_STATIC_CPP_GENERATOR_VERSION_MAJOR }; /*!< dynamic_static.cpp-generator major version */
constexpr int VersionMinor { DYNAMIC_STATIC_CPP_GENERATOR_VERSION_MINOR }; /*!< dynamic_static.cpp-generator minor version */
constexpr int VersionPatch { DYNAMIC_STATIC_CPP_GENERATOR_VERSION_PATCH }; /*!< dynamic_static.cpp-generator patch version */

} // namespace cppgen
} // namespace dst
