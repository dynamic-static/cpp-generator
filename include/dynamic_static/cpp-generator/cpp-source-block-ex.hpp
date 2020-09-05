
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
#define CppSourceBlockLogicEx(OBJECT_TYPE) [&](OBJECT_TYPE) -> std::vector<dst::cppgen::CppSourceBlockEx>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppSourceBlockEx final
{
public:
    class Error;
    class Option;

    /**
    TODO : Documentation
    */
    CppSourceBlockEx() = default;

    /**
    TODO : Documentation
    */
    CppSourceBlockEx(std::string_view cppSource, const std::vector<CppSourceBlockEx>& cppSourceBlocks = { });

    /**
    TODO : Documentation
    */
    CppSourceBlockEx(std::string_view key, std::string_view value);

    /**
    TODO : Documentation
    */
    template <typename CollectionType, typename CppGenLogicType>
    inline CppSourceBlockEx(std::string_view key, const CollectionType& collection, CppGenLogicType cppGenLogic)
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
    void generate(std::ostream& ostrm, const std::vector<CppSourceBlockEx>& cppSourceBlocks = { }) const;

public:
    const std::string& get_key() const;
    const std::string& get_value() const;
    const std::vector<CppSourceBlockEx>& get_cpp_source_blocks() const;
    const CppSourceBlockEx* get_cpp_source_block(std::string_view key) const;
private:
    void set_cpp_source_blocks(const std::vector<CppSourceBlockEx>& cppSourceBlocks);
    std::string mCppSource;
    std::string mKey;
    std::string mValue;
    std::vector<CppSourceBlockEx> mCppSourceBlocks;
    std::map<std::string, CppSourceBlockEx, std::less<>> mKeyedCppSourceBlocks;
    const CppSourceBlockEx* mpParent { nullptr };
};

} // namespace cppgen
} // namespace dst
