/** 
 * @file  Environment.cpp
 *
 * @brief Environment related routines.
 */

#define POCO_NO_UNWINDOWS 1
#include "Environment.h"
// #include <windows.h>
#pragma warning (push)			// prevent "warning C4091: 'typedef ': ignored on left of 'tagGPFIDL_FLAGS' when no variable is declared"
#pragma warning (disable:4091)	// VC bug when using XP enabled toolsets.
// #include <shlobj.h>
#pragma warning (pop)
#include <sstream>
#include <Poco/Path.h>
#include <Poco/Process.h>
#include "paths.h"
// #include "unicoder.h"

#ifdef Q_OS_LINUX
	#include <linux/limits.h>
	#define MAX_PATH PATH_MAX
#endif

using Poco::Path;
using Poco::Process;

namespace env
{

/**
 * @brief Temp path.
 * Static string used by GetTemporaryPath() for storing temp path.
 */
static QString strTempPath;
static QString strProgPath;

void SetTemporaryPath(const QString& path)
{
	strTempPath = paths::AddTrailingSlash(paths::GetLongPath(path));
	paths::CreateIfNeeded(strTempPath);
}

/** 
 * @brief Get folder for temporary files.
 * This function returns system temp folder.
 * @return Temp path, or empty string if error happened.
 * @note Temp path is cached after first call.
 * @todo Should we return `nullptr` for error case?
 */
QString GetTemporaryPath()
{
	if (strTempPath.isEmpty())
	{
		strTempPath = GetSystemTempPath();
		if (strTempPath.isEmpty())
			return strTempPath;

		paths::CreateIfNeeded(strTempPath);
	}
	return strTempPath;
}

/**
 * @brief Get filename for temporary file.
 * @param [in] lpPathName Temporary file folder.
 * @param [in] lpPrefixString Prefix to use for filename.
 * @param [out] pnerr Error code if error happened.
 * @return Full path for temporary file or empty string if error happened.
 */
QString GetTemporaryFileName(const QString& lpPathName, const QString& lpPrefixString, int * pnerr /*= nullptr*/)
{
	QString buffer; // TCHAR [MAX_PATH] = {0};
	if (lpPathName.length() > MAX_PATH-14)
		return QString(""); // failure
	//int rtn = ::GetTempFileName(lpPathName, lpPrefixString, 0, buffer);
	// ToDO
	int rtn = 1;
	if (rtn == 0)
	{
		// ToDo: GetLast Error
		// int err = GetLastError();
		int err = 0;
		if (pnerr != nullptr)
			*pnerr = err;
		return QString("");
	}
	return buffer;
}

QString GetTempChildPath()
{
	QString path;
	do
	{
		path = paths::ConcatPath(GetTemporaryPath(), QString("%08x").arg(rand()));
	} while (paths::IsDirectory(path) || !paths::CreateIfNeeded(path));
	return path;
}

void SetProgPath(const QString& path)
{
	strProgPath = paths::AddTrailingSlash(path);
}

QString GetProgPath()
{
	if (strProgPath.isEmpty())
	{
		QString temp('\0');
		// TCHAR temp[MAX_PATH] = {0};
		// ToDO
		//GetModuleFileName(nullptr, temp, MAX_PATH);
		strProgPath = paths::GetPathOnly(temp);
	}
	return strProgPath;
}

/**
 * @brief Get Windows directory.
 * @return Windows directory.
 */
QString GetWindowsDirectory()
{
	QString path('\0');
	// ToDo port
	//TCHAR path[MAX_PATH];
	//path[0] = _T('\0');
	// ::GetWindowsDirectory(path, MAX_PATH);
	return path;
}

/**
 * @brief Return User's My Documents Folder.
 * This function returns full path to User's My Documents -folder.
 * @return Full path to My Documents -folder.
 */
QString GetMyDocuments()
{
	QString path('\0');
	// path[0] = ();
	// ToDo port
	//SHGetFolderPath(nullptr, CSIDL_PERSONAL, nullptr, 0, path);
	return path;
}

/**
 * @brief Return unique string for the instance.
 * This function formats an unique string for WinMerge instance. The string
 * is quaranteed to be unique for instance asking it.
 * @param [in] name Additional name used as part of the string.
 * @return Unique string for the instance.
 */
QString GetPerInstanceString(const QString& name)
{
	//std::basic_stringstream<QString> stream;
	QString stream;
	stream = name + Process::id();
	return QString(stream);
}

/**
 * @brief Get system temporary directory.
 * @return System temporary director.
 */
QString GetSystemTempPath()
{
	try
	{
		return QString::fromStdString(Path::temp());
	}
	catch (...)
	{
		return QString("");
	}
}

static bool launchProgram(const QString& sCmd, unsigned long wShowWindow)
{
	// ToDo: Port to Qt
	/*STARTUPINFO stInfo = { sizeof(STARTUPINFO) };
	stInfo.dwFlags = STARTF_USESHOWWINDOW;
	stInfo.wShowWindow = wShowWindow;
	PROCESS_INFORMATION processInfo;
	bool retVal = !!CreateProcess(nullptr, (LPTSTR)sCmd.c_str(),
		nullptr, nullptr, FALSE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr,
		&stInfo, &processInfo);
	if (!retVal)
		return false;
	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);*/
	return true;
}

/**
 * @brief Load registry keys from .reg file if existing .reg file
 */
bool LoadRegistryFromFile(const QString& sRegFilePath)
{
	/*if (paths::DoesPathExist(sRegFilePath) != paths::IS_EXISTING_FILE)
		return false;
	return launchProgram(_T("reg.exe import \"") + sRegFilePath + _T("\""), SW_HIDE);*/
}

/** 
 * @brief Save registry keys to .reg file if existing .reg file
 */
bool SaveRegistryToFile(const QString& sRegFilePath, const QString& sRegDir)
{
	/*if (paths::DoesPathExist(sRegFilePath) != paths::IS_EXISTING_FILE)
		return false;
	DeleteFile(sRegFilePath.c_str());
	return launchProgram(_T("reg.exe export HKCU\\") + sRegDir + _T(" \"") + sRegFilePath + _T("\""), SW_HIDE);*/
}

}
