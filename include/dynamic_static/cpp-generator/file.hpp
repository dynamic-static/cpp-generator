
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/defines.hpp"

#include <filesystem>
#include <sstream>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class File final
    : public std::stringstream
{
public:
    /**
    TODO : Documentation
    */
    File(const std::filesystem::path& filePath);

    /**
    TODO : Documentation
    */
    ~File();

private:
    std::filesystem::path mFilePath;
};

} // namespace cppgen
} // namespace dst
