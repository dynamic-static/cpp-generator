
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/file.hpp"

#include <fstream>
#include <iterator>

namespace dst {
namespace cppgen {

File::File(const std::filesystem::path& filePath)
    : mFilePath { filePath }
{
}

File::~File()
{
    if (!mFilePath.empty()) {
        std::filesystem::create_directories(mFilePath.parent_path());
        auto content = str();
        if (content != std::string(std::istreambuf_iterator<char>(std::ifstream(mFilePath)), { })) {
            std::ofstream(mFilePath) << content;
        }
    }
}

} // namespace cppgen
} // namespace dst
