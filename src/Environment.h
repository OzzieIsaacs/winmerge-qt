/** 
 * @file  Environment.h
 *
 * @brief Declaration file for Environment-related routines.
 */
#pragma once

// #include "UnicodeString.h"
#include <QString>

namespace env
{

void SetTemporaryPath(const QString& path);
QString GetTemporaryPath();
QString GetTemporaryFileName(const QString& lpPathName, const QString& lpPrefixString,
		int * pnerr = nullptr);
QString GetTempChildPath();
void SetProgPath(const QString& path);
QString GetProgPath();

QString GetWindowsDirectory();
QString GetMyDocuments();
QString GetSystemTempPath();

QString GetPerInstanceString(const QString& name);

bool LoadRegistryFromFile(const QString& sRegFilePath);
bool SaveRegistryToFile(const QString& sRegFilePath, const QString& sRegDir);

}
