
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-case.hpp"
#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"
#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>

namespace dst {
namespace cppgen {

/**
TODO : Documetation
*/
class CppSwitch final
    : public CppElement
{
public:
    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Definition]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    std::string cppCondition;                     //!< TODO : Documentation
    CppCase::Collection cppCases;                 //!< TODO : Documentation
};

} // namespace cppgen
} // namespace dst
