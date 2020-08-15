
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-declaration.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppDeclaration::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Declaration) {
        if (!empty()) {
            cppCompileGuards.generate(strm, Open);
            strm << *this << '\n';
            cppCompileGuards.generate(strm, Close);
        }
    }
}

void CppDeclaration::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    for (const auto& cppDeclaration : *this) {
        cppDeclaration.generate(strm, cppGenerationFlags);
    }
}

} // namespace cppgen
} // namespace dst
