
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
 * @file  PropCodepage.cpp
 *
 * @brief Implementation file for PropCodepage propertyheet
 *
 */

#include "PropCodepage.h"
#include "ui_QPropCodepage.h"
//#include "common/unicoder.h"
//#include "common/ExConverter.h"
#include "OptionsDef.h"
#include "charsets.h"

QPropCodepage::QPropCodepage(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QPropCodepage)
{
	ui->setupUi(this);
	connect(ui->IDC_DETECT_AUTODETECTTYPE, SIGNAL(itemSelectionChanged()), this, SLOT(OnDetectAutodetecttype()));
	connect(ui->IDC_CP_SYSTEM, SIGNAL(clicked()), this, SLOT(OnCpSystem()));
	connect(ui->IDC_CP_CUSTOM, SIGNAL(clicked()), this, SLOT(OnCpCustom()));
	connect(ui->IDC_DETECT_CODEPAGE2, SIGNAL(clicked()), this, SLOT(OnDetectCodepage2()));
	connect(ui->IDC_CP_UI, SIGNAL(clicked()), this, SLOT(OnCpUi()));
}
QPropCodepage::~QPropCodepage()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 */
void QPropCodepage::ReadOptions()
{
	int CodePageDefault = m_options.value(OPT_CP_DEFAULT_MODE).toInt();
	switch (CodePageDefault) {
		case 0:
			ui->IDC_CP_SYSTEM->setChecked(1);
			break;
		case 1:
			ui->IDC_CP_UI->setChecked(1);
			break;
		case 2:
			ui->IDC_CP_CUSTOM->setChecked(1);
			break;
	}

	ui->IDC_CUSTOM_CP_NUMBER->setCurrentIndex(m_options.value(OPT_CP_DEFAULT_CUSTOM).toInt());
	ui->IDC_DETECT_CODEPAGE->setChecked(m_options.value(OPT_CP_DETECT).toInt()& 1);
	ui->IDC_DETECT_CODEPAGE2->setChecked((m_options.value(OPT_CP_DETECT).toInt()& 2) != 0);

	int nAutodetectType = m_options.value(OPT_CP_DETECT).toInt();
	if (nAutodetectType == 0)
		nAutodetectType = 50001;

	ui->IDC_DETECT_AUTODETECTTYPE->setCurrentIndex(nAutodetectType >> 16);

	// m_nCodepageSystem = GetOptionsMgr()->GetInt(OPT_CP_DEFAULT_MODE);
	/*m_nCustomCodepageValue = GetOptionsMgr()->GetInt(OPT_CP_DEFAULT_CUSTOM);
	m_cCustomCodepageValue = strutils::to_str(m_nCustomCodepageValue);
	m_bDetectCodepage = GetOptionsMgr()->GetInt(OPT_CP_DETECT) & 1;
	m_bDetectCodepage2 = (GetOptionsMgr()->GetInt(OPT_CP_DETECT) & 2) != 0;
	m_nAutodetectType = ((unsigned)GetOptionsMgr()->GetInt(OPT_CP_DETECT) >> 16);
	if (m_nAutodetectType == 0)
		m_nAutodetectType = 50001;*/
	// Enable/disable "Custom codepage" edit field

	// Init UI
	ui->IDC_CUSTOM_CP_NUMBER->setEnabled(ui->IDC_CP_CUSTOM->isChecked());
	// EnableDlgItem(IDC_CUSTOM_CP_NUMBER, IsDlgButtonChecked(IDC_CP_CUSTOM) == 1);
	ui->IDC_DETECT_AUTODETECTTYPE->setEnabled(ui->IDC_DETECT_CODEPAGE2->isChecked());
	/*m_comboAutodetectType.EnableWindow(
			IsDlgButtonChecked(IDC_DETECT_CODEPAGE2) == 1);*/

	// ToDo: Port
	/*m_comboCustomCodepageValue.SetWindowText(strutils::to_str(m_nCustomCodepageValue).c_str());

	IExconverter *pexconv = Exconverter::getInstance();
	if (pexconv != nullptr)
	{
		std::vector<CodePageInfo> cpi = pexconv->enumCodePages();
		for (size_t i = 0, j = 0; i < cpi.size(); i++)
		{
			if (cpi[i].codepage == 1200 /* UNICODE *//*)
				continue;
			String desc = strutils::format(_T("%05d - %s"), cpi[i].codepage, cpi[i].desc.c_str());
			m_comboCustomCodepageValue.AddString(desc.c_str());
			if (cpi[i].codepage == m_nCustomCodepageValue)
				m_comboCustomCodepageValue.SetCurSel(static_cast<int>(j));
			j++;
		}

		static int autodetectTypeList[] = {50001, 50936, 50950, 50932, 50949};
		for (int i = 0; i < sizeof(autodetectTypeList)/sizeof(int); i++)
		{
			String desc;
			pexconv->getCodepageDescription(autodetectTypeList[i], desc);
			m_comboAutodetectType.AddString(desc.c_str());
			m_comboAutodetectType.SetItemData(i, autodetectTypeList[i]);
			if (m_nAutodetectType == autodetectTypeList[i])
				m_comboAutodetectType.SetCurSel(i);
		}
	}*/
}

