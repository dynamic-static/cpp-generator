
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <filesystem>
#include <sstream>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppFile final
{
public:
    class Pair;

    /**
    TODO : Documentation
    */
    CppFile() = default;

    /**
    TODO : Documentation
    */
    CppFile(const std::filesystem::path& filePath);

    /**
    TODO : Documentation
    */
    ~CppFile();

    std::string header;                           //!< TODO : Documentation
    bool pragmaOnce { false };                    //!< TODO : Documentation
    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation

private:
    std::filesystem::path mFilePath;
    std::stringstream mContent;
};

} // namespace cppgen
} // namespace dst
