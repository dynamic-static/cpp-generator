
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-source-block.hpp"
#include "cpp-source-element.hpp"
#include "cpp-source-tag.hpp"

#include <memory>
#include <vector>

namespace dst {
namespace cppgen {

class CppSourceRegion final
    : public CppSourceElement
{
public:
    CppSourceRegion() = default;
    CppSourceRegion(std::string_view cppSource);
    CppSourceRegion(std::string_view cppSource, const CppSourceTag& beginTag);
    CppSourceRegion(const CppSourceRegion& other);
    CppSourceRegion(CppSourceRegion&& other);
    CppSourceRegion& operator=(const CppSourceRegion& other);
    CppSourceRegion& operator=(CppSourceRegion&& other);
    std::unique_ptr<CppSourceElement> clone() const override final;
    size_t get_begin_index(std::string_view cppSource) const override final;
    size_t get_content_begin_index(std::string_view cppSource) const override final;
    size_t get_content_end_index(std::string_view cppSource) const override final;
    size_t get_end_index(std::string_view cppSource) const override final;
    std::string str(std::string_view cppSource) const override final;
    std::string process_cpp_source(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const override final;

private:
    std::string process_cpp_source_elements(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const;
    CppSourceTag mBeginTag;
    std::vector<std::unique_ptr<CppSourceElement>> mElementPtrs;
    CppSourceTag mEndTag;
};

} // namespace cppgen
} // namespace dst
