
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"
#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppEnumerator final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    std::string cppName;                          //!< TODO : Documentation
    std::string cppValue;                         //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppEnumerator::Collection final
    : public CppElement::Collection<CppEnumerator>
{
public:
    using CppElement::Collection<CppEnumerator>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

} // namespace cppgen
} // namespace dst
