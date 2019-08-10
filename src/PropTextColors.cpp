/**
 * @file  PropTextColors.cpp
 *
 * @brief Implementation of PropTextColors propertysheet
 */

#include "PropTextColors.h"
#include "ui_QPropTextColors.h"
//#include "SyntaxColors.h"
//#include "OptionsCustomColors.h"
#include "OptionsDef.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

QPropTextColors::QPropTextColors(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QPropTextColors)
{
	ui->setupUi(this);
}
QPropTextColors::~QPropTextColors()
{
	delete ui;
}

void QPropTextColors::ReadOptions()
{
	// ToDo: port
	//m_bCustomColors = GetOptionsMgr()->GetBool(OPT_CLR_DEFAULT_TEXT_COLORING) ? false : true;
	//SerializeColorsToFromScreen(LOAD_COLORS);
}

/**
 * @brief Writes options values from UI to storage.
 * (Property sheet calls this after displaying all property pages)
 */
void QPropTextColors::WriteOptions()
{
	// ToDo: port
	//GetOptionsMgr()->SaveOption(OPT_CLR_DEFAULT_TEXT_COLORING, !m_bCustomColors);
	// User can only change colors via BrowseColorAndSave,
	// which writes to m_pTempColors
	// so user's latest choices are in m_pTempColors
	// (we don't have to read them from screen)

	// Also, CPropSyntaxColors writes m_pTempColors out, so we don't have to
	// We share m_pTempColors with CPropSyntaxColors
}

/**
 * @brief Let user browse common color dialog, and select a color
 * @param [in] colorButton Button for which to change color.
 * @param [in] colorIndex Index to color table.
 */
/*void QPropTextColors::BrowseColorAndSave(CColorButton & colorButton, int colorIndex)
{
	// ToDo: port
	// Ignore user if colors are slaved to system
	if (IsDlgButtonChecked(IDC_DEFAULT_STANDARD_COLORS) == BST_UNCHECKED)
		return;

	COLORREF currentColor = m_pTempColors->GetColor(colorIndex);
	CColorDialog dialog(currentColor);
	Options::CustomColors::Load(GetOptionsMgr(), m_cCustColors.data());
	dialog.m_cc.lpCustColors = m_cCustColors.data();

	if (dialog.DoModal() == IDOK)
	{
		currentColor = dialog.GetColor();
		colorButton.SetColor(currentColor);
		m_pTempColors->SetColor(colorIndex, currentColor);
	}
	Options::CustomColors::Save(GetOptionsMgr(), m_cCustColors.data());
}*/

/**
 * @brief User wants to change whitespace color
 */
void QPropTextColors::OnWhitespaceBackgroundColor()
{
	//BrowseColorAndSave(m_btnWhitespaceBackground, COLORINDEX_WHITESPACE);
}

/**
 * @brief User wants to change regular background color
 */
void QPropTextColors::OnRegularBackgroundColor()
{
	//BrowseColorAndSave(m_btnRegularBackground, COLORINDEX_BKGND);
}

/**
 * @brief User wants to change regular text color
 */
void QPropTextColors::OnRegularTextColor()
{
	//BrowseColorAndSave(m_btnRegularText, COLORINDEX_NORMALTEXT);
}

/**
 * @brief User wants to change regular selection background color
 */
void QPropTextColors::OnSelectionBackgroundColor()
{
	//BrowseColorAndSave(m_btnSelectionBackground, COLORINDEX_SELBKGND);
}

/**
 * @brief User wants to change regular selection text color
 */
void QPropTextColors::OnSelectionTextColor()
{
	//BrowseColorAndSave(m_btnSelectionText, COLORINDEX_SELTEXT);
}

/**
 * @brief User wants to change margin background color
 */
void QPropTextColors::OnMarginBackgroundColor()
{
	//BrowseColorAndSave(m_btnMarginBackground, COLORINDEX_SELMARGIN);
}

/**
 * @brief Load all colors, Save all colors, or set all colors to default
 * @param [in] op Operation to do, one of
 *  - SET_DEFAULTS : Sets colors to defaults
 *  - LOAD_COLORS : Loads colors from registry
 * (No save operation because BrowseColorAndSave saves immediately when user chooses)
 */
void QPropTextColors::SerializeColorsToFromScreen(OPERATION op)
{
	// ToDo: Port easy
	/*
	if (op == SET_DEFAULTS)
		m_pTempColors->SetDefaults();

	SerializeColorToFromScreen(op, m_btnWhitespaceBackground, COLORINDEX_WHITESPACE);

	SerializeColorToFromScreen(op, m_btnRegularBackground, COLORINDEX_BKGND);
	SerializeColorToFromScreen(op, m_btnRegularText, COLORINDEX_NORMALTEXT);

	SerializeColorToFromScreen(op, m_btnSelectionBackground, COLORINDEX_SELBKGND);
	SerializeColorToFromScreen(op, m_btnSelectionText, COLORINDEX_SELTEXT);

	SerializeColorToFromScreen(op, m_btnMarginBackground, COLORINDEX_SELMARGIN);*/
}

/**
 * @brief Load color to button, Save color from button, or set button color to default
 * @param [in] op Operation to do, one of
 *  - SET_DEFAULTS : Sets colors to defaults
 *  - LOAD_COLORS : Loads colors from registry
 * (No save operation because BrowseColorAndSave saves immediately when user chooses)
 */
/*void IDD_PROPPAGE_COLORS_TEXT::SerializeColorToFromScreen(OPERATION op, CColorButton & btn, int colorIndex)
{
	switch (op)
	{
		case SET_DEFAULTS:
		case LOAD_COLORS:
			btn.SetColor(m_pTempColors->GetColor(colorIndex));
			break;
	}
}*/

/**
 * @brief Set colors to track standard (theme) colors
 */
void QPropTextColors::OnDefaultsStandardColors()
{
	// Reset all text colors to default every time user checks defaults button
	SerializeColorsToFromScreen(SET_DEFAULTS);

	//UpdateData();
}

/**
 * @brief Enable / disable color controls on dialog.
 * @param [in] bEnable If `true` color controls are enabled.
 */
void QPropTextColors::EnableColorButtons(bool bEnable)
{
	// Todo: port easy
	/*
	EnableDlgItem(IDC_CUSTOM_COLORS_GROUP, bEnable);
	EnableDlgItem(IDC_WHITESPACE_COLOR_LABEL, bEnable);
	EnableDlgItem(IDC_TEXT_COLOR_LABEL, bEnable);
	EnableDlgItem(IDC_SELECTION_COLOR_LABEL, bEnable);
	EnableDlgItem(IDC_MARGIN_COLOR_LABEL, bEnable);
	EnableDlgItem(IDC_BACKGROUND_COLUMN_LABEL, bEnable);
	EnableDlgItem(IDC_TEXT_COLUMN_LABEL, bEnable);*/
}
