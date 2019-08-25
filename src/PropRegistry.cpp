#include "PropRegistry.h"
#include "ui_QPropRegistry.h"
#include "OptionsDef.h"
#include <QFileDialog>



// registry values
/*static LPCTSTR f_RegValueEnabled = _T("ContextMenuEnabled");
static LPCTSTR f_RegValuePath = _T("Executable");*/


QPropRegistry::QPropRegistry(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropRegistry)
{
	ui->setupUi(this);
	connect(ui->IDC_EXT_EDITOR_BROWSE, SIGNAL(clicked()), this, SLOT(OnBrowseEditor()));
	connect(ui->IDC_FILTER_USER_BROWSE, SIGNAL(clicked()), this, SLOT(OnBrowseFilterPath()));
	connect(ui->IDC_TMPFOLDER_BROWSE, SIGNAL(clicked()), this, SLOT(OnBrowseTmpFolder()));

	m_options = options;
	/*m_tooltips.Create(this);
	m_tooltips.SetMaxTipWidth(600);
	m_tooltips.AddTool(GetDlgItem(IDC_EXT_EDITOR_PATH),
					   _("You can specify the following parameters to the path:\n"
						 "$file: Path name of the current file\n"
						 "$linenum: Line number of the current cursor position").c_str());*/

}
QPropRegistry::~QPropRegistry()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 */
void QPropRegistry::ReadOptions()
{
	ui->IDC_EXT_EDITOR_PATH->setText(m_options->value(OPT_EXT_EDITOR_CMD).toString());
	ui->IDC_USE_RECYCLE_BIN->setChecked(m_options->value(OPT_USE_RECYCLE_BIN).toBool());
	ui->IDC_FILTER_USER_PATH->setText(m_options->value(OPT_FILTER_USERPATH).toString());
	if (m_options->value(OPT_USE_SYSTEM_TEMP_PATH).toBool()){
		ui->IDC_TMPFOLDER_SYSTEM->setChecked(1);
	} else {
		ui->IDC_TMPFOLDER_CUSTOM->setChecked(1);
	}

	ui->IDC_TMPFOLDER_NAME->setText(m_options->value(OPT_CUSTOM_TEMP_PATH).toString());


	/*m_strEditorPath = GetOptionsMgr()->GetString(OPT_EXT_EDITOR_CMD);
	m_bUseRecycleBin = GetOptionsMgr()->GetBool(OPT_USE_RECYCLE_BIN);
	m_strUserFilterPath = GetOptionsMgr()->GetString(OPT_FILTER_USERPATH);
	m_tempFolderType = GetOptionsMgr()->GetBool(OPT_USE_SYSTEM_TEMP_PATH) ? 0 : 1;
	m_tempFolder = GetOptionsMgr()->GetString(OPT_CUSTOM_TEMP_PATH);*/
}

/**
 * @brief Writes options values from UI to storage.
 */
void QPropRegistry::WriteOptions()
{
	m_options->setValue(OPT_USE_RECYCLE_BIN, ui->IDC_USE_RECYCLE_BIN->isChecked());
	// GetOptionsMgr()->SaveOption(OPT_USE_RECYCLE_BIN, m_bUseRecycleBin);

	QString sExtEditor = ui->IDC_EXT_EDITOR_PATH->toPlainText().trimmed(); // strutils::trim_ws(m_strEditorPath);
	if (sExtEditor.isEmpty())
		sExtEditor = "";// ToDo: Implement defaultValue storage class
		// GetOptionsMgr()->GetDefault<String>(OPT_EXT_EDITOR_CMD);
	m_options->setValue(OPT_EXT_EDITOR_CMD, sExtEditor);
	// GetOptionsMgr()->SaveOption(OPT_EXT_EDITOR_CMD, sExtEditor);

	// String sFilterPath = strutils::trim_ws(m_strUserFilterPath);
	QString sFilterPath = ui->IDC_FILTER_USER_PATH->toPlainText().trimmed();
	m_options->setValue(OPT_FILTER_USERPATH, sFilterPath);
	// GetOptionsMgr()->SaveOption(OPT_FILTER_USERPATH, sFilterPath);

	//bool useSysTemp = ui->IDC_TMPFOLDER_SYSTEM->isChecked() == 0;
	m_options->setValue(OPT_USE_SYSTEM_TEMP_PATH, ui->IDC_TMPFOLDER_SYSTEM->isChecked());
	// GetOptionsMgr()->SaveOption(OPT_USE_SYSTEM_TEMP_PATH, useSysTemp);

	// String tempFolder = strutils::trim_ws(m_tempFolder);
	QString tempFolder = ui->IDC_TMPFOLDER_NAME->toPlainText().trimmed();
	m_options->setValue(OPT_CUSTOM_TEMP_PATH, tempFolder);
	// GetOptionsMgr()->SaveOption(OPT_CUSTOM_TEMP_PATH, tempFolder);
}

/// Open file browse dialog to locate editor
void QPropRegistry::OnBrowseEditor()
{
	QString path;
	path = QFileDialog::getOpenFileName(this, "", ui->IDC_EXT_EDITOR_PATH->toPlainText(),
								 "Programs (*.exe *.bat *.cmd) ;; All Files (*.*)");
	if(path != ""){
		ui->IDC_EXT_EDITOR_PATH->setText(path);
	}
	/*if (SelectFile(GetSafeHwnd(), path, true, m_strEditorPath.c_str(), _T(""), _("Programs|*.exe;*.bat;*.cmd|All Files (*.*)|*.*||")))
	{
		SetDlgItemText(IDC_EXT_EDITOR_PATH, path);
	}*/
}

/// Open Folder selection dialog for user to select filter folder.
void QPropRegistry::OnBrowseFilterPath()
{
	QString path;
	path = QFileDialog::getExistingDirectory(this, "Open", ui->IDC_FILTER_USER_PATH->toPlainText());
	if(path != ""){
		ui->IDC_FILTER_USER_PATH->setText(path);
	}

	/*if (SelectFolder(path, m_strUserFilterPath.c_str(), _("Open"), GetSafeHwnd()))
	{
		SetDlgItemText(IDC_FILTER_USER_PATH, path);
	}*/
}

/// Select temporary files folder.
void QPropRegistry::OnBrowseTmpFolder()
{
	QString path;
	path = QFileDialog::getExistingDirectory(this, "", ui->IDC_TMPFOLDER_NAME->toPlainText());
	if(path != ""){
		ui->IDC_TMPFOLDER_NAME->setText(path);
	}
	/*if (SelectFolder(path, m_tempFolder.c_str(), _T(""), GetSafeHwnd()))
	{
		SetDlgItemText(IDC_TMPFOLDER_NAME, path);
	}*/
}

/*BOOL QPropRegistry::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN ||
		pMsg->message == WM_LBUTTONUP ||
		pMsg->message == WM_MOUSEMOVE)
	{
		m_tooltips.RelayEvent(pMsg);
	}

	return OptionsPanel::PreTranslateMessage(pMsg);
}*/
