
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set(target dynamic_static.cpp-generator)
project(${target} VERSION 0.2.0)

################################################################################

function(DstCreateFileGroup files)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    foreach(file ${files})
        get_filename_component(directory "${file}" DIRECTORY)
        string(REPLACE "${PROJECT_SOURCE_DIR}" "" groupName "${directory}")
        string(REPLACE "${CMAKE_SOURCE_DIR}" "" groupName "${groupName}")
        if(MSVC)
            string(REPLACE "/" "\\" groupName "${groupName}")
        endif()
        source_group("${groupName}" FILES "${file}")
    endforeach()
endfunction()

################################################################################

set(includeDirectory "${CMAKE_CURRENT_LIST_DIR}/include/")
set(includePath "${includeDirectory}/dynamic_static/cpp-generator/")
set(includeFiles
    "${includePath}/ascii-grid.hpp"
    "${includePath}/cpp-compile-guard.hpp"
    "${includePath}/cpp-element-collection.hpp"
    "${includePath}/cpp-file.hpp"
    "${includePath}/cpp-file.pair.hpp"
    "${includePath}/cpp-function.hpp"
    "${includePath}/cpp-namespace.hpp"
    "${includePath}/cpp-parameter.hpp"
    "${includePath}/cpp-source-block.hpp"
    "${includePath}/cpp-source-block.error.hpp"
    "${includePath}/cpp-source-block.option.hpp"
    "${includePath}/cpp-string-element.hpp"
    "${includePath}/cpp-structure.hpp"
    "${includePath}/cpp-template.hpp"
    "${includePath}/cpp-variable.hpp"
    "${includePath}/defines.hpp"
    "${includeDirectory}/dynamic_static/cpp-generator.hpp"
)
set(sourceDirectory "${CMAKE_CURRENT_LIST_DIR}/source/")
set(sourcePath "${sourceDirectory}/dynamic_static/cpp-generator/")
set(sourceFiles

    "${sourcePath}/cpp-compile-guard.cpp"
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
    "${sourcePath}/cpp-template.cpp"
    "${sourcePath}/cpp-variable.cpp"
    "${sourcePath}/string.cpp"
    "${sourcePath}/string.hpp"
)
add_library(${target} STATIC "${includeFiles}" "${sourceFiles}")
target_include_directories(${target} PUBLIC "${includeDirectory}")
target_compile_features(${target} PUBLIC cxx_std_17)
DstCreateFileGroup("${includeFiles}")
DstCreateFileGroup("${sourceFiles}")

################################################################################

set(targetTests ${target}.tests)
set(testsSourcePath "${CMAKE_CURRENT_LIST_DIR}/tests/")
set(testsSourceFiles
    "${testsSourcePath}/catch.hpp"
    "${testsSourcePath}/cpp-parameter.tests.cpp"
    "${testsSourcePath}/cpp-source-block.tests.cpp"
    "${testsSourcePath}/cpp-source-region.tests.cpp"
    "${testsSourcePath}/cpp-source-tag.tests.cpp"
    "${testsSourcePath}/main.cpp"
    "${testsSourcePath}/string.tests.cpp"
)
add_executable(${targetTests} "${testsSourceFiles}")
target_compile_features(${targetTests} PUBLIC cxx_std_17)
target_link_libraries(${targetTests} PUBLIC ${target})
target_include_directories(
    ${targetTests}
    PUBLIC
        "${includeDirectory}"
        "${sourceDirectory}"
        "${testsSourcePath}"
)
DstCreateFileGroup("${testsSourceFiles}")