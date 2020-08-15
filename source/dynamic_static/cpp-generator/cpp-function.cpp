
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-function.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppFunction::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    if (!cppReturnType.empty() && !cppName.empty()) {
        // if (cppFlags & Inline && cppGenerationFlags & Declaration || !(cppFlags & Inline) && ) {
        //     cppGenerationFlags |= Declaration | Definition;
        // }
        // TODO : Open CppCompileGuards...
        cppTemplate.generate(strm, cppGenerationFlags);
        if (!cppTemplate.cppParameters.empty()) {
            strm << '\n';
        }
        if (cppFlags & Inline) {
            strm << "inline ";
        }
        strm << (cppFlags & Static  ? "static "  : "");
        strm << (cppFlags & Extern  ? "extern "  : "");
        strm << (cppFlags & Virtual ? "virtual " : "");
        strm << cppReturnType << ' ';
        if (!cppEnclosingType.empty()) {
            strm << cppEnclosingType << "::";
        }
        strm << cppName;
        cppTemplate.generate(strm, cppGenerationFlags | Specialization);
        strm << '(';
        cppParameters.generate(strm, cppGenerationFlags);
        strm << ')';
        strm << (cppFlags & Const    ? " const"     : "");
        strm << (cppFlags & Override ? " override"  : "");
        strm << (cppFlags & Final    ? " final"     : "");
        strm << (cppFlags & Abstract ? " = 0"       : "");
        strm << (cppFlags & Default  ? " = default" : "");
        strm << (cppFlags & Delete   ? " = delete"  : "");
        if (cppGenerationFlags & Definition) {
            strm << "\n{\n";
            strm << cppSourceBlock;
            strm << '}';
        } else {
            strm << ';';
        }
        strm << '\n';
        // TODO : Close CppCompileGuards...
    }
}

void CppFunction::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    size_t count = 0;
    for (const auto& element : *this) {
        if (cppGenerationFlags & Definition || count++) {
            strm << '\n';
        }
        element.generate(strm, cppGenerationFlags, cppEnclosingType);
    }
}

} // namespace cppgen
} // namespace dst
