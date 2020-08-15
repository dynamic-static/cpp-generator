
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-file.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppFile::Pair final
{
public:
    /**
    TODO : Documentation
    */
    Pair() = default;

    /**
    TODO : Documentation
    */
    Pair(
        const std::filesystem::path& includePath,
        const std::filesystem::path& headerFilePath,
        const std::filesystem::path& sourceFilePath
    );

    std::string header;                           //!< TODO : Documentation
    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    CppFile hpp;                                  //!< TODO : Documentation
    CppFile cpp;                                  //!< TODO : Documentation
};

} // namespace cppgen
} // namespace dst
