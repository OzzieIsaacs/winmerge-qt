cmake_minimum_required(VERSION 3.10)
project(winmerge_gui)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
# include_directories(../lib)
# include_directories(../ext/libxdiff/xdiff)
include_directories(SYSTEM Common)
include_directories(SYSTEM diffutils/src)
include_directories(SYSTEM diffutils)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS qt_ui)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set ( SOURCES
        Common/VersionInfo.cpp
        Common/VersionInfo.h
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
        PropMarkerColors.cpp
        PropSyntaxColors.cpp
        PropTextColors.cpp
        PropMergeColors.cpp
        PropCompare.cpp
        PropCompareBinary.cpp
        PropCompareFolder.cpp
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
        MainMenu.cpp
        MergeApp.cpp
        Common/varprop.h
        Common/varprop.cpp
        OptionsDef.h
        OptionsDef.cpp
        OptionsInit.cpp
        OptionsInit.h
        paths.cpp
        paths.h
        PathContext.h
        OptionsDiffOptions.cpp
        OptionsDiffOptions.h
        OptionsDiffColors.cpp
        OptionsDiffColors.h
        OptionsFont.h
        OptionsFont.cpp
        CompareOptions.h
        MergeCmdLineInfo.h
        MergeCmdLineInfo.cpp
        diffutils/src/diff.h
        diffutils/src/system.h
        diffutils/config.h
        FileFilterHelper.h
        FileFilterHelper.cpp
        PathContext.cpp
        DirItem.h
        DirItem.cpp
        FileVersion.h
        FileVersion.cpp
        FileFilterMgr.h
        Environment.h
        Environment.cpp
        FileFilterMgr.cpp
        FileFilter.h
        FileFilter.cpp
        FilterList.h
        FilterList.cpp
        Common/UniFile.h
        Common/UniFile.cpp
        # opendialog.cpp
        # openfilesdialog.cpp
        qlabelclick.cpp QOptionsMgr.cpp QOptionsMgr.h)

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
        PropMarkerColors.h
        PropSyntaxColors.h
        PropTextColors.h
        PropMergeColors.h
        PropCompare.h
        PropCompareBinary.h
        PropCompareFolder.h
        PropCompareImage.h
        MainMenu.h
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
        qt_ui/QPropMarkerColors.ui
        qt_ui/QPropSyntaxColors.ui
        qt_ui/QPropTextColors.ui
        qt_ui/QPropMergeColors.ui
        qt_ui/QPropCompare.ui
        qt_ui/QPropCompareBinary.ui
        qt_ui/QPropCompareFolder.ui
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
        qt_ui/QMainMenu.ui
        #opendialog.ui
        #openfilesdialog.ui
        )

set ( RESOURCES
        gui.qrc
        translations.qrc
        )

# set the POCO paths and libs
set(Poco_DIR "../ext/Poco/cmake-build-debug/Poco")
set(PocoFoundation_DIR "../ext/Poco/cmake-build-debug/Foundation") # the directory containing "include" and "lib"
set(PocoNet_DIR "../ext/Poco/cmake-build-debug/Net") # the directory containing "include" and "lib"

set(BOOST_ROOT "../ext/boost_1_70_0")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

SET(_moc ${CMAKE_CURRENT_BINARY_DIR}/${_current_MOC})

# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Poco REQUIRED Foundation Net )
find_package(Boost 1.70.0 COMPONENTS filesystem regex)
find_package(Qt5LinguistTools)

# include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT5_WRAP_UI( UI_HEADERS ${UIS} )
QT5_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

FILE(GLOB translations_IN ${CMAKE_CURRENT_SOURCE_DIR}/translations/*.ts)
string(REGEX REPLACE "[.]ts" ".qm" OUTPUT_Translations "${translations_IN}")

add_custom_command(
        OUTPUT   ${OUTPUT_Translations}
        COMMAND ${Qt5_LUPDATE_EXECUTABLE} -verbose ${translations_IN}
        COMMAND ${Qt5_LRELEASE_EXECUTABLE} ${translations_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories("${CMAKE_SOURCE_DIR}/../ext/libxdiff/lib")

add_executable( winmerge_gui ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} version.rc)

set_target_properties( winmerge_gui
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} xdiff)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${OpenMP_CXX_LIBRARIES})
target_link_libraries(${PROJECT_NAME} Poco::Foundation Poco::Net)
target_link_libraries(${PROJECT_NAME} Boost::filesystem Boost::regex)

set (FileList contributors.txt COPYING LICENSE README.md)

foreach( file_i ${FileList})
    add_custom_command(
            TARGET winmerge_gui POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/${file_i} ${PROJECT_BINARY_DIR}/bin
    )
endforeach( file_i )

add_custom_command(TARGET winmerge_gui POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Docs/Users ${CMAKE_BINARY_DIR}/bin/Docs
        )