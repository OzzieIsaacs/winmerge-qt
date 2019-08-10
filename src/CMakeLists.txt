cmake_minimum_required(VERSION 3.10)
project(winmerge_gui)

set(CMAKE_CXX_STANDARD 14)

set ( SOURCES
        Common/VersionInfo.cpp
        Common/VersionInfo.h
        ../lib/libxdiff_tools.cpp
        ../lib/libxdiff_tools.h
        ../lib/dircompare.h
        ../lib/dircompare.cpp
        ../lib/filecompare.cpp
        ../lib/filecompare.h
        ../Version.h
        MergeApp.cpp
        MergeApp.h
        AboutDlg.cpp
        IDD_COMPARE_STATISTICS.cpp
        IDD_COMPARE_STATISTICS3.cpp
        IDD_CONFIRM_COPY.cpp
        IDD_DIRCMP_REPORT.cpp
        IDD_DIRCOLS.cpp
        IDD_DIRCOMP_PROGRESS.cpp
        IDD_DIR_FILTER.cpp
        IDD_EDIT_FIND.cpp
        IDD_EDIT_MARKER.cpp
        IDD_EDITOR_HEADERBAR.cpp
        IDD_EDIT_REPLACE.cpp
        IDD_ENCODINGERROR.cpp
        IDD_FILEFILTERS.cpp
        IDD_GENERATE_PATCH.cpp
        IDD_LOAD_SAVE_CODEPAGE.cpp
        IDD_OPEN.cpp
        IDD_PLUGINS_LIST.cpp
        PreferencesDlg.cpp
        PropArchive.cpp
        PropBackups.cpp
        PropCodepage.cpp
        IDD_PROPPAGE_COLORS_DIR.cpp
        IDD_PROPPAGE_COLORS_MARKER.cpp
        IDD_PROPPAGE_COLORS_SYNTAX.cpp
        PropTextColors.cpp
        IDD_PROPPAGE_COLORS_WINMERGE.cpp
        PropCompare.cpp
        IDD_PROPPAGE_COMPARE_BINARY.cpp
        IDD_PROPPAGE_COMPARE_FOLDER.cpp
        PropCompareImage.cpp
        PropEditor.cpp
        IDD_PROPPAGE_FILTER.cpp
        PropGeneral.cpp
        PropShell.cpp
        PropRegistry.cpp
        IDD_SAVECLOSING.cpp
        IDD_SELECTUNPACKER.cpp
        IDD_SHARED_FILTER.cpp
        IDD_TEST_FILTER.cpp
        IDD_WMGOTO.cpp
        main.cpp
        MainFrm.cpp
        MergeApp.cpp
        Common/OptionsMgr.h
        Common/OptionsMgr.cpp
        Common/varprop.h
        Common/varprop.cpp
        OptionsDef.h
        OptionsDef.cpp
        OptionsInit.cpp
        OptionsInit.h
        paths.cpp
        paths.h
        PathContext.h
        // PathContext.cpp
        # opendialog.cpp
        # openfilesdialog.cpp
        qlabelclick.cpp)

set ( MOC_HEADERS
        AboutDlg.h
        IDD_COMPARE_STATISTICS.h
        IDD_COMPARE_STATISTICS3.h
        IDD_CONFIRM_COPY.h
        IDD_DIRCMP_REPORT.h
        IDD_DIRCOLS.h
        IDD_DIRCOMP_PROGRESS.h
        IDD_DIR_FILTER.h
        IDD_EDIT_FIND.h
        IDD_EDIT_MARKER.h
        IDD_EDITOR_HEADERBAR.h
        IDD_EDIT_REPLACE.h
        IDD_ENCODINGERROR.h
        IDD_FILEFILTERS.h
        IDD_GENERATE_PATCH.h
        IDD_LOAD_SAVE_CODEPAGE.h
        IDD_OPEN.h
        IDD_PLUGINS_LIST.h
        PreferencesDlg.h
        PropArchive.h
        PropBackups.h
        PropCodepage.h
        IDD_PROPPAGE_COLORS_DIR.h
        IDD_PROPPAGE_COLORS_MARKER.h
        IDD_PROPPAGE_COLORS_SYNTAX.h
        PropTextColors.h
        IDD_PROPPAGE_COLORS_WINMERGE.h
        PropCompare.h
        IDD_PROPPAGE_COMPARE_BINARY.h
        IDD_PROPPAGE_COMPARE_FOLDER.h
        PropCompareImage.h
        PropEditor.h
        IDD_PROPPAGE_FILTER.h
        PropGeneral.h
        PropShell.h
        PropRegistry.h
        IDD_SAVECLOSING.h
        IDD_SELECTUNPACKER.h
        IDD_SHARED_FILTER.h
        IDD_TEST_FILTER.h
        IDD_WMGOTO.h
        MainFrm.h
        qlabelclick.h
        #opendialog.h
        #openfilesdialog.h
        )

