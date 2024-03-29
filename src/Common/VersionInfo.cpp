/**
 *  @file version.cpp
 *
 *  @brief Implementation of CVersionInfo class
 */ 

#include "VersionInfo.h"
#include "../Version.h"
#ifdef Q_OS_LINUX
#include <linux/limits.h>
#include <stdint.h>
#include "Common/tchar.h"
#include "coretypes.h"
#define MAX_PATH PATH_MAX


#elif Q_OS_WIN
#include <windows.h>
#include <tchar.h>
#endif

#ifndef  LOWORD
#define LOWORD(l) ((unsigned short)(l))
#endif

#ifndef  HIWORD
#define HIWORD(l) ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))
#endif

#include <cstdio>

#include <cassert>

// #include "TFile.h"
#include <QString>
#include <QCoreApplication>
/**
 * @brief Structure used to store language and codepage.
 */
struct LANGUAGEANDCODEPAGE
{
	WORD wLanguage;
	WORD wCodePage;
};

/** 
 * @brief Constructor for asking only numeric version info.
 * This constructor creates instance that only reads version numbers,
 * not several strings there are. This saves some time.
 * @param [in] bVersionOnly If `true` only version numbers are read.
 */
CVersionInfo::CVersionInfo(bool bVersionOnly)
: m_wLanguage(0)
, m_bVersionOnly(bVersionOnly)
, m_bDllVersion(false)
, m_dwFileVersionMS(0)
, m_dwFileVersionLS(0)
{
	GetVersionInfo();
}

/** 
 * @brief Constructor for asking version infor when language is known.
 * This constructor creates instance which gets version-info matching
 * given language-ID. There can be several different language-codepage
 * combinations, but we use first version info block that matches the
 * given language. So even if codepage isn't correct, we get correct
 * version information.
 * @param [in] wLanguage Language-ID for which the version info is wanted.
 */
CVersionInfo::CVersionInfo(WORD wLanguage)
: m_wLanguage(wLanguage)
, m_bVersionOnly(false)
, m_bDllVersion(false)
, m_dwFileVersionMS(0)
, m_dwFileVersionLS(0)
{
	GetVersionInfo();
}

/** 
 * @brief Constructor.
 * @param [in] szFileToVersion Filename to read version from.
 * @param [in] bDllVersion If `true` queries DLL version.
 */
/*CVersionInfo::CVersionInfo(LPCTSTR szFileToVersion,
						   bool bDllVersion)
: m_wLanguage(0)
, m_bVersionOnly(false)
, m_bDllVersion(bDllVersion)
{
	if (szFileToVersion != nullptr)
		m_strFileName = szFileToVersion;
	GetVersionInfo();
}*/

/** 
 * @brief Constructor.
 * @param [in] szFileToVersion Filename to read version from.
 * @param [in] szLanguage Language for version.
 * @param [in] szCodePage Codepage for version.
 */
CVersionInfo::CVersionInfo(char* szFileToVersion /* = nullptr*/,
						   char* szLanguage /* = nullptr*/,
						   char* szCodepage /* = nullptr*/)
: m_wLanguage(0)
, m_bVersionOnly(false)
, m_bDllVersion(false)
, m_dwFileVersionMS(0)
, m_dwFileVersionLS(0)
{
	if (szFileToVersion != nullptr)
		m_strFileName = szFileToVersion;
	if (szLanguage != nullptr)
		m_strLanguage = szLanguage;
	if (szCodepage != nullptr)
		m_strCodepage = szCodepage;
	GetVersionInfo();
}

/** 
 * @brief Constructor for asking version number from known module.
 * @param [in] hModule Handle to module for version info.
 */
/*CVersionInfo::CVersionInfo(HINSTANCE hModule)
: m_wLanguage(0)
, m_bVersionOnly(false)
, m_bDllVersion(false)
{
	TCHAR szFileName[MAX_PATH];
	GetModuleFileName(hModule, szFileName, MAX_PATH);
	m_strFileName = szFileName;
	GetVersionInfo();
}*/
/**
 * @brief Constructor
 * @param [in] hModule Handle to module for version info.
 */
CVersionInfo::CVersionInfo()
{
	QString szFileName;
	m_strFileName = QCoreApplication::applicationDirPath();
	GetVersionInfo();
}

/** 
 * @brief Return file version string.
 * @return File version as string.
 */
QString CVersionInfo::GetFileVersion() const
{
	return m_strFileVersion;
}

/** 
 * @brief Return private build value.
 * @return Private build number as string.
 */
QString CVersionInfo::GetPrivateBuild() const
{
    return m_strPrivateBuild;
}

