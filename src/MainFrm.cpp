#include "MainFrm.h"
#include "ui_mainwindow.h"
#include "AboutDlg.h"
#include "IDD_COMPARE_STATISTICS.h"
#include "IDD_COMPARE_STATISTICS3.h"
#include "IDD_CONFIRM_COPY.h"
#include "IDD_DIR_FILTER.h"
#include "IDD_DIRCMP_REPORT.h"
#include "IDD_DIRCOLS.h"
#include "IDD_DIRCOMP_PROGRESS.h"
#include "IDD_EDIT_FIND.h"
#include "IDD_EDIT_MARKER.h"
#include "IDD_EDIT_REPLACE.h"
#include "IDD_EDITOR_HEADERBAR.h"
#include "IDD_ENCODINGERROR.h"
#include "IDD_FILEFILTERS.h"
#include "IDD_GENERATE_PATCH.h"
#include "IDD_LOAD_SAVE_CODEPAGE.h"
#include "IDD_OPEN.h"
#include "IDD_PLUGINS_LIST.h"
#include "PreferencesDlg.h"
#include "IDD_SAVECLOSING.h"
#include "IDD_SELECTUNPACKER.h"
#include "IDD_SHARED_FILTER.h"
#include "IDD_TEST_FILTER.h"
#include "IDD_WMGOTO.h"
#include <QFile>
#include <QDir>
#include <QSettings>
#include "Constants.h"
#include "Common/tchar.h"
#include "OptionsInit.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//instanc = this;

	connect(ui->mActionAboutWinMerge, SIGNAL(triggered()), this, SLOT(AboutWinMerge()));
	connect(ui->ID_HELP_GNULICENSE, SIGNAL(triggered()), this, SLOT(OnHelpGnulicense()));
	connect(ui->ID_HELP_RELEASENOTES, SIGNAL(triggered()), this, SLOT(OnHelpReleasenotes()));
	connect(ui->ID_HELP_TRANSLATIONS, SIGNAL(triggered()), this, SLOT(OnHelpTranslations()));
	connect(ui->mActionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui->ID_FILE_OPENPROJECT, SIGNAL(triggered()), this, SLOT(OnFileOpenProject()));
	connect(ui->ID_OPTIONS, SIGNAL(triggered()), this, SLOT(OnOptions()));


	// populate the items of the list
	ui->listWidget->addItem("IDD_COMPARE_STATISTICS");
	ui->listWidget->addItem("IDD_COMPARE_STATISTICS3");
	ui->listWidget->addItem("IDD_CONFIRM_COPY");
	ui->listWidget->addItem("IDD_DIR_FILTER");
	ui->listWidget->addItem("IDD_DIRCMP_REPORT");
	ui->listWidget->addItem("IDD_DIRCOLS");
	ui->listWidget->addItem("IDD_DIRCOMP_PROGRESS");
	ui->listWidget->addItem("IDD_EDIT_FIND");
	ui->listWidget->addItem("IDD_EDIT_MARKER");
	ui->listWidget->addItem("IDD_EDIT_REPLACE");
	ui->listWidget->addItem("IDD_EDITOR_HEADERBAR");
	ui->listWidget->addItem("IDD_ENCODINGERROR");
	ui->listWidget->addItem("IDD_FILEFILTERS");
	ui->listWidget->addItem("IDD_GENERATE_PATCH");
	ui->listWidget->addItem("IDD_LOAD_SAVE_CODEPAGE");
	ui->listWidget->addItem("IDD_OPEN");
	ui->listWidget->addItem("IDD_PLUGINS_LIST");
	ui->listWidget->addItem("IDD_PROP_ARCHIVE");
	ui->listWidget->addItem("IDD_SAVECLOSING");
	ui->listWidget->addItem("IDD_SELECTUNPACKER");
	ui->listWidget->addItem("IDD_SHARED_FILTER");
	ui->listWidget->addItem("IDD_TEST_FILTER");
	ui->listWidget->addItem("IDD_WMGOTO");
	//m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/demosettings.ini";
	//QSettings settings(m_sSettingsFile, QSettings::NativeFormat);
	Options::Init();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{

	// Get the pointer to the currently selected item.
	int item = ui->listWidget->currentRow();
	switch(item)
	{
		case 0:
		{	static IDD_COMPARE_STATISTICS dIDD_COMPARE_STATISTICS;
			dIDD_COMPARE_STATISTICS.show();
			break;
		}
		case 1:
		{	static IDD_COMPARE_STATISTICS3 dIDD_COMPARE_STATISTICS3;
			dIDD_COMPARE_STATISTICS3.show();
			break;
		}
		case 2:
		{	static IDD_CONFIRM_COPY dIDD_CONFIRM_COPY;
			dIDD_CONFIRM_COPY.show();
			break;
		}
		case 3:
		{	static IDD_DIR_FILTER dIDD_DIR_FILTER;
			dIDD_DIR_FILTER.show();
			break;
		}
		case 4:
		{	static IDD_DIRCMP_REPORT dIDD_DIRCMP_REPORT;
			dIDD_DIRCMP_REPORT.show();
			break;
		}
		case 5:
		{	static IDD_DIRCOLS dIDD_DIRCOLS;
			dIDD_DIRCOLS.show();
			break;
		}
		case 6:
		{	static IDD_DIRCOMP_PROGRESS dIDD_DIRCOMP_PROGRESS;
			dIDD_DIRCOMP_PROGRESS.show();
			break;
		}
		case 7:
		{	static IDD_EDIT_FIND dIDD_EDIT_FIND;
			dIDD_EDIT_FIND.show();
			break;
		}
		case 8:
		{	static IDD_EDIT_MARKER dIDD_EDIT_MARKER;
			dIDD_EDIT_MARKER.show();
			break;
		}
		case 9:
		{	static IDD_EDIT_REPLACE dIDD_EDIT_REPLACE;
			dIDD_EDIT_REPLACE.show();
			break;
		}
		case 10:
		{	static IDD_EDITOR_HEADERBAR dIDD_EDITOR_HEADERBAR;
			dIDD_EDITOR_HEADERBAR.show();
			break;
		}
		case 11:
		{	static IDD_ENCODINGERROR dIDD_ENCODINGERROR;
			dIDD_ENCODINGERROR.show();
			break;
		}
		case 12:
		{	static IDD_FILEFILTERS dIDD_FILEFILTERS;
			dIDD_FILEFILTERS.show();
			break;
		}
		case 13:
		{	static IDD_GENERATE_PATCH dIDD_GENERATE_PATCH;
			dIDD_GENERATE_PATCH.show();
			break;
		}
		case 14:
		{	static IDD_LOAD_SAVE_CODEPAGE dIDD_LOAD_SAVE_CODEPAGE;
			dIDD_LOAD_SAVE_CODEPAGE.show();
			break;
		}
		case 15:
		{	static IDD_OPEN dIDD_OPEN;
			dIDD_OPEN.show();
			break;
		}
		case 16:
		{	static IDD_PLUGINS_LIST dIDD_PLUGINS_LIST;
			dIDD_PLUGINS_LIST.show();
			break;
		}
		case 17:
		{	static IDD_SAVECLOSING dIDD_SAVECLOSING;
			dIDD_SAVECLOSING.show();
			break;
		}
		case 18:
		{	static IDD_SELECTUNPACKER dIDD_SELECTUNPACKER;
			dIDD_SELECTUNPACKER.show();
			break;
		}
		case 19:
		{	static IDD_SHARED_FILTER dIDD_SHARED_FILTER;
			dIDD_SHARED_FILTER.show();
			break;
		}
		case 20:
		{	static IDD_TEST_FILTER dIDD_TEST_FILTER;
			dIDD_TEST_FILTER.show();
			break;
		}
		case 21:
		{	static IDD_WMGOTO dIDD_WMGOTO;
			dIDD_WMGOTO.show();
			break;
		}
	}

}
void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    on_pushButton_clicked();
}

