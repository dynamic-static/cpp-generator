
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

CppFile::CppFile(const std::filesystem::path& filePath, CppGenerationFlags cppGenerationFlags)
    : mFilePath { filePath }
    , mCppGenerationFlags { cppGenerationFlags }
{
}

CppFile::~CppFile()
{
    std::stringstream content;
    cppCompileGuards.generate(content, Open);
    content << mContent.str();
    cppCompileGuards.generate(content, Close);
}

} // namespace cppgen
} // namespace dst
