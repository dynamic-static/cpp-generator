
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

#include <iosfwd>
#include <streambuf>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class StreamFilter
    : public std::streambuf
{
public:
    /**
    TODO : Documentation
    */
    StreamFilter(std::ostream& strm);

    /**
    TODO : Documentation
    */
    StreamFilter(StreamFilter&& other);

    /**
    TODO : Documentation
    */
    StreamFilter& operator=(StreamFilter&& other);

    /**
    TODO : Documentation
    */
    virtual ~StreamFilter() = 0;

protected:
    /**
    TODO : Documentation
    */
    virtual int overflow(int c) override = 0;

    /**
    TODO : Documentation
    */
    int putc(char c);

private:
    std::ostream* mpStrm { nullptr };
    std::streambuf* mpStrmBuf { nullptr };
    StreamFilter(const StreamFilter&) = delete;
    StreamFilter& operator=(const StreamFilter&) = delete;
};

} // namespace cppgen
} // namespace dst
