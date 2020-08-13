
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

CppElement::~CppElement()
{
}

std::string to_string(const CppElement& cppElement, CppFlags flags, std::string_view cppEnclosingType)
{
    std::stringstream strStrm;
    cppElement.generate(strStrm, flags, cppEnclosingType);
    return strStrm.str();
}

CppStringElement::~CppStringElement()
{
}

bool operator==(const CppStringElement& lhs, const CppStringElement& rhs)
{
    return (const std::string&)lhs == (const std::string&)rhs;
}

bool operator!=(const CppStringElement& lhs, const CppStringElement& rhs)
{
    return (const std::string&)lhs != (const std::string&)rhs;
}

bool operator<(const CppStringElement& lhs, const CppStringElement& rhs)
{
    return (const std::string&)lhs < (const std::string&)rhs;
}

bool operator>(const CppStringElement& lhs, const CppStringElement& rhs)
{
    return (const std::string&)lhs > (const std::string&)rhs;
}

bool operator<=(const CppStringElement& lhs, const CppStringElement& rhs)
{
    return (const std::string&)lhs <= (const std::string&)rhs;
}

bool operator>=(const CppStringElement& lhs, const CppStringElement& rhs)
{
    return (const std::string&)lhs >= (const std::string&)rhs;
}

std::ostream& operator<<(std::ostream& strm, const CppStringElement& cppStringElement)
{
    return strm << (const std::string&)cppStringElement;
}

} // namespace cppgen
} // namespace dst
