
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

CppTemplate::CppTemplate(
    const CppParameter::Collection& cppParameters,
    const std::vector<std::string>& cppSpecializations
)
    : cppParameters { cppParameters }
    , cppSpecializations { cppSpecializations }
{
}

void CppTemplate::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Declaration | Definition) {
        if (cppGenerationFlags & Specialization && !cppSpecializations.empty()) {
            size_t count = 0;
            for (const auto& cppSpecialization : cppSpecializations) {
                if (!cppSpecialization.empty()) {
                    strm << (!count++ ? "<" : ", ") << cppSpecialization;
                }
            }
            if (count) {
                strm << '>';
            }
        } else {
            if (cppGenerationFlags & Declaration || cppGenerationFlags & Definition && !cppSpecializations.empty()) {
                auto str = to_string(cppParameters, cppGenerationFlags);
                if (!str.empty()) {
                    strm << "template <" << str << '>';
                }
            }
        }
    }
}

} // namespace cppgen
} // namespace dst
