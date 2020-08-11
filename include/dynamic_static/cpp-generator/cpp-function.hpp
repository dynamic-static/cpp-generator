
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

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppFunction final
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, Flags flags) const;

    Flags flags { };                        //!< TODO : Documentation
    CppTemplate cppTemplate;                //!< TODO : Documentation
    std::string cppReturnType;              //!< TODO : Documentation
    std::string cppName;                    //!< TODO : Documentation
    CppParameter::Collection cppParameters; //!< TODO : Documentation
    CppSourceBlock cppSourceBlock;          //!< TODO : Documentation
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
    void generate(std::ostream& strm, Flags flags) const override final;
};

} // namespace cppgen
} // namespace dst
