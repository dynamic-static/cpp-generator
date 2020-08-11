
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

#include <iosfwd>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

/**
TODO : Documentation
*/
#define CppSourceBlockLogic(OBJECT_TYPE) [&](OBJECT_TYPE) -> std::vector<dst::cppgen::CppSourceBlock>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppSourceBlock final
{
public:
    class Error;
    class Option;

    /**
    TODO : Documentation
    */
    CppSourceBlock() = default;

    /**
    TODO : Documentation
    */
    CppSourceBlock(std::string_view cppSource, const std::vector<CppSourceBlock>& cppSourceBlocks = { });

    /**
    TODO : Documentation
    */
    CppSourceBlock(std::string_view key, std::string_view value);

    /**
    TODO : Documentation
    */
    template <typename CollectionType, typename CppGenLogicType>
    inline CppSourceBlock(std::string_view key, const CollectionType& collection, CppGenLogicType cppGenLogic)
        : mKey { key }
    {
        mCppSourceBlocks.reserve(collection.size());
        for (const auto& element : collection) {
            mCppSourceBlocks.push_back({ });
            mCppSourceBlocks.back().set_cpp_source_blocks(cppGenLogic(element));
        }
    }

    /**
    TODO : Documentation
    */
    operator const std::string&() const;

    /**
    TODO : Documentation
    */
    friend std::ostream& operator<<(std::ostream& ostrm, const CppSourceBlock& cppSourceBlock);

public:
    const std::string& get_key() const;
    const std::string& get_value() const;
    const std::vector<CppSourceBlock>& get_cpp_source_blocks() const;
    const CppSourceBlock* get_cpp_source_block(std::string_view key) const;
private:
    void set_cpp_source_blocks(const std::vector<CppSourceBlock>& cppSourceBlocks);
    std::string mCppSource;
    std::string mKey;
    std::string mValue;
    std::vector<CppSourceBlock> mCppSourceBlocks;
    std::map<std::string, CppSourceBlock, std::less<>> mKeyedCppSourceBlocks;
    const CppSourceBlock* mpParent { nullptr };
};

} // namespace cppgen
} // namespace dst
