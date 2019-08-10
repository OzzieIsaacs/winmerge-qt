/** 
 * @file OptionsMgr.h
 *
 * @brief Interface for Options management classes
 *
 */

/* The MIT License
Copyright (c) 2004-2009 Kimmo Varis
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <map>
#include <vector>
// #include "UnicodeString.h"
#include "varprop.h"
#include <QString>
#include "tchar.h"

/**
 * @brief Class to store option name, value and default value.
 */
class COption
{
public:
	/**
	* @brief Return values for functions.
	*/
	enum
	{
		OPT_OK				= 0, /**< All good. */
		OPT_ERR				= 1, /**< General error. */
		OPT_WRONG_TYPE		= 2, /**< Option type was wrong. */
		OPT_UNKNOWN_TYPE	= 3, /**< Given option type is not known. */
		OPT_NOTFOUND		= 4, /**< Option name not found. */
	};

	COption();
	COption(const COption& option);

	COption& operator=(const COption& option);

	int Init(const QString& name, const varprop::VariantValue& defaultVal);
	const varprop::VariantValue& Get() const;
	const varprop::VariantValue& GetDefault() const;
	int Set(const varprop::VariantValue& value, bool allowConversion = false);
	int SetDefault(const varprop::VariantValue& defaultValue); 
	void Reset();

protected:
	bool ConvertInteger(varprop::VariantValue & value, varprop::VT_TYPE nType);
	bool ConvertString(varprop::VariantValue & value, varprop::VT_TYPE nType);
	bool ConvertType(varprop::VariantValue & value, varprop::VT_TYPE nType);

private:
	QString m_strName; /**< Option's name. */
	varprop::VariantValue m_value; /**< Option's current value. */
	varprop::VariantValue m_valueDef; /**< Option's default value. */
};

typedef std::map<QString, COption> OptionsMap;

/**
 * @brief Class to store list of options.
 * This class holds a list of all options (known to application). Options
 * are accessed by their name.
 *
 * Option must be first initialized before it can be read/set. Initialization
 * is done with InitOption() method.
 */
class COptionsMgr
{
public:
	virtual ~COptionsMgr() {}
	int AddOption(const QString& name, const varprop::VariantValue& defaultValue);
	const varprop::VariantValue& Get(const QString& name) const;
	const QString& GetString(const QString& name) const;
	int GetInt(const QString& name) const;
	bool GetBool(const QString& name) const;
	int Set(const QString& name, const varprop::VariantValue& value);
	int Set(const QString& name, const QString& value);
	int Set(const QString& name, const TCHAR *value);
	int Set(const QString& name, bool value);
	int Set(const QString& name, int value);
	int Reset(const QString& name);
	int GetDefault(const QString& name, QString & value) const;
	int GetDefault(const QString& name, unsigned & value) const;
	int GetDefault(const QString& name, bool & value) const;
	template <typename T> T GetDefault(const QString& name) const { T v; GetDefault(name, v); return v; }
	template <template<typename T, typename = std::allocator<T>> class Container = std::vector>
	Container<QString> GetNameList() const
	{
		Container<QString> nameList;
		for (const auto& e : m_optionsMap)
			nameList.push_back(e.first);
		return nameList;
	}
	QString ExpandShortName(const QString & shortname) const;

	virtual int InitOption(const QString& name, const varprop::VariantValue& defaultValue) = 0;
	virtual int InitOption(const QString& name, const QString& defaultValue) = 0;
	virtual int InitOption(const QString& name, const TCHAR *defaultValue) = 0;
	virtual int InitOption(const QString& name, int defaultValue, bool serializable = true) = 0;
	virtual int InitOption(const QString& name, bool defaultValue) = 0;

	virtual int SaveOption(const QString& name) = 0;
	virtual int SaveOption(const QString& name, const varprop::VariantValue& value) = 0;
	virtual int SaveOption(const QString& name, const QString& value) = 0;
	virtual int SaveOption(const QString& name, const TCHAR *value) = 0;
	virtual int SaveOption(const QString& name, int value) = 0;
	virtual int SaveOption(const QString& name, bool value) = 0;
	virtual int SaveOption(const QString& name, unsigned value);

	virtual int RemoveOption(const QString& name);

	virtual int ExportOptions(const QString& filename, const bool bHexColor=false) const = 0;
	virtual int ImportOptions(const QString& filename) = 0;
	
	virtual void SetSerializing(bool serializing=true) = 0;

protected:
	OptionsMap m_optionsMap; /**< Map where options are stored. */

private:
	static varprop::VariantValue m_emptyValue;
};
