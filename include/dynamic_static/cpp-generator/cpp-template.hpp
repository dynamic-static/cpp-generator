
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-element-collection.hpp"
#include "dynamic_static/cpp-generator/cpp-parameter.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <iosfwd>
#include <string>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppTemplate final
    : public IGeneratable
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
    void generate(std::ostream& strm, Flags flags) const override final;

    CppParameter::Collection cppParameters;      //!< TODO : Documentation
    std::vector<std::string> cppSpecializations; //!< TODO : Documentation
};

} // namespace cppgen
} // namespace dst
