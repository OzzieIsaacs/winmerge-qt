/**
 * @file  PropBackups.cpp
 *
 * @brief Implementation of PropBackups propertysheet
 */

#include "PropBackups.h"
#include "ui_QPropBackups.h"
#include <QFileDialog>
#include "OptionsDef.h"
#include "paths.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

QPropBackups::QPropBackups(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropBackups)
{
	ui->setupUi(this);
	connect(ui->IDC_BACKUP_BROWSE, SIGNAL(clicked()), this, SLOT(OnBnClickedBackupBrowse()));
	
	m_options = options;
}
QPropBackups::~QPropBackups()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 */
void QPropBackups::ReadOptions()
{
	ui->IDC_BACKUP_FOLDER->setText(m_options->value(OPT_BACKUP_GLOBALFOLDER).toString());
	ui->IDC_BACKUP_FOLDERCMP->setChecked(m_options->value(OPT_BACKUP_FOLDERCMP).toBool());
	ui->IDC_BACKUP_FILECMP->setChecked(m_options->value(OPT_BACKUP_FILECMP).toBool());
	if (m_options->value(OPT_BACKUP_LOCATION).toBool()){
		ui->IDC_BACKUP_ORIGFOLD->setChecked(true);
	} else {
		ui->IDC_BACKUP_GLOBALFOLD->setChecked(true);
	}
	ui->IDC_BACKUP_APPEND_BAK->setChecked(m_options->value(OPT_BACKUP_ADD_BAK).toBool());
	ui->IDC_BACKUP_APPEND_TIME->setChecked(m_options->value(OPT_BACKUP_ADD_TIME).toBool());


}


/**
 * @brief Writes options values from UI to storage.
 */
void QPropBackups::WriteOptions()
{
	QString sGlobalFolder = ui->IDC_BACKUP_FOLDER->toPlainText().trimmed();
	if (sGlobalFolder.length() > 3)
		sGlobalFolder = paths::AddTrailingSlash(sGlobalFolder);
	m_options->setValue(OPT_BACKUP_GLOBALFOLDER, sGlobalFolder);

	m_options->setValue(OPT_BACKUP_FOLDERCMP, ui->IDC_BACKUP_FOLDERCMP->isChecked());
	m_options->setValue(OPT_BACKUP_FILECMP, ui->IDC_BACKUP_FILECMP->isChecked());
	m_options->setValue(OPT_BACKUP_LOCATION, ui->IDC_BACKUP_ORIGFOLD->isChecked());
	m_options->setValue(OPT_BACKUP_ADD_BAK, ui->IDC_BACKUP_APPEND_BAK->isChecked());
	m_options->setValue(OPT_BACKUP_ADD_TIME, ui->IDC_BACKUP_APPEND_TIME->isChecked());

}

/**
 * @brief Called when user selects Browse-button.
 */
void QPropBackups::OnBnClickedBackupBrowse()
{
	QString path;
	path = QFileDialog::getExistingDirectory(this, "", ui->IDC_BACKUP_FOLDER->toPlainText());
	if(path != ""){
		ui->IDC_BACKUP_FOLDER->setText(path);
	}
}

