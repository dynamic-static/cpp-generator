
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "source-tag.hpp"
#include "dynamic_static/cpp-generator/source-block.hpp"
#include "stream-writer.hpp"
#include "string.hpp"

#include <algorithm>
#include <cctype>

namespace dst {
namespace cppgen {

SourceTag::SourceTag(std::string_view source, Type type)
    : mType { type }
    , mBegin { mType == Type::RegionBegin ? 0 : source.size() }
    , mEnd { mType == Type::RegionBegin ? 0 : source.size() }
{
    dst_cppgen_assert(mType != Type::Invalid);
    dst_cppgen_assert(mType != Type::Replacement);
}

SourceTag::SourceTag(std::string_view source, size_t begin)
    : mBegin { begin }
    , mEnd { mBegin + 1 }
{
    static const std::string EmptyTag = "${}";
    if (EmptyTag.size() <= source.size() - mBegin) {
        auto openBrace = source[mBegin + 1];
        auto closeBrace = openBrace == '{' ? '}' : openBrace == '<' ? '>' : '\0';
        if (closeBrace) {
            mEnd = std::min(find_unquoted({ source, mEnd }, closeBrace), source.size());
            if (mEnd < source.size()) {
                mType = openBrace == '{' ? Type::Replacement : source[mBegin + 2] != '/' ? Type::RegionBegin : Type::RegionEnd;
                auto optionsBegin = mBegin + 1 + (int)(mType == Type::RegionEnd) + 1;
                auto optionsEnd = mEnd++;
                parse_options(source.substr(optionsBegin, optionsEnd - optionsBegin));
            } else {
                mErrors.push_back("tag open brace '" + std::string(1, openBrace) + "' encountered without matching close brace '" + std::string(1, closeBrace) + "'; are there unmatched '\"' or '`' characters in the input source?");
            }
        }
    }
}

SourceTag::Type SourceTag::get_type() const
{
    return mType;
}

const std::string& SourceTag::get_key() const
{
    return mKey;
}

size_t SourceTag::get_begin_index() const
{
    return mBegin;
}

size_t SourceTag::get_end_index() const
{
    return mEnd;
}

const std::string& SourceTag::get_option(const std::string& key) const
{
    static const std::string EmptyValue;
    auto itr = mOptions.find(key);
    return itr != mOptions.end() ? itr->second : EmptyValue;
}

const std::unordered_map<std::string, std::string>& SourceTag::get_options() const
{
    return mOptions;
}

void SourceTag::process_source(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmWriter) const
{
    strmWriter.begin_processing_tag();
    if (!sourceBlock.get_value().empty()) {
        strmWriter << get_option("head");
        strmWriter << sourceBlock.get_value();
        strmWriter << get_option("tail");
    }
    strmWriter.end_processing_tag();
}

void SourceTag::parse_options(std::string_view options)
{
    while (!options.empty()) {
        auto split = std::min(find_unquoted(options, ':'), options.size());
        parse_option(options.substr(0, split));
        options.remove_prefix(std::min(split + 1, options.size()));
    }
}

void SourceTag::parse_option(std::string_view option)
{
    if (!option.empty()) {
        auto split = std::min(find_unquoted(option, '='), option.size());
        auto key = option;
        key.remove_suffix(option.size() - split);
        key = trim_whitespace(key);
        auto value = option;
        value.remove_prefix(std::min(split + 1, option.size()));
        value = trim_whitespace(value);
        if (value.empty() && quoted(key)) {
            std::swap(key, value);
        }
        add_option(key, value);
    }
}

void SourceTag::add_option(std::string_view key, std::string_view value)
{
    if (validate_option_key(key) && validate_option_value(value)) {
        if (value.empty()) {
            if (mKey.empty()) {
                mKey = key;
            } else {
                mErrors.push_back("tag contains multiple keys [ " + mKey + ", " + std::string(key) + " ]; a tag may only have one key");
            }
        } else {
            if (key.empty()) {
                switch (mType) {
                case Type::Replacement: key = mKey.empty() ? "head" : "tail"; break;
                case Type::RegionBegin: key = mKey.empty() ? "head" : "seperator"; break;
                case Type::RegionEnd: key = "tail"; break;
                default: dst_cppgen_assert(mType != Type::Invalid); break;
                }
            }
            if (!mOptions.insert({ std::string(key), unquote(value) }).second) {
                mErrors.push_back("tag contains multiple options with the same key [ " + std::string(key) + " ]; option keys must be unique within a tag");
            }
        }
    }
}

bool SourceTag::validate_option_key(std::string_view key)
{
    if (!std::all_of(key.begin(), key.end(), [](unsigned char c) { return isalnum(c) || c == '_'; })) {
        mErrors.push_back("option key [ " + std::string(key) + " ] contains invalid character(s); option keys may contain '_' and alphanumeric characters");
        return false;
    }
    return true;
}

bool SourceTag::validate_option_value(std::string_view value)
{
    if (!value.empty() && !quoted(value)) {
        mErrors.push_back("option value [ " + std::string(value) + " ] must be enclosed in '\"' or '`' characters");
        return false;
    }
    return true;
}

} // namespace cppgen
} // namespace dst
