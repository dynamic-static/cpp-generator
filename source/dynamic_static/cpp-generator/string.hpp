
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

namespace dst {
namespace cppgen {

std::string_view trim_leading_whitespace(std::string_view strView);
std::string_view trim_trailing_whitespace(std::string_view strView);
std::string_view trim_whitespace(std::string_view strView);
bool quoted(std::string_view strView);
size_t find_unquoted(std::string_view strView, char c);
size_t find_unquoted(std::pair<std::string_view, size_t> subStrView, char c);
std::string unquote(std::string_view strView);

} // namespace cppgen
} // namespace dst
