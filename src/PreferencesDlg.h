/**
 * @file  PreferencesDlg.h
 *
 * @brief Declaration of CPreferencesDlg class
 *
 * @note This code originates from AbstractSpoon / TodoList
 * (http://www.abstractspoon.com/) but is modified to use in
 * WinMerge.
 */
#pragma once

#ifndef PREFERENCESDLG_H
#define PREFERENCESDLG_H

#include <QDialog>
#include "PropGeneral.h"
#include "IDD_PROPPAGE_COMPARE.h"
#include "PropEditor.h"
#include "PropRegistry.h"
#include "IDD_PROPPAGE_CODEPAGE.h"
#include "IDD_PROPPAGE_COLORS_WINMERGE.h"
#include "IDD_PROPPAGE_COLORS_TEXT.h"
#include "IDD_PROPPAGE_COLORS_SYNTAX.h"
#include "IDD_PROPPAGE_COLORS_MARKER.h"
#include "PropArchive.h"
#include "PropBackups.h"
#include "PropShell.h"
#include "IDD_PROPPAGE_COMPARE_FOLDER.h"
#include "IDD_PROPPAGE_COMPARE_BINARY.h"
#include "IDD_PROPPAGE_COMPARE_IMAGE.h"

/*#include "PropertyPageHost.h"*/
// #include <QWidget>
//#include "OptionsMgr.h"
//#include <QSettings>
//class SyntaxColors;

namespace Ui {
class QPreferencesDlg;
}
class QPreferencesDlg : public QDialog
{
	Q_OBJECT

public:
	explicit QPreferencesDlg(QWidget *parent = nullptr);
	~QPreferencesDlg();

	// void SetSyntaxColors(SyntaxColors *pColors);

protected:

	/*void AddPage(CPropertyPage* pPage, UINT nResourceID);
	void AddPage(CPropertyPage* pPage, LPCTSTR szPath);
	void AddPage(CPropertyPage* pPage, UINT nTopHeading, UINT nSubHeading);
	void SetActivePage(int nPage);
	CString GetItemPath(HTREEITEM hti);*/

	void ReadOptions(bool bUpdate = false);
	void SaveOptions();
	void SafeUpdatePage(QWidget* pPage, bool bSaveAndValidate);

	/* CPropertyPageHost m_pphost;*/

	QPropGeneral *m_pageGeneral;
	IDD_PROPPAGE_COMPARE *m_pageCompare;
	QPropEditor *m_pageEditor;
	QPropRegistry *m_pageSystem;
	IDD_PROPPAGE_CODEPAGE *m_pageCodepage;
	IDD_PROPPAGE_COLORS_WINMERGE *m_pageMergeColors;
	IDD_PROPPAGE_COLORS_TEXT *m_pageTextColors;
	IDD_PROPPAGE_COLORS_SYNTAX *m_pageSyntaxColors;
	IDD_PROPPAGE_COLORS_MARKER *m_pageMarkerColors;
	QPropArchive *m_pageArchive;
	QPropBackups *m_pageBackups;
	QPropShell *m_pageShell;
	IDD_PROPPAGE_COMPARE_FOLDER *m_pageCompareFolder;
	IDD_PROPPAGE_COMPARE_BINARY *m_pageCompareBinary;
	IDD_PROPPAGE_COMPARE_IMAGE *m_pageCompareImage;

	/*SyntaxColors *m_pSyntaxColors;

	CMapPtrToPtr m_mapPP2HTI;*/

private slots:
	void OnImportButton();
	void OnExportButton();
	void OnHelpButton();
	void onClickedOk();
	void OnSelchangedPages();


private:
	Ui::QPreferencesDlg *ui;
	// QSettings m_OptionsMgr;
};
#endif // IDD_PREFERENCES_H
