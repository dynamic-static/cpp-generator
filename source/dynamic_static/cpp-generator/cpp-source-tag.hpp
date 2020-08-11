
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

namespace dst {
namespace cppgen {

class CppSourceTag final
    : public CppSourceElement
{
public:
    enum class Type
    {
        Invidual,
        RegionBegin,
        RegionEnd,
    };

    CppSourceTag() = default;
    CppSourceTag(std::string_view cppSource, Type type);
    CppSourceTag(std::string_view cppSource, size_t begin);
    CppSourceTag(const CppSourceTag& other);
    CppSourceTag(CppSourceTag&& other);
    CppSourceTag& operator=(const CppSourceTag& other);
    CppSourceTag& operator=(CppSourceTag&& other);
    std::unique_ptr<CppSourceElement> clone() const override final;
    Type get_type() const;
    size_t get_begin_index(std::string_view cppSource = { }) const override final;
    size_t get_end_index(std::string_view cppSource = { }) const override final;
    std::string str(std::string_view cppSource) const override final;
    std::string process_cpp_source(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const override final;

private:
    Type mType { Type::Invidual };
    size_t mBegin { 0 };
    size_t mEnd { std::string::npos };
};

} // namespace cppgen
} // namespace dst
