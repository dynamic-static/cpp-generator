
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
#include "dynamic_static/cpp-generator/defines.hpp"

#include <iosfwd>
#include <string_view>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppDeclaration final
    : public CppStringElement
{
public:
    class Collection;
    using CppStringElement::CppStringElement;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
class CppDeclaration::Collection final
    : public CppElement::Collection<CppDeclaration>
{
public:
    using CppElement::Collection<CppDeclaration>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
using CppDeclarations = CppDeclaration::Collection;

} // namespace cppgen
} // namespace dst
