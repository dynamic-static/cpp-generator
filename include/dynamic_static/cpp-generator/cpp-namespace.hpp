
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
class CppNamespace final
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
class CppNamespace::Collection final
    : public CppElement::Collection<CppNamespace>
{
public:
    using CppElement::Collection<CppNamespace>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

} // namespace cppgen
} // namespace dst
