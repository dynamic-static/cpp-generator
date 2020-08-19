
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-function.hpp"
#include "dynamic_static/cpp-generator/stream-tab.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

bool CppFunction::empty() const
{
    return cppName.empty();
}

bool CppFunction::operative(CppGenerationFlags cppGenerationFlags) const
{
    return
        !empty() &&
        cppGenerationFlags & (Declaration | Definition) &&
        !(!(cppGenerationFlags & Declaration) && (cppFlags & Default || cppFlags & Delete)) &&
        (cppTemplate.empty() || cppTemplate.operative(cppGenerationFlags));
}

void CppFunction::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    if (operative(cppGenerationFlags)) {
        if (!cppTemplate.empty() && cppTemplate.operative(cppGenerationFlags) && !cppTemplate.operative(Definition)) {
            cppGenerationFlags |= (Declaration | Definition);
        }
        cppCompileGuards.generate(strm, Open);
        cppTemplate.generate(strm, cppGenerationFlags);
        if ((cppGenerationFlags & (Declaration | Definition)) == (Declaration | Definition) && cppEnclosingType.empty()) {
            strm << "inline ";
        }
        if (cppGenerationFlags & Declaration) {
            strm << (cppFlags & Static  ? "static "  : "");
            strm << (cppFlags & Extern  ? "extern "  : "");
            strm << (cppFlags & Virtual ? "virtual " : "");
            strm << (cppFlags & Friend  ? "friend "  : "");
        }
        if (!cppReturnType.empty()) {
            strm << cppReturnType << ' ';
        }
        if (!(cppGenerationFlags & Declaration) && cppGenerationFlags & Definition && !cppEnclosingType.empty()) {
            strm << cppEnclosingType << "::";
        }
        strm << cppName;
        cppTemplate.generate(strm, cppGenerationFlags | Specialization);
        strm << '('; cppParameters.generate(strm, cppGenerationFlags); strm << ')';
        strm << (cppFlags & Const ? " const" : "");
        if (cppGenerationFlags & Declaration) {
            strm << (cppFlags & Override ? " override"  : "");
            strm << (cppFlags & Final    ? " final"     : "");
            strm << (cppFlags & Abstract ? " = 0"       : "");
            strm << (cppFlags & Default  ? " = default" : "");
            strm << (cppFlags & Delete   ? " = delete"  : "");
        }
        if (cppGenerationFlags & Definition &&
            !(cppGenerationFlags & Declaration && cppFlags & Abstract) &&
            !(cppFlags & Default) &&
            !(cppFlags & Delete)) {
            strm << "\n{\n";
            {
                StreamTab strmTab(strm, 1);
                strm << cppSourceBlock;
            }
            strm << '}';
        } else {
            strm << ';';
        }
        strm << '\n';
        cppCompileGuards.generate(strm, Close);
    }
}

void CppFunction::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    size_t count = 0;
    for (const auto& element : *this) {
        if (cppGenerationFlags & Definition && count++) {
            strm << '\n';
        }
        element.generate(strm, cppGenerationFlags, cppEnclosingType);
    }
}

} // namespace cppgen
} // namespace dst
