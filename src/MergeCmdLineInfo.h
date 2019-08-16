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
 * @file  MergeCmdLineInfo.h
 *
 * @brief MergeCmdLineInfo class declaration.
 *
 */
// ID line follows -- this is updated by SVN
// $Id: MergeCmdLineInfo.h 6940 2009-08-01 17:29:01Z kimmov $

#pragma once

// #include "Common/UnicodeString.h"
#include "PathContext.h"
#include <map>
#include "tchar.h"
#include <QStringList>
#include "QOptionsMgr.h"

/** 
 * @brief WinMerge's command line handler.
 * This class calls command line parser(s) and allows reading parsed values
 * from public member variables.
 */
class MergeCmdLineInfo
{
public:
	explicit MergeCmdLineInfo(QStringList );

public:

	enum ExitNoDiff
	{
		Disabled, /**< Don't exit. */
		Exit, /**< Exit and show message. */
		ExitQuiet, /**< Exit and don't show message. */
	};

	enum ShowWindowType
	{
		SHOWNORMAL = 1,
		MAXIMIZE = 3,
		MINIMIZE = 6,
	};

	ShowWindowType m_nCmdShow; /**< Initial state of the application's window. */

	bool m_bEscShutdown; /**< Pressing ESC will close the application */
	ExitNoDiff m_bExitIfNoDiff; /**< Exit if files are identical. */
	bool m_bRecurse; /**< Include sub folder in directories compare. */
	bool m_bNonInteractive; /**< Suppress user's notifications. */
	bool m_bSingleInstance; /**< Allow only one instance of WinMerge executable. */
	bool m_bShowUsage; /**< Show a brief reminder to command line arguments. */
	int  m_nCodepage;  /**< Codepage. */
	bool m_bNoPrefs; /**< Do not load or remember options (preferences) */   

	unsigned m_dwLeftFlags; /**< Left side file's behavior options. */
	unsigned m_dwMiddleFlags; /**< Middle side file's behavior options. */
	unsigned m_dwRightFlags; /**< Right side file's behavior options. */

	QString m_sLeftDesc; /**< Left side file's description. */
	QString m_sMiddleDesc; /**< Middle side file's description. */
	QString m_sRightDesc; /**< Right side file's description. */

	QString m_sFileFilter; /**< File filter mask. */
	QString m_sPreDiffer; /**< Pre-differ name. */

	QString m_sOutputpath;
	QString m_sReportFile;

	PathContext m_Files; /**< Files (or directories) to compare. */

	std::map<QString, QString> m_Options;

	std::vector<QString> m_sErrorMessages;

private:

	void EatParam(const QString &, QString &, bool *flag = nullptr);
	void SetOption(const QString& option, const QString& key, QString* value);
	void SetOption(const QString& option, const QString& key);
	void SetConfig(const QString& option);

	void ParseWinMergeCmdLine(QStringList* q);
	void AddPath(const QString &path);

	/** Operator= is not implemented. */
	MergeCmdLineInfo& operator=(const MergeCmdLineInfo& rhs);
};

