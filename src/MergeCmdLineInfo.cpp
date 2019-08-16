/////////////////////////////////////////////////////////////////////////////
//
//    WinMerge: An interactive diff/merge utility
//    Copyright (C) 1997 Dean P. Grimm
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
/////////////////////////////////////////////////////////////////////////////

/** 
 * @file  MergeCmdLineInfo.cpp
 *
 * @brief MergeCmdLineInfo class implementation.
 *
 */


#include "MergeCmdLineInfo.h"
#include "Constants.h"
#include "paths.h"
#include "OptionsDef.h"
#include <map>

// MergeCmdLineInfo

/**
 * @brief Eat and digest a command line parameter.
 * @param [in] p Points into the command line.
 * @param [out] param Receives the digested command line parameter.
 * @param [out] flag Tells whether param is the name of a flag.
 * @return Points to the remaining portion of the command line.
 */
void MergeCmdLineInfo::EatParam(const QString& p, QString &param, bool *flag /*= nullptr*/)
{
	bool parameter = false;
	param = p.trimmed();

	if (param.at(0) == "\"" or param.at(0) == "'"){
		param.remove(0,1);
	}
	if (param.at(param.length()-1) == "\"" or param.at(param.length()-1) == "'"){
		param.chop(1);
	}

	if (param.at(0) == "-" && flag){
		param = param.remove(0,1).toLower();
		parameter = true;
	}
	if (flag){
		*flag = parameter;
	}
}

void MergeCmdLineInfo::SetOption(const QString& option, const QString& key){
	QString val("1");
	SetOption(option, key, &val);
}

/**
 * @brief Set WinMerge option from command line.
 * @param [in] p Points into the command line.
 * @param [in] key Name of WinMerge option to set.
 * @param [in] value Default value in case none is specified.
 * @return Points to the remaining portion of the command line.
 */
void MergeCmdLineInfo::SetOption(const QString& q, const QString& key,QString *value)
{
	QString s;
	if (q.at(0) == QString(':'))
	{
		EatParam(q, s);
		*value = s.remove(0,1);
	}
	m_Options.insert_or_assign(key, "!");
}

void MergeCmdLineInfo::SetConfig(const QString& q)
{
	QString s;
	if (q.at(0) == QString(':'))
	{
		EatParam(q, s);
		s.remove(0,1);
	}
	size_t pos = s.indexOf('=');
	if (pos != std::string::npos)
	{
		QString key = s.left(pos);
		QString value = s.remove(pos, pos + 1);
		m_Options.insert_or_assign(key, value);
	}
}

/**
 * @brief MergeCmdLineParser's constructor.
 * @param [in] q Points to the beginning of the command line.
 */
MergeCmdLineInfo::MergeCmdLineInfo(QStringList q):
	m_nCmdShow(SHOWNORMAL),
	m_bEscShutdown(false),
	m_bExitIfNoDiff(Disabled),
	m_bRecurse(false),
	m_bNonInteractive(false),
	m_bSingleInstance(false),
	m_bShowUsage(false),
	m_bNoPrefs(false),
	m_nCodepage(0),
	m_dwLeftFlags(FFILEOPEN_NONE),
	m_dwMiddleFlags(FFILEOPEN_NONE),
	m_dwRightFlags(FFILEOPEN_NONE)
{
	QString exeName = q.at(0);
	q.removeFirst();
	ParseWinMergeCmdLine(&q);
}

/**
 * @brief Add path to list of paths.
 * This method adds given string as a path to the list of paths. Path
 * are converted if needed, shortcuts expanded etc.
 * @param [in] path Path string to add.
 */
