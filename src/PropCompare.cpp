#include "PropCompare.h"
#include "ui_QPropCompare.h"
#include "OptionsDef.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

QPropCompare::QPropCompare(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropCompare)
{
	ui->setupUi(this);
	connect(ui->IDC_COMPARE_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));
	m_options = options;
}
QPropCompare::~QPropCompare()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void QPropCompare::ReadOptions()
{
	int m_nIgnoreWhite = m_options->value(OPT_CMP_IGNORE_WHITESPACE).toInt();
	switch (m_nIgnoreWhite)
	{
		case 0:
			ui->IDC_WHITESPACE->setChecked(1);
			break;
		case 1:
			ui->IDC_WHITE_CHANGE->setChecked(1);
			break;
		case 2:
			ui->IDC_ALL_WHITE->setChecked(1);
			break;

	}
	ui->IDC_IGNBLANKS_CHECK->setChecked(m_options->value(OPT_CMP_IGNORE_BLANKLINES).toBool());
	ui->IDC_FILTERCOMMENTS_CHECK->setChecked(m_options->value(OPT_CMP_FILTER_COMMENTLINES).toBool());
	ui->IDC_IGNCASE_CHECK->setChecked(m_options->value(OPT_CMP_IGNORE_CASE).toBool());
	ui->IDC_EOL_SENSITIVE->setChecked(m_options->value(OPT_CMP_IGNORE_EOL).toBool());
	ui->IDC_CP_SENSITIVE->setChecked(m_options->value(OPT_CMP_IGNORE_CODEPAGE).toBool());
	ui->IDC_MOVED_BLOCKS->setChecked(m_options->value(OPT_CMP_MOVED_BLOCKS).toBool());
	ui->IDC_MATCH_SIMILAR_LINES->setChecked(m_options->value(OPT_CMP_MATCH_SIMILAR_LINES).toBool());

}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void QPropCompare::WriteOptions()
{
	int m_nIgnoreWhite = 0;
	if (ui->IDC_WHITESPACE->isChecked())
	{
		m_nIgnoreWhite = 0;
	}
	if (ui->IDC_WHITE_CHANGE->isChecked())
	{
		m_nIgnoreWhite = 1;
	}
	if (ui->IDC_ALL_WHITE->isChecked())
	{
		m_nIgnoreWhite = 2;
	}
	m_options->setValue(OPT_CMP_IGNORE_WHITESPACE,m_nIgnoreWhite);

	m_options->setValue(OPT_CMP_IGNORE_BLANKLINES, ui->IDC_IGNBLANKS_CHECK->isChecked());
	m_options->setValue(OPT_CMP_FILTER_COMMENTLINES, ui->IDC_FILTERCOMMENTS_CHECK->isChecked());
	m_options->setValue(OPT_CMP_IGNORE_CODEPAGE, ui->IDC_IGNCASE_CHECK->isChecked());
	m_options->setValue(OPT_CMP_IGNORE_EOL, ui->IDC_EOL_SENSITIVE->isChecked());
	m_options->setValue(OPT_CMP_IGNORE_CASE, ui->IDC_CP_SENSITIVE->isChecked());
	m_options->setValue(OPT_CMP_MOVED_BLOCKS, ui->IDC_MOVED_BLOCKS->isChecked());
	m_options->setValue(OPT_CMP_MATCH_SIMILAR_LINES, ui->IDC_MATCH_SIMILAR_LINES->isChecked());

}

/**
 * @brief Sets options to defaults
 */
void QPropCompare::OnDefaults()
{
	// ToDo: Handle/Read Default Values
	/*m_nIgnoreWhite = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_IGNORE_WHITESPACE);
	m_bIgnoreEol = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_IGNORE_EOL);
	m_bIgnoreCodepage = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_IGNORE_CODEPAGE);
	m_bIgnoreBlankLines = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_IGNORE_BLANKLINES);
	m_bFilterCommentsLines = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_FILTER_COMMENTLINES);
	m_bIgnoreCase = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_IGNORE_CASE);
	m_bMovedBlocks = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_MOVED_BLOCKS);
	m_bMatchSimilarLines = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_MATCH_SIMILAR_LINES);
	UpdateData(FALSE);*/
}
