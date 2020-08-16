
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

#include <string>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppDocumentation final
{
public:
    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags) const;

    std::string brief;              //!< TODO : Documentation
    std::vector<std::string> notes; //!< TODO : Documentation
};

} // namespace cppgen
} // namespace dst
