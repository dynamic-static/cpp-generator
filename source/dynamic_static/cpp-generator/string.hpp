
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

#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace dst {
namespace cppgen {
namespace string {

struct Segment final
{
    Segment() = default;
    Segment(std::string_view strView, size_t offset = 0, size_t size = std::string::npos);
    Segment(const Segment& other);
    Segment& operator=(const Segment& other);
    bool valid(std::string_view strView) const;
    size_t size() const;
    bool empty() const;
    void clear();
    std::string str(std::string_view strView) const;
    std::string_view str_view(std::string_view strView) const;

    size_t begin { 0 };
    size_t end { 0 };
};

size_t find(std::string_view strView, char c, size_t offset = 0, size_t size = std::string::npos);
Segment trim_leading_whitespace(std::string_view strView, Segment segment);
Segment trim_trailing_whitespace(std::string_view strView, Segment segment);
Segment trim_whitespace(std::string_view strView, Segment segment);
std::string unquote(std::string_view strView, Segment segment);
std::pair<std::vector<Segment>, size_t> get_lines_and_indentation(std::string_view strView);
std::string format(std::string_view strView);

} // namespace string
} // namespace cppgen
} // namespace dst
