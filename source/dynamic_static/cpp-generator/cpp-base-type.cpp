
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-base-type.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

CppBaseType::CppBaseType(CppFlags cppFlags, CppAccessSpecifier cppAccessSpecifier, std::string_view cppName)
    : cppFlags { cppFlags }
    , cppAccessSpecifier { cppAccessSpecifier }
    , cppName { cppName }
{
}

CppBaseType::CppBaseType(CppAccessSpecifier cppAccessSpecifier, std::string_view cppName)
    : CppBaseType(0, cppAccessSpecifier, cppName)
{
}

void CppBaseType::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppFlags & Virtual) {
        strm << "virtual ";
    }
    switch (cppAccessSpecifier) {
    case Public: strm << "public "; break;
    case Protected: strm << "protected "; break;
    case Private: strm << "private "; break;
    default: {
    } break;
    }
    strm << cppName;
}

void CppBaseTypes::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
}

} // namespace cppgen
} // namespace dst
