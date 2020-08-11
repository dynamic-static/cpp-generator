
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-source-block.option.hpp"

#include <algorithm>
#include <utility>

namespace dst {
namespace cppgen {

CppSourceBlock::Option::Option(std::string_view name, std::string_view value)
    : mName { name }
    , mValue { value }
{
}

CppSourceBlock::Option::Option(const Option& other)
{
    *this = other;
}

CppSourceBlock::Option::Option(Option&& other)
{
    *this = std::move(other);
}

CppSourceBlock::Option& CppSourceBlock::Option::operator=(const Option& other)
{
    mName = other.mName;
    mValue = other.mValue;
    return *this;
}

CppSourceBlock::Option& CppSourceBlock::Option::operator=(Option&& other)
{
    mName = std::move(other.mName);
    mValue = std::move(other.mValue);
    return *this;
}

const std::string& CppSourceBlock::Option::get_name() const
{
    return mName;
}

const std::string& CppSourceBlock::Option::get_value() const
{
    return mValue;
}

bool CppSourceBlock::Option::is_valid_name(std::string_view name)
{
    return
        !name.empty() &&
        std::all_of(name.begin(), name.end(),
            [](char c)
            {
                return
                    ('0' <= c && c <= '9') ||
                    ('A' <= c && c <= 'Z') ||
                    ('a' <= c && c <= 'z') ||
                    c == '_';
            }
    );
}

bool operator==(const CppSourceBlock::Option& lhs, const CppSourceBlock::Option& rhs)
{
    return lhs.mName == rhs.mName;
}

bool operator!=(const CppSourceBlock::Option& lhs, const CppSourceBlock::Option& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const CppSourceBlock::Option& lhs, const CppSourceBlock::Option& rhs)
{
    return lhs.mName < rhs.mName;
}

} // namespace cppgen
} // namespace dst
