/**
 * @file PreferencesDlg.cpp
 *
 * @brief Implementation file for CPreferencesDlg
 *
 * @note This code originates from AbstractSpoon / TodoList
 * (http://www.abstractspoon.com/) but is modified to use in
 * WinMerge.
 */
#include "PreferencesDlg.h"
#include "ui_QPreferencesDlg.h"
#include "PropBackups.h"
#include "PropCodepage.h"
#include "IDD_PROPPAGE_COLORS_DIR.h"
#include "PropMarkerColors.h"
#include "PropSyntaxColors.h"
#include "PropTextColors.h"
#include "PropMergeColors.h"
#include "PropCompare.h"
#include "PropCompareBinary.h"
#include "PropCompareFolder.h"
#include "PropCompareImage.h"
#include "PropEditor.h"
#include "PropGeneral.h"
#include "PropShell.h"
#include "PropArchive.h"
#include "PropRegistry.h"
#include "paths.h"
#include <QString>
#include <QListWidgetItem>
#include <QFileDialog>

/**
 * @brief Location for file compare specific help to open.
 */
//ToDo: Port
//static TCHAR OptionsHelpLocation[] = _T("::/htmlhelp/Configuration.html");

/////////////////////////////////////////////////////////////////////////////
// CPreferencesDlg dialog
//ToDo: Port
//const TCHAR PATHDELIM = '>';


QPreferencesDlg::QPreferencesDlg(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPreferencesDlg)

{

	ui->setupUi(this);

	QStringList items;

	m_pageGeneral = new QPropGeneral(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageGeneral);
	items +=m_pageGeneral->windowTitle();
	QWidget *propcomapare = new QPropCompare(this, options);
	ui->IDOPTIONWIDGET->addWidget( propcomapare);
	items += "   " + propcomapare->windowTitle();
	m_pageCompareBinary = new QPropCompareBinary(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageCompareBinary);
	items += "   " + m_pageCompareBinary->windowTitle();
	m_pageCompareFolder= new QPropCompareFolder(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageCompareFolder);
	items += "   " + m_pageCompareFolder->windowTitle();
	m_pageCompareImage = new QPropCompareImage(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageCompareImage);
	items += "   " + m_pageCompareImage->windowTitle();

	m_pageEditor = new QPropEditor(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageEditor);
	items +=m_pageEditor->windowTitle();
	/*QWidget *propcolordir = new IDD_PROPPAGE_COLORS_DIR(this);
	ui->IDOPTIONWIDGET->addWidget( propcolordir);
	items += "   " + propcolordir->windowTitle();*/
	m_pageMarkerColors = new QPropMarkerColors(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageMarkerColors);
	items += "   " + m_pageMarkerColors->windowTitle();
	m_pageSyntaxColors = new QPropSyntaxColors(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageSyntaxColors);
	items += "   " + m_pageSyntaxColors->windowTitle();
	m_pageTextColors = new QPropTextColors(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageTextColors);
	items += "   " + m_pageTextColors->windowTitle();
	m_pageMergeColors = new QPropMergeColors(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageMergeColors);
	items += "   " + m_pageMergeColors->windowTitle();

	m_pageArchive = new QPropArchive(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageArchive);
	items +=m_pageArchive->windowTitle();
	m_pageSystem = new QPropRegistry(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageSystem);
	items +=m_pageSystem->windowTitle();
	m_pageBackups = new QPropBackups(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageBackups);
	items += m_pageBackups->windowTitle();
	m_pageCodepage = new QPropCodepage(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageCodepage);
	items +=m_pageCodepage->windowTitle();
	m_pageShell = new QPropShell(this, options);
	ui->IDOPTIONWIDGET->addWidget( m_pageShell);
	items +=m_pageShell->windowTitle();

	ReadOptions();

	ui->IDPROPLIST->addItems(items);

	connect(ui->IDPROPLIST, SIGNAL(itemSelectionChanged()), this, SLOT(OnSelchangedPages()));
	connect(ui->IDCANCEL, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->IDOK, SIGNAL(clicked()), this, SLOT(onClickedOk()));
	connect(ui->IDC_TREEOPT_HELP, SIGNAL(clicked()), this, SLOT(OnHelpButton()));
	connect(ui->IDC_TREEOPT_IMPORT, SIGNAL(clicked()), this, SLOT(OnImportButton()));
	connect(ui->IDC_TREEOPT_EXPORT, SIGNAL(clicked()), this, SLOT(OnExportButton()));

}
QPreferencesDlg::~QPreferencesDlg()
{
	delete ui;
}

void QPreferencesDlg::OnImportButton()
{
	QString s;
	s = QFileDialog::getOpenFileName(this, "Select file for import", nullptr,
									 "Options files (*.ini) ;; All Files (*.*)");
	if(!s.isEmpty()){
		//Todo Import Options
		/*if (m_pOptionsMgr->ImportOptions(s) == COption::OPT_OK)
		{
			Options::SyntaxColors::Load(m_pOptionsMgr, m_pSyntaxColors);
			ReadOptions(true);
			LangMessageBox(IDS_OPT_IMPORT_DONE, MB_ICONINFORMATION);
		}
		else
			LangMessageBox(IDS_OPT_IMPORT_ERR, MB_ICONWARNING);*/

	}
}

