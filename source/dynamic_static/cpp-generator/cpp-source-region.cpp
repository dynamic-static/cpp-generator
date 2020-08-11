
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "cpp-source-region.hpp"
#include "string.hpp"

#include <sstream>
#include <utility>

namespace dst {
namespace cppgen {

CppSourceRegion::CppSourceRegion(std::string_view cppSource)
    : CppSourceRegion(cppSource, CppSourceTag(cppSource, CppSourceTag::Type::RegionBegin))
{
}

CppSourceRegion::CppSourceRegion(std::string_view cppSource, const CppSourceTag& beginTag)
    : mBeginTag(beginTag)
    , mEndTag(cppSource, CppSourceTag::Type::RegionEnd)
{
    mKey = beginTag.get_key();
    size_t offset = beginTag.get_end_index();
    while (offset < cppSource.size() && mEndTag.empty()) {
        offset = cppSource.find('$', offset);
        if (offset != std::string::npos) {
            CppSourceTag cppSourceTag(cppSource, offset);
            switch (cppSourceTag.get_type()) {
            case CppSourceTag::Type::Invidual: {
                mElementPtrs.push_back(std::make_unique<CppSourceTag>(cppSourceTag));
                offset = mElementPtrs.back()->get_end_index();
            } break;
            case CppSourceTag::Type::RegionBegin: {
                mElementPtrs.push_back(std::make_unique<CppSourceRegion>(cppSource, cppSourceTag));
                offset = mElementPtrs.back()->get_end_index();
            } break;
            case CppSourceTag::Type::RegionEnd: {
                dst_cppgen_assert(!beginTag.empty());
                dst_cppgen_assert(mEndTag.empty());
                mEndTag = cppSourceTag;
            } break;
            }
        }
    }
    take_options(mBeginTag);
    take_options(mEndTag);
}

CppSourceRegion::CppSourceRegion(const CppSourceRegion& other)
{
    *this = other;
}

CppSourceRegion::CppSourceRegion(CppSourceRegion&& other)
{
    *this = std::move(other);
}

CppSourceRegion& CppSourceRegion::operator=(const CppSourceRegion& other)
{
    CppSourceElement::operator=(other);
    mBeginTag = other.mBeginTag;
    mElementPtrs.clear();
    mElementPtrs.reserve(other.mElementPtrs.size());
    for (const auto& pCppSourceElement : other.mElementPtrs) {
        dst_cppgen_assert(pCppSourceElement);
        mElementPtrs.push_back(pCppSourceElement->clone());
    }
    mEndTag = other.mEndTag;
    return *this;
}

CppSourceRegion& CppSourceRegion::operator=(CppSourceRegion&& other)
{
    CppSourceElement::operator=(std::move(other));
    mBeginTag = std::move(other.mBeginTag);
    mElementPtrs = std::move(other.mElementPtrs);
    mEndTag = std::move(other.mEndTag);
    return *this;
}

std::unique_ptr<CppSourceElement> CppSourceRegion::clone() const
{
    return std::make_unique<CppSourceRegion>(*this);
}

size_t CppSourceRegion::get_begin_index(std::string_view cppSource) const
{
    auto beginIndex = mBeginTag.get_begin_index();
    if (!cppSource.empty()) {
        dst_cppgen_assert(beginIndex < cppSource.size());
        for (size_t i = beginIndex; 0 < i; --i) {
            if (isspace((int)cppSource[i - 1])) {
                if (cppSource[i - 1] == '\n') {
                    beginIndex = i - 1;
                    break;
                }
            } else {
                break;
            }
        }
    }
    return beginIndex;
}

size_t CppSourceRegion::get_content_begin_index(std::string_view cppSource) const
{
    return mBeginTag.get_end_index();
}

size_t CppSourceRegion::get_content_end_index(std::string_view cppSource) const
{
    auto contentEndIndex = mEndTag.get_begin_index();
    if (!cppSource.empty()) {
        dst_cppgen_assert(contentEndIndex <= cppSource.size());
        while (0 < contentEndIndex && isspace((int)cppSource[contentEndIndex - 1])) {
            --contentEndIndex;
        }
    }
    return contentEndIndex;
}

size_t CppSourceRegion::get_end_index(std::string_view) const
{
    return mEndTag.get_end_index();
}

std::string CppSourceRegion::str(std::string_view cppSource) const
{
    std::stringstream strStrm;
    auto contentBegin = mBeginTag.get_end_index();
    auto contentEnd = mEndTag.get_begin_index();
    strStrm << mBeginTag.str(cppSource) << std::endl;
    for (const auto& cppSourceElement : mElementPtrs) {
        strStrm << cppSourceElement->str(cppSource) << std::endl;
    }
    strStrm << mEndTag.str(cppSource);
    return strStrm.str();
}

std::string CppSourceRegion::process_cpp_source(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const
{
    std::stringstream strStrm;
    if (!cppSourceBlock.get_cpp_source_blocks().empty()) {
        // TODO : If/when more CppSourceBlock::Options are added, the logic to handle
        //  them should be refactored and validation/error messages should be added.
        // NOTE : Write CppSourceBlock::Option [Lead] set with "l" in a CppSourceTag
        strStrm << get_cpp_source_block_option_value("l");
        // NOTE : Get CppSourceBlock::Option [Seperator] set with "s" in a CppSourceTag
        auto seperator = get_cpp_source_block_option_value("s");
        const auto& subCppSourceBlocks = cppSourceBlock.get_cpp_source_blocks();
        for (auto itr = subCppSourceBlocks.begin(); itr != subCppSourceBlocks.end(); ++itr) {
            if (itr != subCppSourceBlocks.begin()) {
                strStrm << seperator;
            }
            strStrm << process_cpp_source(cppSource, *itr);
        }
        // NOTE : Write CppSourceBlock::Option [Follow] set with "f" in a CppSourceTag
        strStrm << get_cpp_source_block_option_value("f");
    } else {
        strStrm << process_cpp_source_elements(cppSource, cppSourceBlock);
    }
    return strStrm.str();
}

std::string CppSourceRegion::process_cpp_source_elements(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const
{
    std::stringstream strStrm;
    auto cppSourceOffset = get_content_begin_index(cppSource);
    for (const auto& pElement : mElementPtrs) {
        dst_cppgen_assert(pElement);
        auto elementBeginIndex = pElement->get_begin_index(cppSource);
        std::string cppSourceElementStr;
        auto pCppSourceBlock = cppSourceBlock.get_cpp_source_block(pElement->get_key());
        if (pCppSourceBlock) {
            cppSourceElementStr = pElement->process_cpp_source(cppSource, *pCppSourceBlock);
            if (!cppSourceElementStr.empty()) {
                strStrm << cppSource.substr(cppSourceOffset, elementBeginIndex - cppSourceOffset);
                strStrm << cppSourceElementStr;
            } else {
                // TODO : contentCharactersEndIndex...
                strStrm << cppSource.substr(cppSourceOffset, elementBeginIndex - cppSourceOffset);
            }
            cppSourceOffset = pElement->get_end_index();
        } else {
            assert(false && "TODO : Support for missing keys");
        }
    }
    auto contentEndIndex = get_content_end_index(cppSource);
    if (cppSourceOffset < contentEndIndex) {
        strStrm << cppSource.substr(cppSourceOffset, contentEndIndex - cppSourceOffset);
    }
    return strStrm.str();
}

} // namespace cppgen
} // namespace dst
