
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/cpp-file.hpp"

#include <string>

namespace dst {
namespace cppgen {

CppFile::CppFile(const std::filesystem::path& filePath)
    : mFilePath { filePath }
{
}

CppFile::~CppFile()
{
    std::stringstream content;
    content << header << '\n';
    content << (pragmaOnce ? "#pragma once\n\n" : "");
    cppCompileGuards.generate(content, Open);
    content << mContent.str();
    cppCompileGuards.generate(content, Close);
    content << '\n';
}

} // namespace cppgen
} // namespace dst
