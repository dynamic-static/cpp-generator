
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "source-element.hpp"

namespace dst {
namespace cppgen {

SourceElement::~SourceElement()
{
}

void SourceElement::take_options(SourceElement& other)
{
    // TODO : take_options()
}

void SourceElement::take_errors(SourceElement& other)
{
    // TODO : take_errors()
}

const std::vector<std::string>& SourceElement::get_errors() const
{
    return mErrors;
}

} // namespace cppgen
} // namespace dst
