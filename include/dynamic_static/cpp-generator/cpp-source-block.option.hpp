
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-source-block.hpp"

#include <string>
#include <string_view>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppSourceBlock::Option final
{
public:
    /**
    TODO : Documentation
    */
    Option() = default;

    /**
    TODO : Documentation
    */
    Option(std::string_view name, std::string_view value);

    /**
    TODO : Documentation
    */
    Option(const Option& other);

    /**
    TODO : Documentation
    */
    Option(Option&& other);

    /**
    TODO : Documentation
    */
    Option& operator=(const Option& other);

    /**
    TODO : Documentation
    */
    Option& operator=(Option&& other);

    /**
    TODO : Documentation
    */
    const std::string& get_name() const;

    /**
    TODO : Documentation
    */
    const std::string& get_value() const;

    /**
    TODO : Documentation
    */
    static bool is_valid_name(std::string_view name);

    /**
    TODO : Documentation
    */
    friend bool operator==(const Option& lhs, const Option& rhs);

    /**
    TODO : Documentation
    */
    friend bool operator!=(const Option& lhs, const Option& rhs);

    /**
    TODO : Documentation
    */
    friend bool operator<(const Option& lhs, const Option& rhs);

private:
    std::string mName;
    std::string mValue;
};

} // namespace cppgen
} // namespace dst