void QPreferencesDlg::OnExportButton()
{
	QString settingsFile;
	settingsFile = QFileDialog::getOpenFileName(this, "Select file for export", nullptr,
												"Options files (*.ini) ;; All Files (*.*)");
	if(!settingsFile.isEmpty()){
		// ToDo: Export Settings
		/*if (paths::FindExtension(settingsFile).empty())
			settingsFile += _T(".ini");

		// Save all new settings before exporting
		m_pphost.UpdatePagesData();
		SaveOptions();

		if (m_pOptionsMgr->ExportOptions(settingsFile) == COption::OPT_OK)
			LangMessageBox(IDS_OPT_EXPORT_DONE, MB_ICONINFORMATION);
		else
			LangMessageBox(IDS_OPT_EXPORT_ERR, MB_ICONWARNING);*/
	}
}

void QPreferencesDlg::OnHelpButton()
{
	// ToDo: Show Help
	//theApp.ShowHelp(OptionsHelpLocation);
}

void QPreferencesDlg::onClickedOk()
{
	SaveOptions();
	this->close();
}

void QPreferencesDlg::OnSelchangedPages()
{
	// ui->IDPROPLIST->currentRow();
	ui->IDOPTIONWIDGET->setCurrentIndex(ui->IDPROPLIST->currentRow());
}

/**
 * @brief Read options from storage to UI controls.
 * @param [in] bUpdate If `true` UpdateData() is called
 */
void QPreferencesDlg::ReadOptions(bool bUpdate)
{
	m_pageGeneral->ReadOptions();
	//m_pageMergeColors->ReadOptions();
	m_pageTextColors->ReadOptions();
	m_pageSyntaxColors->ReadOptions();
	m_pageMarkerColors->ReadOptions();
	m_pageCompareFolder->ReadOptions();
	m_pageCompareBinary->ReadOptions();
	m_pageCompareImage->ReadOptions();
	m_pageEditor->ReadOptions();
	m_pageCodepage->ReadOptions();
	m_pageArchive->ReadOptions();
	m_pageBackups->ReadOptions();
	m_pageShell->ReadOptions();
	m_pageSystem->ReadOptions();

	if (bUpdate)
	{
		// Not needed anymore?
		SafeUpdatePage(m_pageGeneral, false);
		SafeUpdatePage(m_pageMergeColors, false);
		SafeUpdatePage(m_pageTextColors, false);
		SafeUpdatePage(m_pageSyntaxColors, false);
		SafeUpdatePage(m_pageMarkerColors, false);
		SafeUpdatePage(m_pageSystem, false);
		SafeUpdatePage(m_pageCompare, false);
		SafeUpdatePage(m_pageCompareFolder, false);
		SafeUpdatePage(m_pageCompareBinary, false);
		SafeUpdatePage(m_pageCompareImage, false);
		SafeUpdatePage(m_pageEditor, false);
		SafeUpdatePage(m_pageCodepage, false);
		SafeUpdatePage(m_pageArchive, false);
		SafeUpdatePage(m_pageBackups, false);
		SafeUpdatePage(m_pageShell, false);
	}
}

/**
 * @brief Write options from UI to storage.
 */
void QPreferencesDlg::SaveOptions()
{
	m_pageGeneral->WriteOptions();
	m_pageSystem->WriteOptions();
	m_pageCompare->WriteOptions();
	m_pageCompareFolder->WriteOptions();
	m_pageCompareBinary->WriteOptions();
	m_pageCompareImage->WriteOptions();
	m_pageEditor->WriteOptions();
	//m_pageMergeColors->WriteOptions();
	m_pageTextColors->WriteOptions();
	m_pageSyntaxColors->WriteOptions();
	m_pageMarkerColors->WriteOptions();
	m_pageCodepage->WriteOptions();
	m_pageArchive->WriteOptions();
	m_pageBackups->WriteOptions();
	m_pageShell->WriteOptions();
}

/*
void IDD_PREFERENCES::SetSyntaxColors(SyntaxColors *pColors)
{
	m_pSyntaxColors = pColors;
}
*/
/**
 * @brief Do a safe UpdateData call for propertypage.
 * This function does safe UpdateData call for given propertypage. As it is,
 * all propertypages may not have been yet initialized properly, so we must
 * have some care when calling updateData for them.
 * @param [in] pPage Propertypage to update.
 * @param bSaveAndValidate UpdateData direction parameter.
 */
 // Don't need this function??
void QPreferencesDlg::SafeUpdatePage(QWidget* pPage, bool bSaveAndValidate)
{
	if(pPage != nullptr){
		//pPage->UpdateData(bSaveAndValidate);
	}
}