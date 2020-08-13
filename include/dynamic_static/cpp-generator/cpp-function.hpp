
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
#include "dynamic_static/cpp-generator/cpp-parameter.hpp"
#include "dynamic_static/cpp-generator/cpp-source-block.hpp"
#include "dynamic_static/cpp-generator/cpp-template.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <string>
#include <tuple>
#include <type_traits>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppFunction final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    template <typename ...Args>
    inline CppFunction(const Args&... args)
    {
        process_ctor_arguments(std::tie(args...));
    }

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType = { }) const override final;

    CppCompileGuard::Collection cppCompileGuards; //!< TODO : Documentation
    CppTemplate cppTemplate;                      //!< TODO : Documentation
    std::string cppReturnType;                    //!< TODO : Documentation
    std::string cppName;                          //!< TODO : Documentation
    CppParameter::Collection cppParameters;       //!< TODO : Documentation
    CppFlags cppFlags { };                        //!< TODO : Documentation
    CppSourceBlock cppSourceBlock;                //!< TODO : Documentation

private:
    template <size_t ArgIndex = 0, typename ...Args>
    inline typename std::enable_if<ArgIndex == sizeof...(Args), void>::type process_ctor_arguments(const std::tuple<const Args&...>& args)
    {
    }

    template <size_t ArgIndex = 0, typename ...Args>
    inline typename std::enable_if<ArgIndex < sizeof...(Args), void>::type process_ctor_arguments(const std::tuple<const Args&...>& args)
    {
        auto arg = std::get<ArgIndex>(args);
        if constexpr (std::is_same_v<decltype(arg), CppCompileGuard>) {
            cppCompileGuards.push_back(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppCompileGuard::Collection> || std::is_same_v<decltype(arg), CppCompileGuard::Collection::base_type>) {
            append(cppCompileGuards, arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppTemplate>) {
            append(cppTemplate.cppParameters, arg.cppParameters);
            append(cppTemplate.cppSpecializations, arg.cppSpecializations);
        } else
        if constexpr (std::is_same_v<decltype(arg), const char*>) {
            // TODO : Test with non const char*
            process_ctor_string_argument(arg ? arg : std::string_view { });
        } else
        if constexpr (std::is_same_v<decltype(arg), std::string> || std::is_same_v<decltype(arg), std::string_view>) {
            process_ctor_string_argument(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppParameter>) {
            cppParameters.push_back(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppParameter::Collection> || std::is_same_v<decltype(arg), CppParameter::Collection::base_type>) {
            append(cppParameters, arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppFlagBits> || std::is_integral_v<decltype(arg)>) {
            cppFlags |= arg;
        } else
        if constexpr (std::is_same_v<decltype(arg), CppSourceBlock>) {
            cppSourceBlock = arg;
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
            if (cppReturnType.empty()) {
                cppReturnType = strView;
            } else
            if (cppName.empty()) {
                cppName = strView;
            }
        }
    }
};

/**
TODO : Documentation
*/
class CppFunction::Collection final
    : public CppElement::Collection<CppFunction>
{
public:
    using CppElement::Collection<CppFunction>::Collection;

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType = { }) const override final;
};

/**
TODO : Documentation
*/
using CppFunctions = CppFunction::Collection;

} // namespace cppgen
} // namespace dst
