/** 
 * @file  paths.h
 *
 * @brief Declaration file for path routines
 */
#pragma once

#include "PathContext.h"
#include <QString>
// #include "Common/UnicodeString.h"

#ifndef MAX_PATH_FULL
#  define MAX_PATH_FULL 32767
#endif

namespace paths
{

/**
 * @brief Possible values when checking for file/folder existence.
 */
typedef enum
{
	DOES_NOT_EXIST, /**< File or folder does not exist. */
	IS_EXISTING_FILE, /**< It is existing file */
	IS_EXISTING_DIR, /**< It is existing folder */
	IS_EXISTING_DIR_ARCHIVE, /**< It is existing folder */
} PATH_EXISTENCE;

bool EndsWithSlash(const QString& s);

PATH_EXISTENCE DoesPathExist(const QString& szPath, bool (*IsArchiveFile)(const QString&) = nullptr);
QString FindFileName(const QString& path);
QString FindExtension(const QString& path);
void normalize(QString & sPath);
QString GetLongPath(const QString& szPath, bool bExpandEnvs = true);
bool CreateIfNeeded(const QString& szPath);
PATH_EXISTENCE GetPairComparability(const PathContext & paths, bool (*IsArchiveFile)(const QString&) = nullptr);
bool IsDirectory(const QString& path);
bool IsShortcut(const QString& inPath);
QString CanonicalPath(const QString &inFile);
QString ConcatPath(const QString & path, const QString & subpath);
QString GetParentPath(const QString& path);
QString GetLastSubdir(const QString & path);
bool IsPathAbsolute(const QString & path);
QString EnsurePathExist(const QString & sPath);
void SplitFilename(const QString& s, QString * path, QString * name, QString * ext);
QString GetPathOnly(const QString& fullpath);
bool IsURLorCLSID(const QString& path);
bool IsDecendant(const QString& path, const QString& ancestor);
inline QString AddTrailingSlash(const QString& path) { return !EndsWithSlash(path) ? path + ("\\") : path; }
QString ToWindowsPath(const QString& path);
QString ToUnixPath(const QString& path);

}	
