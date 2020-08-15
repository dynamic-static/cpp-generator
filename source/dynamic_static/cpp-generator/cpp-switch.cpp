
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-switch.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppSwitch::generate(std::ostream& strm, CppGenerationFlags, std::string_view) const
{
    if (!cppCondition.empty()) {
        cppCompileGuards.generate(strm, Open);
        strm << "switch (" << cppCondition << ") {\n";
        cppCases.generate(strm);
        strm << "}\n";
        cppCompileGuards.generate(strm, Close);
    }
}

} // namespace cppgen
} // namespace dst
