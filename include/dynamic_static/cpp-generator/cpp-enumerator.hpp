
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"
#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppEnumerator final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    CppEnumerator() = default;

    /**
    TODO : Documentation
    */
    template <typename T, typename U = typename T>
    inline CppEnumerator(const T& cppName, const U& cppValue = { })
        : cppName { cppName }
        , cppValue { cppValue }
    {
    }

    /**
    TODO : Documentation
    */
    template <typename T, typename U = typename T>
    inline CppEnumerator(const CppCompileGuard::Collection& cppCompileGuards, const T& cppName, const U& cppValue = { })
        : cppCompileGuards { cppCompileGuards }
        , cppName { cppName }
        , cppValue { cppValue }
    {
    }

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Declaration]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    std::string cppName;                          //!< TODO : Documentation
    std::string cppValue;                         //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppEnumerator::Collection final
    : public CppElement::Collection<CppEnumerator>
{
public:
    using CppElement::Collection<CppEnumerator>::Collection;

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Declaration]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
using CppEnumerators = CppEnumerator::Collection;

} // namespace cppgen
} // namespace dst
