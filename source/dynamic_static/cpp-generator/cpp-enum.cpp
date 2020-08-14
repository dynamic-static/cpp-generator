
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-enum.hpp"
#include "dynamic_static/cpp-generator/stream-tab.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppEnum::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    if (!cppName.empty() || !cppEnumerators.empty()) {
        cppCompileGuards.generate(strm, Open);
        strm << (cppFlags & Typedef ? "typedef " : "") << "enum" << (cppFlags & Class ? " class" : cppFlags & Struct ? " struct" : "");
        if (!cppName.empty()) {
            strm << ' ' << cppName;
        }
        if (!cppBaseType.empty()) {
            strm << " : " << cppBaseType;
        }
        strm << "\n{\n";
        {
            StreamTab strmTab(strm, 1);
            cppEnumerators.generate(strm, cppGenerationFlags);
        }
        strm << '}';
        if (cppFlags & Typedef && !cppName.empty()) {
            strm << ' ' << cppName;
        }
        strm << ";\n";
        cppCompileGuards.generate(strm, Close);
    }
}

void CppEnum::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view) const
{
    size_t count = 0;
    for (const auto& cppEnum : *this) {
        if ((!cppEnum.cppName.empty() || !cppEnum.cppEnumerators.empty()) && count++) {
            strm << '\n';
        }
        cppEnum.generate(strm, cppGenerationFlags);
    }
}

} // namespace cppgen
} // namespace dst
