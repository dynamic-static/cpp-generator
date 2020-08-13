
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
#include <set>
#include <string_view>

namespace dst {
namespace cppgen {

void CppCompileGuard::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Open) {
        if (!empty()) {
            strm << "#ifdef " << *this << std::endl;
        }
    } else
    if (cppGenerationFlags & Close) {
        if (!empty()) {
            strm << "#endif // " << *this << std::endl;
        }
    }
}

void CppCompileGuard::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    std::set<std::string_view> cppCompileGuards;
    if (cppGenerationFlags & Open) {
        for (const auto& cppCompileGuard : *this) {
            if (cppCompileGuards.insert(cppCompileGuard.as<std::string>()).second) {
                cppCompileGuard.generate(strm, cppGenerationFlags);
            }
        }
    } else
    if (cppGenerationFlags & Close) {
        std::vector<const CppCompileGuard*> cppCompileGuardPtrs;
        cppCompileGuardPtrs.reserve(size());
        for (const auto& cppCompileGuard : *this) {
            if (cppCompileGuards.insert(cppCompileGuard.as<std::string>()).second) {
                cppCompileGuardPtrs.push_back(&cppCompileGuard);
            }
        }
        for (auto ritr = cppCompileGuardPtrs.rbegin(); ritr != cppCompileGuardPtrs.rend(); ++ritr) {
            dst_cppgen_assert(*ritr);
            (*ritr)->generate(strm, cppGenerationFlags);
        }
    }
}

} // namespace cppgen
} // namespace dst
