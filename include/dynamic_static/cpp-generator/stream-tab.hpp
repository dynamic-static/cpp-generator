
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
#include "dynamic_static/cpp-generator/stream-filter.hpp"

#include <iosfwd>
#include <streambuf>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class StreamTab final
    : public StreamFilter
{
public:
    /**
    TODO : Documentation
    */
    StreamTab(std::ostream& strm, int count = 0, int size = 4, char fill = ' ');

    int count { 0 };   //!< TODO : Documentation
    int size { 4 };    //!< TODO : Documentation
    char fill { ' ' }; //!< TODO : Documentation

private:
    int overflow(int c) override final;
    bool mNewline { true };
};

} // namespace cppgen
} // namespace dst
