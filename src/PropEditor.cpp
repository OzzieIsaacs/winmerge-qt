/**
 * @file  PropEditor.cpp
 *
 * @brief Implementation of PropEditor propertysheet
 */

#include "PropEditor.h"
#include "ui_QPropEditor.h"
#include "OptionsDef.h"

QPropEditor::QPropEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QPropEditor)
{
	ui->setupUi(this);
	LoadBreakTypeStrings();
	//UpdateDataToWindow();
	UpdateLineDiffControls();

	connect(ui->IDC_VIEW_LINE_DIFFERENCES, SIGNAL(clicked()), this, SLOT(OnLineDiffControlClicked()));
	connect(ui->IDC_EDITOR_CHARLEVEL, SIGNAL(clicked()), this, SLOT(OnLineDiffControlClicked()));
	connect(ui->IDC_EDITOR_WORDLEVEL, SIGNAL(clicked()), this, SLOT(OnLineDiffControlClicked()));
	connect(ui->IDC_TAB_EDIT, SIGNAL(clicked()), this, SLOT(OnEnKillfocusTabEdit()));
}
QPropEditor::~QPropEditor()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 */
void QPropEditor::ReadOptions()
{
	// ToDo Port
	/*
	m_nTabSize = GetOptionsMgr()->GetInt(OPT_TAB_SIZE);
	m_nTabType = GetOptionsMgr()->GetInt(OPT_TAB_TYPE);
	m_bAutomaticRescan = GetOptionsMgr()->GetBool(OPT_AUTOMATIC_RESCAN);
	m_bHiliteSyntax = GetOptionsMgr()->GetBool(OPT_SYNTAX_HIGHLIGHT);
	m_bAllowMixedEol = GetOptionsMgr()->GetBool(OPT_ALLOW_MIXED_EOL);
	m_bViewLineDifferences = GetOptionsMgr()->GetBool(OPT_WORDDIFF_HIGHLIGHT);
	m_bBreakOnWords = GetOptionsMgr()->GetBool(OPT_BREAK_ON_WORDS);
	m_nBreakType = GetOptionsMgr()->GetInt(OPT_BREAK_TYPE);
	m_breakChars = GetOptionsMgr()->GetString(OPT_BREAK_SEPARATORS);*/
}

/**
 * @brief Writes options values from UI to storage.
 */
void QPropEditor::WriteOptions()
{
	// ToDo Port
	/*
	// Sanity check tabsize
	if (m_nTabSize < 1)
		m_nTabSize = 1;
	if (m_nTabSize > MAX_TABSIZE)
		m_nTabSize = MAX_TABSIZE;
	GetOptionsMgr()->SaveOption(OPT_TAB_SIZE, (int)m_nTabSize);
	GetOptionsMgr()->SaveOption(OPT_TAB_TYPE, (int)m_nTabType);
	GetOptionsMgr()->SaveOption(OPT_AUTOMATIC_RESCAN, m_bAutomaticRescan);
	GetOptionsMgr()->SaveOption(OPT_ALLOW_MIXED_EOL, m_bAllowMixedEol);
	GetOptionsMgr()->SaveOption(OPT_SYNTAX_HIGHLIGHT, m_bHiliteSyntax);
	GetOptionsMgr()->SaveOption(OPT_WORDDIFF_HIGHLIGHT, m_bViewLineDifferences);
	GetOptionsMgr()->SaveOption(OPT_BREAK_ON_WORDS, m_bBreakOnWords);
	GetOptionsMgr()->SaveOption(OPT_BREAK_TYPE, m_nBreakType);
	GetOptionsMgr()->SaveOption(OPT_BREAK_SEPARATORS, String(m_breakChars));*/
}


/**
 * @brief Load strings (from resource) into combobox for break type
 */
void QPropEditor::LoadBreakTypeStrings()
{
	// ToDo Port
	/*
	CComboBox * cbo = (CComboBox *)GetDlgItem(IDC_BREAK_TYPE);
	cbo->AddString(_("Break at whitespace").c_str());
	cbo->AddString(_("Break at whitespace or punctuation").c_str());*/
}

/**
 * @brief Handlers any clicks in any of the line differencing controls
 */
void QPropEditor::OnLineDiffControlClicked()
{
	UpdateLineDiffControls();
}

/**
 * @brief Update availability of line difference controls
 */
void QPropEditor::UpdateLineDiffControls()
{
	// ToDo Port
	/*
	UpdateDataFromWindow();
	// Can only choose char/word level if line differences are enabled
	EnableDlgItem(IDC_EDITOR_CHARLEVEL, m_bViewLineDifferences);
	EnableDlgItem(IDC_EDITOR_WORDLEVEL, m_bViewLineDifferences);
	// Can only choose break type if line differences are enabled & we're breaking on words
	EnableDlgItem(IDC_BREAK_TYPE, m_bViewLineDifferences);*/
}

/**
 * @brief Check tabsize value when control loses focus.
 */
void QPropEditor::OnEnKillfocusTabEdit()
{
	// ToDo Port
	/*
	unsigned value = GetDlgItemInt(IDC_TAB_EDIT);
	if (value < 1 || value > MAX_TABSIZE)
	{
		String msg = strutils::format_string1(
				_("Value in Tab size -field is not in range WinMerge accepts.\n\nPlease use values 1 - %1."),
				strutils::to_str(MAX_TABSIZE));
		AfxMessageBox(msg.c_str(), MB_ICONWARNING);
	}*/
}
