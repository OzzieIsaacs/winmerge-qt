# WinMerge


WinMerge-qt is a experiment to port WinMerge (http://winmerge.org) to use cross-platform
with Qt5 framework. This project is still in very early stages.

## Prerequisites

Needed packages on Linux (example for Linux Mint)
- QT5-default


## Compiling with qmake

- qtcreator


## Compiling with cmake as build tool

- gcc x.xx


# Current status

- [X] Compiling with cmake and qmake (Qt Designer Project) is working on Linux
- [X] Poco lib has to build manually before compiling the main project
- [x] Libxdiff is building together with main project
- [ ] boost lib is not included in build (but "prebuild" with boost buildchain is needed and working)
- [X] Mainscreen showing menu bar
- [X] Aboutbox is working (no title bar as original, white background)
- [ ] Aboutbox clickable link for winmerge homepage is working, browser is opening on Linux, Windows maybe, MacOS no
- [x] GNU Licence, Contributors, can be opened in editor on Linux, Windows maybe, MacOS no 
- [ ] Help is not working (Port to QHelpEngineCore)
- [X] OptionsManager is replaces by QSettings
- [X] Mechanism for setting default values needs to be implemented
- [ ] Settings have to be send and returned to settings dialog  
- [ ] Basic translation mechanism is implemented
- [ ] Changing language is currently not possible
- [x] Preferences Dialog can be opened, different preferences pages can be selected
- [x] Some Preferences can be saved, many elements working (enabling disabling elements)
- [ ] Preferences filling comboboxes all color selection elements are not working
- [ ] Qt has no mechanism for "not showing this dialog again" (except error dialogs), which are not applicable for winmerge
- [ ] Command line arguments not parsed
- [ ] Main menu is loaded dynamically (mechanism for loading other menus should work)
- [ ] Toolbar for menus is currently not generated and filled (only dummy Toolbar)
- [x] Debug and Info output is ported, but untested
- [x] Version information is taken from version.h file
- [x] File Info metadata for windows should work
- [ ] FileFilter is basically ported, compiles, but is untested (and some parts are commented out)
- [ ] Handling of different codepages needs to be implemented
- [ ] File VersionInfo.h is commented out (no version is returned)
- [ ] File attributes are not properly handled by FileFilter 
