
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-structure.hpp"
#include "dynamic_static/cpp-generator/stream-tab.hpp"

#include <ostream>

namespace dst {
namespace cppgen {

void CppStructure::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    if (!mCppName.empty()) {

        mCppTemplate.generate(strm, cppGenerationFlags);
        strm << (mCppFlags & Class ? "class "  : "struct ");
        strm << mCppName;
        mCppTemplate.generate(strm, cppGenerationFlags | Specialization);
        strm << (mCppFlags & Final ? " final" : "");
        strm << '\n';

        size_t baseTypeCount = 0;
        for (const auto& cppBaseType : mCppBaseTypes) {
            strm << "    ";
            if (!baseTypeCount++) {
                strm << ": ";
            } else {
                strm << ", ";
            }
            cppBaseType.generate(strm, cppGenerationFlags);
            strm << '\n';
        }

        strm << "{\n";
        StreamTab strmTab(strm);
        auto cppAccessSpecifier = Unspecified;
        #if 0
        for (const auto& cppElement : mCppElements) {
            if (cppAccessSpecifier != cppElement.first) {
                cppAccessSpecifier = cppElement.first;
                strmTab.count = 0;
                switch (cppAccessSpecifier) {
                case Public:    strm << "public:\n";    break;
                case Protected: strm << "protected:\n"; break;
                case Private:   strm << "private:\n";   break;
                default: break;
                }
            }
            dst_cppgen_assert(cppElement.second);
            strmTab.count = 1;
            cppElement.second->generate(strm, cppGenerationFlags, mCppName);
        }
        #endif
        strm << "};\n";
    }
}

void CppStructure::Collection::generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType) const
{
    size_t count = 0;
    for (const auto& element : *this) {
        if (count++) {
            strm << '\n';
        }
        element.generate(strm, cppGenerationFlags, cppEnclosingType);
    }
}

} // namespace cppgen
} // namespace dst
