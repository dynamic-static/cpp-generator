
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <algorithm>
#include <cassert>
#include <cctype>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#if 1
#include <sstream>
#endif

namespace dst {

/**
Provides facilities for printing an ASCII chart
*/
class AsciiChart final
{
public:
    /**
    Represents a single entry in an AsciiChart
    */
    class Cell final
    {
    public:
        /**
        Represents a single row of AsciiChart::Cell objects
            @note Row is an alias for std::vector<AsciiChart::Cell>
        */
        using Row = std::vector<Cell>;

        /**
        Represents a grid of AsciiChart::Cell objects
            @note Grid is an alias for std::vector<Row>
        */
        using Grid = std::vector<Row>;

        /**
        Constructs an instance of AsciiChart::Cell
        */
        Cell() = default;

        /**
        Constructs an instance of AsciiChart::Cell
        @param [in] str The std::string to assign to this AsciiChart::Cell
        */
        inline Cell(const std::string& str)
        {
            *this = str;
        }

        /**
        Copies an instance of AsciiChart::Cell
        @param [in] other The AsciiChart::Cell to copy from
        */
        inline Cell(const Cell& other)
        {
            *this = other;
        }

        /**
        Copies an instance of AsciiChart::Cell
        @param [in] other The AsciiChart::Cell to copy from
        @return A reference to this AsciiChart::Cell
        */
        inline Cell& operator=(const Cell& other)
        {
            fill = other.fill;
            mStr = other.mStr;
            mLines = other.mLines;
            mWidth = other.mWidth;
            return *this;
        }

        /**
        Assigns a given std::string to this AsciiChart::Cell
        @param [in] str The std::string to assign to this AsciiChart::Cell
        */
        inline Cell& operator=(const std::string& str)
        {
            clear();
            mStr = str;
            size_t lineBegin = 0;
            while (lineBegin < mStr.size()) {
                auto lineEnd = mStr.size();
                for (size_t char_i = lineBegin; char_i < mStr.size(); ++char_i) {
                    switch (mStr[char_i]) {
                    case '\t': {
                        static const std::string sTabStr = "    ";
                        mStr.replace(char_i, 1, sTabStr);
                        char_i += sTabStr.size();
                    } break;
                    case '\n': {
                        lineEnd = char_i;
                        char_i = mStr.size();
                    } break;
                    }
                }
                auto lineSize = lineEnd - lineBegin;
                mLines.emplace_back(lineBegin, lineSize);
                mWidth = std::max(mWidth, lineSize);
                lineBegin = lineEnd + 1;
                if (lineBegin == mStr.size()) {
                    mLines.emplace_back();
                }
            }
            return *this;
        }

        /**
        Gets a single line from this AsciiChart::Cell object's assigned std::string
        @param [in] lineIndex The index of the line to get from this AsciiChart::Cell object's assigned std::string
        @return The specified line from this AsciiChart::Cell object's assigned std::string
            @note If lineIndex exceeds the value returned by get_height() an empty std::string will be returned
        */
        inline std::string operator[](size_t lineIndex) const
        {
            return lineIndex < mLines.size() ? mStr.substr(mLines[lineIndex].first, mLines[lineIndex].second) : std::string();
        }

        /**
        Converts this AsciiChart::Cell to its assigned std::string
        @return A const reference to this AsciiChart::Cell object's assigned std::string
        */
        inline operator const std::string&() const
        {
            return mStr;
        }

        /**
        Gets this AsciiChart::Cell object's width in characters
        @return This AsciiChart::Cell object's width in characters
        */
        size_t get_width() const
        {
            return mWidth;
        }

        /**
        Gets this AsciiChart::Cell object's height in characters
        @return This AsciiChart::Cell object's height in characters
        */
        size_t get_height() const
        {
            return mLines.size();
        }

        /**
        Clears this AsciiChart::Cell
        */
        inline void clear()
        {
            mStr.clear();
            mLines.clear();
            mWidth = 0;
        }

