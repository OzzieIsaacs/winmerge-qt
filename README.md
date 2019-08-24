# WinMerge


WinMerge-qt is a port of WinMerge (http://winmerge.org) to use cross-platform
with Qt framework. This project is still in very early stages.

## Compiling
---------

WinMerge uses Qt's qmake or cmake. To create makefiles you'll need to
run command:

> qmake -recursive

in shell/command prompt. To create VS project files, run:

> qmake -recursive -tp vc

in Visual Studio command prompt.

Installed:

## Compiling qmake
qt 5.9.5 Linux Mint
qmake 3.1

## Compiling cmake

tested using gcc 7.4 on linux mint
- qt5-default and Qttools5-dev-tools
using boost 1.70.0 and poco 
cmake 3.13.2 (min 3.9)


# Current status

- [X] Compiling with cmake and qmake (Qt Designer Project) is working on Linux
- [X] Poco lib has to build manually before compiling the main project
- [x] Libxdiff is building together with main project
- [ ] boost lib is not included in  build (and is currently not needed)
- [X] Mainscreen showing menu bar
- [X] Aboutbox is working (no title bar as original, white background)
- [ ] Aboutbox clickable link for winmerge homepage is working, browser is opening on Linux, Windows maybe, MacOS no
- [x] GNU Licence, Contributors, can be opened in editor on Linux, Windows maybe, MacOS no 
- [ ] Help is not working (Port to QHelpEngineCore)
- [X] OptionsManager is replaces by QSettings
- [ ] Mechanism for setting default values needs to be implemented
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

