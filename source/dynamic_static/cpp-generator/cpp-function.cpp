
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-function.hpp"

namespace dst {
namespace cppgen {

CppFunction::CppFunction(
    CppAccessModifier cppAccessModifier = { Unspecified },
    const std::vector<std::string>& cppCompileGuards = { },
    const CppTemplate& cppTemplate = { },
    std::string_view cppReturnType = { },
    std::string_view cppName = { },
    const CppParameter::Collection& cppParameters = { },
    CppFlags cppFlags = { },
    CppSourceBlock cppSourceBlock = { }
)
    : cppAccessModifier { cppAccessModifier }
    , cppCompileGuards { cppCompileGuards }
    , cppTemplate { cppTemplate }
    , cppReturnType { cppReturnType }
    , cppName { cppName }
    , cppParameters { cppParameters }
    , cppFlags { cppFlags }
    , cppSourceBlock { cppSourceBlock }
{
}

CppFunction::CppFunction(
    std::string_view cppReturnType = { },
    std::string_view cppName = { },
    const CppParameter::Collection& cppParameters = { },
    CppSourceBlock cppSourceBlock = { }
)
    : cppReturnType { cppReturnType }
    , cppName { cppName }
    , cppParameters { cppParameters }
    , cppSourceBlock { cppSourceBlock }
{
}

void CppFunction::generate(std::ostream& strm, CppFlags cppFlags) const
{

}

void CppFunction::Collection::generate(std::ostream& strm, CppFlags cppFlags) const
{

}

} // namespace cppgen
} // namespace dst
