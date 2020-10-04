
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/source-block.hpp"
#include "source-region.hpp"
#include "stream-writer.hpp"

#include <sstream>

namespace dst {
namespace cppgen {

SourceBlock::SourceBlock(std::string_view source, const std::vector<SourceBlock>& sourceBlocks)
    : mSource { source }
{
    set_source_blocks(sourceBlocks);
}

SourceBlock::SourceBlock(std::string_view key, std::string_view value)
    : mKey { key }
    , mValue { value }
{
}

SourceBlock::SourceBlock(const Condition& condition)
    : mCondition { condition }
{
}

SourceBlock::operator std::string() const
{
    std::stringstream strStrm;
    strStrm << *this;
    return strStrm.str();
}

const Condition& SourceBlock::get_condition() const
{
    return mCondition;
}

const std::string& SourceBlock::get_key() const
{
    return mKey;
}

const std::string& SourceBlock::get_value() const
{
    return mValue;
}

const std::vector<SourceBlock>& SourceBlock::get_source_blocks() const
{
    return mSourceBlocks;
}

const std::unordered_map<std::string, SourceBlock>& SourceBlock::get_keyed_source_blocks() const
{
    return mKeyedSourceBlocks;
}

std::ostream& operator<<(std::ostream& ostrm, const SourceBlock& sourceBlock)
{
    SourceRegion region(sourceBlock.mSource);
    if (region.get_errors().empty()) {
        const_cast<SourceBlock&>(sourceBlock).set_parent_ptrs();
        region.process_source(sourceBlock.mSource, sourceBlock, StreamWriter(ostrm));
    } else {
        // TODO : Error handling
    }
    return ostrm;
}

const SourceBlock* SourceBlock::get_source_block(const std::string& key) const
{
    auto itr = mKeyedSourceBlocks.find(key);
    return itr != mKeyedSourceBlocks.end() ? &itr->second : mpParent ? mpParent->get_source_block(key) : nullptr;
}

void SourceBlock::set_source_blocks(const std::vector<SourceBlock>& sourceBlocks)
{
    for (const auto& sourceBlock : sourceBlocks) {
        if (!sourceBlock.mKey.empty()) {
            if (!mKeyedSourceBlocks.insert({ sourceBlock.mKey, sourceBlock }).second) {
                // TODO : Error handling
            }
        } else {
            mCondition = sourceBlock.get_condition();
        }
    }
}

void SourceBlock::set_parent_ptrs()
{
    for (auto& sourceBlock : mSourceBlocks) {
        sourceBlock.mpParent = this;
        sourceBlock.set_parent_ptrs();
    }
    for (auto& keyedSourceBlock : mKeyedSourceBlocks) {
        keyedSourceBlock.second.mpParent = this;
        keyedSourceBlock.second.set_parent_ptrs();
    }
}

} // namespace cppgen
} // namespace dst
