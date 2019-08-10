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
 * @file  ProjectFile.cpp
 *
 * @brief Implementation file for ProjectFile class.
 */

#include "ProjectFile.h"

#include <stack>
#include <string>
#include <Poco/FileStream.h>
#include <Poco/XML/XMLWriter.h>
#include <Poco/SAX/SAXParser.h>
#include <Poco/SAX/ContentHandler.h>
#include <Poco/Exception.h>
#include "UnicodeString.h"
#include "unicoder.h"

using Poco::FileStream;
using Poco::XML::SAXParser;
using Poco::XML::ContentHandler;
using Poco::XML::Locator;
using Poco::XML::XMLWriter;
using Poco::XML::XMLChar;
using Poco::XML::XMLString;
using Poco::XML::Attributes;
using Poco::Exception;
using ucr::toTString;
using ucr::toUTF8;

// Constants for xml element names
const char Root_element_name[] = "project";
const char Paths_element_name[] = "paths";
const char Left_element_name[] = "left";
const char Middle_element_name[] = "middle";
const char Right_element_name[] = "right";
const char Filter_element_name[] = "filter";
const char Subfolders_element_name[] = "subfolders";
const char Left_ro_element_name[] = "left-readonly";
const char Middle_ro_element_name[] = "middle-readonly";
const char Right_ro_element_name[] = "right-readonly";

namespace
{

String xmlch2tstr(const XMLChar *ch, int length)
{
	return toTString(std::string(ch, length));
}

void writeElement(XMLWriter& writer, const std::string& tagname, const std::string& characters)
{
	writer.startElement("", "", tagname);
	writer.characters(characters);
	writer.endElement("", "", tagname);
}

}

class ProjectFileHandler: public ContentHandler
{
public:
	explicit ProjectFileHandler(ProjectFile *pProject) : m_pProject(pProject) {}

	void setDocumentLocator(const Locator* loc) {}
	void startDocument() {}
	void endDocument() {}
	void startElement(const XMLString& uri, const XMLString& localName, const XMLString& qname, const Attributes& attributes)
	{
		m_stack.push(localName);
	}
	void endElement(const XMLString& uri, const XMLString& localName, const XMLString& qname)
	{
		m_stack.pop();
	}
	void characters(const XMLChar ch[], int start, int length)
	{
		if (m_stack.size() != 3)
			return;

		const std::string& nodename = m_stack.top();
		if (nodename == Left_element_name)
		{
			m_pProject->m_paths.SetLeft(m_pProject->m_paths.GetLeft() + xmlch2tstr(ch + start, length));
			m_pProject->m_bHasLeft = true;
		}
		else if (nodename == Middle_element_name)
		{
			m_pProject->m_paths.SetMiddle(m_pProject->m_paths.GetMiddle() + xmlch2tstr(ch + start, length));
			m_pProject->m_bHasMiddle = true;
		}
		else if (nodename == Right_element_name)
		{
			m_pProject->m_paths.SetRight(m_pProject->m_paths.GetRight() + xmlch2tstr(ch + start, length));
			m_pProject->m_bHasRight = true;
		}
		else if (nodename == Filter_element_name)
		{
			m_pProject->m_filter += xmlch2tstr(ch + start, length);
			m_pProject->m_bHasFilter = true;
		}
		else if (nodename == Subfolders_element_name)
		{
			m_pProject->m_subfolders = atoi(std::string(ch + start, length).c_str());
			m_pProject->m_bHasSubfolders = true;
		}
		else if (nodename == Left_ro_element_name)
		{
			m_pProject->m_bLeftReadOnly = atoi(std::string(ch + start, length).c_str()) != 0;
		}
		else if (nodename == Middle_ro_element_name)
		{
			m_pProject->m_bMiddleReadOnly = atoi(std::string(ch +  start, length).c_str()) != 0;
		}
		else if (nodename == Right_ro_element_name)
		{
			m_pProject->m_bRightReadOnly = atoi(std::string(ch + start, length).c_str()) != 0;
		}
	}
	void ignorableWhitespace(const XMLChar ch[], int start, int length)	{}
	void processingInstruction(const XMLString& target, const XMLString& data) {}
	void startPrefixMapping(const XMLString& prefix, const XMLString& uri) {}
	void endPrefixMapping(const XMLString& prefix) {}
	void skippedEntity(const XMLString& name) {}

private:
	ProjectFile *m_pProject;
	std::stack<std::string> m_stack;
};

