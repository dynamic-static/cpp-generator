
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/cpp-generator/stream-filter.hpp"

#include <ostream>
#include <stdexcept>
#include <utility>

namespace dst {
namespace cppgen {

StreamFilter::StreamFilter(std::ostream& strm)
    : mpStrm { &strm }
    , mpStrmBuf { strm.rdbuf() }
{
    if (!mpStrmBuf) {
        throw std::runtime_error("TODO : Documentation");
    }
    mpStrm->rdbuf(this);
}

StreamFilter::StreamFilter(StreamFilter&& other)
{
    *this = std::move(other);
}

StreamFilter& StreamFilter::operator=(StreamFilter&& other)
{
    if (this != &other) {
        mpStrm = std::move(other.mpStrm);
        mpStrmBuf = std::move(other.mpStrmBuf);
        other.mpStrm = nullptr;
        other.mpStrmBuf = nullptr;
    }
    return *this;
}

StreamFilter::~StreamFilter()
{
    if (mpStrm) {
        mpStrm->rdbuf(mpStrmBuf);
    }
}

int StreamFilter::putc(char c)
{
    dst_cppgen_assert(mpStrmBuf);
    return mpStrmBuf->sputc(c);
}

} // namespace cppgen
} // namespace dst
