
#==========================================
#  Copyright (c) 2016-2020 dynamic_static
#    Patrick Purcell
#      Licensed under the MIT license
#    http://opensource.org/licenses/MIT
#==========================================

# dynamic_static.Core CMake configuration
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(dynamic_static.cpp-generator VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(external "${CMAKE_CURRENT_LIST_DIR}/external/")
include("${external}/dynamic_static.build.cmake")

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
        "${includePath}/defines.hpp"
        "${includePath}/error.hpp"
        "${includePath}/file.hpp"
        "${includePath}/source-block.hpp"
        "${includeDirectory}/dynamic_static/cpp-generator.hpp"
    sourceFiles
        "${sourcePath}/error.cpp"
        "${sourcePath}/file.cpp"
        "${sourcePath}/source-block.cpp"
        "${sourcePath}/source-element.cpp"
        "${sourcePath}/source-element.hpp"
        "${sourcePath}/source-region.cpp"
        "${sourcePath}/source-region.hpp"
        "${sourcePath}/source-tag.cpp"
        "${sourcePath}/source-tag.hpp"
        "${sourcePath}/stream-writer.cpp"
        "${sourcePath}/stream-writer.hpp"
        "${sourcePath}/string.cpp"
        "${sourcePath}/string.hpp"
)

################################################################################

# dynamic_static.cpp-generator.tests
# if(DST_CORE_BUILD_TESTS)
    set(testsSourcePath "${CMAKE_CURRENT_LIST_DIR}/tests/")
    dst_add_target_test_suite(
        target dynamic_static.cpp-generator
        includeDirectories
            "${sourceDirectory}"
        sourceFiles
            "${testsSourcePath}/error.tests.cpp"
            "${testsSourcePath}/file.tests.cpp"
            "${testsSourcePath}/source-block.tests.cpp"
            "${testsSourcePath}/source-region.tests.cpp"
            "${testsSourcePath}/source-tag.tests.cpp"
            "${testsSourcePath}/string.tests.cpp"
    )
# endif()
