/**
 * @file  PropEditor.cpp
 *
 * @brief Implementation of PropEditor propertysheet
 */

#include "PropEditor.h"
#include "ui_QPropEditor.h"
#include "OptionsDef.h"
#include <QMessageBox>

/** @brief Maximum size for tabs in spaces. */
static const int MAX_TABSIZE = 64;


QPropEditor::QPropEditor(QWidget *parent, QOptionsMgr* options) :
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

	//ToDo: Implement Focus out handling
	//connect(ui->IDC_TAB_EDIT, SIGNAL(focusOutEvent()), this, SLOT(OnEnKillfocusTabEdit()));

	m_options = options;
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
	ui->IDC_TAB_EDIT->setPlainText(m_options->value(OPT_TAB_SIZE).toString());
	bool tabType = m_options->value(OPT_TAB_TYPE).toBool();
	if (tabType){
		ui->IDC_PROP_INSERT_TABS->setChecked(true);
	}
	else
	{
		ui->IDC_PROP_INSERT_SPACES->setChecked(true);
	}
	ui->IDC_AUTOMRESCAN_CHECK->setChecked(m_options->value(OPT_AUTOMATIC_RESCAN).toBool());
	ui->IDC_HILITE_CHECK->setChecked(m_options->value(OPT_SYNTAX_HIGHLIGHT).toBool());
	ui->IDC_MIXED_EOL->setChecked(m_options->value(OPT_ALLOW_MIXED_EOL).toBool());
	ui->IDC_VIEW_LINE_DIFFERENCES->setChecked(m_options->value(OPT_WORDDIFF_HIGHLIGHT).toBool());
	ui->IDC_HILITE_CHECK->setChecked(m_options->value(OPT_SYNTAX_HIGHLIGHT).toBool());
	ui->IDC_HILITE_CHECK->setChecked(m_options->value(OPT_SYNTAX_HIGHLIGHT).toBool());

	bool breakSeperator = m_options->value(OPT_BREAK_ON_WORDS).toBool();
	if (breakSeperator){
		ui->IDC_EDITOR_CHARLEVEL->setChecked(true);
	}
	else
	{
		ui->IDC_EDITOR_WORDLEVEL->setChecked(true);
	}
	ui->IDC_BREAK_CHARS->setPlainText(m_options->value(OPT_BREAK_SEPARATORS).toString());

	// 	m_nBreakType = GetOptionsMgr()->GetInt(OPT_BREAK_TYPE);


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
	ui->IDC_BREAK_TYPE->addItem(tr("Break at whitespace"));
	ui->IDC_BREAK_TYPE->addItem(tr("Break at whitespace or punctuation"));
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
	unsigned value = ui->IDC_TAB_EDIT->toPlainText().toInt();
	if (value < 1 || value > MAX_TABSIZE)
	{
		QString msg = tr("Value in Tab size -field is not in range WinMerge accepts.\n\nPlease use values 1 - %1.").arg(MAX_TABSIZE);
		QMessageBox::warning(nullptr, QObject::tr("Warning"), msg);
	}
}
