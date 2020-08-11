
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-element.hpp"

#include <sstream>

namespace dst {
namespace cppgen {

CppElement::~CppElement()
{
}

std::string CppElement::generate(CppGenerationFlags flags) const
{
    std::stringstream strStrm;
    generate(strStrm, flags);
    return strStrm.str();
}

} // namespace cppgen
} // namespace dst
