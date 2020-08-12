
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

#include <iosfwd>
#include <string>
#include <string_view>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppParameter final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    CppParameter(
        std::string_view cppType = { },
        std::string_view cppName = { },
        std::string_view cppValue = { }
    );

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    std::string cppType;  //!< TODO : Documentation
    std::string cppName;  //!< TODO : Documentation
    std::string cppValue; //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppParameter::Collection final
    : public CppElement::Collection<CppParameter>
{
public:
    using CppElement::Collection<CppParameter>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
using CppParameters = CppParameter::Collection;

} // namespace cppgen
} // namespace dst
