
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

void CppTemplate::generate(std::ostream& strm, CppFlags cppFlags) const
{
    if (flags & Declaration || flags & Definition) {
        if (flags & Specialization && !cppSpecializations.empty()) {
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
            if (flags & Declaration || flags & Definition && !cppSpecializations.empty()) {
                auto str = to_string(cppParameters, flags);
                if (!str.empty()) {
                    strm << "template <" << str << '>';
                }
            }
        }
    }
}

} // namespace cppgen
} // namespace dst
