
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-case.hpp"
#include "dynamic_static/cpp-generator/stream-tab.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppCase::generate(std::ostream& strm, CppGenerationFlags, std::string_view) const
{
    if (cppFlags & Default || !cppLabel.empty()) {
        cppCompileGuards.generate(strm, Open);
        if (cppFlags & Default || cppLabel == "default") {
            strm << "default";
        } else {
            strm << "case " << cppLabel;
        }
        strm << ": {\n";
        {
            StreamTab strmTab(strm, 1);
            strm << cppSourceBlock;
        }
        strm << "}";
        if (cppFlags & Break) {
            strm << " break;";
        }
        strm << '\n';
        cppCompileGuards.generate(strm, Close);
    }
}

void CppCase::Collection::generate(std::ostream& strm, CppGenerationFlags, std::string_view) const
{
    for (const auto& cppCase : *this) {
        cppCase.generate(strm);
    }
}

} // namespace cppgen
} // namespace dst
