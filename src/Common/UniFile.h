/**
 *  @file   UniFile.h
 *  @author Perry Rapp, Creator, 2003-2006
 *  @date   Created: 2003-10
 *  @date   Edited:  2006-02-20 (Perry Rapp)
 *
 *  @brief  Declaration of Unicode file classes.
 */
#pragma once

#include "unicoder.h"

namespace Poco { class SharedMemory; }

/**
 * @brief Interface to file classes in this module
 */
class UniFile
{
public:

	/**
	 * @brief A struct for error message or error code.
	 */
	struct UniError
	{
		String desc; // valid if apiname empty

		UniError();
		bool HasError() const;
		void ClearError();
		String GetError() const;
	};

	virtual ~UniFile() { }
	virtual bool OpenReadOnly(const String& filename) = 0;
	virtual void Close() = 0;
	virtual bool IsOpen() const = 0;

	virtual String GetFullyQualifiedPath() const = 0;
	virtual const UniError & GetLastUniError() const = 0;

	virtual bool IsUnicode() = 0;
	virtual bool ReadBom() = 0;
	virtual bool HasBom() const = 0;
	virtual void SetBom(bool bom) = 0;

	virtual ucr::UNICODESET GetUnicoding() const = 0;
	virtual void SetUnicoding(ucr::UNICODESET unicoding) = 0;
	virtual int GetCodepage() const = 0;
	virtual void SetCodepage(int codepage) = 0;

public:
	virtual bool ReadString(String & line, bool * lossy) = 0;
	virtual bool ReadString(String & line, String & eol, bool * lossy) = 0;
	virtual int GetLineNumber() const = 0;
	virtual int64_t GetPosition() const = 0;
	virtual bool WriteString(const String & line) = 0;

	struct txtstats
	{
		int ncrs;
		int nlfs;
		int ncrlfs;
		int nzeros;
		int nlosses;
		txtstats() { clear(); }
		void clear() { ncrs = nlfs = ncrlfs = nzeros = nlosses = 0; }
	};
	virtual const txtstats & GetTxtStats() const = 0;
};

/**
 * @brief Local file access code used by both UniMemFile and UniStdioFile
 *
 * This class lacks an actual handle to a file
 */
class UniLocalFile : public UniFile
{
public:
	UniLocalFile();
	void Clear();

	virtual String GetFullyQualifiedPath() const { return m_filepath; }
	virtual const UniError & GetLastUniError() const { return m_lastError; }

	virtual ucr::UNICODESET GetUnicoding() const { return m_unicoding; }
	virtual void SetUnicoding(ucr::UNICODESET unicoding) { m_unicoding = unicoding; }
	virtual int GetCodepage() const { return m_codepage; }
	virtual void SetCodepage(int codepage) { 
		m_codepage = codepage;
		switch (m_codepage)
		{
		case ucr::CP_UCS2LE:
			m_unicoding = ucr::UCS2LE;
			m_charsize = 2;
			break;
		case ucr::CP_UCS2BE:
			m_unicoding = ucr::UCS2BE;
			m_charsize = 2;
			break;
		case ucr::CP_UTF_8:
			m_charsize = 1;
			m_unicoding = ucr::UTF8;
			break;
		default:
			m_charsize = 1;
			m_unicoding = ucr::NONE;
			break;
		}
	}

	virtual int GetLineNumber() const { return m_lineno; }
	virtual const txtstats & GetTxtStats() const { return m_txtstats; }

	bool IsUnicode();

protected:
	virtual bool DoGetFileStatus();
	virtual void LastErrorCustom(const String& desc);

protected:
	int m_statusFetched; // 0 not fetched, -1 error, +1 success
	int64_t m_filesize;
	String m_filepath;
	String m_filename;
	int m_lineno; // current 0-based line of m_current
	UniError m_lastError;
	ucr::UNICODESET m_unicoding;
	int m_charsize; // 2 for UCS-2, else 1
	int m_codepage; // only valid if m_unicoding==ucr::NONE;
	txtstats m_txtstats;
	bool m_bom; /**< Did the file have a BOM when reading? */
	bool m_bUnicodingChecked; /**< Has unicoding been checked for the file? */
	bool m_bUnicode; /**< Is the file unicode file? */
};

/**
 * @brief Memory-Mapped disk file (read-only access)
 */
class UniMemFile : public UniLocalFile
{
	friend class UniMarkdownFile;
public:
	enum AccessMode
	{
		AM_READ = 0,
		AM_WRITE
	};

	UniMemFile();
	virtual ~UniMemFile() { Close(); }

	virtual bool GetFileStatus();

	virtual bool OpenReadOnly(const String& filename);
	virtual bool Open(const String& filename);
	virtual bool Open(const String& filename, AccessMode mode);
	void Close();
	virtual bool IsOpen() const;

	virtual bool ReadBom();
	virtual bool HasBom() const;
	virtual void SetBom(bool bom);

public:
	virtual bool ReadString(String & line, bool * lossy);
	virtual bool ReadString(String & line, String & eol, bool * lossy);
	virtual int64_t GetPosition() const { return m_current - m_base; }
	virtual bool WriteString(const String & line);

// Implementation methods
protected:
	virtual bool DoOpen(const String& filename, AccessMode mode);

// Implementation data
private:
	Poco::SharedMemory *m_hMapping;
	unsigned char *m_base; // points to base of mapping
	unsigned char *m_data; // similar to m_base, but after BOM if any
	unsigned char *m_current; // current location in file
};

/**
 * @brief Regular buffered file (write-only access)
 * (ReadString methods have never been implemented,
 *  because UniMemFile above is good for reading)
 */
class UniStdioFile : public UniLocalFile
{
public:
	UniStdioFile();
	~UniStdioFile();

	virtual bool GetFileStatus();

	virtual bool OpenReadOnly(const String& filename);
	virtual bool OpenCreate(const String& filename);
	virtual bool OpenCreateUtf8(const String& filename);
	virtual bool Open(const String& filename, const String& mode);
	void Close();

	virtual bool IsOpen() const;

	virtual bool ReadBom();
	virtual bool HasBom() const;
	virtual void SetBom(bool bom);

protected:
	virtual bool ReadString(String & line, bool * lossy);
	virtual bool ReadString(String & line, String & eol, bool * lossy);

public:
	virtual int64_t GetPosition() const;

	virtual int WriteBom();
	virtual bool WriteString(const String & line);

// Implementation methods
protected:
	virtual bool DoOpen(const String& filename, const String& mode);
	virtual void LastErrorCustom(const String& desc);

// Implementation data
private:
	FILE * m_fp;
	int64_t m_data; // offset after any initial BOM
	ucr::buffer m_ucrbuff;
};
