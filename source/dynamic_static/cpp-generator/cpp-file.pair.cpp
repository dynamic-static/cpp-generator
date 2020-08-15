
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
    : hpp(includePath / headerFilePath)
    , cpp(sourceFilePath)
{
}

CppFile::Pair::~Pair()
{
    std::stringstream content;
    content << header << '\n';
    cppCompileGuards.generate(content, Open);
    cppCompileGuards.generate(content, Close);
    content << '\n';
}

} // namespace cppgen
} // namespace dst
