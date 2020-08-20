
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
#include "dynamic_static/cpp-generator/cpp-declaration.hpp"
#include "dynamic_static/cpp-generator/cpp-element.hpp"
#include "dynamic_static/cpp-generator/cpp-enum.hpp"
#include "dynamic_static/cpp-generator/cpp-function.hpp"
#include "dynamic_static/cpp-generator/cpp-template.hpp"
#include "dynamic_static/cpp-generator/cpp-variable.hpp"
#include "dynamic_static/cpp-generator/defines.hpp"

#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace dst {
namespace cppgen {

/**
TODO : Documentation
*/
class CppStructure final
    : public CppElement
{
public:
    class Collection;

    /**
    TODO : Documentation
    */
    template <typename ...Args>
    inline CppStructure(const Args&... args)
    {
        process_ctor_arguments(std::tie(args...));
    }

    /**
    TODO : Documentation
    */
    void generate(std::ostream& strm, CppGenerationFlags cppGenerationFlags, std::string_view cppEnclosingType = { }) const override final;

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
            mCppCompileGuards.push_back(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppCompileGuard::Collection>) {
            append(mCppCompileGuards, arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppTemplate>) {
            append(mCppTemplate.cppParameters, arg.cppParameters);
            append(mCppTemplate.cppSpecializations, arg.cppSpecializations);
        } else
        if constexpr (std::is_same_v<decltype(arg), const char*>) {
            // TODO : Test with non const char*
            process_ctor_string_argument(arg ? arg : std::string_view { });
        } else
        if constexpr (std::is_same_v<decltype(arg), std::string> || std::is_same_v<decltype(arg), std::string_view>) {
            process_ctor_string_argument(arg);
        } else
        if constexpr (std::is_same_v<decltype(arg), CppFlagBits> || std::is_integral_v<decltype(arg)>) {
            mCppFlags |= arg;
        } else
        if constexpr (std::is_same_v<decltype(arg), CppAccessSpecifier>) {
            mCppAccessModififer = arg;
        } else
        if constexpr (std::is_base_of_v<CppElement, decltype(arg)>) {
            mCppElements.push_back({ mCppAccessModififer, std::make_unique<decltype(arg)>(arg) });
        } else {
            static_assert(
                !std::is_same_v<decltype(arg), decltype(arg)>,
                "CppStructure ctor given unsupported type\n"
                "CppStructure ctor arguments must be one of:\n"
                "   CppCompileGuard\n"
                "   CppCompileGuard::Collection\n"
                "   CppTemplate\n"
                "   char*\n"
                "   std::string\n"
                "   std::string_view\n"
                "   CppFlagBits\n"
                "   CppAccessSpecifier\n"
                "   CppElement\n"
            );
            UnsupportedType<Argument<ArgIndex>, decltype(arg)> CppStructure_UnsupportedType;
        }
        process_ctor_arguments<ArgIndex + 1>(args);
    }

    inline void process_ctor_string_argument(std::string_view strView)
    {
        if (mCppName.empty() && !strView.empty()) {
            mCppName = strView;
        }
    }

    CppCompileGuard::Collection mCppCompileGuards;
    CppTemplate mCppTemplate;
    std::string mCppName;
    CppFlags mCppFlags { };
    std::vector<std::pair<CppAccessSpecifier, std::unique_ptr<CppElement>>> mCppElements;
    CppAccessSpecifier mCppAccessModififer { Unspecified };
};

} // namespace cppgen
} // namespace dst
