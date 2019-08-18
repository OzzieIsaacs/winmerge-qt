/////////////////////////////////////////////////////////////////////////////
//    License (GPLv2+):
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/////////////////////////////////////////////////////////////////////////////
/** 
 * @file  FileFilterHelper.h
 *
 * @brief Declaration file for FileFilterHelper
 */
#pragma once

#include <vector>
#include <memory>
// #include "UnicodeString.h"
#include <QString>
#include "DirItem.h"

class FileFilterMgr;
class FilterList;
struct FileFilter;

/**
 * @brief File extension of file filter files.
 */
const QString FileFilterExt(".flt");

/**
 * @brief Helper structure for UI and management of filters.
 *
 * This structure is mostly used as UI aid and to manage filters from UI.
 * fileinfo contains time of filter file's last modification time. By
 * comparing fileinfo to filter file in disk we can determine if file
 * is changed since we last time loaded it.
 */
struct FileFilterInfo
{
	QString name; 			/**< Name of filter */
	QString description; 	/**< Description of filter (shown in UI) */
	QString fullpath;		/**< Full path to filter file */
	DirItem fileinfo;		/**< For tracking if file has been modified */
};

/// Interface for testing files & directories for exclusion, as diff traverses file tree
class IDiffFilter
{
public:
	virtual bool includeFile(const QString& szFileName) const = 0;
	virtual bool includeDir(const QString& szDirName) const = 0;
	bool includeFile(const QString& szFileName1, const QString& szFileName2) const
	{
		if (!szFileName1.isEmpty())
			return includeFile(szFileName1);
		else if (!szFileName2.isEmpty())
			return includeFile(szFileName2);
		else
			return false;
	}
	bool includeFile(const QString& szFileName1, const QString& szFileName2, const QString& szFileName3) const
	{
		if (!szFileName1.isEmpty())
			return includeFile(szFileName1);
		else if (!szFileName2.isEmpty())
			return includeFile(szFileName2);
		else if (!szFileName3.isEmpty())
			return includeFile(szFileName3);
		else
			return false;
	}
	bool includeDir(const QString& szDirName1, const QString& szDirName2) const
	{
		if (!szDirName1.isEmpty())
			return includeDir(szDirName1);
		else if (!szDirName2.isEmpty())
			return includeDir(szDirName2);
		else
			return false;
	}
	bool includeDir(const QString& szDirName1, const QString& szDirName2, const QString& szDirName3) const
	{
		if (!szDirName1.isEmpty())
			return includeDir(szDirName1);
		else if (!szDirName2.isEmpty())
			return includeDir(szDirName2);
		else if (!szDirName3.isEmpty())
			return includeDir(szDirName3);
		else
			return false;
	}
};

/**
 * @brief Helper class for using filefilters.
 *
 * A FileFilterHelper object is the owner of any active mask, and of the file filter manager
 * This is kind of a File Filter SuperManager, taking care of both inline filters from strings
 *  and loaded file filters (the latter handled by its internal file filter manager)
 *
 * This class is mainly for handling two ways to filter files in WinMerge:
 * - File masks: *.ext lists (*.cpp *.h etc)
 * - File filters: regular expression rules in separate files
 *
 * There can be only one filter or file mask active at a time. This class
 * keeps track of selected filtering method and provides simple functions for
 * clients for querying if file is included to compare. Clients don't need
 * to care about compare methods etc details.
 */
class FileFilterHelper : public IDiffFilter
{
public:
	FileFilterHelper();
	~FileFilterHelper();

	QString GetGlobalFilterPathWithCreate() const;
	QString GetUserFilterPathWithCreate() const;

	FileFilterMgr * GetManager() const;
	void SetFileFilterPath(const QString& szFileFilterPath);
	void GetFileFilters(std::vector<FileFilterInfo> * filters, QString & selected) const;
	QString GetFileFilterName(const QString& filterPath) const;
	QString GetFileFilterPath(const QString& filterName) const;
	void SetUserFilterPath(const QString & filterPath);

	void ReloadUpdatedFilters();
	void LoadAllFileFilters();

	void LoadFileFilterDirPattern(const QString& dir, const QString& szPattern);

	void UseMask(bool bUseMask);
	void SetMask(const QString& strMask);

	bool IsUsingMask() const;
	QString GetFilterNameOrMask() const;
	bool SetFilter(const QString &filter);

	bool includeFile(const QString& szFileName) const;
	bool includeDir(const QString& szDirName) const;

protected:
	QString ParseExtensions(const QString &extensions) const;

private:
	std::unique_ptr<FilterList> m_pMaskFilter;       /*< Filter for filemasks (*.cpp) */
	FileFilter * m_currentFilter;     /*< Currently selected filefilter */
	std::unique_ptr<FileFilterMgr> m_fileFilterMgr;  /*< Associated FileFilterMgr */
	QString m_sFileFilterPath;        /*< Path to current filter */
	QString m_sMask;   /*< File mask (if defined) "*.cpp *.h" etc */
	bool m_bUseMask;   /*< If `true` file mask is used, filter otherwise */
	QString m_sGlobalFilterPath;    /*< Path for shared filters */
	QString m_sUserSelFilterPath;     /*< Path for user's private filters */
};
