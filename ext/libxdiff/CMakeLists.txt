CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

# Project definition

project(xdiff)

# Package name and version

SET(PACKAGE_NAME xdiff)

SET(PACKAGE_MAJOR_VERSION 0)
SET(PACKAGE_VERSION "${PACKAGE_MAJOR_VERSION}.23")


# Check for some include files and functions

include_directories(.)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckFunctionExists)

CHECK_INCLUDE_FILES(limits.h HAVE_LIMITS_H)
CHECK_FUNCTION_EXISTS(memchr HAVE_MEMCHR)
CHECK_FUNCTION_EXISTS(memcmp HAVE_MEMCMP)
CHECK_FUNCTION_EXISTS(memcpy HAVE_MEMCPY)
CHECK_FUNCTION_EXISTS(memset HAVE_MEMSET)
CHECK_INCLUDE_FILES(stdio.h HAVE_STDIO_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_FUNCTION_EXISTS(strlen HAVE_STRLEN)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)

# Configure LibXDiff

# CONFIGURE_FILE(config.h.in config.h)
set ( SOURCES
        xdiff/xadler32.c
        xdiff/xalloc.c
        xdiff/xbdiff.c
        xdiff/xbpatchi.c
        xdiff/xdiffi.c
        xdiff/xemit.c
        xdiff/xmerge3.c
        xdiff/xmissing.c
        xdiff/xpatchi.c
        xdiff/xprepare.c
        xdiff/xrabdiff.c
        xdiff/xrabply.c
        xdiff/xutils.c
        xdiff/xversion.c
        )

set ( HEADERS
        xdiff/xadler32.h
        xdiff/xbdiff.h
        xdiff/xdiff.h
        xdiff/xdiffi.h
        xdiff/xemit.h
        xdiff/xinclude.h
        xdiff/xmacros.h
        xdiff/xmissing.h
        xdiff/xprepare.h
        xdiff/xtypes.h
        xdiff/xutils.h
        )

ADD_DEFINITIONS(-DHAVE_CONFIG_H)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# Build LibXDiff

if(LINUX)
    list(HEADERS config.h)
    ADD_DEFINITIONS(-DHAVE_CONFIG_H)
    # list(DEFINES HAVE_CONFIG_H)
elseif(WIN32)
    ADD_DEFINITIONS(-DLIBXDIFF_DLL_EXPORT)
    if(MinGW)    # ???
        # MingW
        list(HEADERS config.h)
        ADD_DEFINITIONS(-DHAVE_CONFIG_H)
    endif()
    if(CMAKE_CL_64 OR CMAKE_CL)
        # Visual Studio
        list(HEADERS winconfig.h)
        ADD_DEFINITIONS(-DHAVE_WINCONFIG_H)
    endif()
endif()

ADD_LIBRARY(xdiff STATIC ${SOURCES} ${HEADERS} )
target_include_directories (${PACKAGE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties( ${PACKAGE_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        )
SET_TARGET_PROPERTIES(${PACKAGE_NAME} PROPERTIES VERSION ${PACKAGE_VERSION})
SET_TARGET_PROPERTIES(${PACKAGE_NAME} PROPERTIES SOVERSION ${PACKAGE_MAJOR_VERSION})


