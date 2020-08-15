
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-file.pair.hpp"

#include <string>

namespace dst {
namespace cppgen {

CppFile::Pair::Pair(
    const std::filesystem::path& includePath,
    const std::filesystem::path& headerFilePath,
    const std::filesystem::path& sourceFilePath
)
    : hpp(includePath / headerFilePath, Declaration)
    , cpp(sourceFilePath, Definition)
{
    // hpp << "pragma once\n";
    // cpp << "#include \"" << (includePath / headerFilePath).str() << "\"\n";
}

CppFile::Pair::~Pair()
{
    // cppCompileGuards.generate(hpp, Open);
    // cppCompileGuards.generate(cpp, Close);
}

} // namespace cppgen
} // namespace dst
