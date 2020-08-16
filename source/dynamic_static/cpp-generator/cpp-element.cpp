
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
#include <utility>

namespace dst {
namespace cppgen {

CppElement::~CppElement()
{
    static_assert(Declaration == Inline, "TODO : Documentation");
}

std::string to_string(const CppElement& cppElement, CppFlags flags, std::string_view cppEnclosingType)
{
    std::stringstream strStrm;
    cppElement.generate(strStrm, flags, cppEnclosingType);
    return strStrm.str();
}

CppStringElement::CppStringElement(const base_type& other)
    : base_type(other)
{
}

CppStringElement::CppStringElement(const std::string_view& other)
    : base_type(other)
{
}

CppStringElement::CppStringElement(base_type&& other)
    : base_type(std::move(other))
{
}

CppStringElement& CppStringElement::operator=(const base_type& other)
{
    base_type::operator=(other);
    return *this;
}

CppStringElement& CppStringElement::operator=(const std::string_view& other)
{
    base_type::operator=(other);
    return *this;
}

CppStringElement& CppStringElement::operator=(base_type&& other)
{
    base_type::operator=(std::move(other));
    return *this;
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
