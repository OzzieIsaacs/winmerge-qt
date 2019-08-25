/**
 *  @file version.h
 *
 *  @brief Declaration of CVersionInfo class
 */ 
#pragma once

#include <memory>
#include <QString>

/**
 * @brief Class providing access to version information of a file.
 * This class reads version information block from a file. Version information
 * consists of version numbers, copyright, descriptions etc. Since that is
 * many strings to read, there is constructor taking `bool` parameter and
 * only reading version numbers. That constructor is suggested to be used
 * if string information is not needed.
 */
#ifdef Q_OS_LINUX
#include "types.h"
typedef struct tagVS_FIXEDFILEINFO {
  DWORD dwSignature;
  DWORD dwStrucVersion;
  DWORD dwFileVersionMS;
  DWORD dwFileVersionLS;
  DWORD dwProductVersionMS;
  DWORD dwProductVersionLS;
  DWORD dwFileFlagsMask;
  DWORD dwFileFlags;
  DWORD dwFileOS;
  DWORD dwFileType;
  DWORD dwFileSubtype;
  DWORD dwFileDateMS;
  DWORD dwFileDateLS;
} VS_FIXEDFILEINFO;
#else
//#include <Verrsrc.h>
#include <tchar.h>
#include <windows.h>
#endif

class CVersionInfo
{
private:
	VS_FIXEDFILEINFO m_FixedFileInfo; /**< Fixed file information */
	std::unique_ptr<BYTE[]> m_pVffInfo; /**< Pointer to version information block */
	bool m_bVersionOnly; /**< Ask version numbers only */
	bool m_bDllVersion; /**< Dll file version is being queried */
	WORD m_wLanguage; /**< Language-ID to use (if given) */
	bool m_bVersionFound; /**< Was version info found from file? */
	DWORD m_dwFileVersionMS;
	DWORD m_dwFileVersionLS;

	QString m_strFileName;
	QString m_strLanguage;
	QString m_strCodepage;
	QString m_strCompanyName;
	QString m_strFileDescription;
	QString m_strFileVersion;
	QString m_strInternalName;
	QString m_strLegalCopyright;
	QString m_strOriginalFilename;
	QString m_strProductName;
	QString m_strProductVersion;
	QString m_strComments;
	QString m_strSpecialBuild;
	QString m_strPrivateBuild;

public:
	explicit CVersionInfo(bool bVersionOnly);
	explicit CVersionInfo(WORD wLanguage);
	/*CVersionInfo(LPCTSTR szFileToVersion,
				   bool bDllVersion);*/
	CVersionInfo(char* szFileToVersion = nullptr,
				 char* szLanguage = nullptr,
				 char* szCodepage = nullptr);
    // explicit CVersionInfo(HINSTANCE hModule);
	CVersionInfo();
	QString GetFileVersion() const;
	QString GetCompanyName() const;
	QString GetFileDescription() const;
	QString GetInternalName() const;
	QString GetFullFileName() const;
	QString GetLegalCopyright() const;
	QString GetOriginalFilename() const;
	QString GetProductVersion() const;
	QString GetComments() const;
	QString GetSpecialBuild() const;
	QString GetPrivateBuild() const;
	QString GetFixedProductVersion();
	QString GetFixedFileVersion();
    // DLLVERSIONINFO m_dvi;
	bool GetFixedFileVersion(unsigned& versionMS, unsigned& versionLS);

protected:
	void GetVersionInfo();
	void GetFixedVersionInfo();
	void QueryStrings();
	void QueryValue(LPCTSTR szId, QString& s);
	bool GetCodepageForLanguage(WORD wLanguage, WORD & wCodePage);
};