/**
 * @brief Show GNU licence information in notepad (local file) or in Web Browser
 */
void MainWindow::OnHelpGnulicense()
{
	QFile spath(QCoreApplication::applicationDirPath() + QDir::separator() + LicenseFile);
	this->OpenFileOrUrl(spath, LicenceUrl);
}

/**
 * @brief Shows the release notes for user.
 * This function opens release notes HTML document into browser.
 */
void MainWindow::OnHelpReleasenotes()
{
	QFile spath(QCoreApplication::applicationDirPath() + QDir::separator() + RelNotes);
	this->OpenFileOrUrl(spath, nullptr);
}

/**
 * @brief Shows the translations page.
 * This function opens translations page URL into browser.
 */
void MainWindow::OnHelpTranslations()
{
	QFile dummyFile(nullptr);
	this->OpenFileOrUrl(dummyFile, TranslationsUrl);
}


void MainWindow::AboutWinMerge()
{
	QAboutDlg dlg(this);
	dlg.exec();
}

/**
 * @brief Open project-file.
 */
void MainWindow::OnFileOpenProject()
{
	return;
}

/**
 * @brief Opens Options-dialog and saves changed options
 */
void MainWindow::OnOptions() {
	// Using singleton shared syntax colors
	// IDD_PREFERENCES dlg(GetOptionsMgr(), theApp.GetMainSyntaxColors());
	QPreferencesDlg dlg(this);
	dlg.exec();
}

void MainWindow::OpenFileOrUrl(QFile& file, const TCHAR* szUrl)
{
#ifdef __linux__
	if (file.exists())
		system(("xdg-open " + file.fileName().toStdString()).c_str());
	else
		system((QString("xdg-open ") + szUrl).toStdString().c_str());
#else
	if (paths::DoesPathExist(szFile) == paths::IS_EXISTING_FILE)
		ShellExecute(nullptr, _T("open"), _T("notepad.exe"), szFile, nullptr, SW_SHOWNORMAL);
	else
		ShellExecute(nullptr, _T("open"), szUrl, nullptr, nullptr, SW_SHOWNORMAL);
#endif
}
