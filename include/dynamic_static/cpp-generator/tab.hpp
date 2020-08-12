
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

#include <algorithm>
#include <iosfwd>
#include <iterator>
#include <type_traits>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class StreamTab final
    : public std::streambuf
{
public:
    /**
    TODO : Documentation
    */
    StreamTab(std::ostream& strm, int count = 0, int size = 4, char fill = ' ')
        : mpStrm { &strm }
        , mpStrmBuf { strm.rdbuf() }
        , count { count }
        , size { size }
        , fill { fill }
    {
        dst_cppgen_assert(mpStrm);
        mpStrm->rdbuf(this);
    }

    /**
    TODO : Documentation
    */
    ~StreamTab()
    {
        dst_cppgen_assert(mpStrm);
        dst_cppgen_assert(mpStrmBuf);
        mpStrm->rdbuf(mpStrmBuf);
    }

    int count { 0 };   //!< TODO : Documentation
    int size { 4 };    //!< TODO : Documentation
    char fill { ' ' }; //!< TODO : Documentation

private:
    int overflow(int c) override final
    {
        dst_cppgen_assert(mpStrmBuf);
        int charCount = 0;
        if (mNewline && c != '\n') {
            mStr.resize(std::max(0, count * size));
            if (!mStr.empty()) {
                auto fillChar = !isspace((int)fill) ? fill : ' ';
                if (mStr[0] != fillChar) {
                    std::fill_n(mStr.begin(), mStr.size(), fillChar);
                }
                mpStrmBuf->sputn(mStr.c_str(), mStr.size());
            }
        }
        mNewline = c == '\n';
        return charCount + mpStrmBuf->sputc(c);
    }

    friend std::ostream& operator<<(std::ostream& strm, StreamTab& tab)
    {
        return strm;
    }

    std::string mStr;
    bool mNewline { true };
    std::ostream* mpStrm { nullptr };
    std::streambuf* mpStrmBuf { nullptr };
};

} // namespace cppgen
} // namespace dst
