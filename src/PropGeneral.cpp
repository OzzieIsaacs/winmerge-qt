/////////////////////////////////////////////////////////////////////////////
//    WinMerge:  an interactive diff/merge utility
//    Copyright (C) 1997-2000  Thingamahoochie Software
//    Author: Dean Grimm
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
/////////////////////////////////////////////////////////////////////////////
/**
 * @file  PropGeneral.cpp
 *
 * @brief Implementation file for PropGeneral propertyheet
 *
 */
 #include "MergeApp.h"
#include "OptionsDef.h"
#include "PropGeneral.h"
#include "ui_QPropGeneral.h"


QPropGeneral::QPropGeneral(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropGeneral)
{
	ui->setupUi(this);

	/*CComboBox *pWnd = (CComboBox*)GetDlgItem(IDC_AUTO_COMPLETE_SOURCE);
	ASSERT(pWnd != nullptr);*/

	ui->IDC_AUTO_COMPLETE_SOURCE->addItem("Disabled");
	ui->IDC_AUTO_COMPLETE_SOURCE->addItem("From file system");
	ui->IDC_AUTO_COMPLETE_SOURCE->addItem("From MRU list");

	m_options = options;
	/*m_ctlLangList.SetDroppedWidth(600);
	m_ctlLangList.EnableWindow(FALSE);
	m_pLoadLanguagesThread = AfxBeginThread(LoadLanguagesThreadProc, this, 0, 0, CREATE_SUSPENDED);
	m_pLoadLanguagesThread->m_bAutoDelete = FALSE;
	m_pLoadLanguagesThread->ResumeThread();*/

	// return true;  // return TRUE  unless you set the focus to a control

}
QPropGeneral::~QPropGeneral()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 */
void QPropGeneral::ReadOptions()
{
	ui->IDC_SCROLL_CHECK->setChecked(m_options->value(OPT_SCROLL_TO_FIRST).toBool());
	ui->IDC_ESC_CLOSES_WINDOW->setChecked( m_options->value(OPT_CLOSE_WITH_ESC).toBool());
	ui->IDC_VERIFY_OPEN_PATHS->setChecked(m_options->value(OPT_VERIFY_OPEN_PATHS).toBool());
	ui->IDC_SINGLE_INSTANCE->setChecked(m_options->value(OPT_SINGLE_INSTANCE).toBool());
	ui->IDC_ASK_MULTIWINDOW_CLOSE->setChecked( m_options->value(OPT_ASK_MULTIWINDOW_CLOSE).toBool());
	ui->IDC_PRESERVE_FILETIME->setChecked(m_options->value(OPT_PRESERVE_FILETIMES).toBool());
	ui->IDC_STARTUP_FOLDER_SELECT->setChecked(m_options->value(OPT_SHOW_SELECT_FILES_AT_STARTUP).toBool());
	ui->IDC_CLOSE_WITH_OK->setChecked(m_options->value(OPT_CLOSE_WITH_OK).toBool());
	ui->IDC_AUTO_COMPLETE_SOURCE->setCurrentIndex(m_options->value(OPT_AUTO_COMPLETE_SOURCE).toInt());
}

/**
 * @brief Writes options values from UI to storage.
 */
void QPropGeneral::WriteOptions()
{
	m_options->setValue(OPT_SCROLL_TO_FIRST, ui->IDC_SCROLL_CHECK->isChecked());
	m_options->setValue(OPT_SINGLE_INSTANCE, ui->IDC_SINGLE_INSTANCE->isChecked());
	m_options->setValue(OPT_VERIFY_OPEN_PATHS, ui->IDC_VERIFY_OPEN_PATHS->isChecked());
    m_options->setValue(OPT_CLOSE_WITH_ESC, ui->IDC_ESC_CLOSES_WINDOW->isChecked());
	m_options->setValue(OPT_ASK_MULTIWINDOW_CLOSE, ui->IDC_ASK_MULTIWINDOW_CLOSE->isChecked());
	m_options->setValue(OPT_AUTO_COMPLETE_SOURCE, ui->IDC_AUTO_COMPLETE_SOURCE->currentIndex());
	m_options->setValue(OPT_PRESERVE_FILETIMES, ui->IDC_PRESERVE_FILETIME->isChecked());
	m_options->setValue(OPT_SHOW_SELECT_FILES_AT_STARTUP, ui->IDC_STARTUP_FOLDER_SELECT->isChecked());
	m_options->setValue(OPT_CLOSE_WITH_OK, ui->IDC_CLOSE_WITH_OK->isChecked());
	//ToDo: Enable language settings
	/*int index = m_ctlLangList.GetCurSel();
	if (index >= 0)
	{
		WORD lang = (WORD)m_ctlLangList.GetItemData(index);
		GetOptionsMgr()->SaveOption(OPT_SELECTED_LANGUAGE, (int)lang);
	}*/
}

/*
UINT QPropGeneral::LoadLanguagesThreadProc(void *pParam)
{
	PropGeneral *pPropGeneral = reinterpret_cast<PropGeneral *>(pParam);
	pPropGeneral->m_langs = theApp.m_pLangDlg->GetAvailableLanguages();
	pPropGeneral->PostMessage(WM_APP);
	return 0;
}

LRESULT QPropGeneral::OnLoadLanguages(WPARAM, LPARAM)
{
	for (auto&& i : m_langs)
	{
		m_ctlLangList.AddString(i.second.c_str());
		m_ctlLangList.SetItemData(m_ctlLangList.GetCount() - 1, i.first);
		if (i.first == theApp.m_pLangDlg->GetLangId())
			m_ctlLangList.SetCurSel(m_ctlLangList.GetCount() - 1);
	}
	m_ctlLangList.EnableWindow(TRUE);
	return 0;
}*/

