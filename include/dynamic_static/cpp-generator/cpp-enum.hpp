
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
#include <vector>

namespace dst {
namespace cppgen {

class CppEnumerator final
{
public:
    // TODO : CppCompileGuard::Collection cppCompileGuards;
    std::string cppName;  //!< TODO : Documentation
    std::string cppValue; //!< TODO : Documentation
};

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

    // TODO : CppCompileGuard::Collection cppCompileGuards;
    Type cppType { Type::Unscoped };           //!< TODO : Documentation
    std::string cppBaseType;                   //!< TODO : Documentation
    std::vector<CppEnumerator> cppEnumerators; //!< TODO : Documentation
};

} // namespace cppgen
} // namespace dst
