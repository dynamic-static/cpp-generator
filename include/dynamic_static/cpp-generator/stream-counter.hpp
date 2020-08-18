
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

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class StreamCounter final
    : public StreamFilter
{
public:
    /**
    TODO : Documentation
    */
    StreamCounter(std::ostream& strm);

    /**
    TODO : Documentation
    */
    size_t count() const;

    /**
    TODO : Documentation
    */
    void reset();

    /**
    TODO : Documentation
    */
    void reset(std::ostream& strm);

private:
    int overflow(int c) override final;
};

} // namespace cppgen
} // namespace dst
