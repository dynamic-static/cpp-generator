
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
#include <cctype>
#include <sstream>

namespace dst {
namespace cppgen {

std::string_view trim_leading_whitespace(std::string_view strView)
{
    while (!strView.empty() && isspace((int)strView.front())) {
        strView.remove_prefix(1);
    }
    return strView;
}

std::string_view trim_trailing_whitespace(std::string_view strView)
{
    while (!strView.empty() && isspace((int)strView.back())) {
        strView.remove_suffix(1);
    }
    return strView;
}

std::string_view trim_whitespace(std::string_view strView)
{
    return trim_leading_whitespace(trim_trailing_whitespace(strView));
}

bool quoted(std::string_view strView)
{
    return 1 < strView.size() && (strView.front() == '"' || strView.front() == '`') && strView.front() == strView.back();
}

size_t find_unquoted(std::string_view strView, char c)
{
    return find_unquoted({ strView, 0 }, c);
}

size_t find_unquoted(std::pair<std::string_view, size_t> subStrView, char c)
{
    auto [strView, offset] = subStrView;
    for (size_t i = offset; i < strView.size(); ++i) {
        if (strView[i] == '"' || strView[i] == '`') {
            size_t escapedRegionEnd = i + 1;
            while (escapedRegionEnd < strView.size()) {
                escapedRegionEnd = std::min(strView.find(strView[i], escapedRegionEnd), strView.size());
                if (strView[escapedRegionEnd - 1] == '\\') {
                    ++escapedRegionEnd;
                } else {
                    break;
                }
            }
            i = escapedRegionEnd;
        } else
        if (strView[i] == c) {
            return i;
        }
    }
    return std::string::npos;
}

std::string unquote(std::string_view strView)
{
    std::stringstream strStrm;
    if (quoted(strView)) {
        strView.remove_prefix(1);
        strView.remove_suffix(1);
        for (size_t i = 0; i < strView.size(); ++i) {
            auto c = strView[i];
            if (c == '\\' && i + 1 < strView.size()) {
                switch (strView[++i]) {
                case 'n': c = '\n'; break;
                case '"': c = '\"'; break;
                case '`': c = '`'; break;
                default: --i; break;
                }
            }
            strStrm << c;
        }
    } else {
        strStrm << strView;
    }
    return strStrm.str();
}

} // namespace cppgen
} // namespace dst
