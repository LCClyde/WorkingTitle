include(ExternalProject)

set(EXTERNALS_INSTALL_DIRECTORY ${EXTERNALS_DIRECTORY}/install)

ExternalProject_Add(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        PREFIX ${EXTERNALS_DIRECTORY}/sfml/
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNALS_INSTALL_DIRECTORY})
        
ExternalProject_Add(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        PREFIX ${EXTERNALS_DIRECTORY}/gtest/
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy
            "${EXTERNALS_DIRECTORY}/gtest_patch.txt" <SOURCE_DIR>/CMakeLists.txt
        INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
            <SOURCE_DIR>/googletest/include/ ${EXTERNALS_INSTALL_DIRECTORY}/include/
            COMMAND ${CMAKE_COMMAND} -E copy
            <BINARY_DIR>/googletest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
            ${EXTERNALS_INSTALL_DIRECTORY}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
            COMMAND ${CMAKE_COMMAND} -E copy
            <BINARY_DIR>/googletest/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
            ${EXTERNALS_INSTALL_DIRECTORY}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
        


