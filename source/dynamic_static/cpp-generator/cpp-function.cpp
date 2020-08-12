
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
            strm << std::endl;
        }
        if (cppFlags & Inline) {
            strm << "inline ";
        }
        strm << (cppFlags & Static  ? "static "  : std::string());
        strm << (cppFlags & Extern  ? "extern "  : std::string());
        strm << (cppFlags & Virtual ? "virtual " : std::string());
        strm << cppReturnType << ' ';
        if (!cppEnclosingType.empty()) {
            strm << cppEnclosingType << "::";
        }
        strm << cppName;
        cppTemplate.generate(strm, cppGenerationFlags | Specialization);
        strm << '(';
        cppParameters.generate(strm, cppGenerationFlags);
        strm << ')';
        strm << (cppFlags & Const    ? " const"     : std::string());
        strm << (cppFlags & Override ? " override"  : std::string());
        strm << (cppFlags & Final    ? " final"     : std::string());
        strm << (cppFlags & Abstract ? " = 0"       : std::string());
        strm << (cppFlags & Default  ? " = default" : std::string());
        strm << (cppFlags & Delete   ? " = delete"  : std::string());
        if (cppGenerationFlags & Definition) {
            strm << std::endl;
            strm << '{' << std::endl;
            strm << cppSourceBlock;
            strm << '}';
        } else {
            strm << ';';
        }
        strm << std::endl;
        // TODO : Close CppCompileGuards...
    }
}

void CppFunction::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    size_t count = 0;
    for (const auto& element : *this) {
        if (cppGenerationFlags & Definition || count++) {
            strm << std::endl;
        }
        element.generate(strm, cppGenerationFlags, cppEnclosingType);
    }
}

} // namespace cppgen
} // namespace dst
