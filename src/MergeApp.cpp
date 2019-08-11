#ifdef __linux__
#include <cerrno>
#include <iostream>
#define TRACE(ARG) std::cout << #ARG << std::endl; ARG
#else
#include "StdAfx.h"

#endif

#include "MergeApp.h"
// #include "Merge.h"
#include "Common/VersionInfo.h"
// #include "paths.h"
#include "Constants.h"
// #include "unicoder.h"
#include <QString>
#include <QCoreApplication>
#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include <QTime>
#include "MainFrm.h"

// Get user language description of error, if available
QString GetSysError(int nerr /* =-1 */)
{
	QString str = "?";
#ifdef __linux__
	str = strerror(errno);
#else
	if (nerr == -1)
		nerr = GetLastError();
	LPVOID lpMsgBuf;
	String str = _T("?");
	if (FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		nerr,
		0, // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		nullptr 
		))
	{
		str = (LPCTSTR)lpMsgBuf;
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
#endif
	return str;
}


// Send message to log and debug window
void LogErrorString(const QString& sz)
{
	if (sz.isEmpty()) return;
	// ToDO: Check if formatstring is necessary
	QString now = QTime::currentTime().toString();
	//CString now = COleDateTime::GetCurrentTime().Format();
	TRACE((QString("%s: %s").arg(now, sz)).toStdString());
}

/// Send message to log and debug window
void LogErrorStringUTF8(const std::string& sz)
{
	if (sz.empty()) return;
	QString str = QString::fromStdString(sz);
	QString now = QTime::currentTime().toString();
	TRACE((QString("%s: %s").arg(now, str)).toStdString());
}

/**
 * @brief Load string resource and return as CString.
 * @param [in] id Resource string ID.
 * @return Resource string as CString.
 */
/*String LoadResString(unsigned id)
{
	return theApp.LoadString(id);
}
*/


namespace AppMsgBox {

	/*namespace detail {
		int convert_to_winflags(int flags) {
			int newflags = 0;

			if ((flags & (YES | NO | CANCEL)) == (YES | NO | CANCEL)) newflags |= MB_YESNOCANCEL;
			else if ((flags & (YES | NO)) == (YES | NO)) newflags |= MB_YESNO;
			else if ((flags & (OK | CANCEL)) == (OK | CANCEL)) newflags |= MB_OKCANCEL;
			else if ((flags & OK) == OK) newflags |= MB_OK;

			if (flags & YES_TO_ALL) newflags |= MB_YES_TO_ALL;
			if (flags & DONT_DISPLAY_AGAIN) newflags |= MB_DONT_DISPLAY_AGAIN;

			return newflags;
		}

		int convert_resp(int resp) {
			switch (resp) {
				case IDOK:
					return OK;
				case IDCANCEL:
					return CANCEL;
				case IDNO:
					return NO;
				case IDYES:
					return YES;
				case IDYESTOALL:
					return YES_TO_ALL;
				default:
					return OK;
			}
		}
	}*/

	int error(const QString &msg, int type=0) {
		return QMessageBox::critical(nullptr, QObject::tr("Error"), msg);
		//return detail::convert_resp(AfxMessageBox(msg.c_str(), detail::convert_to_winflags(type) | MB_ICONSTOP));
	}

	int warning(const QString &msg, int type=0) {
		return QMessageBox::warning(nullptr, QObject::tr("Warning"), msg);
		//return detail::convert_resp(AfxMessageBox(msg.c_str(), detail::convert_to_winflags(type) | MB_ICONWARNING));
	}

	int information(const QString &msg, int type=0) {
		return QMessageBox::information(nullptr, QObject::tr("Information"), msg);
		// return detail::convert_resp(AfxMessageBox(msg.c_str(), detail::convert_to_winflags(type) | MB_ICONINFORMATION));
	}

}

void AppErrorMessageBox(const QString& msg)
{
	AppMsgBox::error(msg);
}

AboutInfo::AboutInfo()
{
    CVersionInfo verinfo;
	// version = strutils::format_string1("Version %1", );
	version = QString(QObject::tr("Version %1")).arg(verinfo.GetProductVersion());
	private_build = verinfo.GetPrivateBuild();

    if (!private_build.isEmpty())
	{
		version += " + " + private_build;
	}

    if (version.indexOf(" - ") != std::string::npos)
	{
        version.replace(" - ","\n");
		version += " ";
	}
	else
	{
		version += "\n";
    }
//ToDo: Is this right??
#ifdef Q_COMPILER_UNICODE_STRINGS
	version += " ";
	version += QObject::tr("Unicode");
#endif

#if defined Q_PROCESSOR_X86_32
	version += " ";
	version += "x86";
#elif defined Q_PROCESSOR_IA64
	version += " IA64";
#elif defined Q_PROCESSOR_X86_64
	version += " ";
	version += "X64";
#endif

#if defined QT_DEBUG
	version += " (";
	version += "Debug";
	version += ")";
#endif

    copyright = QObject::tr("WinMerge comes with ABSOLUTELY NO WARRANTY. This is free software and you are welcome to redistribute it under certain circumstances; see the GNU General Public License in the Help menu for details.");
    copyright += ("\n");
    copyright += verinfo.GetLegalCopyright();
    copyright += QObject::tr(" - All rights reserved.");

    website = WinMergeURL;

    developers = QObject::tr("Developers:\n");
    developers += "Dean Grimm, Christian List, Kimmo Varis, Jochen Tucht, Tim Gerundt, Takashi Sawanaka, Gal Hammer, Alexander Skinner";
	developers.replace(", ","\n");
}
