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
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
set(SOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/source)
set(EXTERNALS_DIRECTORY ${CMAKE_BINARY_DIR}/externals)
set(TEST_MAIN ${EXTERNALS_DIRECTORY}/gtest/src/gtest/googletest/src/gtest_main.cc)

add_subdirectory(${EXTERNALS_DIRECTORY})
include_directories(include ${INCLUDE_DIRECTORY})
find_library(GTEST NAMES gtest gtest_main)
find_package(Threads)

file(GLOB modules RELATIVE ${SOURCE_DIRECTORY} ${SOURCE_DIRECTORY}/*)

# Build all tests
foreach(dir ${modules})
    if(IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir})
        # Add all include directories
        if(IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/include)
            include_directories(include ${SOURCE_DIRECTORY}/${dir}/include/)
        endif()

        # Add all include directories
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/tests)
        if(IS_DIRECTORY ${SOURCE_DIRECTORY}/${dir}/tests)
            file(GLOB tests RELATIVE ${SOURCE_DIRECTORY}/${dir}/tests ${SOURCE_DIRECTORY}/${dir}/tests/*.cpp)
            foreach(test ${tests})
                string(REGEX REPLACE "\\.[^.]*$" "" TEST_APP ${test})
                #add_executable(${TEST_APP} ${SOURCE_DIRECTORY}/${dir}/tests/${test} ${TEST_MAIN})
                #target_link_libraries(${TEST_APP} ${GTEST} ${CMAKE_THREAD_LIBS_INIT})
            endforeach()
        endif()
    endif()
endforeach()

#file(GLOB SOURCES source/*.cpp)

#add_library(ROSIA ${SOURCES})