set ( UIS
        qt_ui/QAboutDlg.ui
        qt_ui/IDD_COMPARE_STATISTICS.ui
        qt_ui/IDD_COMPARE_STATISTICS3.ui
        qt_ui/IDD_CONFIRM_COPY.ui
        qt_ui/IDD_DIRCMP_REPORT.ui
        qt_ui/IDD_DIRCOLS.ui
        qt_ui/IDD_DIRCOMP_PROGRESS.ui
        qt_ui/IDD_DIR_FILTER.ui
        qt_ui/IDD_EDIT_FIND.ui
        qt_ui/IDD_EDIT_MARKER.ui
        qt_ui/IDD_EDITOR_HEADERBAR.ui
        qt_ui/IDD_EDIT_REPLACE.ui
        qt_ui/IDD_ENCODINGERROR.ui
        qt_ui/IDD_FILEFILTERS.ui
        qt_ui/IDD_GENERATE_PATCH.ui
        qt_ui/IDD_LOAD_SAVE_CODEPAGE.ui
        qt_ui/IDD_OPEN.ui
        qt_ui/IDD_PLUGINS_LIST.ui
        qt_ui/QPreferencesDlg.ui
        qt_ui/QPropArchive.ui
        qt_ui/QPropBackups.ui
        qt_ui/QPropCodepage.ui
        qt_ui/IDD_PROPPAGE_COLORS_DIR.ui
        qt_ui/IDD_PROPPAGE_COLORS_MARKER.ui
        qt_ui/IDD_PROPPAGE_COLORS_SYNTAX.ui
        qt_ui/QPropTextColors.ui
        qt_ui/IDD_PROPPAGE_COLORS_WINMERGE.ui
        qt_ui/QPropCompare.ui
        qt_ui/IDD_PROPPAGE_COMPARE_BINARY.ui
        qt_ui/IDD_PROPPAGE_COMPARE_FOLDER.ui
        qt_ui/QPropCompareImage.ui
        qt_ui/QPropEditor.ui
        qt_ui/IDD_PROPPAGE_FILTER.ui
        qt_ui/QPropGeneral.ui
        qt_ui/QPropShell.ui
        qt_ui/QPropRegistry.ui
        qt_ui/IDD_SAVECLOSING.ui
        qt_ui/IDD_SELECTUNPACKER.ui
        qt_ui/IDD_SHARED_FILTER.ui
        qt_ui/IDD_TEST_FILTER.ui
        qt_ui/IDD_WMGOTO.ui
        qt_ui/mainwindow.ui
        #opendialog.ui
        #openfilesdialog.ui
        )

set ( RESOURCES
        gui.qrc
        )

# set the POCO paths and libs
set(Poco_DIR "../ext/poco/cmake-build-debug/Poco") # the directory containing "include" and "lib"
set(PocoFoundation_DIR "../ext/poco/cmake-build-debug/Foundation") # the directory containing "include" and "lib"
set(PocoNet_DIR "../ext/poco/cmake-build-debug/Net") # the directory containing "include" and "lib"

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Poco REQUIRED Foundation Net )

# include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

include_directories(.)
include_directories(../lib)
include_directories(../ext/libxdiff/xdiff)
include_directories(SYSTEM Common)

# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT5_WRAP_UI( UI_HEADERS ${UIS} )
QT5_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

add_executable( winmerge_gui ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} version.rc)

# specify which libraries to connect
target_link_libraries(winmerge_gui /home/matthias/Entwicklung/WinMergeqt_clion/ext/libxdiff/liblibxdiff.a)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Poco::Foundation Poco::Net)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS qt_ui)
set(CMAKE_INCLUDE_CURRENT_DIR ON)