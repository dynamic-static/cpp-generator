
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
#include <string>
#include <string_view>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppElement
{
public:
    template <typename CppElementType>
    class Collection;

    /**
    TODO : Documentation
    */
    virtual ~CppElement() = 0;

    /**
    TODO : Documentation
    */
    virtual void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType = { }) const = 0;
};

/**
TODO : Documentation
*/
std::string to_string(const CppElement& cppElement, CppFlags flags, std::string_view cppEnclosingType = { });

/**
TODO : Documentation
*/
template <typename CppElementType>
class CppElement::Collection
    : public CppElement
    , private std::vector<CppElementType>
{
public:
    using base_type = std::vector<CppElementType>;
    using value_type = typename base_type::value_type;
    using allocator_type = typename base_type::allocator_type;
    using size_type = typename base_type::size_type;
    using difference_type = typename base_type::difference_type;
    using reference = typename base_type::reference;
    using const_reference = typename base_type::const_reference;
    using pointer = typename base_type::pointer;
    using const_pointer = typename base_type::const_pointer;
    using iterator = typename base_type::iterator;
    using const_iterator = typename base_type::const_iterator;
    using reverse_iterator = typename base_type::reverse_iterator;
    using const_reverse_iterator = typename base_type::const_reverse_iterator;

    using base_type::vector;
    using base_type::operator=;
    using base_type::operator[];
    using base_type::assign;
    using base_type::get_allocator;
    using base_type::at;
    using base_type::front;
    using base_type::back;
    using base_type::data;
    using base_type::begin;
    using base_type::cbegin;
    using base_type::end;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::crbegin;
    using base_type::rend;
    using base_type::crend;
    using base_type::empty;
    using base_type::size;
    using base_type::max_size;
    using base_type::reserve;
    using base_type::capacity;
    using base_type::shrink_to_fit;
    using base_type::clear;
    using base_type::insert;
    using base_type::emplace;
    using base_type::erase;
    using base_type::push_back;
    using base_type::emplace_back;
    using base_type::pop_back;
    using base_type::resize;
    using base_type::swap;

    virtual ~Collection() = 0;

    template <typename T>
    const std::string& as() const
    {
        static_assert(std::is_same_v<T, base_type>, "TODO : Documentation");
        return (const base_type&)*this;
    }

    template <typename T>
    std::string& as()
    {
        static_assert(std::is_same_v<T, base_type>, "TODO : Documentation");
        return (const base_type&)*this;
    }

    inline friend bool operator==(const CppElement::Collection<CppElementType>& lhs, const CppElement::Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs == (const base_type&)rhs;
    }

    inline friend bool operator!=(const CppElement::Collection<CppElementType>& lhs, const CppElement::Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs != (const base_type&)rhs;
    }

    inline friend bool operator<(const CppElement::Collection<CppElementType>& lhs, const CppElement::Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs < (const base_type&)rhs;
    }

    inline friend bool operator>(const CppElement::Collection<CppElementType>& lhs, const CppElement::Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs > (const base_type&)rhs;
    }

    inline friend bool operator<=(const CppElement::Collection<CppElementType>& lhs, const CppElement::Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs <= (const base_type&)rhs;
    }

    inline friend bool operator>=(const CppElement::Collection<CppElementType>& lhs, const CppElement::Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs >= (const base_type&)rhs;
    }
};

template <typename CppElementType>
inline CppElement::Collection<CppElementType>::~Collection()
{
}

/**
TODO : Documentation
*/
template <typename CppElementCollectionType>
inline void append(CppElementCollectionType& lhs, const CppElementCollectionType& rhs)
{
    lhs.insert(lhs.end(), rhs.begin(), rhs.end());
}

/**
TODO : Documentation
*/
class CppStringElement
    : public CppElement
    , private std::string
{
public:
    using base_type = std::string;
    using traits_type = base_type::traits_type;
    using value_type = base_type::value_type;
    using allocator_type = base_type::allocator_type;
    using size_type = base_type::size_type;
    using difference_type = base_type::difference_type;
    using reference = base_type::reference;
    using const_reference = base_type::const_reference;
    using pointer = base_type::pointer;
    using const_pointer = base_type::const_pointer;
    using iterator = base_type::iterator;
    using const_iterator = base_type::const_iterator;
    using reverse_iterator = base_type::reverse_iterator;
    using const_reverse_iterator = base_type::const_reverse_iterator;
    static constexpr auto npos { (size_type)-1 };

    using base_type::basic_string;
    using base_type::operator=;
    using base_type::operator+=;
    using base_type::operator[];
    using base_type::assign;
    using base_type::get_allocator;
    using base_type::at;
    using base_type::front;
    using base_type::back;
    using base_type::data;
    using base_type::c_str;
    using base_type::begin;
    using base_type::cbegin;
    using base_type::end;
    using base_type::cend;
    using base_type::rbegin;
    using base_type::crbegin;
    using base_type::rend;
    using base_type::crend;
    using base_type::empty;
    using base_type::size;
    using base_type::length;
    using base_type::max_size;
    using base_type::reserve;
    using base_type::capacity;
    using base_type::shrink_to_fit;
    using base_type::clear;
    using base_type::insert;
    using base_type::erase;
    using base_type::push_back;
    using base_type::pop_back;
    using base_type::append;
    using base_type::compare;
    using base_type::replace;
    using base_type::substr;
    using base_type::copy;
    using base_type::resize;
    using base_type::swap;
    using base_type::find;
    using base_type::rfind;
    using base_type::find_first_of;
    using base_type::find_first_not_of;
    using base_type::find_last_of;
    using base_type::find_last_not_of;

    CppStringElement(const base_type& other);
    CppStringElement(const std::string_view& other);
    CppStringElement(base_type&& other);
    CppStringElement& operator=(const base_type& other);
    CppStringElement& operator=(const std::string_view& other);
    CppStringElement& operator=(base_type&& other);

    virtual ~CppStringElement() = 0;

    template <typename T>
    const std::string& as() const
    {
        static_assert(std::is_same_v<T, base_type>, "TODO : Documentation");
        return (const base_type&)*this;
    }

    template <typename T>
    std::string& as()
    {
        static_assert(std::is_same_v<T, base_type>, "TODO : Documentation");
        return (const base_type&)*this;
    }

    friend bool operator==(const CppStringElement& lhs, const CppStringElement& rhs);
    friend bool operator!=(const CppStringElement& lhs, const CppStringElement& rhs);
    friend bool operator<(const CppStringElement& lhs, const CppStringElement& rhs);
    friend bool operator>(const CppStringElement& lhs, const CppStringElement& rhs);
    friend bool operator<=(const CppStringElement& lhs, const CppStringElement& rhs);
    friend bool operator>=(const CppStringElement& lhs, const CppStringElement& rhs);
    friend std::ostream& operator<<(std::ostream& strm, const CppStringElement& cppStringElement);
};

} // namespace cppgen
} // namespace dst
