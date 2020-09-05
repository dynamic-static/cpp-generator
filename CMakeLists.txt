
#==========================================
#  Copyright (c) 2016-2020 dynamic_static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# dynamic_static.Core CMake configuration
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(dynamic_static.cpp-generator VERSION 0.2.0)
set(CMAKE_CXX_STANDARD 17)
# option(DST_CORE_BUILD_TESTS "Build dynamic_static.core.tests" ON)
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")
set(externalDirectory "${CMAKE_CURRENT_LIST_DIR}/external/")

################################################################################
include("${CMAKE_CURRENT_LIST_DIR}/../cmake/dynamic_static.cmake")
# include("${externalDirectory}/cmake/dynamic_static.cmake")
################################################################################

# TODO : Documentation
function(dst_add_cpp_generator)
    cmake_parse_arguments(args "" "target;folder" "inputFiles;includeDirectories;includeFiles;sourceFiles;linkLibraries;compileDefinitions" ${ARGN})
    dst_add_executable(${ARGN})
    target_link_libraries(${args_target} dynamic_static.cpp-generator)
endfunction()

# dynamic_static.cpp-generator library
set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
set(includePath "${includeDirectory}/dynamic_static/cpp-generator/")
set(sourceDirectory "${CMAKE_CURRENT_LIST_DIR}/source/")
set(sourcePath "${sourceDirectory}/dynamic_static/cpp-generator/")
dst_add_static_library(
    target dynamic_static.cpp-generator
    includeDirectories
        "${includeDirectory}"
    includeFiles
        "${includePath}/ascii-grid.hpp"
        "${includePath}/cpp-case.hpp"
        "${includePath}/cpp-compile-guard.hpp"
        "${includePath}/cpp-declaration.hpp"
        "${includePath}/cpp-documentation.hpp"
        "${includePath}/cpp-element.hpp"
        "${includePath}/cpp-enum.hpp"
        "${includePath}/cpp-enumerator.hpp"
        "${includePath}/cpp-file.hpp"
        "${includePath}/cpp-file.pair.hpp"
        "${includePath}/cpp-function.hpp"
        "${includePath}/cpp-namespace.hpp"
        "${includePath}/cpp-parameter.hpp"
        "${includePath}/cpp-source-block.hpp"
        "${includePath}/cpp-source-block.error.hpp"
        "${includePath}/cpp-source-block.option.hpp"
        "${includePath}/cpp-structure.hpp"
        "${includePath}/cpp-switch.hpp"
        "${includePath}/cpp-template.hpp"
        "${includePath}/cpp-variable.hpp"
        "${includePath}/defines.hpp"
        "${includePath}/stream-counter.hpp"
        "${includePath}/stream-filter.hpp"
        "${includePath}/stream-tab.hpp"
        "${includeDirectory}/dynamic_static/cpp-generator.hpp"
    sourceFiles
        "${sourcePath}/cpp-case.cpp"
        "${sourcePath}/cpp-compile-guard.cpp"
        "${sourcePath}/cpp-declaration.cpp"
        "${sourcePath}/cpp-documentation.cpp"
        "${sourcePath}/cpp-element.cpp"
        "${sourcePath}/cpp-enum.cpp"
        "${sourcePath}/cpp-enumerator.cpp"
        "${sourcePath}/cpp-file.cpp"
        "${sourcePath}/cpp-file.pair.cpp"
        "${sourcePath}/cpp-function.cpp"
        "${sourcePath}/cpp-namespace.cpp"
        "${sourcePath}/cpp-parameter.cpp"
        "${sourcePath}/cpp-source-block.cpp"
        "${sourcePath}/cpp-source-block.error.cpp"
        "${sourcePath}/cpp-source-block.option.cpp"
        "${sourcePath}/cpp-source-element.cpp"
        "${sourcePath}/cpp-source-element.hpp"
        "${sourcePath}/cpp-source-region.cpp"
        "${sourcePath}/cpp-source-region.hpp"
        "${sourcePath}/cpp-source-tag.cpp"
        "${sourcePath}/cpp-source-tag.hpp"
        "${sourcePath}/cpp-structure.cpp"
        "${sourcePath}/cpp-switch.cpp"
        "${sourcePath}/cpp-template.cpp"
        "${sourcePath}/cpp-variable.cpp"
        "${sourcePath}/stream-counter.cpp"
        "${sourcePath}/stream-filter.cpp"
        "${sourcePath}/stream-tab.cpp"
        "${sourcePath}/string.cpp"
        "${sourcePath}/string.hpp"
)

################################################################################

# dynamic_static.cpp-generator.tests
# if(DST_CORE_BUILD_TESTS)
    set(testsSourcePath "${CMAKE_CURRENT_LIST_DIR}/tests/")
    dst_add_test_suite(
        target dynamic_static.cpp-generator
        includeDirectories
            "${sourceDirectory}"
        sourceFiles
            "${testsSourcePath}/cpp-case.tests.cpp"
            "${testsSourcePath}/cpp-compile-guard.tests.cpp"
            "${testsSourcePath}/cpp-declaration.tests.cpp"
            "${testsSourcePath}/cpp-documentation.tests.cpp"
            "${testsSourcePath}/cpp-enum.tests.cpp"
            "${testsSourcePath}/cpp-enumerator.tests.cpp"
            "${testsSourcePath}/cpp-function.tests.cpp"
            "${testsSourcePath}/cpp-function.collection.tests.cpp"
            "${testsSourcePath}/cpp-namespace.tests.cpp"
            "${testsSourcePath}/cpp-parameter.tests.cpp"
            "${testsSourcePath}/cpp-source-block.tests.cpp"
            "${testsSourcePath}/cpp-source-region.tests.cpp"
            "${testsSourcePath}/cpp-source-tag.tests.cpp"
            "${testsSourcePath}/cpp-structure.tests.cpp"
            "${testsSourcePath}/cpp-switch.tests.cpp"
            "${testsSourcePath}/cpp-template.tests.cpp"
            "${testsSourcePath}/cpp-variable.tests.cpp"
            "${testsSourcePath}/string.tests.cpp"
    )
# endif()
