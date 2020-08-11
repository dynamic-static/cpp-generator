
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "cpp-source-element.hpp"
#include "string.hpp"

#include <algorithm>
#include <utility>

namespace dst {
namespace cppgen {

CppSourceElement::~CppSourceElement()
{
}

CppSourceElement::CppSourceElement(const CppSourceElement& other)
{
    *this = other;
}

CppSourceElement::CppSourceElement(CppSourceElement&& other)
{
    *this = std::move(other);
}

CppSourceElement& CppSourceElement::operator=(const CppSourceElement& other)
{
    mKey = other.mKey;
    mOptions = other.mOptions;
    return *this;
}

CppSourceElement& CppSourceElement::operator=(CppSourceElement&& other)
{
    mKey = std::move(other.mKey);
    mOptions = std::move(other.mOptions);
    return *this;
}

const std::string& CppSourceElement::get_key() const
{
    return mKey;
}

const std::string& CppSourceElement::get_cpp_source_block_option_value(std::string_view optionName) const
{
    static const std::string EmptyStr { };
    auto itr = mOptions.find(optionName);
    return itr != mOptions.end() ? itr->second.get_value() : EmptyStr;
}

size_t CppSourceElement::get_content_begin_index(std::string_view) const
{
    return get_begin_index();
}

size_t CppSourceElement::get_content_end_index(std::string_view) const
{
    return get_end_index();
}

bool CppSourceElement::empty() const
{
    dst_cppgen_assert(get_begin_index() <= get_end_index());
    return get_begin_index() == get_end_index();
}

void CppSourceElement::parse_options(std::string_view cppSource, size_t offset, size_t size)
{
    string::Segment options(cppSource, offset, size);
    while (options.begin < options.end) {
        auto split = std::min(string::find(cppSource, ':', options.begin, options.size()), options.end);
        parse_option(cppSource, options.begin, split - options.begin);
        options.begin = split + 1;
    }
}

void CppSourceElement::parse_option(std::string_view cppSource, size_t offset, size_t size)
{
    string::Segment option(cppSource, offset, size);
    if (!option.empty()) {
        auto split = std::min(string::find(cppSource, '=', option.begin, option.size()), option.end);
        auto name = string::trim_whitespace(cppSource, { cppSource, option.begin, split - option.begin });
        if (CppSourceBlock::Option::is_valid_name(name.str_view(cppSource))) {
            if (split == option.end) {
                if (mKey.empty()) {
                    mKey = name.str_view(cppSource);
                } else {
                    assert(false && "TODO : Error handling");
                }
            } else {
                auto value = string::trim_whitespace(cppSource, { cppSource, split + 1, option.end - (split + 1) });
                if (!value.empty()) {
                    auto openQuote = cppSource[value.begin] == '"';
                    auto closeQuote = cppSource[value.end - 1] == '"' && 1 < value.size();
                    if (openQuote == closeQuote) {
                        if (openQuote && closeQuote) {
                            add_option({ name.str_view(cppSource), string::unquote(cppSource, value) });
                        } else {
                            assert(false && "TODO : Error handling");
                        }
                    } else {
                        assert(false && "TODO : Error handling");
                    }
                } else {
                    assert(false && "TODO : Error handling");
                }
            }
        } else {
            assert(false && "TODO : Error handling");
        }
    }
}

void CppSourceElement::add_option(CppSourceBlock::Option&& option)
{
    if (!mOptions.insert({ option.get_name(), std::move(option) }).second) {
        assert(false && "TODO : Error handling");
    }
}

void CppSourceElement::take_options(CppSourceElement& other)
{
    while (!other.mOptions.empty()) {
        auto node = other.mOptions.extract(other.mOptions.begin());
        if (!mOptions.insert(std::move(node)).inserted) {
            assert(false && "TODO : Error handling");
        }
    }
}

} // namespace cppgen
} // namespace dst
