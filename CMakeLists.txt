cmake_minimum_required(VERSION 2.8.11)

INCLUDE_DIRECTORIES(include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(EXTERNALS_DIRECTORY ${CMAKE_BINARY_DIR}/externals)

add_subdirectory(${EXTERNALS_DIRECTORY})

#set(SFML_FILE "SFML-2.3.2-sources.zip")
#set(SFML_URL "http://www.sfml-dev.org/files/${SFML_FILE}")
#set(SFML_DIRECTORY "${EXTERNALS_DIRECTORY}sfml/")

#if (NOT EXISTS "${SFML_DIRECTORY}${SFML_FILE}")
#    file(DOWNLOAD "${SFML_URL}" "${SFML_DIRECTORY}${SFML_FILE}")
#endif()


#add_custom_command(
#    OUTPUT "${MY_EXTRACTED_FILE}"
#    COMMAND command to unpack
#    DEPENDS "${MY_DOWNLOAD_PATH}")

#file(GLOB SOURCES source/*.cpp)

#add_library(ROSIA ${SOURCES})
#add_executable(testROSIA test/main.cpp)
#target_link_libraries (testROSIA LINK_PUBLIC ROSIA)
