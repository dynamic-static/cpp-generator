
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-element.hpp"

#include <sstream>

namespace dst {
namespace cppgen {

std::string to_string(const CppElement& cppElement, CppFlags flags, std::string_view cppEnclosingType)
{
    std::stringstream strStrm;
    cppElement.generate(strStrm, flags, cppEnclosingType);
    return strStrm.str();
}

} // namespace cppgen
} // namespace dst
