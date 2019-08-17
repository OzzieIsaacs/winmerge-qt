/////////////////////////////////////////////////////////////////////////////
//    License (GPLv2+):
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    General Public License for more details.
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/////////////////////////////////////////////////////////////////////////////
/**
 *  @file FileFilterMgr.h
 *
 *  @brief Declaration file for FileFilterMgr
 */ 
#pragma once

#include <vector>
// #include "UnicodeString.h"
#include "FileFilter.h"
#include <QString>

/**
 * @brief Return values for many filter functions.
 */
enum FILTER_RETVALUE
{
	FILTER_OK = 0,  /**< Success */
	FILTER_ERROR_FILEACCESS,  /**< File could not be opened etc. */
	FILTER_NOTFOUND, /**< Filter not found */
};

/**
 * @brief File filter manager for handling filefilters.
 *
 * The FileFilterMgr loads a collection of named file filters from disk,
 * and provides lookup access by name, or array access by index, to these
 * named filters. It also provides test functions for actually using the
 * filters.
 *
 * We are using PCRE for regular expressions. Nice thing in PCRE is it supports
 * UTF-8 unicode, unlike many other libs. For ANSI builds we use just ansi
 * strings, and for unicode we must first convert strings to UTF-8.
 */
class FileFilterMgr
{
private:

public:
	~FileFilterMgr();
	// Reload filter array from specified directory (passed to CFileFind)
	void LoadFromDirectory(const QString& dir, const QString& szPattern, const QString& szExt);
	// Reload an edited filter
	int ReloadFilterFromDisk(FileFilter * pfilter);
	int ReloadFilterFromDisk(const QString& szFullPath);
	// Load a filter from a string
	void LoadFilterString(const QString& szFilterString);
	int AddFilter(const QString& szFilterFile);
	void RemoveFilter(const QString& szFilterFile);

	// access to array of filters
	int GetFilterCount() const { return (int) m_filters.size(); }
	QString GetFilterName(int i) const;
	QString GetFilterName(const FileFilter *pFilter) const;
	QString GetFilterPath(int i) const;
	QString GetFilterDesc(int i) const;
	QString GetFilterDesc(const FileFilter *pFilter) const;
	FileFilter * GetFilterByPath(const QString& szFilterName);
	QString GetFullpath(FileFilter * pfilter) const;

	// methods to actually use filter
	bool TestFileNameAgainstFilter(const FileFilter * pFilter, const QString& szFileName) const;
	bool TestDirNameAgainstFilter(const FileFilter * pFilter, const QString& szDirName) const;

	void DeleteAllFilters();

// Implementation methods
protected:
	// Clear the list of known filters
	// Load a filter from a file (if syntax is valid)
	FileFilter * LoadFilterFile(const QString& szFilepath, int & errorcode);

// Implementation data
private:
	std::vector<FileFilterPtr> m_filters; /*< List of filters loaded */
};


bool TestAgainstRegList(const std::vector<FileFilterElementPtr> *filterList, const QString& szTest);
void EmptyFilterList(std::vector<FileFilterElementPtr> *filterList);
