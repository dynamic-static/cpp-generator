
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
#include "source-element.hpp"

#include <string>
#include <string_view>
#include <unordered_map>

namespace dst {
namespace cppgen {

class SourceBlock;
class StreamWriter;

class SourceTag final
    : public SourceElement
{
public:
    enum class Type
    {
        Invalid,
        Replacement,
        RegionBegin,
        RegionEnd,
    };

    SourceTag() = default;
    SourceTag(std::string_view source, Type type);
    SourceTag(std::string_view source, size_t begin);
    Type get_type() const;
    const std::string& get_key() const override final;
    size_t get_begin_index() const override final;
    size_t get_end_index() const override final;
    const std::string& get_option(const std::string& key) const override final;
    const std::unordered_map<std::string, std::string>& get_options() const;
    void process_source(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmFormatter) const;

private:
    void parse_options(std::string_view options);
    void parse_option(std::string_view option);
    void add_option(std::string_view key, std::string_view value);
    bool validate_option_key(std::string_view key);
    bool validate_option_value(std::string_view value);

    Type mType { Type::Invalid };
    std::string mKey;
    size_t mBegin { 0 };
    size_t mEnd { std::string::npos };
    std::unordered_map<std::string, std::string> mOptions;
};

} // namespace cppgen
} // namespace dst
