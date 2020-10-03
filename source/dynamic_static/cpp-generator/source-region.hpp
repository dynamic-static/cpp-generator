
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
#include "source-element.hpp"
#include "source-tag.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace dst {
namespace cppgen {

class SourceBlock;
class StreamWriter;

class SourceRegion final
    : public SourceElement
{
public:
    SourceRegion() = default;
    SourceRegion(std::string_view source);
    SourceRegion(std::string_view source, const SourceTag& begin);
    const std::string& get_key() const override final;
    size_t get_begin_index() const override final;
    size_t get_end_index() const override final;
    const std::string& get_option(const std::string& key) const override final;
    const SourceTag& get_begin_tag() const;
    const std::vector<std::unique_ptr<SourceElement>>& get_source_elements() const;
    const SourceTag& get_end_tag() const;
    void process_source(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmWriter) const;

private:
    template <typename ItrType>
    void process_source_blocks(std::string_view source, ItrType begin, ItrType end, StreamWriter& strmWriter) const;
    void process_source_elements(std::string_view source, const SourceBlock& sourceBlock, StreamWriter& strmWriter) const;
    SourceTag mBegin;
    std::vector<std::unique_ptr<SourceElement>> mSourceElements;
    SourceTag mEnd;
};

} // namespace cppgen
} // namespace dst
