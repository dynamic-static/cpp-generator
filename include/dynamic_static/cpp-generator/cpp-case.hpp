
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
#include "dynamic_static/cpp-generator/cpp-source-block.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>

namespace dst {
namespace cppgen {

/**
TODO : Documetation
*/
class CppCase final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Definition]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    std::string cppLabel;                         //!< TODO : Documentation
    CppSourceBlock cppSourceBlock;                //!< TODO : Documentation
    CppFlags cppFlags { };                        //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppCase::Collection final
    : public CppElement::Collection<CppCase>
{
public:
    using CppElement::Collection<CppCase>::Collection;

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Definition]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

} // namespace cppgen
} // namespace dst