/** 
 * @brief Return special build value.
 * @return Special build number as string.
 */
QString CVersionInfo::GetSpecialBuild() const
{
	return m_strSpecialBuild;
}

/** 
 * @brief Return company name.
 * @return Company name.
 */
QString CVersionInfo::GetCompanyName() const
{
	return m_strCompanyName;
}

/** 
 * @brief Return file description string.
 * @return File description string.
 */
QString CVersionInfo::GetFileDescription() const
{
	return m_strFileDescription;
}

/** 
 * @brief Return internal name.
 * @return Internal name.
 */
QString CVersionInfo::GetInternalName() const
{
	return m_strInternalName;
}

/** 
 * @brief Return full file name.
 * @return full file name.
 */
QString CVersionInfo::GetFullFileName() const
{
	return m_strFileName;
}

/** 
 * @brief Return copyright info.
 * @return Copyright info.
 */
QString CVersionInfo::GetLegalCopyright() const
{
	return m_strLegalCopyright;
}

/** 
 * @brief Return original filename.
 * @return Original filename.
 */
QString CVersionInfo::GetOriginalFilename() const
{
	return m_strOriginalFilename;
}

/** 
 * @brief Return product's version number.
 * @return Product's version number as string.
 */
QString CVersionInfo::GetProductVersion() const
{
	return m_strProductVersion;
}

/** 
 * @brief Format version string from numbers.
 * Version number consists of four WORD (16-bit) numbers. This function
 * formats those numbers to string, where numbers are separated by
 * dots. If the last number is zero it is not printed.
 * @param [in] First two (most significant) numbers for version number.
 * @param [in] Last two numbers for version number.
 * @return Formatted version string.
 */
static QString MakeVersionString(unsigned int hi, unsigned int lo)
{
	QString ver;
	if (LOWORD(lo) == 0)
	{
		ver = QString("%1.%2.%3").arg(HIWORD(hi),LOWORD(hi), HIWORD(lo));
	}
	else
	{
		ver = QString("%1.%2.%3.%4").arg(HIWORD(hi)).arg(LOWORD(hi)).arg(HIWORD(lo)).arg(LOWORD(lo));
	}
	return ver;
}


/** 
 * @brief Return numeric file's version number.
 * This function returns version number given as a number in version info.
 * @return File's version number as string.
 */
QString CVersionInfo::GetFixedFileVersion()
{
	if (!m_bVersionFound)
		return QString("");
	return m_strFileVersion; /*MakeVersionString(m_FixedFileInfo.dwFileVersionMS
		, m_FixedFileInfo.dwFileVersionLS);*/
}

/** 
 * @brief Return numeric file's version number.
 * This function returns version number given as two DWORDs.
 * @param [out] versionMS High DWORD for version number.
 * @param [out] versionLS Low DWORD for version number.
 * @return `true` if version info was found, `false` otherwise.
 */
bool CVersionInfo::GetFixedFileVersion(unsigned& versionMS, unsigned& versionLS)
{
	if (m_bVersionFound)
	{
		versionMS = m_dwFileVersionMS;
		versionLS = m_dwFileVersionLS;
		return true;
	}
	return false;
}

/** 
 * @brief Return comment string.
 * @return Comment string.
 */
QString CVersionInfo::GetComments() const
{
	return m_strComments;
}

/** 
 * @brief Read version info from file.
 * This function reads version information from file's version resource
 * to member variables.
 */
void CVersionInfo::GetVersionInfo()
{
	/*ZeroMemory(&m_FixedFileInfo, sizeof(m_FixedFileInfo));
	ZeroMemory(&m_dvi, sizeof(m_dvi));

	DWORD dwVerHnd = 0;			// An 'ignored' parameter, always '0'
	TCHAR szFileName[MAX_PATH];

	if (m_strFileName.empty())
	{
		::GetModuleFileName(nullptr, szFileName, MAX_PATH);
		m_strFileName = szFileName;
	}
	else
		StringCchCopy(szFileName, MAX_PATH, m_strFileName.c_str());
	
	DWORD dwVerInfoSize = ::GetFileVersionInfoSize(szFileName, &dwVerHnd);
	if (dwVerInfoSize)
	{
		m_bVersionFound = true;
		m_pVffInfo.reset(new BYTE[dwVerInfoSize]);
		if (::GetFileVersionInfo(szFileName, 0, dwVerInfoSize, m_pVffInfo.get()))
		{
			GetFixedVersionInfo();
			if (!m_bVersionOnly)
				QueryStrings();
		}
	}*/
	QueryStrings();

	/*if (m_bDllVersion)
	{
		if (HINSTANCE hinstDll = ::LoadLibrary(szFileName))
		{
			DLLGETVERSIONPROC DllGetVersion = (DLLGETVERSIONPROC) 
					::GetProcAddress(hinstDll, "DllGetVersion");
			if (DllGetVersion)
			{
				m_dvi.cbSize = sizeof(m_dvi);
				if (FAILED(DllGetVersion(&m_dvi)))
				{
					m_dvi.cbSize = 0;
				}
			}
			::FreeLibrary(hinstDll);
		}
	}*/
}

