
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-namespace.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppNamespace::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Open) {
        if (!empty()) {
            strm << "namespace " << *this << ' {' << std::endl;
        }
    } else
    if (cppGenerationFlags & Close) {
        if (!empty()) {
            strm << "} // namespace " << *this << std::endl;
        }
    }
}

void CppNamespace::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (cppGenerationFlags & Open) {
        for (const auto& cppNamespace : *this) {
            cppNamespace.generate(strm, cppGenerationFlags);
        }
    } else
    if (cppGenerationFlags & Close) {
        for (auto ritr = rbegin(); ritr != rend(); ++ritr) {
            ritr->generate(strm, cppGenerationFlags);
        }
    }
}

} // namespace cppgen
} // namespace dst
