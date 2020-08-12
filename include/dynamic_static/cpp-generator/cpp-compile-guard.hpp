
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
class CppCompileGuard final
    : public CppElement
{
public:
    class Collection;

    CppCompileGuard() = default;
    CppCompileGuard(const std::string& str)
        : mStr { str }
    {
    }

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

private:
    std::string mStr;
};

/**
TODO : Documentation
*/
class CppCompileGuard::Collection final
    : public CppElement::Collection<CppCompileGuard>
{
public:
    using CppElement::Collection<CppCompileGuard>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
using CppCompileGuards = CppCompileGuard::Collection;

} // namespace cppgen
} // namespace dst
