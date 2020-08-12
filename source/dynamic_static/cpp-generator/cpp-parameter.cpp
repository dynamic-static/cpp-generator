
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-parameter.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

CppParameter::CppParameter(
    std::string_view cppType,
    std::string_view cppName,
    std::string_view cppValue
)
    : cppType { cppType }
    , cppName { cppName }
    , cppValue { cppValue }
{
}

void CppParameter::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Declaration | Definition) {
        if (!cppType.empty()) {
            strm << cppType;
            if (!cppName.empty()) {
                strm << ' ' << cppName;
                if (!cppValue.empty() && cppGenerationFlags & Declaration) {
                    strm << " = " << cppValue;
                }
            }
        }
    }
}

void CppParameter::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    size_t count = 0;
    for (const auto& element : *this) {
        if (!element.cppType.empty()) {
            if (count++) {
                strm << ", ";
            }
            element.generate(strm, cppGenerationFlags);
        }
    }
}

} // namespace cppgen
} // namespace dst
