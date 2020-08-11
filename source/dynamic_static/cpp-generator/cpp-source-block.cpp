
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-source-block.hpp"
#include "cpp-source-region.hpp"
#include "string.hpp"

#include <ostream>
#include <utility>

namespace dst {
namespace cppgen {

CppSourceBlock::CppSourceBlock(std::string_view cppSource, const std::vector<CppSourceBlock>& cppSourceBlocks)
{
    set_cpp_source_blocks(cppSourceBlocks);
    mCppSource = string::format(CppSourceRegion(cppSource).process_cpp_source(cppSource, *this));
}

CppSourceBlock::CppSourceBlock(std::string_view key, std::string_view value)
    : mKey { key }
    , mValue { value }
{
}

CppSourceBlock::operator const std::string&() const
{
    return mCppSource;
}

std::ostream& operator<<(std::ostream& ostrm, const CppSourceBlock& cppSourceBlock)
{
    return ostrm << cppSourceBlock.mCppSource;
}

const std::string& CppSourceBlock::get_key() const
{
    return mKey;
}

const std::string& CppSourceBlock::get_value() const
{
    return mValue;
}

const std::vector<CppSourceBlock>& CppSourceBlock::get_cpp_source_blocks() const
{
    return mCppSourceBlocks;
}

const CppSourceBlock* CppSourceBlock::get_cpp_source_block(std::string_view key) const
{
    auto itr = mKeyedCppSourceBlocks.find(key);
    return itr != mKeyedCppSourceBlocks.end() ? &itr->second : mpParent ? mpParent->get_cpp_source_block(key) : nullptr;
}

void CppSourceBlock::set_cpp_source_blocks(const std::vector<CppSourceBlock>& cppSourceBlocks)
{
    for (const auto& cppSourceBlock : cppSourceBlocks) {
        if (!cppSourceBlock.mKey.empty()) {
            auto result = mKeyedCppSourceBlocks.insert({ cppSourceBlock.mKey, cppSourceBlock });
            if (result.second) {
                result.first->second.mpParent = this;
            } else {
                dst_cppgen_assert(false && "TODO : throw");
            }
        } else {
            dst_cppgen_assert(false && "TODO : throw");
        }
    }
}

} // namespace cppgen
} // namespace dst