        char fill { '\0' }; //!< TODO : Documentation

    private:
        std::string mStr;
        std::vector<std::pair<size_t, size_t>> mLines;
        size_t mWidth { 0 };
    };

    /**
    Encapsulates the characters used to draw an AsciiChart object's borders and row seperators
    */
    struct Seperator
    {
        /**
        Encapsulates the characters used to draw an AsciiChart object's row seperators
        */
        struct Characters
        {
            char left       { ' ' }; //!< This AsciiChart::Seperator::Characters object's left character
            char inner      { ' ' }; //!< This AsciiChart::Seperator::Characters object's inner character
            char right      { ' ' }; //!< This AsciiChart::Seperator::Characters object's right character
            char horizontal { ' ' }; //!< This AsciiChart::Seperator::Characters object's horizontal seperator character
        };

        Characters top { };    //!< This AsciiChart::Seperator object's top line characters
        Characters inner { };  //!< This AsciiChart::Seperator object's inner line characters
        Characters bottom { }; //!< This AsciiChart::Seperator object's bottom line characters
        char vertical { ' ' }; //!< This AsciiChart::Seperator object's vertical seperator character
    };

    /**
    An AsciiChart::Seperator the utilizes empty characters
    */
    inline static const Seperator Empty { };

    /**
    An AsciiChart::Seperator the utilizes basic ASCII characters
    */
    inline static const Seperator Basic {
        { '+', '+', '+', '-' },
        { '+', '+', '+', '-' },
        { '+', '+', '+', '-' },
        '|'
    };

    /**
    An AsciiChart::Seperator the utilizes the extended ASCII box characters
    */
    inline static const Seperator Box {
        { (char)218, (char)194, (char)191, (char)196 },
        { (char)195, (char)197, (char)180, (char)196 },
        { (char)192, (char)193, (char)217, (char)196 },
        (char)179
    };

    /**
    An AsciiChart::Seperator the utilizes the extended ASCII bold box characters
    */
    inline static const Seperator BoldBox {
        { (char)201, (char)203, (char)187, (char)205 },
        { (char)204, (char)206, (char)185, (char)205 },
        { (char)200, (char)202, (char)188, (char)205 },
        (char)186
    };

    Cell::Grid cells;              //!< This AsciiChart object's AsciiChart::Cell::Grid
    Seperator seperator { Basic }; //!< This AsciiChart object's AsciiChart::Seperator
    char fill { '\0' };            //!< TODO : Documentation

    /**
    TODO : Documentation
    */
    inline const Cell& operator[](size_t cellIndex) const
    {
        size_t row_i = 0;
        while (cells[row_i].size() <= cellIndex) {
            cellIndex -= cells[row_i++].size();
        }
        return cells[row_i][cellIndex];
    }

    /**
    TODO : Documentation
    */
    inline Cell& operator[](size_t cellIndex)
    {
        auto constThis = const_cast<const AsciiChart*>(this);
        return const_cast<Cell&>(constThis->operator[](cellIndex));
    }

    /**
    TODO : Documentation
    */
    inline size_t get_cell_count() const
    {
        size_t cellCount = 0;
        for (const auto& row : cells) {
            cellCount += row.size();
        }
        return cellCount;
    }

