
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/cpp-generator/cpp-compile-guard.hpp"
#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/cpp-source-block.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>

namespace dst {
namespace cppgen {

/**
TODO : Documetation
*/
class CppCase final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    CppCase() = default;

    /**
    TODO : Documentation
    */
    template <typename ...Args>
    inline CppCase(const Args&... args)
    {
        process_ctor_arguments(std::tie(args...));
    }

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags = 0, std::string_view = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    std::string cppLabel;                         //!< TODO : Documentation
    CppSourceBlock cppSourceBlock;                //!< TODO : Documentation
    CppFlags cppFlags { };                        //!< TODO : Documentation

private:
    template <size_t ArgIndex = 0, typename ...Args>
    inline typename std::enable_if<ArgIndex == sizeof...(Args), void>::type process_ctor_arguments(const std::tuple<const Args&...>& args)
    {
    }

    template <size_t ArgIndex = 0, typename ...Args>
    inline typename std::enable_if < ArgIndex < sizeof...(Args), void>::type process_ctor_arguments(const std::tuple<const Args&...>& args)
    {
        auto arg = std::get<ArgIndex>(args);
        if constexpr (std::is_same_v<decltype(arg), CppCompileGuard>) {
            cppCompileGuards.push_back(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppCompileGuard::Collection>) {
            append(cppCompileGuards, arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), const char*> || std::is_same_v<decltype(arg), char*>) {
            process_ctor_string_argument(arg ? arg : std::string_view { });
        } else
        if constexpr (std::is_same_v<decltype(arg), std::string> || std::is_same_v<decltype(arg), std::string_view>) {
            process_ctor_string_argument(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppSourceBlock>) {
            cppSourceBlock = arg;
        } else
        if constexpr (std::is_same_v<decltype(arg), CppFlagBits> || std::is_integral_v<decltype(arg)>) {
            cppFlags |= arg;
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
            if (cppLabel.empty()) {
                cppLabel = strView;
            }
        }
    }
};

/**
TODO : Documentation
*/
class CppCase::Collection final
    : public CppElement::Collection<CppCase>
{
public:
    using CppElement::Collection<CppCase>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags = 0, std::string_view = { }) const override final;
};

/**
TODO : Documentation
*/
using CppCases = CppCase::Collection;

} // namespace cppgen
} // namespace dst