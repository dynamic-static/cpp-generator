
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/stream-tab.hpp"

#include <algorithm>
#include <ostream>

namespace dst {
namespace cppgen {

StreamTab::StreamTab(std::ostream& strm, int count, int size, char fill)
    : StreamFilter(strm)
    , count { count }
    , size { size }
    , fill { fill }
{
}

int StreamTab::overflow(int c)
{
    if (mNewline && c != '\n') {
        auto fillCount = std::max(0, count * size);
        while (fillCount--) {
            putc(fill);
        }
    }
    mNewline = c == '\n';
    return putc(c);
}

} // namespace cppgen
} // namespace dst
