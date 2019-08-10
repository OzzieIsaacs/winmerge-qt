/**
 *  @file PathContext.h
 *
 *  @brief Declarations of PathInfo and PathContext
 */
#pragma once

//#include "Common/UnicodeString.h"
#include <vector>
#include <QString>

class PathContext;
class PathContextIterator;

/**
 * @brief Information for one path.
 *
 * Path is stored in normalized format (no trailing slash).
 */
class PathInfo
{
	friend class PathContext;
public:
	PathInfo() {}
	PathInfo(const PathInfo &pi);

	QString GetPath(bool bNormalized = true) const;
	QString& GetRef();
	// void SetPath(const TCHAR *path);
	void SetPath(const QString & path);
	void NormalizePath();

private:
	QString m_sPath;  /**< Directory / file path */
};

/**
 * @brief Holds path information of compared files/directories.
 */
class PathContext
{
public:
	typedef PathContextIterator const_iterator;

	PathContext();
	explicit PathContext(const QString& sLeft);
	PathContext(const QString& sLeft, const QString& sRight);
	PathContext(const QString& sLeft, const QString& sMiddle, const QString& sRight);
	PathContext(const PathContext &paths);
	explicit PathContext(const std::vector<QString>& paths);

	QString GetAt(int nIndex) const;
	QString& GetElement(int nIndex);
	void SetAt(int nIndex, const QString& newElement);
	QString operator[](int nIndex) const;
	QString& operator[](int nIndex);

	QString GetLeft(bool bNormalized = true) const;
	QString GetRight(bool bNormalized = true) const;
	QString GetMiddle(bool bNormalized = true) const;
	QString GetPath(int index, bool bNormalized = true) const;
	void SetLeft(const QString& path, bool bNormalized = true);
	void SetRight(const QString& path, bool bNormalized = true);
	void SetMiddle(const QString& path, bool bNormalized = true);
	void SetPath(int index, const QString& path, bool bNormalized = true);
	void SetSize(int nFiles);
	int GetSize() const;
	void RemoveAll();
	void Swap();

	const_iterator begin() const;
	const_iterator end() const;
	size_t size() const;
private:
	int m_nFiles;
	PathInfo m_path[3]; /**< First, second, third path (left path at start) */
};

class PathContextIterator : public std::iterator<std::forward_iterator_tag, QString>
{
public:
	explicit PathContextIterator(const PathContext *pPathContext) : m_pPathContext(pPathContext)
	{
		m_sel =  (pPathContext->GetSize() == 0) ? -1 : 0;
	}

	PathContextIterator() : m_pPathContext(nullptr), m_sel(-1)
	{
	}

	~PathContextIterator() {}

	PathContextIterator& operator=(const PathContextIterator& it)
	{
		m_sel = it.m_sel;
		m_pPathContext = it.m_pPathContext;
		return *this;
	}

	PathContextIterator& operator++()
	{
		m_sel++;
		if (m_sel >= m_pPathContext->GetSize())
			m_sel = -1;
		return *this;
	}

	QString operator*()
	{
		return m_pPathContext->GetAt(m_sel);
	}

	bool operator==(const PathContextIterator& it) const
	{
		return m_sel == it.m_sel;
	}

	bool operator!=(const PathContextIterator& it) const
	{
		return m_sel != it.m_sel;
	}

public:
	const PathContext *m_pPathContext;
	int m_sel;
};
