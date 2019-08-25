/**
 * @file  PropCompareFolder.cpp
 *
 * @brief Implementation of PropCompareFolder propertysheet
 */

#include "PropCompareFolder.h"
#include "ui_QPropCompareFolder.h"
#include "OptionsDef.h"



static const int Mega = 1024 * 1024;


QPropCompareFolder::QPropCompareFolder(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropCompareFolder)
{
	ui->setupUi(this);

	ui->IDC_COMPAREMETHODCOMBO->addItem(tr("Full Contents"));
	ui->IDC_COMPAREMETHODCOMBO->addItem(tr("Quick Contents"));
	ui->IDC_COMPAREMETHODCOMBO->addItem(tr("Binary Contents"));
	ui->IDC_COMPAREMETHODCOMBO->addItem(tr("Modified Date"));
	ui->IDC_COMPAREMETHODCOMBO->addItem(tr("Modified Date and Size"));
	ui->IDC_COMPAREMETHODCOMBO->addItem(tr("Size"));

	connect(ui->IDC_COMPAREFOLDER_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));
	connect(ui->IDC_COMPAREMETHODCOMBO, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnCbnSelchangeComparemethodcombo(const QString&)));
	connect(ui->IDC_RECURS_CHECK, SIGNAL(clicked()), this, SLOT(OnBnClickedRecursCheck()));

	m_options = options;
}
QPropCompareFolder::~QPropCompareFolder()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void QPropCompareFolder::ReadOptions() {
	ui->IDC_COMPAREMETHODCOMBO->setCurrentIndex(m_options->value(OPT_CMP_METHOD).toInt());

	ui->IDC_COMPARE_STOPFIRST->setChecked(m_options->value(OPT_CMP_STOP_AFTER_FIRST).toBool());
	ui->IDC_IGNORE_SMALLTIMEDIFF->setChecked(m_options->value(OPT_IGNORE_SMALL_FILETIME).toBool());
	ui->IDC_COMPARE_WALKSUBDIRS->setChecked(m_options->value(OPT_CMP_WALK_UNIQUE_DIRS).toBool());
	ui->IDC_RECURS_CHECK->setChecked(m_options->value(OPT_CMP_INCLUDE_SUBDIRS).toBool());
	ui->IDC_EXPAND_SUBDIRS->setChecked(m_options->value(OPT_DIRVIEW_EXPAND_SUBDIRS).toBool());
	ui->IDC_IGNORE_REPARSEPOINTS->setChecked(m_options->value(OPT_CMP_IGNORE_REPARSE_POINTS).toBool());
	ui->IDC_COMPARE_QUICKC_LIMIT->setText(QString::number(m_options->value(OPT_CMP_QUICK_LIMIT).toInt()/Mega));
	ui->IDC_COMPARE_THREAD_COUNT->setText(m_options->value(OPT_CMP_COMPARE_THREADS).toString());
}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void QPropCompareFolder::WriteOptions()
{
	m_options->setValue(OPT_CMP_METHOD, ui->IDC_COMPAREMETHODCOMBO->currentIndex());
	m_options->setValue(OPT_CMP_STOP_AFTER_FIRST, ui->IDC_COMPARE_STOPFIRST->isChecked());
	m_options->setValue(OPT_IGNORE_SMALL_FILETIME, ui->IDC_IGNORE_SMALLTIMEDIFF->isChecked());
	m_options->setValue(OPT_CMP_WALK_UNIQUE_DIRS, ui->IDC_COMPARE_WALKSUBDIRS->isChecked());
	m_options->setValue(OPT_CMP_INCLUDE_SUBDIRS, ui->IDC_RECURS_CHECK->isChecked());
	m_options->setValue(OPT_DIRVIEW_EXPAND_SUBDIRS, ui->IDC_EXPAND_SUBDIRS->isChecked());
	m_options->setValue(OPT_CMP_IGNORE_REPARSE_POINTS, ui->IDC_IGNORE_REPARSEPOINTS->isChecked());

	int nQuickCompareLimit = ui->IDC_COMPARE_QUICKC_LIMIT->toPlainText().toInt();
	if (nQuickCompareLimit > 2000)
		nQuickCompareLimit = 2000;
	m_options->setValue(OPT_CMP_QUICK_LIMIT, nQuickCompareLimit * Mega);

	m_options->setValue(OPT_CMP_COMPARE_THREADS, ui->IDC_COMPARE_THREAD_COUNT->toPlainText().toInt());
}


/**
 * @brief Sets options to defaults
 */
void QPropCompareFolder::OnDefaults()
{
	/*m_compareMethod = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_METHOD);
	m_bStopAfterFirst = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_STOP_AFTER_FIRST);
	m_bIncludeUniqFolders = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_WALK_UNIQUE_DIRS);
	m_bIncludeSubdirs = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_INCLUDE_SUBDIRS);
	m_bExpandSubdirs = GetOptionsMgr()->GetDefault<bool>(OPT_DIRVIEW_EXPAND_SUBDIRS);
	m_bIgnoreReparsePoints = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_IGNORE_REPARSE_POINTS);
	m_nQuickCompareLimit = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_QUICK_LIMIT) / Mega;
	m_nCompareThreads = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_COMPARE_THREADS);
	UpdateData(FALSE);*/
}

/**
 * @brief Called when compare method dropdown selection is changed.
 * Enables / disables "Stop compare after first difference" checkbox.
 * That checkbox is valid only for quick contents compare method.
 */
void QPropCompareFolder::OnCbnSelchangeComparemethodcombo(const QString&)
{
	UpdateControls();
}

void QPropCompareFolder::OnBnClickedRecursCheck()
{
	UpdateControls();
}

void QPropCompareFolder::UpdateControls()
{
	int i = ui->IDC_COMPAREMETHODCOMBO->currentIndex() <= 1 ? 1 : 0;
	ui->IDC_COMPARE_STOPFIRST->setEnabled(ui->IDC_COMPAREMETHODCOMBO->currentIndex() == 1);
	ui->IDC_EXPAND_SUBDIRS->setEnabled(ui->IDC_RECURS_CHECK->isChecked());
	ui->IDC_COMPARE_THREAD_COUNT->setDisabled(ui->IDC_COMPAREMETHODCOMBO->currentIndex() <= 1 ? 0 : 1);
}