void MergeCmdLineInfo::AddPath(const QString &path)
{
	QString param(path);

	// Set flag indicating path is from command line
	const size_t ord = m_Files.GetSize();
	if (ord == 0)
		m_dwLeftFlags |= FFILEOPEN_CMDLINE;
	else if (ord == 1)
		m_dwRightFlags |= FFILEOPEN_CMDLINE;
	else if (ord == 2)
		m_dwMiddleFlags |= FFILEOPEN_CMDLINE;

	if (!paths::IsURLorCLSID(path))
	{
		// Convert paths given in Linux-style ('/' as separator) given from
		// Cygwin to Windows style ('\' as separator)
		// param.replace("/","\\");

		// If shortcut, expand it first
		/*if (paths::IsShortcut(param))
			param = paths::ExpandShortcut(param);*/
		param = paths::CanonicalPath(param);
		m_Files.SetPath(m_Files.GetSize(), param);
	}
	else
	{
		m_Files.SetPath(m_Files.GetSize(), param, false);
	}
}

/**
 * @brief Parse native WinMerge command line.
 * @param [in] p Points into the command line.
 */
void MergeCmdLineInfo::ParseWinMergeCmdLine(QStringList* q)
{
	QString param;
	bool flag;

	for (int i = 0; i < q->size(); ++i)
	{
		EatParam(q->at(i), param, &flag);
		if (!flag)
		{
			// Its not a flag so it is a path
			AddPath(param);
		}
		else if (param == QString("?"))
		{
			// -? to show common command line arguments.
			m_bShowUsage = true;
		}
		else if (param == QString("o"))
		{
			// -o "outputfilename"
			EatParam(q->at(++i), m_sOutputpath);
		}
		else if (param == QString("or"))
		{
			// -or "reportfilename"
			EatParam(q->at(++i), m_sReportFile);
		}
		else if (param == QString("dl"))
		{
			// -dl "desc" - description for left file
			EatParam(q->at(++i), m_sLeftDesc);
		}
		else if (param == QString("dm"))
		{
			// -dr "desc" - description for middle file
			EatParam(q->at(++i), m_sMiddleDesc);
		}
		else if (param == QString("dr"))
		{
			// -dr "desc" - description for right file
			EatParam(q->at(++i), m_sRightDesc);
		}
		else if (param == QString("e"))
		{
			// -e to allow closing with single esc press
			m_bEscShutdown = true;
		}
		else if (param == QString("f"))
		{
			// -f "mask" - file filter mask ("*.h *.cpp")
			EatParam(q->at(++i), m_sFileFilter);
		}
		else if (param == QString("r"))
		{
			// -r to compare recursively
			m_bRecurse = true;
		}
		else if (param == QString("s"))
		{
			// -s to allow only one instance
			m_bSingleInstance = true;
		}
		else if (param == QString("noninteractive"))
		{
			// -noninteractive to suppress message boxes & close with result code
			m_bNonInteractive = true;
		}
		else if (param == QString("noprefs"))
		{
			// -noprefs means do not load or remember options (preferences)
			m_bNoPrefs = true;
		}
		else if (param == QString("minimize"))
		{
			// -minimize means minimize the main window.
			m_nCmdShow = MINIMIZE;
		}
		else if (param == QString("maximize"))
		{
			// -maximize means maximize the main window.
			m_nCmdShow = MAXIMIZE;
		}
		else if (param == QString("prediffer"))
		{
			// Get prediffer if specified (otherwise prediffer will be blank, which is default)
			EatParam(q->at(++i), m_sPreDiffer);
		}
		else if (param == QString("wl"))
		{
			// -wl to open left path as read-only
			m_dwLeftFlags |= FFILEOPEN_READONLY;
		}
		else if (param == QString("wm"))
		{
			// -wm to open middle path as read-only
			m_dwMiddleFlags |= FFILEOPEN_READONLY;
		}
		else if (param == QString("wr"))
		{
			// -wr to open right path as read-only
			m_dwRightFlags |= FFILEOPEN_READONLY;
		}
		else if (param == QString("ul"))
		{
			// -ul to not add left path to MRU
			m_dwLeftFlags |= FFILEOPEN_NOMRU;
		}
		else if (param == QString("um"))
		{
			// -um to not add middle path to MRU
			m_dwMiddleFlags |= FFILEOPEN_NOMRU;
		}
		else if (param == QString("ur"))
		{
			// -ur to not add right path to MRU
			m_dwRightFlags |= FFILEOPEN_NOMRU;
		}
		else if (param == QString("u") || param == QString("ub"))
		{
			// -u or -ub (deprecated) to add neither right nor left path to MRU
			m_dwLeftFlags |= FFILEOPEN_NOMRU;
			m_dwMiddleFlags |= FFILEOPEN_NOMRU;
			m_dwRightFlags |= FFILEOPEN_NOMRU;
		}
		else if (param == QString("fl"))
		{
			// -fl to set focus to the left panbe
			m_dwLeftFlags |= FFILEOPEN_SETFOCUS;
		}
		else if (param == QString("fm"))
		{
			// -fm to set focus to the middle pane
			m_dwMiddleFlags |= FFILEOPEN_SETFOCUS;
		}
		else if (param == QString("fr"))
		{
			// -fr to set focus to the right pane
			m_dwRightFlags |= FFILEOPEN_SETFOCUS;
		}
		else if (param == QString("al"))
		{
			// -al to auto-merge at the left pane
			m_dwLeftFlags |= FFILEOPEN_AUTOMERGE;
		}
		else if (param == QString("am"))
		{
			// -am to auto-merge at the middle pane
			m_dwMiddleFlags |= FFILEOPEN_AUTOMERGE;
		}
		else if (param == QString("ar"))
		{
			// -ar to auto-merge at the right pane
			m_dwRightFlags |= FFILEOPEN_AUTOMERGE;
		}
		else if (param == QString("x"))
		{
			// -x to close application if files are identical.
			m_bExitIfNoDiff = Exit;
		}
		else if (param == QString("xq"))
		{
			// -xn to close application if files are identical without showing
			// any messages
			m_bExitIfNoDiff = ExitQuiet;
		}
		else if (param == QString("cp"))
		{
			QString codepage;
			EatParam(q->at(++i), codepage);
			//m_nCodepage = atoi(ucr::toUTF8(codepage).c_str()); // ToDo: Port
		}
		else if (param == QString("ignorews"))
		{
			SetOption(q->at(++i), OPT_CMP_IGNORE_WHITESPACE);
		}
		else if (param == QString("ignoreblanklines"))
		{
			SetOption(q->at(++i), OPT_CMP_IGNORE_BLANKLINES);
		}
		else if (param == QString("ignorecase"))
		{
			SetOption(q->at(++i), OPT_CMP_IGNORE_CASE);
		}
		else if (param == QString("ignoreeol"))
		{
			SetOption(q->at(++i), OPT_CMP_IGNORE_EOL);
		}
		else if (param == QString("ignorecodepage"))
		{
			SetOption(q->at(++i), OPT_CMP_IGNORE_CODEPAGE);
		}
		else if (param == QString("cfg") || param == ("config"))
		{
			SetConfig(q->at(++i));
		}
		else
		{
			m_sErrorMessages.push_back(("Unknown option '-") + param + ("'"));
		}
	}
	// If "compare file dir" make it "compare file dir\file".
	if (m_Files.GetSize() >= 2)
	{
		paths::PATH_EXISTENCE p1 = paths::DoesPathExist(m_Files[0]);
		paths::PATH_EXISTENCE p2 = paths::DoesPathExist(m_Files[1]);

		if ((p1 == paths::IS_EXISTING_FILE) && (p2 == paths::IS_EXISTING_DIR))
		{
			m_Files[1] = paths::ConcatPath(m_Files[1], paths::FindFileName(m_Files[0]));
		}
	}
	if (m_bShowUsage)
	{
		m_bNonInteractive = false;
	}
}
