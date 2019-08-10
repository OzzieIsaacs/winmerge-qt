#pragma once

#define POCO_NO_UNWINDOWS 1
#include <Poco/File.h>
// #include "UnicodeString.h"
// #include "unicoder.h"
#include <QString>

class TFile : public Poco::File
{
public:
/*	explicit TFile(const QString& path) : File(ucr::toUTF8(path)) {}
	void copyTo(const QString& path) const { File::copyTo(ucr::toUTF8(path)); }
	void moveTo(const QString& path) { File::moveTo(ucr::toUTF8(path)); }
	void renameTo(const QString& path) { File::renameTo(ucr::toUTF8(path)); }*/
	explicit TFile(const QString& path) : File(path.toStdString()) {}
	void copyTo(const QString& path) const { File::copyTo(path.toStdString()); }
	void moveTo(const QString& path) { File::moveTo(path.toStdString()); }
	void renameTo(const QString& path) { File::renameTo(path.toStdString()); }

};

