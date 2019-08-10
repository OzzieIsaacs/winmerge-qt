/**
 * @file  PathContext.cpp
 *
 * @brief Implementation file for PathInfo and PathContext
 *
 */

#include "PathContext.h"
#include <cassert>
#include "paths.h"

/**
 * @brief Copy constructor.
 */
PathInfo::PathInfo(const PathInfo &pi)
: m_sPath(pi.m_sPath)
{
}

/**
 * @brief Get path.
 * @param [in] sbNormalized true if path is wanted in normalized format.
 */
QString PathInfo::GetPath(bool bNormalized /*= true*/) const
{ 
	if (!bNormalized)
		return paths::AddTrailingSlash(m_sPath);
	else
		return m_sPath;
}

QString& PathInfo::GetRef()
{ 
	return m_sPath;
}

/**
 * @brief Set path.
 * @param [in] sPath New path for item.
 */
/*void PathInfo::SetPath(const TCHAR *sPath)
{
	m_sPath = sPath;
}*/

void PathInfo::SetPath(const QString & sPath)
{
	m_sPath = sPath;
}

/**
 * @brief Normalize path.
 */
void PathInfo::NormalizePath()
{
	paths::normalize(m_sPath);
}

PathContext::PathContext()
{
	m_nFiles = 0;
}

PathContext::PathContext(const QString& sLeft)
{
	m_nFiles = 1;
	m_path[0].SetPath(sLeft);
}

PathContext::PathContext(const QString& sLeft, const QString& sRight)
{
	m_nFiles = 2;
	m_path[0].SetPath(sLeft);
	m_path[1].SetPath(sRight);
}

PathContext::PathContext(const QString& sLeft, const QString& sMiddle, const QString& sRight)
{
	m_nFiles = 3;
	m_path[0].SetPath(sLeft);
	m_path[1].SetPath(sMiddle);
	m_path[2].SetPath(sRight);
}

PathContext::PathContext(const PathContext &paths)
{
	m_nFiles = paths.m_nFiles;
	std::copy_n(paths.m_path, m_nFiles, m_path);
}

PathContext::PathContext(const std::vector<QString> &paths)
{
	m_nFiles = static_cast<int>(paths.size());
	for (size_t i = 0; i < paths.size(); i++)
		m_path[i].SetPath(paths[i]);
}

QString PathContext::GetAt(int nIndex) const
{
	assert(nIndex < m_nFiles);
	return m_path[nIndex].GetPath();
}

QString& PathContext::GetElement(int nIndex)
{
	assert(nIndex < m_nFiles);
	return m_path[nIndex].GetRef();
}

void PathContext::SetAt(int nIndex, const QString& newElement)
{
	assert(nIndex < m_nFiles);
	m_path[nIndex].SetPath(newElement);
}

QString PathContext::operator[](int nIndex) const
{
	return GetAt(nIndex);
}

QString& PathContext::operator[](int nIndex)
{
	return GetElement(nIndex);
}

/**
 * @brief set number of files.
 */
void PathContext::SetSize(int nFiles)
{
	m_nFiles = nFiles;
}

/**
 * @brief Return number of files.
 */
int PathContext::GetSize() const
{
	return m_nFiles;
}

/**
 * @brief Empty m_path array
 */
void PathContext::RemoveAll()
{
	m_nFiles = 0;
	m_path[0].SetPath((""));
	m_path[1].SetPath((""));
	m_path[2].SetPath((""));
}

/**
 * @brief Return left path.
 * @param [in] sNormalized If true normalized path is returned.
 */
QString PathContext::GetLeft(bool bNormalized) const
{
	if (m_nFiles == 0)
		return QString("");
	return m_path[0].GetPath(bNormalized);
}

/**
 * @brief Return right path.
 * @param [in] sNormalized If true normalized path is returned.
 */
QString PathContext::GetRight(bool bNormalized) const
{
	if (m_nFiles < 2)
		return QString("");
	return m_path[m_nFiles - 1].GetPath(bNormalized);
}

/**
 * @brief Return middle path.
 * @param [in] sNormalized If true normalized path is returned.
 */
QString PathContext::GetMiddle(bool bNormalized) const
{
	if (m_nFiles < 3)
		return QString("");
	return m_path[1].GetPath(bNormalized);
}

/**
 * @brief Return path
 * @param [in] index index of path to return
 * @param [in] sNormalized If true normalized path is returned.
 */
QString PathContext::GetPath(int index, bool bNormalized) const
{
	return m_path[index].GetPath(bNormalized);
}

/**
 * @brief Set left path.
 * @param [in] path New path for item.
 */
void PathContext::SetLeft(const QString& path, bool bNormalized)
{
	if (m_nFiles == 0)
		m_nFiles = 1;
	m_path[0].SetPath(path);
	if (bNormalized)
		m_path[0].NormalizePath();
}

/**
 * @brief Set right path.
 * @param [in] path New path for item.
 */
void PathContext::SetRight(const QString& path, bool bNormalized)
{
	if (m_nFiles < 2)
		m_nFiles = 2;
	m_path[m_nFiles - 1].SetPath(path);
	if (bNormalized)
		m_path[m_nFiles - 1].NormalizePath();
}

/**
 * @brief Set middle path.
 * @param [in] path New path for item.
 */
void PathContext::SetMiddle(const QString& path, bool bNormalized)
{
	if (m_nFiles < 3)
	{
		m_nFiles = 3;
		m_path[2] = m_path[1];
	}
	m_path[1].SetPath(path);
	if (bNormalized)
		m_path[1].NormalizePath();
}

/**
 * @brief Set path
 * @param [in] index index of path to set
 * @param [in] path New path for item.
 */
void PathContext::SetPath(int index, const QString& path, bool bNormalized)
{
	if (index >= sizeof(m_path)/sizeof(m_path[0]))
		return;
	if (index >= m_nFiles)
		m_nFiles = index + 1;
	m_path[index].SetPath(path);
	if (bNormalized)
		m_path[index].NormalizePath();
}

/**
 * @brief Swap paths.
 */
void PathContext::Swap()
{
	if (m_nFiles < 3)
		m_path[0].m_sPath.swap(m_path[1].m_sPath);
	else
		m_path[0].m_sPath.swap(m_path[2].m_sPath);
}

PathContextIterator PathContext::begin() const
{
	return PathContextIterator(this);
}

PathContextIterator PathContext::end() const
{
	return PathContextIterator();
}

size_t PathContext::size() const
{
	return m_nFiles;
}