/**
 * @brief Writes options values from UI to storage.
 */
void QPropCodepage::WriteOptions()
{
	int nCodepage;
	if (ui->IDC_CP_CUSTOM->isChecked())
	{
		nCodepage = 0;
	}
	if (ui->IDC_CP_UI->isChecked())
	{
		nCodepage = 1;
	}
	if (ui->IDC_CP_SYSTEM->isChecked())
	{
		nCodepage = 2;
	}

	ui->IDC_DETECT_CODEPAGE2->setChecked((m_options.value(OPT_CP_DETECT).toInt()& 2) != 0);

	m_options.setValue(OPT_CP_DEFAULT_MODE, nCodepage);
	//GetOptionsMgr()->SaveOption(OPT_CP_DEFAULT_MODE, (int)m_nCodepageSystem);
	GetEncodingCodePageFromNameString();
	m_options.setValue(OPT_CP_DEFAULT_CUSTOM, ui->IDC_CUSTOM_CP_NUMBER->currentIndex());

	int nAutodetectType = 0; //ui->IDC_CUSTOM_CP_NUMBER->itemData(ui->IDC_CUSTOM_CP_NUMBER->currentIndex()); ToDO: Fix
	bool bDetectCodepage = ui->IDC_DETECT_CODEPAGE->isChecked();
	bool bDetectCodepage2  = ui->IDC_DETECT_CODEPAGE2->isChecked();

	m_options.setValue(OPT_CP_DETECT, (bDetectCodepage ? 1 : 0) | (bDetectCodepage2 << 1) | (nAutodetectType << 16));
	// GetOptionsMgr()->SaveOption(OPT_CP_DEFAULT_CUSTOM, (int)m_nCustomCodepageValue);
	// GetOptionsMgr()->SaveOption(OPT_CP_DETECT, (m_bDetectCodepage ? 1 : 0) | (m_bDetectCodepage2 << 1) | (m_nAutodetectType << 16));
}

void QPropCodepage::OnCpSystem()
{
	ui->IDC_CUSTOM_CP_NUMBER->setEnabled(false);
	// EnableDlgItem(IDC_CUSTOM_CP_NUMBER, false);
}

void QPropCodepage::OnCpCustom()
{
	ui->IDC_CUSTOM_CP_NUMBER->setEnabled(true);
	// EnableDlgItem(IDC_CUSTOM_CP_NUMBER, true);
}

void QPropCodepage::OnDetectCodepage2()
{
	ui->IDC_DETECT_AUTODETECTTYPE->setEnabled(ui->IDC_DETECT_CODEPAGE2->isChecked());
	/*m_comboAutodetectType.EnableWindow(
			IsDlgButtonChecked(IDC_DETECT_CODEPAGE2) == 1);*/
}

void QPropCodepage::OnDetectAutodetecttype()
{
	// Todo: Port to Qt
	//m_nAutodetectType = static_cast<int>(m_comboAutodetectType.GetItemData(m_comboAutodetectType.GetCurSel()));
}

void QPropCodepage::OnCpUi()
{
	ui->IDC_CUSTOM_CP_NUMBER->setEnabled(false);
	// EnableDlgItem(IDC_CUSTOM_CP_NUMBER, false);
}

void QPropCodepage::GetEncodingCodePageFromNameString()
{
	// ToDo: Port
	/*int nCustomCodepageValue = _ttol(m_cCustomCodepageValue.c_str());
	if (nCustomCodepageValue == 0)
		nCustomCodepageValue = GetEncodingCodePageFromName(ucr::toSystemCP(m_cCustomCodepageValue).c_str());
	//if found a new codepage valid
	if (nCustomCodepageValue)
		m_nCustomCodepageValue = nCustomCodepageValue;*/
}

