
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
using Condition = std::pair<std::string, bool>;

/**
TODO : Documentation
*/
class SourceBlock final
{
public:
    /**
    TODO : Documentation
    */
    SourceBlock() = default;

    /**
    TODO : Documentation
    */
    SourceBlock(std::string_view source, const std::vector<SourceBlock>& logicBlocks = { });

    /**
    TODO : Documentation
    */
    SourceBlock(std::string_view key, std::string_view value);

    /**
    TODO : Documentation
    */
    SourceBlock(const Condition& condition);

    /**
    TODO : Documentation
    */
    template <typename CollectionType, typename ProcessElementFunctionType>
    inline SourceBlock(std::string_view key, const CollectionType& collection, ProcessElementFunctionType processElement)
        : mKey { key }
    {
        mSourceBlocks.reserve(collection.size());
        for (const auto& element : collection) {
            mSourceBlocks.push_back({ });
            mSourceBlocks.back().set_source_blocks(processElement(element));
        }
    }

    /**
    TODO : Documentation
    */
    operator std::string() const;

    /**
    TODO : Documentation
    */
    const Condition& get_condition() const;

    /**
    TODO : Documentation
    */
    const std::string& get_key() const;

    /**
    TODO : Documentation
    */
    const std::string& get_value() const;

    /**
    TODO : Documentation
    */
    const SourceBlock* get_source_block(const std::string& key) const;

    /**
    TODO : Documentation
    */
    const std::vector<SourceBlock>& get_source_blocks() const;

    /**
    TODO : Documentation
    */
    const std::unordered_map<std::string, SourceBlock>& get_keyed_source_blocks() const;

    /**
    TODO : Documentation
    */
    friend std::ostream& operator<<(std::ostream& ostrm, const SourceBlock& sourceBlock);

private:
    void set_source_blocks(const std::vector<SourceBlock>& sourceBlocks);
    std::string mSource;
    Condition mCondition;
    std::string mKey;
    std::string mValue;
    std::vector<SourceBlock> mSourceBlocks;
    std::unordered_map<std::string, SourceBlock> mKeyedSourceBlocks;
    std::unordered_map<std::string, std::string> mOptions;
    const SourceBlock* mpParent { nullptr };
};

} // namespace cppgen
} // namespace dst
