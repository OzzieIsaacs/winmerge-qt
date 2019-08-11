TEMPLATE = app
TARGET = winmerge

MOC_DIR = temp
OBJECTS_DIR = temp
UI_DIR = temp

QT += widgets

# Compiler flags
msvc:QMAKE_CXXFLAGS += /openmp
gcc:QMAKE_CXXFLAGS += -fopenmp -D_GLIBCXX_PARALLEL

# Compiler Libs
gcc:LIBS += -fopenmp

CONFIG += c++14

# Windows manifest embedding
CONFIG += embed_manifest_exe

INCLUDEPATH += ../ext/libxdiff/xdiff \
    ../lib \
    ../ext/poco/Foundation/include \
    ../ext/poco/JSON/include \
    ../ext/poco/Net/include \
    ../ext/poco/Util/include \

RESOURCES = gui.qrc
win32:RC_FILE = gui.rc
macx {
    ICON = res/mac/winmerge.icns
    QMAKE_INFO_PLIST = res/mac/Info.plist
}

FORMS = qt_ui/QAboutDlg.ui \
        qt_ui/IDD_COMPARE_STATISTICS.ui \
        qt_ui/IDD_COMPARE_STATISTICS3.ui \
        qt_ui/IDD_CONFIRM_COPY.ui \
        qt_ui/IDD_DIRCMP_REPORT.ui \
        qt_ui/IDD_DIRCOLS.ui \
        qt_ui/IDD_DIRCOMP_PROGRESS.ui \
        qt_ui/IDD_DIR_FILTER.ui \
        qt_ui/IDD_EDIT_FIND.ui \
        qt_ui/IDD_EDIT_MARKER.ui \
        qt_ui/IDD_EDITOR_HEADERBAR.ui \
        qt_ui/IDD_EDIT_REPLACE.ui \
        qt_ui/IDD_ENCODINGERROR.ui \
        qt_ui/IDD_FILEFILTERS.ui \
        qt_ui/IDD_GENERATE_PATCH.ui \
        qt_ui/IDD_LOAD_SAVE_CODEPAGE.ui \
        qt_ui/IDD_OPEN.ui \
        qt_ui/IDD_PLUGINS_LIST.ui \
        qt_ui/QPreferencesDlg.ui \
        qt_ui/QPropArchive.ui \
        qt_ui/QPropBackups.ui \
        qt_ui/QPropCodepage.ui \
        qt_ui/IDD_PROPPAGE_COLORS_DIR.ui \
        qt_ui/QPropMarkerColors.ui \
        qt_ui/QPropSyntaxColors.ui \
        qt_ui/QPropTextColors.ui \
        qt_ui/QPropMergeColors.ui \
        qt_ui/QPropCompare.ui \
        qt_ui/QPropCompareBinary.ui \
        qt_ui/QPropCompareFolder.ui \
        qt_ui/QPropCompareImage.ui \
        qt_ui/QPropEditor.ui \
        qt_ui/IDD_PROPPAGE_FILTER.ui \
        qt_ui/QPropGeneral.ui \
        qt_ui/QPropShell.ui \
        qt_ui/QPropRegistry.ui \
        qt_ui/IDD_SAVECLOSING.ui \
        qt_ui/IDD_SELECTUNPACKER.ui \
        qt_ui/IDD_SHARED_FILTER.ui \
        qt_ui/IDD_TEST_FILTER.ui \
        qt_ui/IDD_WMGOTO.ui \
        qt_ui/mainwindow.ui \
        #opendialog.ui \
        #openfilesdialog.ui \

#TRANSLATIONS = translations/gui_en_US.ts \
#               translations/gui_de_DE.ts \

include($$PWD/../lib/lib.pri)

HEADERS += AboutDlg.h \
            IDD_COMPARE_STATISTICS.h \
            IDD_COMPARE_STATISTICS3.h \
            IDD_CONFIRM_COPY.h \
            IDD_DIRCMP_REPORT.h \
            IDD_DIRCOLS.h \
            IDD_DIRCOMP_PROGRESS.h \
            IDD_DIR_FILTER.h \
            IDD_EDIT_FIND.h \
            IDD_EDIT_MARKER.h \
            IDD_EDITOR_HEADERBAR.h \
            IDD_EDIT_REPLACE.h \
            IDD_ENCODINGERROR.h \
            IDD_FILEFILTERS.h \
            IDD_GENERATE_PATCH.h \
            IDD_LOAD_SAVE_CODEPAGE.h \
            IDD_OPEN.h \
            IDD_PLUGINS_LIST.h \
            PreferencesDlg.h \
            PropArchive.h \
            PropBackups.h \
            PropCodepage.h \
            IDD_PROPPAGE_COLORS_DIR.h \
            PropMarkerColors.h \
            PropSyntaxColors.h \
            PropTextColors.h \
            PropMergeColors.h \
            PropCompare.h \
            PropCompareBinary.h \
            PropCompareFolder.h \
            PropCompareImage.h \
            PropEditor.h \
            IDD_PROPPAGE_FILTER.h \
            PropGeneral.h \
            PropShell.h \
            PropRegistry.h \
            IDD_SAVECLOSING.h \
            IDD_SELECTUNPACKER.h \
            IDD_SHARED_FILTER.h \
            IDD_TEST_FILTER.h \
            IDD_WMGOTO.h \
            MainFrm.h \
            #opendialog.h \
            #openfilesdialog.h \
            MergeApp.h \
            qlabelclick.h \
            OptionsInit.h \
            Common/VersionInfo.h \
            Common/tchar.h \
            paths.h \
            PathContext.h \
            OptionsDef.h \
            Common/varprop.h \


