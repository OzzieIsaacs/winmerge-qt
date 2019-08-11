/**
 * @file  PropSyntaxColors.cpp
 *
 * @brief Implementation of PropSyntaxColors propertysheet
 */

#include "PropSyntaxColors.h"
#include "ui_QPropSyntaxColors.h"
//#include "SyntaxColors.h"
//#include "OptionsSyntaxColors.h"
//#include "OptionsCustomColors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


QPropSyntaxColors::QPropSyntaxColors(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QPropSyntaxColors)
{
	ui->setupUi(this);
	/*
	connect(ui->IDC_SCOLOR_KEYWORDS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_KEYWORD>()));
	connect(ui->IDC_SCOLOR_FUNCTIONS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_FUNCNAME>()));
	connect(ui->IDC_SCOLOR_COMMENTS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_COMMENT>()));
	connect(ui->IDC_SCOLOR_NUMBERS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_NUMBER>()));
	connect(ui->IDC_SCOLOR_OPERATORS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_OPERATOR>()));
	connect(ui->IDC_SCOLOR_STRINGS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_STRING>()));
	connect(ui->IDC_SCOLOR_PREPROCESSOR, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_PREPROCESSOR>()));
	connect(ui->IDC_SCOLOR_USER1, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_USER1>()));
	connect(ui->IDC_SCOLOR_USER2, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolor<COLORINDEX_USER2>()));
	connect(ui->IDC_SCOLORS_BDEFAULTS, SIGNAL(clicked()), this, SLOT(OnBnClickedEcolorsBdefaults()));
	connect(ui->IDC_SCOLOR_KEYWORDS_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_KEYWORDS_BOLD, COLORINDEX_KEYWORD>()));
	connect(ui->IDC_SCOLOR_FUNCTIONS_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_FUNCTIONS_BOLD, COLORINDEX_FUNCNAME>()));
	connect(ui->IDC_SCOLOR_COMMENTS_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_COMMENTS_BOLD, COLORINDEX_COMMENT>()));
	connect(ui->IDC_SCOLOR_NUMBERS_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_NUMBERS_BOLD, COLORINDEX_NUMBER>()));
	connect(ui->IDC_SCOLOR_OPERATORS_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_OPERATORS_BOLD, COLORINDEX_OPERATOR>()));
	connect(ui->IDC_SCOLOR_STRINGS_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_STRINGS_BOLD, COLORINDEX_STRING>()));
	connect(ui->IDC_SCOLOR_PREPROCESSOR_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_PREPROCESSOR_BOLD, COLORINDEX_PREPROCESSOR>()));
	connect(ui->IDC_SCOLOR_USER1_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_USER1_BOLD, COLORINDEX_USER1>()));
	connect(ui->IDC_SCOLOR_USER2_BOLD, SIGNAL(clicked()), this, SLOT(OnBnClickedBoldButton<IDC_SCOLOR_USER2_BOLD, COLORINDEX_USER2>()));
	 */
}
QPropSyntaxColors::~QPropSyntaxColors()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * (Property sheet calls this before displaying all property pages)
 */
void QPropSyntaxColors::ReadOptions()
{
	// Set colors for buttons
	/*for (auto&& colorIndex : ColorIndices)
	{
		m_colorButtons[colorIndex].SetColor(m_pTempColors->GetColor(colorIndex));
		m_nBolds[colorIndex] = GetCheckVal(colorIndex);
	}*/
}

/**
 * @brief Writes options values from UI to storage.
 * (Property sheet calls this after displaying all property pages)
 */
void QPropSyntaxColors::WriteOptions()
{
	// User can only change colors via BrowseColorAndSave,
	// which writes to m_pTempColors
	// so user's latest choices are in m_pTempColors
	// (we don't have to read them from screen)
	//Options::SyntaxColors::Save(GetOptionsMgr(), m_pTempColors);
}

/**
 * @brief Let user browse common color dialog, and select a color & save to registry
 */
void QPropSyntaxColors::BrowseColorAndSave(unsigned colorIndex)
{
	/*COLORREF currentColor = m_pTempColors->GetColor(colorIndex);
	CColorDialog dialog(currentColor);
	Options::CustomColors::Load(GetOptionsMgr(), m_cCustColors.data());
	dialog.m_cc.lpCustColors = m_cCustColors.data();

	if (dialog.DoModal() == IDOK)
	{
		currentColor = dialog.GetColor();
		m_colorButtons[colorIndex].SetColor(currentColor);
		m_pTempColors->SetColor(colorIndex, currentColor);
	}
	Options::CustomColors::Save(GetOptionsMgr(), m_cCustColors.data());*/
}

/*template <unsigned colorIndex>
void QPropSyntaxColors::OnBnClickedEcolor()
{
	BrowseColorAndSave(colorIndex);
}

void QPropSyntaxColors::OnBnClickedEcolorsBdefaults()
{
	m_pTempColors->SetDefaults();
	for (auto&& colorIndex : ColorIndices)
	{
		m_colorButtons[colorIndex].SetColor(m_pTempColors->GetColor(colorIndex));
		m_nBolds[colorIndex] = GetCheckVal(colorIndex);
	}

	UpdateData(FALSE);
}

template <unsigned ctlId, unsigned colorIndex>
void QPropSyntaxColors::OnBnClickedBoldButton()
{
	m_pTempColors->SetBold(colorIndex, IsDlgButtonChecked(ctlId) == BST_CHECKED);
}
*/
int QPropSyntaxColors::GetCheckVal(unsigned int nColorIndex)
{
	/*if (m_pTempColors->GetBold(nColorIndex))
		return BST_CHECKED;
	else
		return BST_UNCHECKED;*/
}
