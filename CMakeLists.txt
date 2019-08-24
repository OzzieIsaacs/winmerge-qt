cmake_minimum_required(VERSION 3.11)
project(winmerge-qt)

include(ExternalProject)

ExternalProject_Add(Boost
        CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/ext/boost_1_70_0/bootstrap.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ext/boost_1_70_0
        BUILD_IN_SOURCE 1
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/boost_1_70_0/
        BUILD_COMMAND ${CMAKE_SOURCE_DIR}/ext/boost_1_70_0/b2 -sBOOST_ROOT=${CMAKE_SOURCE_DIR}/ext/boost_1_70_0
        INSTALL_COMMAND ""
#        # INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
        )

ExternalProject_Add(Poco
        # GIT_REPOSITORY "https://github.com/json-c/json-c.git"
        # UPDATE_COMMAND git pull "https://github.com/json-c/json-c.git"

        # CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../ext/Poco/bootstrap.sh
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/Poco/
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug
        INSTALL_COMMAND ""
        # BUILD_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../ext/boost_1_70_0/b2
        # INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
        )

add_subdirectory(ext/libxdiff)
# add_subdirectory(ext/poco)
add_subdirectory(src)
