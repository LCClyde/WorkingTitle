#
# The MIT License (MIT)
#
# Copyright (c) 2015 Clyde Stanfield
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#
cmake_minimum_required(VERSION 2.8.12.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

#TODO: Only set this if the caller did not set it
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
set(SOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/source)
set(EXTERNALS_DIRECTORY ${CMAKE_BINARY_DIR}/externals)
set(TEST_MAIN ${EXTERNALS_DIRECTORY}/gtest/src/gtest/googletest/src/gtest_main.cc)

#TODO: Hack, I should remove this
set(CMAKE_PREFIX_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} {CMAKE_PREFIX_PATH})

#add_subdirectory(${EXTERNALS_DIRECTORY})
include_directories(include ${INCLUDE_DIRECTORY})
find_library(GTEST NAMES gtest PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFML_SYSTEM NAMES sfml-system PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFML_WINDOW NAMES sfml-window PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFML_GRAPHICS NAMES sfml-graphics PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_package(Threads)

file(GLOB modules RELATIVE ${SOURCE_DIRECTORY} ${SOURCE_DIRECTORY}/*)

# Build all tests
foreach(dir ${modules})
    if (IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir})

        # Remove some variables
        unset(DEPENDS)
        unset(TEST_DEPENDS)
        unset(CURRENT_LIB)

        # Check for a custom cmake
        if(EXISTS ${SOURCE_DIRECTORY}/${dir}/CMakeLists.txt)
            add_subdirectory(${SOURCE_DIRECTORY}/${dir})
        endif()

        # Copy data
        # TODO: Copy directory at build time
        if (IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/data)
            file(COPY ${SOURCE_DIRECTORY}/${dir}/data DESTINATION ${CMAKE_INSTALL_PREFIX})
        endif()

        # Add all include directories
        if (IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/include)
            include_directories(include ${SOURCE_DIRECTORY}/${dir}/include/)
        endif()

        # library
        if (IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/source)
            file(GLOB SOURCES ${SOURCE_DIRECTORY}/${dir}/source/*.cpp)
            set(CURRENT_LIB ${dir})
            add_library(${CURRENT_LIB} ${SOURCES})
            add_dependencies(${CURRENT_LIB} SFML_PROJECT)
            target_link_libraries(${CURRENT_LIB} ${DEPENDS})
        endif()

        # Build tests
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
        if (IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/tests)
            file(GLOB tests RELATIVE ${SOURCE_DIRECTORY}/${dir}/tests ${SOURCE_DIRECTORY}/${dir}/tests/*.cpp)
            foreach(test ${tests})
                string(REGEX REPLACE "\\.[^.]*$" "" TEST_APP ${test})
                set(TEST_APP test_${TEST_APP})
                add_executable(${TEST_APP} ${SOURCE_DIRECTORY}/${dir}/tests/${test})
                target_link_libraries(${TEST_APP} ${CURRENT_LIB})
            endforeach()
        endif()

        # Build unittests
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/unittests)
        if (IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/unittests)
            file(GLOB tests RELATIVE ${SOURCE_DIRECTORY}/${dir}/unittests ${SOURCE_DIRECTORY}/${dir}/unittests/*.cpp)
            foreach(test ${tests})
                string(REGEX REPLACE "\\.[^.]*$" "" TEST_APP ${test})
                set(TEST_APP unittest_${TEST_APP})
                add_executable(${TEST_APP} ${SOURCE_DIRECTORY}/${dir}/unittests/${test} ${TEST_MAIN})
                target_link_libraries(${TEST_APP} ${CURRENT_LIB} ${GTEST} ${CMAKE_THREAD_LIBS_INIT})
            endforeach()
        endif()
    endif()
endforeach()

add_custom_command(
        TARGET post_cppcheck
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_PREFIX}/bin/cppcheck ${SOURCE_DIR})