/** 
 * @brief Read strings from version info data.
 */
void CVersionInfo::QueryStrings()
{
	/*if (m_wLanguage != 0)
	{
		WORD codepage;
		GetCodepageForLanguage(m_wLanguage, codepage);
		TCHAR temp[20];
		StringCchPrintf(temp, countof(temp) - 1, _T("%04x"), m_wLanguage);
		m_strLanguage = temp;
		StringCchPrintf(temp, countof(temp) - 1, _T("%04x"), codepage);
		m_strCodepage = temp;
	}
	else if (m_strLanguage.empty()
		|| m_strCodepage.empty())
	{
		LANGUAGEANDCODEPAGE *lpTranslate;
		DWORD langLen;
		if (!!VerQueryValue((LPVOID)m_pVffInfo.get(),
				_T("\\VarFileInfo\\Translation"),
				(LPVOID *)&lpTranslate, (UINT *)&langLen))
		{
			TCHAR temp[20];
			StringCchPrintf(temp, countof(temp) - 1, _T("%4.4X"),
					lpTranslate[0].wLanguage);
			m_strLanguage = temp;
			StringCchPrintf(temp, countof(temp) - 1, _T("%4.4X"),
					lpTranslate[0].wCodePage);
			m_strCodepage = temp;
		}
	}*/

	m_strCompanyName = QString::fromUtf8(COMPANYNAME);
	m_strFileDescription = FILEDESCRIPTION;
	m_strFileVersion = STRFILEVER;
	m_strInternalName = INTERNALNAME;
	m_strLegalCopyright = QString::fromUtf8(LEGALCOPYRIGHT);
	m_strOriginalFilename = ORIGINALFILENAME;
	m_strProductName = PRODUCTNAME;
	m_strProductVersion = QString::fromUtf8(STRPRODUCTVER);
	m_strComments = COMMENTS;
	m_strSpecialBuild = "";
	m_strPrivateBuild = QString::fromUtf8(STRPRIVATEBUILD);
}


/** 
 * @brief Read numeric version information.
 */
void CVersionInfo::GetFixedVersionInfo()
{
	/*VS_FIXEDFILEINFO * pffi;
	UINT len = sizeof(*pffi);
	bool bRetCode = !!VerQueryValue(
		(LPVOID)m_pVffInfo.get(), _T("\\"), (LPVOID *)&pffi, &len);
	if (bRetCode)
		m_FixedFileInfo = *pffi;
	else
		m_FixedFileInfo = { 0 };
	m_dvi.dwMajorVersion = HIWORD(m_FixedFileInfo.dwFileVersionMS);
	m_dvi.dwMinorVersion = LOWORD(m_FixedFileInfo.dwFileVersionMS);
	m_dvi.dwBuildNumber = HIWORD(m_FixedFileInfo.dwFileVersionLS);*/
}

/** 
 * @brief Get codepage for given language.
 * This function finds codepage value for given language from version info.
 * That is, we have certain combinations of language-codepage in version info.
 * This function tells which codepage exists with given language, so we can
 * find existing version info data.
 * @param [in] wLanguage Language ID for which we need matching codepage.
 * @param [out] wCodePage Found codepage.
 * @return `true` if language was found from version info block.
 */
bool CVersionInfo::GetCodepageForLanguage(WORD wLanguage, WORD & wCodePage)
{
	/*LANGUAGEANDCODEPAGE *lpTranslate;
	UINT cbTranslate;
	// Read the list of languages and code pages.

	VerQueryValue((LPVOID)m_pVffInfo.get(), 
				_T("\\VarFileInfo\\Translation"),
				(LPVOID*)&lpTranslate,
				&cbTranslate);

	// Read the file description for each language and code page.

	const int nLangCount = cbTranslate / sizeof(LANGUAGEANDCODEPAGE);
	int i = 0;*/
	bool bFound = false;
	/*while (!bFound && i < nLangCount)
	{
		if (lpTranslate[i].wLanguage == wLanguage)
		{
			wCodePage = lpTranslate[i].wCodePage;
			bFound = true;
		}
		else
			++i;
	}*/
	return bFound;
}
