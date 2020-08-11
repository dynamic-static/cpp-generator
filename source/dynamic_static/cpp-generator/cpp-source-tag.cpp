
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "cpp-source-tag.hpp"
#include "string.hpp"

#include <sstream>
#include <utility>

namespace dst {
namespace cppgen {

CppSourceTag::CppSourceTag(std::string_view cppSource, Type type)
    : mType { type }
    , mBegin { mType == Type::RegionBegin ? 0 : cppSource.size() }
    , mEnd { mType == Type::RegionBegin ? 0 : cppSource.size() }
{
    dst_cppgen_assert(mType != Type::Invidual);
}

CppSourceTag::CppSourceTag(std::string_view cppSource, size_t begin)
    : mBegin { begin }
    , mEnd { begin + 1 }
{
    // TODO : Search for '/' anywhere in a RegionEnd...
    static const std::string EmptyRegionEndTagStr = "$</>";
    if (EmptyRegionEndTagStr.size() <= cppSource.size() - mBegin) {
        auto openChar = cppSource[mBegin + 1];
        auto closeChar = openChar == '{' ? '}' : openChar == '<' ? '>' : '\0';
        if (closeChar) {
            mType = openChar == '{' ? Type::Invidual : openChar == '<' && cppSource[mEnd + 1] != '/' ? Type::RegionBegin : Type::RegionEnd;
            mEnd = string::find(cppSource, closeChar, mEnd);
            if (mEnd != std::string::npos) {
                ++mEnd;
                auto optionsBegin = mBegin + 1 + (int)(mType == Type::RegionEnd) + 1;
                auto optionsEnd = mEnd - 1;
                parse_options(cppSource, optionsBegin, optionsEnd - optionsBegin);
            } else {
                assert(false && "TODO : Error handling");
            }
        } else {
            assert(false && "TODO : Error handling");
        }
    } else {
        assert(false && "TODO : Error handling");
    }
}

CppSourceTag::CppSourceTag(const CppSourceTag& other)
{
    *this = other;
}

CppSourceTag::CppSourceTag(CppSourceTag&& other)
{
    *this = std::move(other);
}

CppSourceTag& CppSourceTag::operator=(const CppSourceTag& other)
{
    CppSourceElement::operator=(other);
    mType = other.mType;
    mBegin = other.mBegin;
    mEnd = other.mEnd;
    return *this;
}

CppSourceTag& CppSourceTag::operator=(CppSourceTag&& other)
{
    CppSourceElement::operator=(std::move(other));
    mType = std::move(other.mType);
    mBegin = std::move(other.mBegin);
    mEnd = std::move(other.mEnd);
    return *this;
}

std::unique_ptr<CppSourceElement> CppSourceTag::clone() const
{
    return std::make_unique<CppSourceTag>(*this);
}

CppSourceTag::Type CppSourceTag::get_type() const
{
    return mType;
}

size_t CppSourceTag::get_begin_index(std::string_view cppSource) const
{
    auto beginIndex = mBegin;
    // if (!cppSource.empty()) {
    //     dst_cppgen_assert(beginIndex < cppSource.size());
    //     while (beginIndex && isspace((int)cppSource[beginIndex - 1]) && cppSource[beginIndex - 1] != '\n') {
    //         --beginIndex;
    //     }
    // }
    return beginIndex;
}

size_t CppSourceTag::get_end_index(std::string_view) const
{
    return mEnd;
}

std::string CppSourceTag::str(std::string_view cppSource) const
{
    std::stringstream strStrm;
    strStrm << cppSource.substr(mBegin, mEnd - mBegin);
    return strStrm.str();
}

std::string CppSourceTag::process_cpp_source(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const
{
    std::stringstream strStrm;
    const auto& value = cppSourceBlock.get_value();
    if (!value.empty()) {
        strStrm << get_cpp_source_block_option_value("l");
        strStrm << cppSourceBlock.get_value();
        strStrm << get_cpp_source_block_option_value("f");
    }
    return strStrm.str();
}

} // namespace cppgen
} // namespace dst
