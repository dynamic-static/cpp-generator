
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/cpp-parameter.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppTemplate final
    : public CppElement
{
public:
    /**
    TODO : Documentation
    */
    CppTemplate() = default;

    /**
    TODO : Documentation
    */
    template <typename ...Args>
    inline CppTemplate(const Args &... args)
    {
        process_ctor_arguments(std::tie(args...));
    }

    /**
    TODO : Documentation
    */
    bool empty() const;

    /**
    TODO : Documentation
    */
    bool operative(CppGenerationFlags cppGenerationFlags) const;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view = { }) const override final;

    CppParameter::Collection cppParameters;      //!< TODO : Documentation
    std::vector<std::string> cppSpecializations; //!< TODO : Documentation

private:
    template <size_t ArgIndex = 0, typename ...Args>
    inline typename std::enable_if<ArgIndex == sizeof...(Args), void>::type process_ctor_arguments(const std::tuple<const Args&...>& args)
    {
    }

    template <size_t ArgIndex = 0, typename ...Args>
    inline typename std::enable_if < ArgIndex < sizeof...(Args), void>::type process_ctor_arguments(const std::tuple<const Args&...>& args)
    {
        auto arg = std::get<ArgIndex>(args);
        if constexpr (std::is_same_v<decltype(arg), CppParameter>) {
            cppParameters.push_back(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppParameter::Collection>) {
            append(cppParameters, arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), const char*> || std::is_same_v<decltype(arg), char*>) {
            process_ctor_string_argument(arg ? arg : std::string_view { });
        } else
        if constexpr (std::is_same_v<decltype(arg), std::string> || std::is_same_v<decltype(arg), std::string_view>) {
            process_ctor_string_argument(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), std::vector<std::string>>) {
            append(cppSpecializations, arg);
        } else {
            static_assert(
                !std::is_same_v<decltype(arg), decltype(arg)>,
                "TODO : Documentation"
            );
        }
        process_ctor_arguments<ArgIndex + 1>(args);
    }

    inline void process_ctor_string_argument(std::string_view strView)
    {
        if (!strView.empty()) {
            cppSpecializations.emplace_back(strView);
        }
    }
};

/**
TODO : Documentation
*/
using CppSpecialization = std::string;

/**
TODO : Documentation
*/
using CppSpecializations = std::vector<std::string>;

} // namespace cppgen
} // namespace dst
