
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
    virtual void generate(std::ostream& strm, CppGenerationFlags flags) const = 0;

    /**
    TODO : Documentation
    */
    std::string generate(CppGenerationFlags flags) const;
};

/**
TODO : Documentation
*/
template <typename CppElementType>
class CppElement::Collection
    : public CppElement
    , private std::vector<CppElementType>
{
public:
    using vector_type = std::vector<CppElementType>;
    using value_type = typename vector_type::value_type;
    using allocator_type = typename vector_type::allocator_type;
    using size_type = typename vector_type::size_type;
    using difference_type = typename vector_type::difference_type;
    using reference = typename vector_type::reference;
    using const_reference = typename vector_type::const_reference;
    using pointer = typename vector_type::pointer;
    using const_pointer = typename vector_type::const_pointer;
    using iterator = typename vector_type::iterator;
    using const_iterator = typename vector_type::const_iterator;
    using reverse_iterator = typename vector_type::reverse_iterator;
    using const_reverse_iterator = typename vector_type::const_reverse_iterator;

    using vector_type::vector;
    using vector_type::operator=;
    using vector_type::operator[];
    using vector_type::assign;
    using vector_type::get_allocator;
    using vector_type::at;
    using vector_type::front;
    using vector_type::back;
    using vector_type::data;
    using vector_type::begin;
    using vector_type::cbegin;
    using vector_type::end;
    using vector_type::cend;
    using vector_type::rbegin;
    using vector_type::crbegin;
    using vector_type::rend;
    using vector_type::crend;
    using vector_type::empty;
    using vector_type::size;
    using vector_type::max_size;
    using vector_type::reserve;
    using vector_type::capacity;
    using vector_type::shrink_to_fit;
    using vector_type::clear;
    using vector_type::insert;
    using vector_type::emplace;
    using vector_type::erase;
    using vector_type::push_back;
    using vector_type::emplace_back;
    using vector_type::pop_back;
    using vector_type::resize;
    using vector_type::swap;

    virtual ~Collection() = 0;

    inline friend bool operator==(const Collection<CppElementType>& lhs, const Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs == (const base_type&)rhs;
    }

    inline friend bool operator!=(const Collection<CppElementType>& lhs, const Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs != (const base_type&)rhs;
    }

    inline friend bool operator<(const Collection<CppElementType>& lhs, const Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs < (const base_type&)rhs;
    }

    inline friend bool operator>(const Collection<CppElementType>& lhs, const Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs > (const base_type&)rhs;
    }

    inline friend bool operator<=(const Collection<CppElementType>& lhs, const Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs <= (const base_type&)rhs;
    }

    inline friend bool operator>=(const Collection<CppElementType>& lhs, const Collection<CppElementType>& rhs)
    {
        return (const base_type&)lhs >= (const base_type&)rhs;
    }
};

template <typename CppElementType>
inline CppElement::Collection<CppElementType>::~Collection()
{
}

} // namespace cppgen
} // namespace dst
