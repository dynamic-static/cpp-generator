
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-source-block-ex.hpp"
#include "cpp-source-region.hpp"
#include "string.hpp"

#include <ostream>
#include <utility>

namespace dst {
namespace cppgen {

CppSourceBlockEx::CppSourceBlockEx(std::string_view cppSource, const std::vector<CppSourceBlockEx>& cppSourceBlocks)
{
    set_cpp_source_blocks(cppSourceBlocks);
    mCppSource = string::format(CppSourceRegion(cppSource).process_cpp_source(cppSource, *this));
}

CppSourceBlockEx::CppSourceBlockEx(std::string_view key, std::string_view value)
    : mKey { key }
    , mValue { value }
{
}

void CppSourceBlockEx::generate(std::ostream& ostrm, const std::vector<CppSourceBlockEx>& cppSourceBlocks) const
{

}

const std::string& CppSourceBlockEx::get_key() const
{
    return mKey;
}

const std::string& CppSourceBlockEx::get_value() const
{
    return mValue;
}

const std::vector<CppSourceBlockEx>& CppSourceBlockEx::get_cpp_source_blocks() const
{
    return mCppSourceBlocks;
}

const CppSourceBlockEx* CppSourceBlockEx::get_cpp_source_block(std::string_view key) const
{
    auto itr = mKeyedCppSourceBlocks.find(key);
    return itr != mKeyedCppSourceBlocks.end() ? &itr->second : mpParent ? mpParent->get_cpp_source_block(key) : nullptr;
}

void CppSourceBlockEx::set_cpp_source_blocks(const std::vector<CppSourceBlockEx>& cppSourceBlocks)
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
