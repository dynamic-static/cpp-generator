
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
#include "dynamic_static/cpp-generator/cpp-enumerator.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppEnum final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    enum class Type
    {
        Unscoped, //!< TODO : Documentation
        Scoped,   //!< TODO : Documentation
    };

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    Type cppType { Type::Unscoped };              //!< TODO : Documentation
    std::string cppBaseType;                      //!< TODO : Documentation
    CppEnumerator::Collection cppEnumerators;     //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppEnum::Collection final
    : public CppElement::Collection<CppEnum>
{
public:
    using CppElement::Collection<CppEnum>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

} // namespace cppgen
} // namespace dst
