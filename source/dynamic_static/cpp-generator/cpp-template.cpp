
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-template.hpp"

#include <ostream>
#include <sstream>

namespace dst {
namespace cppgen {

void CppTemplate::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if ((!cppParameters.empty() || !cppSpecializations.empty()) &&
        (cppGenerationFlags & Declaration || cppGenerationFlags & Definition && cppParameters.empty())) {
        if (!(cppGenerationFlags & Specialization)) {
            strm << "template <"; cppParameters.generate(strm, cppGenerationFlags); strm << ">\n";
        } else
        if (cppGenerationFlags & Declaration || cppParameters.empty()) {
            size_t count = 0;
            for (const auto& cppSpecialization : cppSpecializations) {
                if (!cppSpecialization.empty()) {
                    strm << (!count++ ? "<" : ", ") << cppSpecialization;
                }
            }
            if (count) {
                strm << '>';
            }
        }
    }
}

} // namespace cppgen
} // namespace dst
