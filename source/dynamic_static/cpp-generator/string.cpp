
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "string.hpp"

#include <algorithm>
#include <cassert>
#include <sstream>

namespace dst {
namespace cppgen {
namespace string {

Segment::Segment(std::string_view strView, size_t offset, size_t size)
    : begin { std::min(offset, strView.size()) }
    , end { std::min(begin + std::min(size, strView.size()), strView.size()) }
{
}

Segment::Segment(const Segment& other)
{
    *this = other;
}

Segment& Segment::operator=(const Segment& other)
{
    begin = other.begin;
    end = other.end;
    return *this;
}

bool Segment::valid(std::string_view strView) const
{
    return begin + size() <= strView.size();
}

size_t Segment::size() const
{
    return begin < end ? end - begin : 0;
}

bool Segment::empty() const
{
    return !size();
}

void Segment::clear()
{
    begin = 0;
    end = 0;
}

std::string Segment::str(std::string_view strView) const
{
    return std::string(str_view(strView));
}

std::string_view Segment::str_view(std::string_view strView) const
{
    return valid(strView) ? strView.substr(begin, size()) : std::string_view();
}

size_t find(std::string_view strView, char c, size_t offset, size_t size)
{
    Segment subStr(strView, offset, size);
    for (size_t i = subStr.begin; i < subStr.end; ++i) {
        if (strView[i] == '"' || strView[i] == '`') {
            size_t escapeRegionEnd = i + 1;
            while (escapeRegionEnd < subStr.end) {
                escapeRegionEnd = std::min(strView.find(strView[i], escapeRegionEnd), subStr.end);
                if (strView[escapeRegionEnd - 1] == '\\') {
                    ++escapeRegionEnd;
                } else {
                    break;
                }
            }
            i = escapeRegionEnd;
        } else
        if (strView[i] == c) {
            return i;
        }
    }
    return std::string::npos;
}

Segment trim_leading_whitespace(std::string_view strView, Segment segment)
{
    dst_cppgen_assert(segment.valid(strView));
    while (!segment.empty() && isspace((int)strView[segment.begin])) {
        ++segment.begin;
    }
    return segment;
}

Segment trim_trailing_whitespace(std::string_view strView, Segment segment)
{
    dst_cppgen_assert(segment.valid(strView));
    while (!segment.empty() && isspace((int)strView[segment.end - 1])) {
        --segment.end;
    }
    return segment;
}

Segment trim_whitespace(std::string_view strView, Segment subStr)
{
    return trim_leading_whitespace(strView, trim_trailing_whitespace(strView, subStr));
}

std::string unquote(std::string_view strView, Segment segment)
{
    dst_cppgen_assert(segment.valid(strView));
    dst_cppgen_assert(1 < segment.size());
    dst_cppgen_assert(strView[segment.begin] == '"');
    dst_cppgen_assert(strView[segment.end - 1] == '"');
    ++segment.begin;
    --segment.end;
    std::stringstream strStrm;
    while (segment.begin < segment.end) {
        // TODO : Unescape \t?
        static const std::string EscapedNewlineStr = "\\n";
        auto i = std::min(strView.find(EscapedNewlineStr.c_str(), segment.begin, segment.size()), segment.end);
        strStrm << strView.substr(segment.begin, i - segment.begin);
        segment.begin = i;
        if (i < segment.end) {
            segment.begin = i + EscapedNewlineStr.size();
            strStrm << '\n';
        }
    }
    return strStrm.str();
}

std::pair<std::vector<string::Segment>, size_t> get_lines_and_indentation(std::string_view strView)
{
    std::vector<string::Segment> lines;
    size_t indentation = (size_t)-1;
    size_t offset = 0;
    while (offset < strView.size()) {
        string::Segment line { };
        line.begin = offset;
        line.end = std::min(strView.find('\n', offset), strView.size());
        offset = line.end + 1;
        auto lineContent = trim_whitespace(strView, line);
        line.end = lineContent.end;
        if (!line.empty() || !lines.empty()) {
            lines.push_back(line);
            if (!line.empty()) {
                indentation = std::min(lineContent.begin - line.begin, indentation);
            }
        }
    }
    while (!lines.empty() && lines.back().empty()) {
        lines.pop_back();
    }
    return { lines, indentation };
}

std::string format(std::string_view strView)
{
    std::stringstream strStrm;
    const auto& [lines, indentation] = get_lines_and_indentation(strView);
    for (auto line : lines) {
        line.begin += indentation;
        strStrm << line.str_view(strView) << '\n';
    }
    return strStrm.str();
}

} // namespace string
} // namespace cppgen
} // namespace dst
