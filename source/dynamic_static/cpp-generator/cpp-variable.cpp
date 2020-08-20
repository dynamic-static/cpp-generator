
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-variable.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

CppVariable::CppVariable(
    std::string_view cppType,
    std::string_view cppName,
    std::string_view cppValue
)
    : cppType { cppType }
    , cppName { cppName }
    , cppValue { cppValue }
{
}

void CppVariable::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    if (cppGenerationFlags & Declaration) {
        if (!cppType.empty() && !cppName.empty()) {
            strm << cppType << ' ' << cppName;
            if (!cppValue.empty()) {
                strm << "{ " << cppValue << " }";
            } else
            if (cppFlags & Default) {
                strm << "{ }";
            }
            strm << ";\n";
        }
    }
}

} // namespace cppgen
} // namespace dst
