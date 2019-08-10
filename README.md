# WinMerge


WinMerge-qt is a port of WinMerge (http://winmerge.org) to use cross-platform
with Qt framework. This project is still in very early stages.

Compiling
---------

WinMerge uses Qt's qmake or cmake. To create makefiles you'll need to
run command:

> qmake -recursive

in shell/command prompt. To create VS project files, run:

> qmake -recursive -tp vc

in Visual Studio command prompt.

Installed:
QT5-default
qtcreator
