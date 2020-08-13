
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
#include "dynamic_static/cpp-generator/cpp-parameter.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppTemplate final
    : public CppElement
{
public:
    /**
    TODO : Documentation
    */
    CppTemplate(
        const CppParameter::Collection& cppParameters = { },
        const std::vector<std::string>& cppSpecializations = { }
    );

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppParameter::Collection cppParameters;      //!< TODO : Documentation
    std::vector<std::string> cppSpecializations; //!< TODO : Documentation
};

} // namespace cppgen
} // namespace dst
