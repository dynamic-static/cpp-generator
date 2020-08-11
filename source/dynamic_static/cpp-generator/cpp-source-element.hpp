
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
#include "dynamic_static/cpp-generator/cpp-source-block.option.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

namespace dst {
namespace cppgen {

class CppSourceElement
{
public:
    CppSourceElement() = default;
    virtual ~CppSourceElement() = 0;
    CppSourceElement(const CppSourceElement& other);
    CppSourceElement(CppSourceElement&& other);
    CppSourceElement& operator=(const CppSourceElement& other);
    CppSourceElement& operator=(CppSourceElement&& other);
    virtual std::unique_ptr<CppSourceElement> clone() const = 0;
    const std::string& get_key() const;
    const std::string& get_cpp_source_block_option_value(std::string_view optionName) const;
    virtual size_t get_begin_index(std::string_view cppSource = { }) const = 0;
    virtual size_t get_content_begin_index(std::string_view cppSource) const;
    virtual size_t get_content_end_index(std::string_view cppSource) const;
    virtual size_t get_end_index(std::string_view cppSource = { }) const = 0;
    bool empty() const;
    virtual std::string str(std::string_view cppSource) const = 0;
    virtual std::string process_cpp_source(std::string_view cppSource, const CppSourceBlock& cppSourceBlock) const = 0;

protected:
    void parse_options(std::string_view cppSource, size_t offset, size_t size);
    void parse_option(std::string_view cppSource, size_t offset, size_t size);
    void add_option(CppSourceBlock::Option&& option);
    void take_options(CppSourceElement& other);
    std::string mKey;
    std::map<std::string, CppSourceBlock::Option, std::less<>> mOptions;
};

} // namespace cppgen
} // namespace dst
