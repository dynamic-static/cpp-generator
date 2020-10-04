
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "source-region.hpp"
#include "dynamic_static/cpp-generator/source-block.hpp"
#include "stream-writer.hpp"

namespace dst {
namespace cppgen {

SourceRegion::SourceRegion(std::string_view source)
    : SourceRegion(source, { source, SourceTag::Type::RegionBegin })
{
}

SourceRegion::SourceRegion(std::string_view source, const SourceTag& begin)
    : mBegin { begin }
    , mEnd { source, SourceTag::Type::RegionEnd }
{
    size_t offset = mBegin.get_end_index();
    while (offset < source.size() && mEnd.get_begin_index() == mEnd.get_end_index()) {
        offset = source.find('$', offset);
        if (offset != std::string::npos) {
            SourceTag tag(source, offset);
            switch (tag.get_type()) {
            case SourceTag::Type::Replacement: {
                mSourceElements.push_back(std::make_unique<SourceTag>(tag));
                offset = mSourceElements.back()->get_end_index();
            } break;
            case SourceTag::Type::RegionBegin: {
                mSourceElements.push_back(std::make_unique<SourceRegion>(source, tag));
                offset = mSourceElements.back()->get_end_index();
            } break;
            case SourceTag::Type::RegionEnd: {
                mEnd = tag;
            } break;
            }
        }
    }
    if (mEnd.get_type() != SourceTag::Type::Invalid) {
        for (const auto& option : mBegin.get_options()) {
            if (option.first == "condition" && mBegin.get_options().size() != 1 && !mEnd.get_options().empty()) {
                mErrors.push_back("TODO : Error handling");
            } else 
            if (mEnd.get_options().find(option.first) != mEnd.get_options().end()) {
                mErrors.push_back("TODO : Error handling");
            }
        }
        if (!mEnd.get_key().empty() && mEnd.get_key() != mBegin.get_key()) {
            mErrors.push_back("TODO : Error handling");
        }
    } else {
        mErrors.push_back("TODO : Error handling");
    }
}

const std::string& SourceRegion::get_key() const
{
    return mBegin.get_key();
}

size_t SourceRegion::get_begin_index() const
{
    return mBegin.get_begin_index();
}

size_t SourceRegion::get_end_index() const
{
    return mEnd.get_end_index();
}

const std::string& SourceRegion::get_option(const std::string& key) const
{
    const auto& value = mBegin.get_option(key);
    return !value.empty() ? value : mEnd.get_option(key);
}

const SourceTag& SourceRegion::get_begin_tag() const
{
    return mBegin;
}

const std::vector<std::unique_ptr<SourceElement>>& SourceRegion::get_source_elements() const
{
    return mSourceElements;
}

const SourceTag& SourceRegion::get_end_tag() const
{
    return mEnd;
}

void SourceRegion::process_source(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmWriter) const
{
    if (!sourceBlock.get_source_blocks().empty()) {
        const auto& sourceBlocks = sourceBlock.get_source_blocks();
        if (get_option("reverse") == "true") {
            process_source_blocks(source, sourceBlocks.rbegin(), sourceBlocks.rend(), strmWriter);
        } else {
            process_source_blocks(source, sourceBlocks.begin(), sourceBlocks.end(), strmWriter);
        }
    } else
    if (!sourceBlock.get_keyed_source_blocks().empty()) {
        process_source_elements(source, sourceBlock, strmWriter);
    }
}

template <typename ItrType>
void SourceRegion::process_source_blocks(std::string_view source, ItrType begin, ItrType end, StreamWriter& strmWriter) const
{
    // TODO : Differentiate head and tail seperators...
    strmWriter << get_option("head");
    const auto& seperator = get_option("seperator");
    for (auto itr = begin; itr != end; ++itr) {
        if (itr != begin) {
            strmWriter << seperator;
        }
        process_source(source, *itr, strmWriter);
    }
    strmWriter << get_option("tail");
}

void SourceRegion::process_source_elements(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmWriter) const
{
    auto offset = mBegin.get_end_index();
    for (const auto& pSourceElement : mSourceElements) {
        dst_cppgen_assert(pSourceElement);
        strmWriter << source.substr(offset, pSourceElement->get_begin_index() - offset);
        strmWriter.begin_processing_tag();
        strmWriter.end_processing_tag();
        auto pSourceBlock = sourceBlock.get_source_block(pSourceElement->get_key());
        if (!pSourceBlock && sourceBlock.get_condition().second && pSourceElement->get_option("condition") == sourceBlock.get_condition().first) {
            pSourceBlock = &sourceBlock;
        }
        static const SourceBlock sEmptySourceBlock;
        pSourceElement->process_source(source, pSourceBlock ? *pSourceBlock : sEmptySourceBlock, strmWriter);
        offset = pSourceElement->get_end_index();
    }
    strmWriter << source.substr(offset, mEnd.get_begin_index() - offset);
    strmWriter.begin_processing_tag();
    strmWriter.end_processing_tag();
}

} // namespace cppgen
} // namespace dst
