
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-enumerator.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppEnumerator::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Declaration) {
        if (!cppName.empty()) {
            cppCompileGuards.generate(strm, Open);
            strm << cppName;
            if (!cppValue.empty()) {
                strm << " = " << cppValue;
            }
            strm << ',' << std::endl;
            cppCompileGuards.generate(strm, Close);
        }
    }
}

void CppEnumerator::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    for (const auto& cppEnumerator : *this) {
        cppEnumerator.generate(strm, cppGenerationFlags);
    }
}

} // namespace cppgen
} // namespace dst
