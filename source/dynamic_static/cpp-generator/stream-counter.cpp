
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/stream-counter.hpp"

namespace dst {
namespace cppgen {

StreamCounter::StreamCounter(std::ostream& strm)
    : StreamFilter(strm)
{
}

size_t StreamCounter::count() const
{
    return 0;
}

void StreamCounter::reset()
{
}

void StreamCounter::reset(std::ostream& strm)
{
}

int StreamCounter::overflow(int c)
{
    return 0;
}

} // namespace cppgen
} // namespace dst