    /**
    Writes a given AsciiChart to a given std::ostream
    @param [in] strm The std::ostream to write the given AsciiChart to
    @param [in] asciiChart The AsciiChart to write to the given std::ostream
    @return A reference to the given std::ostream
    */
    inline friend std::ostream& operator<<(std::ostream& strm, const AsciiChart& asciiChart)
    {
        if (!asciiChart.cells.empty()) {
            asciiChart.write(strm);
        }
        return strm;
    }

private:
    inline void write(std::ostream& strm) const
    {
        size_t maxCellWidth = 0;
        size_t maxCellHeight = 0;
        for (const auto& row : cells) {
            for (const auto& cell : row) {
                maxCellWidth = std::max(maxCellWidth, cell.get_width());
                maxCellHeight = std::max(maxCellHeight, cell.get_height());
            }
        }
        write_row_seperator(strm, seperator.top, maxCellWidth, cells.front().size(), cells.front().size());
        for (size_t row_i = 0; row_i < cells.size(); ++row_i) {
            const auto& row = cells[row_i];
            write_row_cells(strm, maxCellWidth, maxCellHeight, row);
            if (row_i + 1 < cells.size()) {
                write_row_seperator(strm, seperator.inner, maxCellWidth, row.size(), cells[row_i + 1].size());
            }
        }
        write_row_seperator(strm, seperator.bottom, maxCellWidth, cells.back().size(), cells.back().size());
    }

    inline void write_row_seperator(std::ostream& strm, Seperator::Characters seperatorCharacters, size_t maxCellWidth, size_t leadRowCellCount, size_t followRowCellCount) const
    {
        strm << seperatorCharacters.left;
        auto maxCellCount = std::max(leadRowCellCount, followRowCellCount);
        for (size_t cell_i = 0; cell_i < maxCellCount; ++cell_i) {
            if (leadRowCellCount <= cell_i) {
                seperatorCharacters = seperator.top;
            } else
            if (followRowCellCount <= cell_i) {
                seperatorCharacters = seperator.bottom;
            }
            std::fill_n(std::ostream_iterator<char>(strm), maxCellWidth, seperatorCharacters.horizontal);
            strm << (cell_i + 1 < maxCellCount ? seperatorCharacters.inner : seperatorCharacters.right);
        }
        strm << std::endl;
    }

    inline void write_row_cells(std::ostream& strm, size_t maxCellWidth, size_t maxCellHeight, const Cell::Row& row) const
    {
        for (size_t line_i = 0; line_i < maxCellHeight; ++line_i) {
            strm << seperator.vertical;
            for (size_t cell_i = 0; cell_i < row.size(); ++cell_i) {
                const auto& cell = row[cell_i];
                auto line = cell[line_i];
                auto fillCharacter = cell.fill ? cell.fill : fill ? fill : ' ';
                if (fillCharacter) {
                    std::replace_if(line.begin(), line.end(), [](char c) { return isspace((int)c); }, fillCharacter);
                }
                std::fill_n(std::ostream_iterator<char>(strm << line), maxCellWidth - line.size(), fillCharacter);
                strm << seperator.vertical;
            }
            strm << std::endl;
        }
    }
};

} // namespace dst





namespace dst {

inline std::string get_debug_view(std::string_view strView, std::vector<size_t> highLights = { })
{
    dst::AsciiChart asciiChart;
    dst::AsciiChart::Cell* pAsciiChartCell = nullptr;
    #if 0
    asciiChart.seperator = dst::AsciiChart::Box;
    #else
    asciiChart.seperator = dst::AsciiChart::Basic;
    #endif
    size_t lineBegin = 0;
    while (lineBegin < strView.size()) {
        auto lineEnd = std::min(strView.find('\n', lineBegin), strView.size());
        auto lineSize = lineEnd + 1 - lineBegin;
        asciiChart.cells.emplace_back();
        asciiChart.cells.back().reserve(lineSize);
        for (size_t i = lineBegin; i < lineEnd; ++i) {
            asciiChart.cells.back().emplace_back(std::to_string(i) + "\n\n  " + strView[i] + " ");
        }
        asciiChart.cells.back().emplace_back(std::to_string(lineEnd) + "\n\n \\n ");
        lineBegin = lineEnd + 1;
    }
    for (auto highLight : highLights) {
        #if 0
        asciiChart[highLight].fill = (char)177;
        #else
        asciiChart[highLight].fill = '.';
        #endif
    }
    std::stringstream strStrm;
    strStrm << asciiChart;
    return strStrm.str();
}

} // namespace dst