SOURCES += AboutDlg.cpp \
            IDD_COMPARE_STATISTICS.cpp \
            IDD_COMPARE_STATISTICS3.cpp \
            IDD_CONFIRM_COPY.cpp \
            IDD_DIRCMP_REPORT.cpp \
            IDD_DIRCOLS.cpp \
            IDD_DIRCOMP_PROGRESS.cpp \
            IDD_DIR_FILTER.cpp \
            IDD_EDIT_FIND.cpp \
            IDD_EDIT_MARKER.cpp \
            IDD_EDITOR_HEADERBAR.cpp \
            IDD_EDIT_REPLACE.cpp \
            IDD_ENCODINGERROR.cpp \
            IDD_FILEFILTERS.cpp \
            IDD_GENERATE_PATCH.cpp \
            IDD_LOAD_SAVE_CODEPAGE.cpp \
            IDD_OPEN.cpp \
            IDD_PLUGINS_LIST.cpp \
            PreferencesDlg.cpp \
            PropArchive.cpp \
            PropBackups.cpp \
            PropCodepage.cpp \
            IDD_PROPPAGE_COLORS_DIR.cpp \
            PropMarkerColors.cpp \
            PropSyntaxColors.cpp \
            PropTextColors.cpp \
            PropMergeColors.cpp \
            PropCompare.cpp \
            PropCompareBinary.cpp \
            PropCompareFolder.cpp \
            PropCompareImage.cpp \
            PropEditor.cpp \
            IDD_PROPPAGE_FILTER.cpp \
            PropGeneral.cpp \
            PropShell.cpp \
            PropRegistry.cpp \
            IDD_SAVECLOSING.cpp \
            IDD_SELECTUNPACKER.cpp \
            IDD_SHARED_FILTER.cpp \
            IDD_TEST_FILTER.cpp \
            IDD_WMGOTO.cpp \
            main.cpp \
            MainFrm.cpp \
            #opendialog.cpp \
            #openfilesdialog.cpp \
            OptionsInit.cpp \
            MergeApp.cpp \
            qlabelclick.cpp \            
            Common/VersionInfo.cpp \
            Common/varprop.cpp \
            OptionsDef.cpp \
            paths.cpp \
            PathContext.cpp
    

# Link with libxdiff - need to select library name to link with first
win32 {
    contains(QMAKE_CC, gcc) {
        # MingW
        LIBXDIFFLIBRARY = liblibxdiff.a
    }
    contains(QMAKE_CC, cl) {
        # Visual Studio
        LIBXDIFFLIBRARY = libxdiff.lib
    }

    CONFIG(debug, debug|release) {
        LIBS += $$quote(../ext/libxdiff/debug/$${LIBXDIFFLIBRARY})
    } else {
        LIBS += $$quote(../ext/libxdiff/release/$${LIBXDIFFLIBRARY})
    }
}

unix:LIBS += -L../ext/libxdiff -llibxdiff

unix:!macx: LIBS += -L$$PWD/../ext/poco/lib/ -lPocoFoundationd

INCLUDEPATH += $$PWD/../ext/poco/cmake-build-debug
DEPENDPATH += $$PWD/../ext/poco/cmake-build-debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../ext/poco/lib/libPocoFoundationd.a

unix:!macx: LIBS += -L$$PWD/../ext/poco/lib/ -lPocoJSONd

INCLUDEPATH += $$PWD/../ext/poco/cmake-build-debug
DEPENDPATH += $$PWD/../ext/poco/cmake-build-debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../ext/poco/lib/libPocoJSONd.a

unix:!macx: LIBS += -L$$PWD/../ext/poco/lib/ -lPocoNetd

INCLUDEPATH += $$PWD/../ext/poco/cmake-build-debug
DEPENDPATH += $$PWD/../ext/poco/cmake-build-debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../ext/poco/lib/libPocoNetd.a

unix:!macx: LIBS += -L$$PWD/../ext/poco/lib/ -lPocoUtild

INCLUDEPATH += $$PWD/../ext/poco/cmake-build-debug
DEPENDPATH += $$PWD/../ext/poco/cmake-build-debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../ext/poco/lib/libPocoUtild.a

unix:!macx: LIBS += -L$$PWD/../ext/poco/lib/ -lPocoXMLd

INCLUDEPATH += $$PWD/../ext/poco/cmake-build-debug
DEPENDPATH += $$PWD/../ext/poco/cmake-build-debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../ext/poco/lib/libPocoXMLd.a
