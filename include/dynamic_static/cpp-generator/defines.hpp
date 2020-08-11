
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
#include <sstream>

#define dst_cppgen_assert(EXPRESSION) \
assert(EXPRESSION && "dynamic_static.cpp-generator maintenance required")

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
enum FlagBits
{
    Inline         = 1,
    Declaration    = Inline,  //!< TODO : Documentation
    Definition     = 1 << 1,  //!< TODO : Documentation
    Static         = 1 << 2,  //!< TODO : Documentation
    Extern         = 1 << 3,  //!< TODO : Documentation
    Const          = 1 << 4,  //!< TODO : Documentation
    Virtual        = 1 << 5,  //!< TODO : Documentation
    Abstract       = 1 << 6,  //!< TODO : Documentation
    Override       = 1 << 7,  //!< TODO : Documentation
    Final          = 1 << 8,  //!< TODO : Documentation
    Default        = 1 << 9,  //!< TODO : Documentation
    Delete         = 1 << 10, //!< TODO : Documentation
    Typedef        = 1 << 11, //!< TODO : Documentation
    Specialization = 1 << 12, //!< TODO : Documentation
};

/**
TODO : Documentation
*/
using Flags = uint32_t;

/**
TODO : Documentation
*/
enum AccessModifier
{
    Unspecified, //!< TODO : Documentation
    Public,      //!< TODO : Documentation
    Protected,   //!< TODO : Documentation
    Private,     //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class IGeneratable
{
public:
    /**
    TODO : Documentation
    */
    virtual void generate(std::ostream& strm, Flags flags) const = 0;
};

/**
TODO : Documentation
*/
inline std::string to_string(const IGeneratable& generatable, Flags flags)
{
    std::stringstream strStrm;
    generatable.generate(strStrm, flags);
    return strStrm.str();
}

} // namespace cppgen
} // namespace dst