/** @brief File extension for path files */
const String ProjectFile::PROJECTFILE_EXT = toTString("WinMerge");

/** 
 * @brief Standard constructor.
 */
 ProjectFile::ProjectFile()
: m_bHasLeft(false)
, m_bHasMiddle(false)
, m_bHasRight(false)
, m_bHasFilter(false)
, m_bHasSubfolders(false)
, m_subfolders(-1)
, m_bLeftReadOnly(false)
, m_bMiddleReadOnly(false)
, m_bRightReadOnly(false)
{
}

/** 
 * @brief Open given path-file and read data from it to member variables.
 * @param [in] path Path to project file.
 * @param [out] sError Error string if error happened.
 * @return true if reading succeeded, false if error happened.
 */
bool ProjectFile::Read(const String& path)
{
	ProjectFileHandler handler(this);
	SAXParser parser;
	parser.setContentHandler(&handler);
	parser.parse(toUTF8(path));
	return true;
}

/** 
 * @brief Save data from member variables to path-file.
 * @param [in] path Path to project file.
 * @param [out] sError Error string if error happened.
 * @return true if saving succeeded, false if error happened.
 */
bool ProjectFile::Save(const String& path) const
{
	FileStream out(toUTF8(path), FileStream::trunc);
	XMLWriter writer(out, XMLWriter::WRITE_XML_DECLARATION | XMLWriter::PRETTY_PRINT);
	writer.startDocument();
	writer.startElement("", "", Root_element_name);
	{
		writer.startElement("", "", Paths_element_name);
		{
			if (!m_paths.GetLeft().empty())
				writeElement(writer, Left_element_name, toUTF8(m_paths.GetLeft()));
			if (!m_paths.GetMiddle().empty())
				writeElement(writer, Middle_element_name, toUTF8(m_paths.GetMiddle()));
			if (!m_paths.GetRight().empty())
				writeElement(writer, Right_element_name, toUTF8(m_paths.GetRight()));
			if (!m_filter.empty())
				writeElement(writer, Filter_element_name, toUTF8(m_filter));
			writeElement(writer, Subfolders_element_name, m_subfolders != 0 ? "1" : "0");
			writeElement(writer, Left_ro_element_name, m_bLeftReadOnly ? "1" : "0");
			if (!m_paths.GetMiddle().empty())
				writeElement(writer, Middle_ro_element_name, m_bMiddleReadOnly ? "1" : "0");
			writeElement(writer, Right_ro_element_name, m_bRightReadOnly ? "1" : "0");
		}
		writer.endElement("", "", Paths_element_name);
	}
	writer.endElement("", "", Root_element_name);
	writer.endDocument();
	return true;
}

/** 
 * @brief Returns if left path is defined in project file.
 * @return true if project file has left path.
 */
bool ProjectFile::HasLeft() const
{
	return m_bHasLeft;
}

/** 
 * @brief Returns if middle path is defined.
 */
bool ProjectFile::HasMiddle() const
{
	return m_bHasMiddle;
}

/** 
 * @brief Returns if right path is defined in project file.
 * @return true if project file has right path.
 */
bool ProjectFile::HasRight() const
{
	return m_bHasRight;
}

/** 
 * @brief Returns if filter is defined in project file.
 * @return true if project file has filter.
 */
bool ProjectFile::HasFilter() const
{
	return m_bHasFilter;
}

/** 
 * @brief Returns if subfolder is defined in projectfile.
 * @return true if project file has subfolder definition.
 */
bool ProjectFile::HasSubfolders() const
{
	return m_bHasSubfolders;
}

/** 
 * @brief Returns left path.
 * @param [out] pReadOnly true if readonly was specified for path.
 * @return Left path.
 */
String ProjectFile::GetLeft(bool * pReadOnly /*= nullptr*/) const
{
	if (pReadOnly != nullptr)
		*pReadOnly = m_bLeftReadOnly;
	return m_paths.GetLeft();
}

