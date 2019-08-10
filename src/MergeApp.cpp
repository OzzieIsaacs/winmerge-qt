#ifdef __linux__
#include <cerrno>
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

/**
 * @brief Get Options Manager.
 * @return Pointer to OptionsMgr.
 */

COptionsMgr * GetOptionsMgr()
{
	// COptionsMgr *test = MainWindow::getInstance().GetMergeOptionsMgr();
	//QList alfea = QApplication::instance()->findChildren<MainWindow *>();
	// int i = QApplication::instance()->findChildren<QMainWindow *>("QMainWindow").size();
	//COptionsMgr *alfa = QApplication::instance()->findChild<MainWindow *>()->GetMergeOptionsMgr();
	//return i;// QApplication::instance()->findChildren<MainWindow *>().first()->GetMergeOptionsMgr();
	// MainWindow* mainWindow = MainWindow::getInstance();
	// return mainWindow->GetMergeOptionsMgr();
	// return test;

	//CMergeApp *pApp = static_cast<CMergeApp *>(AfxGetApp());
	//return pApp->GetMergeOptionsMgr();
}
/*
// Send message to log and debug window
void LogErrorString(const String& sz)
{
	if (sz.empty()) return;
	CString now = COleDateTime::GetCurrentTime().Format();
	TRACE(_T("%s: %s\n"), (LPCTSTR)now, sz.c_str());
}

// Send message to log and debug window
void LogErrorStringUTF8(const std::string& sz)
{
	if (sz.empty()) return;
	String str = ucr::toTString(sz);
	CString now = COleDateTime::GetCurrentTime().Format();
	TRACE(_T("%s: %s\n"), (LPCTSTR)now, str.c_str());
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

String tr(const std::string &str)
{
	String translated_str;
	theApp.TranslateString(str, translated_str);
	return translated_str;
}

void AppErrorMessageBox(const String& msg)
{
	AppMsgBox::error(msg);
}

namespace AppMsgBox
{

namespace detail
{
	int convert_to_winflags(int flags)
	{
		int newflags = 0;

		if ((flags & (YES | NO | CANCEL)) == (YES | NO | CANCEL)) newflags |= MB_YESNOCANCEL;
		else if ((flags & (YES | NO)) == (YES | NO)) newflags |= MB_YESNO;
		else if ((flags & (OK | CANCEL)) == (OK | CANCEL)) newflags |= MB_OKCANCEL;
		else if ((flags & OK) == OK) newflags |= MB_OK;
	
		if (flags & YES_TO_ALL) newflags |= MB_YES_TO_ALL;
		if (flags & DONT_DISPLAY_AGAIN) newflags |= MB_DONT_DISPLAY_AGAIN;

		return newflags;
	}

	int convert_resp(int resp)
	{
		switch (resp)
		{
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
/*
int error(const String& msg, int type)
{
	return detail::convert_resp(AfxMessageBox(msg.c_str(), detail::convert_to_winflags(type) | MB_ICONSTOP));
}

int warning(const String& msg, int type)
{
	return detail::convert_resp(AfxMessageBox(msg.c_str(), detail::convert_to_winflags(type) | MB_ICONWARNING));
}

int information(const String& msg, int type)
{
	return detail::convert_resp(AfxMessageBox(msg.c_str(), detail::convert_to_winflags(type) | MB_ICONINFORMATION));
}

}*/

AboutInfo::AboutInfo()
{
    CVersionInfo verinfo;
	// version = strutils::format_string1("Version %1", );
	version = QString("Version %1").arg(verinfo.GetProductVersion());
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
#ifdef _UNICODE
	version += _T(" ");
	version += _("Unicode");
#endif

#if defined _M_IX86
	version += " ";
	version += "x86";
#elif defined _M_IA64
	version += _T(" IA64");
#elif defined _M_X64
	version += " ";
	version += "X64";
#endif

#if defined _DEBUG
	version += " (";
	version += "Debug";
	version += ")";
#endif

    copyright = ("WinMerge comes with ABSOLUTELY NO WARRANTY. This is free software and you are welcome to redistribute it under certain circumstances; see the GNU General Public License in the Help menu for details.");
    copyright += ("\n");
    copyright += verinfo.GetLegalCopyright();
    copyright += (" - All rights reserved.");

    website = ("winmerge.org"); // WinMergeURL;

    developers = ("Developers:\nDean Grimm, Christian List, Kimmo Varis, Jochen Tucht, Tim Gerundt, Takashi Sawanaka, Gal Hammer, Alexander Skinner");
	developers.replace(", ","\n");
    // strutils::replace(developers, _T(", "), _T("\n"));
}
