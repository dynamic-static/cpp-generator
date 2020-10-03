
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
#include <vector>

namespace dst {
namespace cppgen {

class SourceBlock;
class StreamWriter;

class SourceElement
{
public:
    virtual ~SourceElement() = 0;
    virtual const std::string& get_key() const = 0;
    virtual size_t get_begin_index() const = 0;
    virtual size_t get_end_index() const = 0;
    virtual const std::string& get_option(const std::string& key) const = 0;
    virtual void process_source(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmWriter) const = 0;
    const std::vector<std::string>& get_errors() const;

protected:
    void take_options(SourceElement& other);
    void take_errors(SourceElement& other);
    std::vector<std::string> mErrors;
};

} // namespace cppgen
} // namespace dst
