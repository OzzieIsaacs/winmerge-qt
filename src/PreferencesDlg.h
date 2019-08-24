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
#include "PropCompare.h"
#include "PropEditor.h"
#include "PropRegistry.h"
#include "PropCodepage.h"
#include "PropMergeColors.h"
#include "PropTextColors.h"
#include "PropSyntaxColors.h"
#include "PropMarkerColors.h"
#include "PropArchive.h"
#include "PropBackups.h"
#include "PropShell.h"
#include "PropCompareFolder.h"
#include "PropCompareBinary.h"
#include "PropCompareImage.h"

#include "QOptionsMgr.h"

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
	explicit QPreferencesDlg(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
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
	QPropCompare *m_pageCompare;
	QPropEditor *m_pageEditor;
	QPropRegistry *m_pageSystem;
	QPropCodepage *m_pageCodepage;
	QPropMergeColors *m_pageMergeColors;
	QPropTextColors *m_pageTextColors;
	QPropSyntaxColors *m_pageSyntaxColors;
	QPropMarkerColors *m_pageMarkerColors;
	QPropArchive *m_pageArchive;
	QPropBackups *m_pageBackups;
	QPropShell *m_pageShell;
	QPropCompareFolder *m_pageCompareFolder;
	QPropCompareBinary *m_pageCompareBinary;
	QPropCompareImage *m_pageCompareImage;

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
	// QOptionsMgr* m_OptionsMgr;
};
#endif // IDD_PREFERENCES_H
