
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

#include <ostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

namespace dst {
namespace cppgen {

class StreamWriter final
    : public std::streambuf
{
public:
    StreamWriter(std::ostream& ostrm);
    ~StreamWriter();
    void begin_processing_tag();
    void end_processing_tag();

    template <typename T>
    inline std::ostream& operator<<(const T& obj)
    {
        return mOstrm << obj;
    }

private:
    class Line final
    {
    public:
        size_t size { 0 };
        size_t indentation { 0 };
        size_t trailingWhitespace { 0 };
        std::stringstream content;
        bool isWhitespace { true };
        bool containsTag { false };
    };

    int overflow(int c) override final;

    std::ostream& mOstrm;
    std::streambuf* mpStrmBuf { nullptr };
    size_t mIndentation { std::string::npos };
    std::vector<Line> mLines;
    bool mTagActive { false };

    StreamWriter(const StreamWriter&) = delete;
    StreamWriter& operator=(const StreamWriter&) = delete;
};

} // namespace cppgen
} // namespace dst
