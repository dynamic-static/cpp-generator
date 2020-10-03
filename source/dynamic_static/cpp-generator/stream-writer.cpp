
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "stream-writer.hpp"

#include <algorithm>
#include <string_view>

namespace dst {
namespace cppgen {

StreamWriter::StreamWriter(std::ostream& ostrm)
    : mOstrm { ostrm }
    , mpStrmBuf { ostrm.rdbuf() }
    , mIndentation { std::string::npos }
    , mLines(1)
{
    mOstrm.rdbuf(this);
}

StreamWriter::~StreamWriter()
{
    mOstrm.rdbuf(mpStrmBuf);
    if (mIndentation == std::string::npos) {
        mIndentation = 0;
    }
    for (const auto& line : mLines) {
        if (!line.isWhitespace) {
            auto str = line.content.str();
            std::string_view strView = str;
            dst_cppgen_assert(mIndentation < strView.size());
            strView.remove_prefix(mIndentation);
            strView.remove_suffix(line.trailingWhitespace);
            mOstrm << strView;
        } else
        if (!line.containsTag) {
            mOstrm << '\n';
        }
    }
}

void StreamWriter::begin_processing_tag()
{
    mTagActive = true;
    dst_cppgen_assert(!mLines.empty());
    mLines.back().containsTag = true;
}

void StreamWriter::end_processing_tag()
{
    mTagActive = false;
}

int StreamWriter::overflow(int c)
{
    dst_cppgen_assert(!mLines.empty());
    auto& line = mLines.back();
    line.content << (char)c;
    ++line.size;
    if (c == '\n') {
        auto previousLineIndentation = line.indentation;
        mLines.push_back({ });
        auto& newLine = mLines.back();
        if (mTagActive) {
            newLine.containsTag = true;
            newLine.size = previousLineIndentation;
            newLine.indentation = previousLineIndentation;
            std::fill_n(std::ostream_iterator<char>(newLine.content), previousLineIndentation, ' ');
        }
    } else
    if (!isspace(c) && line.isWhitespace) {
        line.isWhitespace = false;
        line.indentation = line.size - 1;
        mIndentation = std::min(line.indentation, mIndentation);
    }
    return 1;
}

} // namespace cppgen
} // namespace dst
