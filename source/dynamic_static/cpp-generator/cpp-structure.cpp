
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
        strm << (mCppFlags & Class ? "class "  : "struct ");
        strm << mCppName;
        strm << (mCppFlags & Final ? " final" : "");
        strm << "\n{\n";
        StreamTab strmTab(strm);
        auto cppAccessSpecifier = Unspecified;
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
        strm << "};\n";
    }
}

} // namespace cppgen
} // namespace dst
