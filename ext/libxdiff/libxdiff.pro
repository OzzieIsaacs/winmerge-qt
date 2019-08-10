TEMPLATE = lib
TARGET = libxdiff
DEPENDPATH += . xdiff
INCLUDEPATH += . xdiff
CONFIG += warn_on staticlib
QT -= gui

# Input
HEADERS += xdiff/xadler32.h \
           xdiff/xbdiff.h \
           xdiff/xdiff.h \
           xdiff/xdiffi.h \
           xdiff/xemit.h \
           xdiff/xinclude.h \
           xdiff/xmacros.h \
           xdiff/xmissing.h \
           xdiff/xprepare.h \
           xdiff/xtypes.h \
           xdiff/xutils.h

SOURCES += xdiff/xadler32.c \
           xdiff/xalloc.c \
           xdiff/xbdiff.c \
           xdiff/xbpatchi.c \
           xdiff/xdiffi.c \
           xdiff/xemit.c \
           xdiff/xmerge3.c \
           xdiff/xmissing.c \
           xdiff/xpatchi.c \
           xdiff/xprepare.c \
           xdiff/xrabdiff.c \
           xdiff/xrabply.c \
           xdiff/xutils.c \
           xdiff/xversion.c

# For configuration file selection we need to detect these three cases:
# 1. Windows with MSVC compiler
# 2. Windows with GCC compiler (and MinGW?)
# 3. Linux/Unix
# Since 1. uses Windows MSVC config and 2. and 3. uses GCC config
win32 {
    contains(QMAKE_CC, gcc){
        # MingW
        HEADERS += config.h
        DEFINES += HAVE_CONFIG_H
    }
    contains(QMAKE_CC, cl){
        # Visual Studio
        HEADERS += winconfig.h
        DEFINES += HAVE_WINCONFIG_H
    }
}
unix {
    HEADERS += config.h
    DEFINES += HAVE_CONFIG_H
}
