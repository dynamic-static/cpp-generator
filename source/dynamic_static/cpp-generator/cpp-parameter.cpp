
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

CppParameter::CppParameter(std::string_view cppType, std::string_view cppName, std::string_view cppValue)
{
    this->cppType = cppType;
    this->cppName = cppName;
    this->cppValue = cppValue;
}

void CppParameter::generate(std::ostream& strm, CppGenerationFlags flags) const
{
    if (!cppType.empty()) {
        strm << cppType;
        if (!cppName.empty()) {
            strm << ' ' << cppName;
            if (!cppValue.empty() && flags & Declaration) {
                strm << " = " << cppValue;
            }
        }
    }
}

void CppParameter::Collection::generate(std::ostream& strm, CppGenerationFlags flags) const
{
    size_t count = 0;
    for (const auto& element : *this) {
        if (!element.cppType.empty()) {
            if (count++) {
                strm << ", ";
            }
            element.generate(strm, flags);
        }
    }
}

} // namespace cppgen
} // namespace dst
