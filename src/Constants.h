/** 
 * @file Constants.h
 *
 * @brief WinMerge constants, URLs, paths etc.
 *
 */
#pragma once
#include <QString>

/** @brief URL for hyperlink in About-dialog. */
const QString WinMergeURL = ("https://winmerge.org/");

/**
 * @brief URL to help index in internet.
 * We use internet help when local help file is not found (not installed).
 */
const QString DocsURL = ("https://manual.winmerge.org/index.html");

/** @brief URL to translations page in internet. */
const QString TranslationsUrl = ("http://winmerge.org/translations/");

/** @brief URL of the GPL license. */
const QString LicenceUrl = ("http://www.gnu.org/licenses/gpl-2.0.html");

/** @brief Relative (to WinMerge executable ) path to local help file. */
const QString DocsPath = ("Docs/WinMerge%s.chm");

/** @brief Contributors list. */
const QString ContributorsPath = ("contributors.txt");

/** @brief Release notes in HTML format. */
const QString RelNotes = ("\\Docs\\ReleaseNotes.html");

/** @brief GPL Licence local file name. */
const QString LicenseFile = ("Copying");

/** @brief WinMerge folder in My Folders-folder. */
const QString WinMergeDocumentsFolder = ("WinMerge");

/**
 * @brief Default relative path to "My Documents" for private filters.
 * We want to use WinMerge folder as general user-file folder in future.
 * So it makes sense to have own subfolder for filters.
 */
const QString DefaultRelativeFilterPath = ("WinMerge/Filters");

/** @brief Executable Filename for ANSI build. */
const QString ExecutableFilename = ("WinMerge.exe");
/** @brief Executable Filename for Unicode build. */
const QString ExecutableFilenameU = ("WinMergeU.exe");

/** @brief Temp folder name prefix for WinMerge temp folders. */
const QString TempFolderPrefix = ("WinMergeEMP_");

/** @brief registry dir to WinMerge */
const QString RegDir = ("Software\\Thingamahoochie\\WinMerge");

/**
 * @brief Flags used when opening files
 */
enum
{
	FFILEOPEN_NONE		= 0x0000,
	FFILEOPEN_NOMRU		= 0x0001, /**< Do not add this path to MRU list */
	FFILEOPEN_READONLY	= 0x0002, /**< Open this path as read-only */
	FFILEOPEN_MODIFIED  = 0x0004, /**< Mark file modified after opening. */
	FFILEOPEN_CMDLINE	= 0x0010, /**< Path is read from commandline */
	FFILEOPEN_PROJECT	= 0x0020, /**< Path is read from project-file */
	FFILEOPEN_SETFOCUS  = 0x0040, /**< Set focus to this pane */
	FFILEOPEN_AUTOMERGE = 0x0080, /**< auto-merge at this pane */
};
