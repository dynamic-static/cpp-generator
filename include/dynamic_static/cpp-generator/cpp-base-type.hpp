
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>
#include <string_view>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppBaseType final
    : public CppElement
{
public:
    class CppBaseTypes;

    /**
    TODO : Documentation
    */
    CppBaseType(CppFlags cppFlags, CppAccessSpecifier cppAccessSpecifier, std::string_view cppName);

    /**
    TODO : Documentation
    */
    CppBaseType(CppAccessSpecifier cppAccessSpecifier, std::string_view cppName);

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppFlags cppFlags { 0 };                          //!< TODO : Documentation
    CppAccessSpecifier cppAccessSpecifier { Public }; //!< TODO : Documentation
    std::string cppName;                              //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppBaseTypes final
    : public CppElement::Collection<CppBaseType>
{
public:
    using CppElement::Collection<CppBaseType>::Collection;

    /**
    TODO : Documentation
        @note Supports CppGenerationFlagBits [Open || Close]
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

} // namespace cppgen
} // namespace dst
