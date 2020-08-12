
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

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppVariable final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    CppVariable(
        std::string_view cppType = { },
        std::string_view cppName = { },
        std::string_view cppValue = { }
    );

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType = { }) const override final;

    std::string cppType;  //!< TODO : Documentation
    std::string cppName;  //!< TODO : Documentation
    std::string cppValue; //!< TODO : Documentation
};

#if 0
/**
TODO : Documentation
*/
class CppVariable::Collection final
    : public CppElementCollection<CppVariable>
{
public:
    using CppElementCollection<CppVariable>::CppElementCollection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType = { }) const override final;
};
#endif

} // namespace cppgen
} // namespace dst
