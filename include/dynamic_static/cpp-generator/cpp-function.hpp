
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-element-collection.hpp"
#include "dynamic_static/cpp-generator/cpp-parameter.hpp"
#include "dynamic_static/cpp-generator/cpp-source-block.hpp"
#include "dynamic_static/cpp-generator/cpp-template.hpp"
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
class CppFunction final
    : public IGeneratable
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    CppFunction(
        CppAccessModifier cppAccessModifier = { Unspecified },
        const std::vector<std::string>& cppCompileGuards = { },
        const CppTemplate& cppTemplate = { },
        std::string_view cppReturnType = { },
        std::string_view cppName = { },
        const CppParameter::Collection& cppParameters = { },
        CppFlags cppFlags = { },
        CppSourceBlock cppSourceBlock = { }
    );

    /**
    TODO : Documentation
    */
    CppFunction(
        std::string_view cppReturnType = { },
        std::string_view cppName = { },
        const CppParameter::Collection& cppParameters = { },
        CppSourceBlock cppSourceBlock = { }
    );

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppFlags cppFlags) const override final;

    CppAccessModifier cppAccessModifier { Unspecified }; //!< TODO : Documentation
    std::vector<std::string> cppCompileGuards;           //!< TODO : Documentation
    CppTemplate cppTemplate;                             //!< TODO : Documentation
    std::string cppReturnType;                           //!< TODO : Documentation
    std::string cppName;                                 //!< TODO : Documentation
    CppParameter::Collection cppParameters;              //!< TODO : Documentation
    CppFlags cppFlags { };                               //!< TODO : Documentation
    CppSourceBlock cppSourceBlock;                       //!< TODO : Documentation
};

/**
TODO : Documentation
*/
class CppFunction::Collection final
    : public CppElementCollection<CppFunction>
{
public:
    using CppElementCollection<CppFunction>::CppElementCollection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppFlags cppFlags) const override final;
};

} // namespace cppgen
} // namespace dst
