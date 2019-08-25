/**
 * @file  PropArchive.cpp
 *
 * @brief Implementation of PropArchive propertysheet
 */

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

#include "PropArchive.h"
#include "ui_QPropArchive.h"
#include "OptionsDef.h"

QPropArchive::QPropArchive(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropArchive)
{
	ui->setupUi(this);
	connect(ui->IDC_ARCHIVE_ENABLE, SIGNAL(clicked()), this, SLOT(OnEnableClicked()));
	m_options = options;
}
QPropArchive::~QPropArchive()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 */
void QPropArchive::ReadOptions()
{
	ui->IDC_ARCHIVE_ENABLE->setChecked(m_options->value(OPT_ARCHIVE_ENABLE).toBool());

	//int enable = GetOptionsMgr()->GetInt(OPT_ARCHIVE_ENABLE);
	// m_bEnableSupport = enable > 0;
	ui->IDC_ARCHIVE_DETECTTYPE->setChecked(m_options->value(OPT_ARCHIVE_PROBETYPE).toBool());
	//m_bProbeType = GetOptionsMgr()->GetBool(OPT_ARCHIVE_PROBETYPE);
	UpdateControls();
}

/**
 * @brief Writes options values from UI to storage.
 */
void QPropArchive::WriteOptions()
{
	m_options->setValue(OPT_ARCHIVE_ENABLE, ui->IDC_ARCHIVE_ENABLE->isChecked());
	m_options->setValue(OPT_ARCHIVE_PROBETYPE, ui->IDC_ARCHIVE_DETECTTYPE->isChecked());
	//GetOptionsMgr()->SaveOption(OPT_ARCHIVE_ENABLE, (int)(m_bEnableSupport ? 1 : 0));
	//GetOptionsMgr()->SaveOption(OPT_ARCHIVE_PROBETYPE, m_bProbeType);
}

/**
 * @brief Called when archive support is enabled or disabled.
 */
void QPropArchive::OnEnableClicked()
{
	UpdateControls();
}

/**
 * @brief Called Updates controls enabled/disables state.
 */
void QPropArchive::UpdateControls()
{
	ui->IDC_ARCHIVE_DETECTTYPE->setEnabled(ui->IDC_ARCHIVE_ENABLE->isChecked());
	// EnableDlgItem(IDC_ARCHIVE_DETECTTYPE, IsDlgButtonChecked(IDC_ARCHIVE_ENABLE) == 1);
}
