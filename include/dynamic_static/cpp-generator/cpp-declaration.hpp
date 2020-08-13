
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

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppDeclaration final
    : public CppStringElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    CppDeclaration() = default;

    /**
    TODO : Documentation
    */
    template <typename T>
    inline CppDeclaration(const T& cppDeclaration)
        : CppStringElement(cppDeclaration)
    {
    }

    /**
    TODO : Documentation
    */
    template <typename T>
    inline CppDeclaration(const CppCompileGuard::Collection& cppCompileGuards, const T& cppDeclaration)
        : CppStringElement(cppDeclaration)
        , cppCompileGuards { cppCompileGuards }
    {
    }

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Declaration]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppDeclaration::Collection final
    : public CppElement::Collection<CppDeclaration>
{
public:
    using CppElement::Collection<CppDeclaration>::Collection;

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Declaration]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
using CppDeclarations = CppDeclaration::Collection;

} // namespace cppgen
} // namespace dst
