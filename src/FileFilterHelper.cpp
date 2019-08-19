/////////////////////////////////////////////////////////////////////////////
//    License (GPLv2+):
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or (at
//    your option) any later version.
//    
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/////////////////////////////////////////////////////////////////////////////
/** 
 * @file  FileFilterHelper.cpp
 *
 * @brief Implementation file for FileFilterHelper class
 */

#include "FileFilterHelper.h"
#include "paths.h"
#include <QDebug>

#include "FilterList.h"
#include "DirItem.h"
#include "FileFilterMgr.h"
#include "Environment.h"
// #include "UnicodeString.h"
// #include "unicoder.h"
#include <QDebug>
using std::vector;

/** 
 * @brief Constructor, creates new filtermanager.
 */
FileFilterHelper::FileFilterHelper()
: m_pMaskFilter(nullptr)
, m_bUseMask(true)
, m_fileFilterMgr(new FileFilterMgr) // ToDo
, m_currentFilter(nullptr)
{
	qDebug() << "HElp";
	qDebug() << m_bUseMask;
}

/** 
 * @brief Destructor, deletes filtermanager.
 */
FileFilterHelper::~FileFilterHelper()
{
}

/** 
 * @brief Return filtermanager used.
 */

FileFilterMgr * FileFilterHelper::GetManager() const
{
	return m_fileFilterMgr.get();
}

/**
 * @brief Store current filter path.
 *
 * Select filter based on filepath. If filter with that path
 * is found select it. Otherwise set path to empty (default).
 * @param [in] szFileFilterPath Full path to filter to select.
 */
void FileFilterHelper::SetFileFilterPath(const QString& szFileFilterPath)
{
	// Use none as default path
	m_sFileFilterPath.clear();

	if (m_fileFilterMgr == nullptr)
		return;

	// Don't bother to lookup empty path
	if (!szFileFilterPath.isEmpty())
	{
		m_currentFilter = m_fileFilterMgr->GetFilterByPath(szFileFilterPath);
		if (m_currentFilter != nullptr)
			m_sFileFilterPath = szFileFilterPath;
	}
}

/**
 * @brief Get list of filters currently available.
 *
 * @param [out] filters Filter list to receive found filters.
 * @param [out] selected Filepath of currently selected filter.
 */
void FileFilterHelper::GetFileFilters(std::vector<FileFilterInfo> * filters, QString & selected) const
{
	/*if (m_fileFilterMgr != nullptr)
	{
		const int count = m_fileFilterMgr->GetFilterCount();
		filters->reserve(count);
		for (int i = 0; i < count; ++i)
		{
			FileFilterInfo filter;
			filter.fullpath = m_fileFilterMgr->GetFilterPath(i);
			filter.name = m_fileFilterMgr->GetFilterName(i);
			filter.description = m_fileFilterMgr->GetFilterDesc(i);
			filters->push_back(filter);
		}
	}
	selected = m_sFileFilterPath;*/
}

/**
 * @brief Return name of filter in given file.
 * If no filter cannot be found, return empty string.
 * @param [in] filterPath Path to filterfile.
 * @sa FileFilterHelper::GetFileFilterPath()
 */
QString FileFilterHelper::GetFileFilterName(const QString& filterPath) const
{
	vector<FileFilterInfo> filters;
	QString selected;
	QString name;

	GetFileFilters(&filters, selected);
	vector<FileFilterInfo>::const_iterator iter = filters.begin();
	while (iter != filters.end())
	{
		if ((*iter).fullpath == filterPath)
		{
			name = (*iter).name;
			break;
		}
		++iter;
	}
	return name;
}

/** 
 * @brief Return path to filter with given name.
 * @param [in] filterName Name of filter.
 * @sa FileFilterHelper::GetFileFilterName()
 */
QString FileFilterHelper::GetFileFilterPath(const QString& filterName) const
{
	vector<FileFilterInfo> filters;
	QString selected;
	QString path;

	GetFileFilters(&filters, selected);
	vector<FileFilterInfo>::const_iterator iter = filters.begin();
	while (iter != filters.end())
	{
		if ((*iter).name == filterName)
		{
			path = (*iter).fullpath;
			break;
		}
		++iter;
	}
	return path;
}

/** 
 * @brief Set User's filter folder.
 * @param [in] filterPath Location of User's filters.
 */
void FileFilterHelper::SetUserFilterPath(const QString & filterPath)
{
	m_sUserSelFilterPath = filterPath;
	paths::normalize(m_sUserSelFilterPath);
}

/** 
 * @brief Select between mask and filterfile.
 * @param [in] bUseMask If true we use mask instead of filter files.
 */
void FileFilterHelper::UseMask(bool bUseMask)
{
	m_bUseMask = bUseMask;
	if (m_bUseMask)
	{
		if (m_pMaskFilter == nullptr)
		{
			m_pMaskFilter.reset(new FilterList);
		}
	}
	else
	{
		m_pMaskFilter.reset();
	}
}

/** 
 * @brief Set filemask for filtering.
 * @param [in] strMask Mask to set (e.g. *.cpp;*.h).
 */
void FileFilterHelper::SetMask(const QString& strMask)
{
	qDebug() << m_bUseMask;
	if (!m_bUseMask)
	{

		throw "Filter mask tried to set when masks disabled!";
	}
	m_sMask = strMask;
	QString regExp = ParseExtensions(strMask);

	std::string regexp_str = QString(regExp).toStdString();

	//m_pMaskFilter->RemoveAllFilters();	ToDO revert
	//m_pMaskFilter->AddRegExp(regexp_str);
}

/**
 * @brief Check if any of filefilter rules match to filename.
 *
 * @param [in] szFileName Filename to test.
 * @return true unless we're suppressing this file by filter
 */
bool FileFilterHelper::includeFile(const QString& szFileName) const
{
	if (m_bUseMask)
	{
		if (m_pMaskFilter == nullptr)
		{
			throw "Use mask set, but no filter rules for mask!";
		}

		// preprend a backslash if there is none
		QString strFileName = szFileName.toLower();
		if (strFileName.isEmpty() || strFileName[0] != '\\')
			strFileName = ("\\") + strFileName;
		// append a point if there is no extension
		if (strFileName.indexOf('.') == std::string::npos)
			strFileName = strFileName + (".");

		return m_pMaskFilter->Match(QString(strFileName).toStdString());
	}
	else
	{
		if (m_fileFilterMgr == nullptr || m_currentFilter ==nullptr)
			return true;
		return m_fileFilterMgr->TestFileNameAgainstFilter(m_currentFilter, szFileName);
	}
}

/**
 * @brief Check if any of filefilter rules match to directoryname.
 *
 * @param [in] szFileName Directoryname to test.
 * @return true unless we're suppressing this directory by filter
 */
bool FileFilterHelper::includeDir(const QString& szDirName) const
{
	if (m_bUseMask)
	{
		// directories have no extension
		return true; 
	}
	else
	{
		if (m_fileFilterMgr == nullptr || m_currentFilter == nullptr)
			return true;

		// Add a backslash
		QString strDirName("\\");
		strDirName += szDirName;

		return m_fileFilterMgr->TestDirNameAgainstFilter(m_currentFilter, strDirName);
	}
}

/**
 * @brief Load in all filters in a folder.
 * @param [in] dir Folder from where to load filters.
 * @param [in] sPattern Wildcard defining files to add to map as filter files.
 *   It is filemask, for example, "*.flt"
 */
void FileFilterHelper::LoadFileFilterDirPattern(const QString& dir, const QString& szPattern)
{
	m_fileFilterMgr->LoadFromDirectory(dir, szPattern, FileFilterExt);
}

/** 
 * @brief Convert user-given extension list to valid regular expression.
 * @param [in] Extension list/mask to convert to regular expression.
 * @return Regular expression that matches extension list.
 */
QString FileFilterHelper::ParseExtensions(const QString &extensions) const
{
	QString strParsed;
	QString strPattern;
	QString ext(extensions);
	bool bFilterAdded = false;
	static const QString pszSeps = (" ;|,:");

	ext += (";"); // Add one separator char to end
	size_t pos = ext.indexOf(pszSeps);
	
	while (pos != std::string::npos)
	{
		QString token = ext.left(pos); // Get first extension
		ext = ext.right(ext.length () - pos - 1); // Remove extension + separator
		
		// Only "*." or "*.something" allowed, other ignored
		if (token.length() >= 1)
		{
			bFilterAdded = true;
			QString strRegex = token;
			strRegex.replace(".","\\.");
			strRegex.replace("?",".");
			strRegex.replace("(","\\(");
			strRegex.replace(")","\\)");
			strRegex.replace("[","\\[");
			strRegex.replace("]","\\]");
			strRegex.replace("$","\\$");
			strRegex.replace("*",".*");
			strRegex += ("$");
			strPattern += ("(^|\\\\)") + strRegex;
		}
		else
			bFilterAdded = false;

		pos = ext.indexOf(pszSeps);
		if (bFilterAdded && pos != std::string::npos && extensions.length() > 1)
			strPattern += ("|");
	}

	if (strPattern.isEmpty())
		strParsed = (".*"); // Match everything
	else
	{

		strPattern = strPattern.toLower();
		strParsed = strPattern; //+ _T("$");
	}
	return strParsed;
}

/** 
 * @brief Returns true if active filter is a mask.
 */
bool FileFilterHelper::IsUsingMask() const
{
	return m_bUseMask;
}

/** 
 * @brief Returns active filter (or mask string)
 * @return The active filter.
 */
QString FileFilterHelper::GetFilterNameOrMask() const
{
	QString sFilter;

	if (!IsUsingMask())
		sFilter = GetFileFilterName(m_sFileFilterPath);
	else
		sFilter = m_sMask;

	return sFilter;
}

/** 
 * @brief Set filter.
 *
 * Simple-to-use function to select filter. This function determines
 * filter type so caller doesn't need to care about it.
 *
 * @param [in] filter File mask or filter name.
 * @return true if given filter was set, false if default filter was set.
 * @note If function returns false, you should ask filter set with
 * GetFilterNameOrMask().
 */
bool FileFilterHelper::SetFilter(const QString &filter)
{
	// If filter is empty string set default filter
	if (filter.isEmpty())
	{
		UseMask(true);
		SetMask(("*.*"));
		SetFileFilterPath((""));
		return false;
	}

	// Remove leading and trailing whitespace characters from the string.
	QString flt = filter.trimmed();

	// Star means we have a file extension mask
	if (filter.indexOf(("*?")) != std::string::npos)
	{
		UseMask(true);
		SetMask(flt);
		SetFileFilterPath((""));
	}
	else
	{
		QString path = GetFileFilterPath(flt);
		if (!path.isEmpty())
		{
			UseMask(false);
			SetFileFilterPath(path);
		}
		// If filter not found with given name, use default filter
		else
		{
			UseMask(true);
			SetMask(("*.*"));
			SetFileFilterPath((""));
			return false;
		}
	}
	return true;
}

/** 
 * @brief Reloads changed filter files
 *
 * Checks if filter file has been modified since it was last time
 * loaded/reloaded. If file has been modified we reload it.
 * @todo How to handle an error in reloading filter?
 */
void FileFilterHelper::ReloadUpdatedFilters()
{
	vector<FileFilterInfo> filters;
	/*DirItem fileInfo;
	QString selected;

	GetFileFilters(&filters, selected);
	vector<FileFilterInfo>::const_iterator iter = filters.begin();
	while (iter != filters.end())
	{
		QString path = (*iter).fullpath;

		fileInfo.Update(path);
		if (fileInfo.mtime != (*iter).fileinfo.mtime ||
			fileInfo.size != (*iter).fileinfo.size)
		{
			// Reload filter after changing it
			int retval = m_fileFilterMgr->ReloadFilterFromDisk(path);

			if (retval == 0) // if (retval == FILTER_OK) Todo revert
			{
				// If it was active filter we have to re-set it
				if (path == selected)
					SetFileFilterPath(path);
			}
		}
		++iter;
	}*/
}

/**
 * @brief Load any known file filters
 * @todo Preserve filter selection? How?
 */
void FileFilterHelper::LoadAllFileFilters()
{
	// First delete existing filters
	/*m_fileFilterMgr->DeleteAllFilters();

	// Program application directory
	m_sGlobalFilterPath = paths::ConcatPath(env::GetProgPath(), ("Filters"));
	paths::normalize(m_sGlobalFilterPath);
	QString pattern(("*"));
	pattern += FileFilterExt;
	LoadFileFilterDirPattern(m_sGlobalFilterPath, pattern);
	if (m_sGlobalFilterPath.toLower() != m_sUserSelFilterPath.toLower())
		LoadFileFilterDirPattern(m_sUserSelFilterPath, pattern);*/
}

/**
 * @brief Return path to global filters (& create if needed), or empty if cannot create
 */
QString FileFilterHelper::GetGlobalFilterPathWithCreate() const
{
	return paths::EnsurePathExist(m_sGlobalFilterPath);
}

/**
 * @brief Return path to user filters (& create if needed), or empty if cannot create
 */
QString FileFilterHelper::GetUserFilterPathWithCreate() const
{
	return paths::EnsurePathExist(m_sUserSelFilterPath);
}