/** 
 * @brief Returns if left path is specified read-only.
 * @return true if left path is read-only, false otherwise.
 */
bool ProjectFile::GetLeftReadOnly() const
{
	return m_bLeftReadOnly;
}

/** 
 * @brief Set left path, returns old left path.
 * @param [in] sLeft Left path.
 * @param [in] bReadOnly Will path be recorded read-only?
 */
void ProjectFile::SetLeft(const String& sLeft, const bool * pReadOnly /*= nullptr*/)
{
	m_paths.SetLeft(sLeft, false);
	if (pReadOnly != nullptr)
		m_bLeftReadOnly = *pReadOnly;
}

/** 
 * @brief Returns middle path.
 * @param [out] pReadOnly true if readonly was specified for path.
 */
String ProjectFile::GetMiddle(bool * pReadOnly /*= nullptr*/) const
{
	if (pReadOnly != nullptr)
		*pReadOnly = m_bMiddleReadOnly;
	return m_paths.GetMiddle();
}

/** 
 * @brief Returns if middle path is specified read-only.
 */
bool ProjectFile::GetMiddleReadOnly() const
{
	return m_bMiddleReadOnly;
}

/** 
 * @brief Set middle path, returns old middle path.
 * @param [in] sMiddle Middle path.
 * @param [in] bReadOnly Will path be recorded read-only?
 */
void ProjectFile::SetMiddle(const String& sMiddle, const bool * pReadOnly /*= nullptr*/)
{
	m_paths.SetMiddle(sMiddle, false);
	if (pReadOnly != nullptr)
		m_bMiddleReadOnly = *pReadOnly;

	return;
}

/** 
 * @brief Returns right path.
 * @param [out] pReadOnly true if readonly was specified for path.
 * @return Right path.
 */
String ProjectFile::GetRight(bool * pReadOnly /*= nullptr*/) const
{
	if (pReadOnly != nullptr)
		*pReadOnly = m_bRightReadOnly;
	return m_paths.GetRight();
}

/** 
 * @brief Returns if right path is specified read-only.
 * @return true if right path is read-only, false otherwise.
 */
bool ProjectFile::GetRightReadOnly() const
{
	return m_bRightReadOnly;
}

/** 
 * @brief Set right path, returns old right path.
 * @param [in] sRight Right path.
 * @param [in] bReadOnly Will path be recorded read-only?
 */
void ProjectFile::SetRight(const String& sRight, const bool * pReadOnly /*= nullptr*/)
{
	m_paths.SetRight(sRight, false);
	if (pReadOnly != nullptr)
		m_bRightReadOnly = *pReadOnly;
}

/** 
 * @brief Returns filter.
 * @return Filter string.
 */
String ProjectFile::GetFilter() const
{
	return m_filter;
}

/** 
 * @brief Set filter.
 * @param [in] sFilter New filter string to set.
 */
void ProjectFile::SetFilter(const String& sFilter)
{
	m_filter = sFilter;
}

/** 
 * @brief Returns subfolder included -setting.
 * @return != 0 if subfolders are included.
 */
int ProjectFile::GetSubfolders() const
{
	return m_subfolders;
}

/** 
 * @brief set subfolder.
 * @param [in] iSubfolder New value for subfolder inclusion.
 */
void ProjectFile::SetSubfolders(bool bSubfolder)
{
	m_subfolders = bSubfolder ? 1 : 0;
}

/** 
 * @brief 
 *
 * @param [in] files Files in project
 * @param [in] bSubFolders If true subfolders included (recursive compare)
 */
void ProjectFile::SetPaths(const PathContext& files, bool bSubfolders)
{
	m_paths = files;
	m_subfolders = bSubfolders;
}

/** 
 * @brief Returns left and right paths and recursive from project file
 * 
 * @param [out] files Files in project
 * @param [out] bSubFolders If true subfolders included (recursive compare)
 */
void ProjectFile::GetPaths(PathContext& files, bool & bSubfolders) const
{
	files = m_paths;
	if (HasSubfolders())
		bSubfolders = (GetSubfolders() == 1);
}
