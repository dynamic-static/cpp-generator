
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppCompileGuard::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{

}

void CppCompileGuard::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Open) {
        for (const auto& cppCompileGuard : *this) {
            cppCompileGuard.generate(strm, cppGenerationFlags);
            strm << std::endl;
        }
    } else
    if (cppGenerationFlags & Close) {
        for (auto ritr = rbegin(); ritr != rend(); ++ritr) {
            ritr->generate(strm, cppGenerationFlags);
            strm << std::endl;
        }
    }
}

} // namespace cppgen
} // namespace dst
