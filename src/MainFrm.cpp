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
#include "paths.h"
#include "MainMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/** @brief Location for command line help to open. */
static const QString CommandLineHelpLocation("::/htmlhelp/Command_line.html");

/** @brief Backup file extension. */
static const QString BACKUP_FILE_EXT("bak");


MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->mMenubar = new QMainMenu(this);

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


	// Parse command-line arguments.
	/*MergeCmdLineInfo cmdInfo(GetCommandLine());
	if (cmdInfo.m_bNoPrefs)
		m_pOptions->SetSerializing(false); // Turn off serializing to registry.
	*/
	Options::Init();
	/*
	Options::Init(m_pOptions.get()); // Implementation in OptionsInit.cpp
	ApplyCommandLineConfigOptions(cmdInfo);
	if (cmdInfo.m_sErrorMessages.size() > 0)
	{
		if (AttachConsole(ATTACH_PARENT_PROCESS))
		{
			DWORD dwWritten;
			for (auto& msg : cmdInfo.m_sErrorMessages)
			{
				String line = _T("WinMerge: ") + msg + _T("\n");
				WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), line.c_str(), static_cast<DWORD>(line.length()), &dwWritten, nullptr);
			}
			FreeConsole();
		}
	}

	// Initialize temp folder
	SetupTempPath();

	// If paths were given to commandline we consider this being an invoke from
	// commandline (from other application, shellextension etc).
	bool bCommandLineInvoke = cmdInfo.m_Files.GetSize() > 0;

	// WinMerge registry settings are stored under HKEY_CURRENT_USER/Software/Thingamahoochie
	// This is the name of the company of the original author (Dean Grimm)
	SetRegistryKey(_T("Thingamahoochie"));

	bool bSingleInstance = GetOptionsMgr()->GetBool(OPT_SINGLE_INSTANCE) ||
						   (true == cmdInfo.m_bSingleInstance);

	// Create exclusion mutex name
	TCHAR szDesktopName[MAX_PATH] = _T("Win9xDesktop");
	DWORD dwLengthNeeded;
	GetUserObjectInformation(GetThreadDesktop(GetCurrentThreadId()), UOI_NAME,
							 szDesktopName, sizeof(szDesktopName), &dwLengthNeeded);
	TCHAR szMutexName[MAX_PATH + 40];
	// Combine window class name and desktop name to form a unique mutex name.
	// As the window class name is decorated to distinguish between ANSI and
	// UNICODE build, so will be the mutex name.
	wsprintf(szMutexName, _T("%s-%s"), CMainFrame::szClassName, szDesktopName);
	HANDLE hMutex = CreateMutex(nullptr, FALSE, szMutexName);
	if (hMutex != nullptr)
		WaitForSingleObject(hMutex, INFINITE);
	if (bSingleInstance && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// Activate previous instance and send commandline to it
		HWND hWnd = FindWindow(CMainFrame::szClassName, nullptr);
		if (hWnd != nullptr)
		{
			if (IsIconic(hWnd))
				ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(GetLastActivePopup(hWnd));
			LPTSTR cmdLine = GetCommandLine();
			COPYDATASTRUCT data = { 0, (lstrlen(cmdLine) + 1) * sizeof(TCHAR), cmdLine};
			if (::SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&data))
			{
				ReleaseMutex(hMutex);
				CloseHandle(hMutex);
				return FALSE;
			}
		}
	}

	LoadStdProfileSettings(GetOptionsMgr()->GetInt(OPT_MRU_MAX));  // Load standard INI file options (including MRU)

	InitializeFileFilters();

	// Read last used filter from registry
	// If filter fails to set, reset to default
	const String filterString = m_pOptions->GetString(OPT_FILEFILTER_CURRENT);
	bool bFilterSet = m_pGlobalFileFilter->SetFilter(filterString);
	if (!bFilterSet)
	{
		String filter = m_pGlobalFileFilter->GetFilterNameOrMask();
		m_pOptions->SaveOption(OPT_FILEFILTER_CURRENT, filter);
	}

	charsets_init();
	UpdateCodepageModule();

	FileTransform::g_UnpackerMode = static_cast<PLUGIN_MODE>(GetOptionsMgr()->GetInt(OPT_PLUGINS_UNPACKER_MODE));
	FileTransform::g_PredifferMode = static_cast<PLUGIN_MODE>(GetOptionsMgr()->GetInt(OPT_PLUGINS_PREDIFFER_MODE));

	NONCLIENTMETRICS ncm = { sizeof NONCLIENTMETRICS };
	if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof NONCLIENTMETRICS, &ncm, 0))
	{
		const int lfHeight = -MulDiv(9, CClientDC(CWnd::GetDesktopWindow()).GetDeviceCaps(LOGPIXELSY), 72);
		if (abs(ncm.lfMenuFont.lfHeight) > abs(lfHeight))
			ncm.lfMenuFont.lfHeight = lfHeight;
		if (wcscmp(ncm.lfMenuFont.lfFaceName, L"Meiryo") == 0 || wcscmp(ncm.lfMenuFont.lfFaceName, L"\U000030e1\U000030a4\U000030ea\U000030aa"/* "Meiryo" in Japanese *///) == 0)
	/*		wcscpy_s(ncm.lfMenuFont.lfFaceName, L"Meiryo UI");
		m_fontGUI.CreateFontIndirect(&ncm.lfMenuFont);
	}

	if (m_pSyntaxColors != nullptr)
		Options::SyntaxColors::Load(GetOptionsMgr(), m_pSyntaxColors.get());

	if (m_pMarkers != nullptr)
		m_pMarkers->LoadFromRegistry();

	if (m_pLineFilters != nullptr)
		m_pLineFilters->Initialize(GetOptionsMgr());

	// If there are no filters loaded, and there is filter string in previous
	// option string, import old filters to new place.
	if (m_pLineFilters->GetCount() == 0)
	{
		String oldFilter = theApp.GetProfileString(_T("Settings"), _T("RegExps"));
		if (!oldFilter.empty())
			m_pLineFilters->Import(oldFilter);
	}

	// Check if filter folder is set, and create it if not
	String pathMyFolders = GetOptionsMgr()->GetString(OPT_FILTER_USERPATH);
	if (pathMyFolders.empty())
	{
		// No filter path, set it to default and make sure it exists.
		pathMyFolders = GetOptionsMgr()->GetDefault<String>(OPT_FILTER_USERPATH);
		GetOptionsMgr()->SaveOption(OPT_FILTER_USERPATH, pathMyFolders);
		theApp.m_pGlobalFileFilter->SetUserFilterPath(pathMyFolders);
	}
	if (!paths::CreateIfNeeded(pathMyFolders))
	{
		// Failed to create a folder, check it didn't already
		// exist.
		DWORD errCode = GetLastError();
		if (errCode != ERROR_ALREADY_EXISTS)
		{
			// Failed to create a folder for filters, fallback to
			// "My Documents"-folder. It is not worth the trouble to
			// bother user about this or user more clever solutions.
			GetOptionsMgr()->SaveOption(OPT_FILTER_USERPATH, env::GetMyDocuments());
		}
	}

	strdiff::Init(); // String diff init
	strdiff::SetBreakChars(GetOptionsMgr()->GetString(OPT_BREAK_SEPARATORS).c_str());

	m_bMergingMode = GetOptionsMgr()->GetBool(OPT_MERGE_MODE);

	// Initialize i18n (multiple language) support

	m_pLangDlg->InitializeLanguage((WORD)GetOptionsMgr()->GetInt(OPT_SELECTED_LANGUAGE));

	m_mainThreadScripts = new CAssureScriptsForThread;

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	// Open view
	m_pOpenTemplate = new CMultiDocTemplate(
			IDR_MAINFRAME,
			RUNTIME_CLASS(COpenDoc),
			RUNTIME_CLASS(COpenFrame), // custom MDI child frame
			RUNTIME_CLASS(COpenView));
	AddDocTemplate(m_pOpenTemplate);

	// Merge Edit view
	m_pDiffTemplate = new CMultiDocTemplate(
			IDR_MERGEDOCTYPE,
			RUNTIME_CLASS(CMergeDoc),
			RUNTIME_CLASS(CChildFrame), // custom MDI child frame
			RUNTIME_CLASS(CMergeEditSplitterView));
	AddDocTemplate(m_pDiffTemplate);

	// Merge Edit view
	m_pHexMergeTemplate = new CMultiDocTemplate(
			IDR_MERGEDOCTYPE,
			RUNTIME_CLASS(CHexMergeDoc),
			RUNTIME_CLASS(CHexMergeFrame), // custom MDI child frame
			RUNTIME_CLASS(CHexMergeView));
	AddDocTemplate(m_pHexMergeTemplate);

	// Directory view
	m_pDirTemplate = new CMultiDocTemplate(
			IDR_DIRDOCTYPE,
			RUNTIME_CLASS(CDirDoc),
			RUNTIME_CLASS(CDirFrame), // custom MDI child frame
			RUNTIME_CLASS(CDirView));
	AddDocTemplate(m_pDirTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		if (hMutex != nullptr)
		{
			ReleaseMutex(hMutex);
			CloseHandle(hMutex);
		}
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// Init menus -- hMenuDefault is for MainFrame
	pMainFrame->m_hMenuDefault = pMainFrame->NewDefaultMenu();

	// Set the menu
	// Note : for Windows98 compatibility, use FromHandle and not Attach/Detach
	CMenu * pNewMenu = CMenu::FromHandle(pMainFrame->m_hMenuDefault);
	pMainFrame->MDISetMenu(pNewMenu, nullptr);

	// The main window has been initialized, so activate and update it.
	pMainFrame->ActivateFrame(cmdInfo.m_nCmdShow);
	pMainFrame->UpdateWindow();

	// Since this function actually opens paths for compare it must be
	// called after initializing CMainFrame!
	bool bContinue = true;
	if (!ParseArgsAndDoOpen(cmdInfo, pMainFrame) && bCommandLineInvoke)
		bContinue = false;

	if (hMutex != nullptr)
		ReleaseMutex(hMutex);

	// If user wants to cancel the compare, close WinMerge
	if (!bContinue)
	{
		pMainFrame->PostMessage(WM_CLOSE, 0, 0);
	}

#ifdef TEST_WINMERGE
	WinMergeTest::TestAll();
#endif

	return bContinue;*/

}

/**
 * @brief Called when application is about to exit.
 * This functions is called when application is exiting, so this is
 * good place to do cleanups.
 * @return Application's exit value (returned from WinMain()).
 */
MainWindow::~MainWindow()
{
	delete ui;
	/*charsets_cleanup();

	//  Save registry keys if existing WinMerge.reg
	env::SaveRegistryToFile(paths::ConcatPath(env::GetProgPath(), _T("WinMerge.reg")), RegDir);

	// Remove tempfolder
	const String temp = env::GetTemporaryPath();
	ClearTempfolder(temp);

	// Cleanup left over tempfiles from previous instances.
	// Normally this should not neet to do anything - but if for some reason
	// WinMerge did not delete temp files this makes sure they are removed.
	CleanupWMtemp();

	delete m_mainThreadScripts;
	CWinApp::ExitInstance();
	return 0;*/
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

/** @brief Open help from mainframe when user presses F1*/
void MainWindow::OnHelp()
{
	ShowHelp();
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


void MainWindow::OnAppAbout()
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
	// Using singleton shared syntax colors
	/*INT_PTR rv = dlg.DoModal();

	if (rv == IDOK)
	{
		LANGID lang = static_cast<LANGID>(GetOptionsMgr()->GetInt(OPT_SELECTED_LANGUAGE));
		if (lang != theApp.m_pLangDlg->GetLangId())
		{
			theApp.m_pLangDlg->SetLanguage(lang, true);

			// Update status bar inicator texts
			theApp.SetIndicators(m_wndStatusBar, 0, 0);

			// Update the current menu
			ReloadMenu();

			// update the title text of the document
			UpdateDocTitle();

			UpdateResources();
		}

		// Set new temporary path
		theApp.SetupTempPath();

		// Set new filterpath
		String filterPath = GetOptionsMgr()->GetString(OPT_FILTER_USERPATH);
		theApp.m_pGlobalFileFilter->SetUserFilterPath(filterPath);

		theApp.UpdateCodepageModule();

		strdiff::SetBreakChars(GetOptionsMgr()->GetString(OPT_BREAK_SEPARATORS).c_str());

		// make an attempt at rescanning any open diff sessions
		ApplyDiffOptions();

		// Update all dirdoc settings
		for (auto pDirDoc : GetAllDirDocs())
			pDirDoc->RefreshOptions();
		for (auto pOpenDoc : GetAllOpenDocs())
			pOpenDoc->RefreshOptions();
		for (auto pMergeDoc : GetAllHexMergeDocs())
			pMergeDoc->RefreshOptions();
	}*/

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


/**
 * @brief Show Help - this is for opening help from outside mainframe.
 * @param [in] helpLocation Location inside help, if `nullptr` main help is opened.
 */
void MainWindow::ShowHelp() // LPCTSTR helpLocation /*= nullptr*/)
{
	// ToDo: Implement help
	/*String name, ext;
	LANGID LangId = GetLangId();
	paths::SplitFilename(m_pLangDlg->GetFileName(LangId), nullptr, &name, &ext);
	String sPath = paths::ConcatPath(env::GetProgPath(), strutils::format(DocsPath, name.c_str()));
	if (paths::DoesPathExist(sPath) != paths::IS_EXISTING_FILE)
		sPath = paths::ConcatPath(env::GetProgPath(), strutils::format(DocsPath, _T("")));
	if (helpLocation == nullptr)
	{
		if (paths::DoesPathExist(sPath) == paths::IS_EXISTING_FILE)
			::HtmlHelp(nullptr, sPath.c_str(), HH_DISPLAY_TOC, NULL);
		else
			ShellExecute(nullptr, _T("open"), DocsURL, nullptr, nullptr, SW_SHOWNORMAL);
	}
	else
	{
		if (paths::DoesPathExist(sPath) == paths::IS_EXISTING_FILE)
		{
			sPath += helpLocation;
			::HtmlHelp(nullptr, sPath.c_str(), HH_DISPLAY_TOPIC, NULL);
		}
	}*/
}

/**
 * @brief Set flag so that application will broadcast notification at next
 * idle time (via WM_TIMER id=IDLE_TIMER)
 */
void MainWindow::SetNeedIdleTimer()
{
	// m_bNeedIdleTimer = true;
}

bool MainWindow::IsReallyIdle() const
{
	bool idle = true;
	/*POSITION pos = m_pDirTemplate->GetFirstDocPosition();
	while (pos != nullptr)
	{
		CDirDoc *pDirDoc = static_cast<CDirDoc *>(m_pDirTemplate->GetNextDoc(pos));
		if (const CompareStats *pCompareStats = pDirDoc->GetCompareStats())
		{
			if (!pCompareStats->IsCompareDone() || pDirDoc->GetGeneratingReport())
				idle = false;
		}
	}*/
	return idle;
}

bool MainWindow::OnIdle(long int lCount)
{
	/*if (CWinApp::OnIdle(lCount))
		return TRUE;

	// If anyone has requested notification when next idle occurs, send it
	if (m_bNeedIdleTimer)
	{
		m_bNeedIdleTimer = false;
		m_pMainWnd->SendMessageToDescendants(WM_TIMER, IDLE_TIMER, lCount, TRUE, FALSE);
	}

	if (m_bNonInteractive && IsReallyIdle())
		m_pMainWnd->PostMessage(WM_CLOSE, 0, 0);

	static_cast<CRegOptionsMgr *>(GetOptionsMgr())->CloseHandles();

	return FALSE;*/
}

/**
 * @brief Load any known file filters.
 *
 * This function loads filter files from paths we know contain them.
 * @note User's filter location may not be set yet.
 */
void MainWindow::InitializeFileFilters()
{
	/*QString filterPath = GetOptionsMgr()->GetString(OPT_FILTER_USERPATH);

	if (!filterPath.empty())
	{
		m_pGlobalFileFilter->SetUserFilterPath(filterPath);
	}
	m_pGlobalFileFilter->LoadAllFileFilters();*/
}

/*void MainWindow::ApplyCommandLineConfigOptions(MergeCmdLineInfo& cmdInfo)
{
	/*if (cmdInfo.m_bNoPrefs)
		m_pOptions->SetSerializing(false); // Turn off serializing to registry.

	for (const auto& it : cmdInfo.m_Options)
	{
		if (m_pOptions->Set(it.first, it.second) == COption::OPT_NOTFOUND)
		{
			String longname = m_pOptions->ExpandShortName(it.first);
			if (!longname.empty())
			{
				m_pOptions->Set(longname, it.second);
			}
			else
			{
				cmdInfo.m_sErrorMessages.push_back(strutils::format_string1(_T("Invalid key '%1' specified in /config option"), it.first));
			}
		}
	}
}*/

/** @brief Read command line arguments and open files for comparison.
 *
 * The name of the function is a legacy code from the time that this function
 * actually parsed the command line. Today the parsing is done using the
 * MergeCmdLineInfo class.
 * @param [in] cmdInfo Commandline parameters info.
 * @param [in] pMainFrame Pointer to application main frame.
 * @return `true` if we opened the compare, `false` if the compare was canceled.
 */
/*bool MainWindow::ParseArgsAndDoOpen(MergeCmdLineInfo& cmdInfo, CMainFrame* pMainFrame)
{
	/*bool bCompared = false;
	String strDesc[3];
	m_bNonInteractive = cmdInfo.m_bNonInteractive;

	// Set the global file filter.
	if (!cmdInfo.m_sFileFilter.empty())
	{
		m_pGlobalFileFilter->SetFilter(cmdInfo.m_sFileFilter);
	}

	// Set codepage.
	if (cmdInfo.m_nCodepage)
	{
		UpdateDefaultCodepage(2,cmdInfo.m_nCodepage);
	}

	// Unless the user has requested to see WinMerge's usage open files for
	// comparison.
	if (cmdInfo.m_bShowUsage)
	{
		ShowHelp(CommandLineHelpLocation);
	}
	else
	{
		// Set the required information we need from the command line:

		m_bExitIfNoDiff = cmdInfo.m_bExitIfNoDiff;
		m_bEscShutdown = cmdInfo.m_bEscShutdown;

		m_strSaveAsPath = cmdInfo.m_sOutputpath;

		strDesc[0] = cmdInfo.m_sLeftDesc;
		if (cmdInfo.m_Files.GetSize() < 3)
		{
			strDesc[1] = cmdInfo.m_sRightDesc;
		}
		else
		{
			strDesc[1] = cmdInfo.m_sMiddleDesc;
			strDesc[2] = cmdInfo.m_sRightDesc;
		}

		if (cmdInfo.m_Files.GetSize() > 2)
		{
			cmdInfo.m_dwLeftFlags |= FFILEOPEN_CMDLINE;
			cmdInfo.m_dwMiddleFlags |= FFILEOPEN_CMDLINE;
			cmdInfo.m_dwRightFlags |= FFILEOPEN_CMDLINE;
			DWORD dwFlags[3] = {cmdInfo.m_dwLeftFlags, cmdInfo.m_dwMiddleFlags, cmdInfo.m_dwRightFlags};
			bCompared = pMainFrame->DoFileOpen(&cmdInfo.m_Files,
											   dwFlags, strDesc, cmdInfo.m_sReportFile, cmdInfo.m_bRecurse, nullptr,
											   cmdInfo.m_sPreDiffer);
		}
		else if (cmdInfo.m_Files.GetSize() > 1)
		{
			DWORD dwFlags[3] = {cmdInfo.m_dwLeftFlags, cmdInfo.m_dwRightFlags, FFILEOPEN_NONE};
			bCompared = pMainFrame->DoFileOpen(&cmdInfo.m_Files,
											   dwFlags, strDesc, cmdInfo.m_sReportFile, cmdInfo.m_bRecurse, nullptr,
											   cmdInfo.m_sPreDiffer);
		}
		else if (cmdInfo.m_Files.GetSize() == 1)
		{
			String sFilepath = cmdInfo.m_Files[0];
			if (IsProjectFile(sFilepath))
			{
				bCompared = LoadAndOpenProjectFile(sFilepath);
			}
			else if (IsConflictFile(sFilepath))
			{
				//For a conflict file, load the descriptions in their respective positions:  (they will be reordered as needed)
				strDesc[0] = cmdInfo.m_sLeftDesc;
				strDesc[1] = cmdInfo.m_sMiddleDesc;
				strDesc[2] = cmdInfo.m_sRightDesc;
				bCompared = pMainFrame->DoOpenConflict(sFilepath, strDesc);
			}
			else
			{
				DWORD dwFlags[3] = {cmdInfo.m_dwLeftFlags, cmdInfo.m_dwRightFlags, FFILEOPEN_NONE};
				bCompared = pMainFrame->DoFileOpen(&cmdInfo.m_Files,
												   dwFlags, strDesc, cmdInfo.m_sReportFile, cmdInfo.m_bRecurse, nullptr,
												   cmdInfo.m_sPreDiffer);
			}
		}
		else if (cmdInfo.m_Files.GetSize() == 0) // if there are no input args, we can check the display file dialog flag
		{
			bool showFiles = m_pOptions->GetBool(OPT_SHOW_SELECT_FILES_AT_STARTUP);
			if (showFiles)
				pMainFrame->DoFileOpen();
		}
	}
	return bCompared;
}*/

void MainWindow::UpdateDefaultCodepage(int cpDefaultMode, int cpCustomCodepage)
{
	int wLangId;

	/*switch (cpDefaultMode)
	{
		case 0:
			ucr::setDefaultCodepage(GetACP());
			break;
		case 1:
			TCHAR buff[32];
			wLangId = GetLangId();
			if (GetLocaleInfo(wLangId, LOCALE_IDEFAULTANSICODEPAGE, buff, sizeof(buff)/sizeof(buff[0])))
				ucr::setDefaultCodepage(_ttol(buff));
			else
				ucr::setDefaultCodepage(GetACP());
			break;
		case 2:
			ucr::setDefaultCodepage(cpCustomCodepage);
			break;
		default:
			// no other valid option
			assert (false);
			ucr::setDefaultCodepage(GetACP());
	}*/
}

/**
 * @brief Send current option settings into codepage module
 */
void MainWindow::UpdateCodepageModule()
{
	// Get current codepage settings from the options module
	// and push them into the codepage module
	//UpdateDefaultCodepage(GetOptionsMgr()->GetInt(OPT_CP_DEFAULT_MODE), GetOptionsMgr()->GetInt(OPT_CP_DEFAULT_CUSTOM));
}

/**
 * @brief Open given file to external editor specified in options.
 * @param [in] file Full path to file to open.
 *
 * Opens file to defined (in Options/system), Notepad by default,
 * external editor. Path is decorated with quotation marks if needed
 * (contains spaces). Also '$file' in editor path is replaced by
 * filename to open.
 * @param [in] file Full path to file to open.
 * @param [in] nLineNumber Line number to go to.
 */
void MainWindow::OpenFileToExternalEditor(const QString& file, int nLineNumber/* = 1*/)
{
	/*String sCmd = GetOptionsMgr()->GetString(OPT_EXT_EDITOR_CMD);
	String sFile(file);
	strutils::replace(sCmd, _T("$linenum"), strutils::to_str(nLineNumber));

	size_t nIndex = sCmd.find(_T("$file"));
	if (nIndex != String::npos)
	{
		sFile.insert(0, _T("\""));
		strutils::replace(sCmd, _T("$file"), sFile);
		nIndex = sCmd.find(' ', nIndex + sFile.length());
		if (nIndex != String::npos)
			sCmd.insert(nIndex, _T("\""));
		else
			sCmd += '"';
	}
	else
	{
		sCmd += _T(" \"");
		sCmd += sFile;
		sCmd += _T("\"");
	}

	bool retVal = false;
	STARTUPINFO stInfo = { sizeof STARTUPINFO };
	PROCESS_INFORMATION processInfo;

	retVal = !!CreateProcess(nullptr, (LPTSTR)sCmd.c_str(),
							 nullptr, nullptr, FALSE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr,
							 &stInfo, &processInfo);

	if (!retVal)
	{
		// Error invoking external editor
		String msg = strutils::format_string1(_("Failed to execute external editor: %1"), sCmd);
		AfxMessageBox(msg.c_str(), MB_ICONSTOP);
	}
	else
	{
		CloseHandle(processInfo.hThread);
		CloseHandle(processInfo.hProcess);
	}*/
}


/**
 * @brief Creates backup before file is saved or copied over.
 * This function handles formatting correct path and filename for
 * backup file. Formatting is done based on several options available
 * for users in Options/Backups dialog. After path is formatted, file
 * is simply just copied. Not much error checking, just if copying
 * succeeded or failed.
 * @param [in] bFolder Are we creating backup in folder compare?
 * @param [in] pszPath Full path to file to backup.
 * @return `true` if backup succeeds, or isn't just done.
 */
bool MainWindow::CreateBackup(bool bFolder, const QString& pszPath)
{
	// If user doesn't want to backups in folder compare, return
	// success so operations don't abort.
	/*if (bFolder && !(GetOptionsMgr()->GetBool(OPT_BACKUP_FOLDERCMP)))
		return true;
		// Likewise if user doesn't want backups in file compare
	else if (!bFolder && !(GetOptionsMgr()->GetBool(OPT_BACKUP_FILECMP)))
		return true;

	// create backup copy of file if destination file exists
	if (paths::DoesPathExist(pszPath) == paths::IS_EXISTING_FILE)
	{
		String bakPath;
		String path;
		String filename;
		String ext;

		paths::SplitFilename(paths::GetLongPath(pszPath), &path, &filename, &ext);

		// Determine backup folder
		if (GetOptionsMgr()->GetInt(OPT_BACKUP_LOCATION) ==
			PropBackups::FOLDER_ORIGINAL)
		{
			// Put backups to same folder than original file
			bakPath = path;
		}
		else if (GetOptionsMgr()->GetInt(OPT_BACKUP_LOCATION) ==
				 PropBackups::FOLDER_GLOBAL)
		{
			// Put backups to global folder defined in options
			bakPath = GetOptionsMgr()->GetString(OPT_BACKUP_GLOBALFOLDER);
			if (bakPath.empty())
				bakPath = path;
			else
				bakPath = paths::GetLongPath(bakPath);
		}
		else
		{
			_RPTF0(_CRT_ERROR, "Unknown backup location!");
		}

		bool success = false;
		if (GetOptionsMgr()->GetBool(OPT_BACKUP_ADD_BAK))
		{
			// Don't add dot if there is no existing extension
			if (ext.size() > 0)
				ext += _T(".");
			ext += BACKUP_FILE_EXT;
		}

		// Append time to filename if wanted so
		// NOTE just adds timestamp at the moment as I couldn't figure out
		// nice way to add a real time (invalid chars etc).
		if (GetOptionsMgr()->GetBool(OPT_BACKUP_ADD_TIME))
		{
			struct tm tm;
			time_t curtime = 0;
			time(&curtime);
			::localtime_s(&tm, &curtime);
			CString timestr;
			timestr.Format(_T("%04d%02d%02d%02d%02d%02d"), tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			filename += _T("-");
			filename += timestr;
		}

		// Append filename and extension (+ optional .bak) to path
		if ((bakPath.length() + filename.length() + ext.length())
			< MAX_PATH_FULL)
		{
			success = true;
			bakPath = paths::ConcatPath(bakPath, filename);
			bakPath += _T(".");
			bakPath += ext;
		}

		if (success)
		{
			success = !!CopyFileW(TFile(pszPath).wpath().c_str(), TFile(bakPath).wpath().c_str(), FALSE);
		}

		if (!success)
		{
			String msg = strutils::format_string1(
					_("Unable to backup original file:\n%1\n\nContinue anyway?"),
					pszPath);
			if (AfxMessageBox(msg.c_str(), MB_YESNO | MB_ICONWARNING | MB_DONT_ASK_AGAIN) != IDYES)
				return false;
		}
		return true;
	}

	// we got here because we're either not backing up of there was nothing to backup
	return true;*/
}

/**
 * @brief Checks if path (file/folder) is read-only and asks overwriting it.
 *
 * @param strSavePath [in,out] Path where to save (file or folder)
 * @param bMultiFile [in] Single file or multiple files/folder
 * @param bApplyToAll [in,out] Apply last user selection for all items?
 * @return Users selection:
 * - IDOK: Item was not readonly, no actions
 * - IDYES/IDYESTOALL: Overwrite readonly item
 * - IDNO: User selected new filename (single file) or user wants to skip
 * - IDCANCEL: Cancel operation
 * @sa CMainFrame::SyncFileToVCS()
 * @sa CMergeDoc::DoSave()
 */
int MainWindow::HandleReadonlySave(QString& strSavePath, bool bMultiFile,
								  bool &bApplyToAll)
{
	/*CFileStatus status;
	int nRetVal = IDOK;
	bool bFileRO = false;
	bool bFileExists = false;
	String s;
	String str;
	CString title;

	if (!strSavePath.empty())
	{
		try
		{
			TFile file(strSavePath);
			bFileExists = file.exists();
			if (bFileExists)
				bFileRO = !file.canWrite();
		}
		catch (...)
		{
		}
	}

	if (bFileExists && bFileRO)
	{
		UINT userChoice = 0;

		// Don't ask again if its already asked
		if (bApplyToAll)
			userChoice = IDYES;
		else
		{
			// Prompt for user choice
			if (bMultiFile)
			{
				// Multiple files or folder
				str = strutils::format_string1(_("%1\nis marked read-only. Would you like to override the read-only item?"), strSavePath);
				userChoice = AfxMessageBox(str.c_str(), MB_YESNOCANCEL |
														MB_ICONWARNING | MB_DEFBUTTON3 | MB_DONT_ASK_AGAIN |
														MB_YES_TO_ALL, IDS_SAVEREADONLY_MULTI);
			}
			else
			{
				// Single file
				str = strutils::format_string1(_("%1 is marked read-only. Would you like to override the read-only file ? (No to save as new filename.)"), strSavePath);
				userChoice = AfxMessageBox(str.c_str(), MB_YESNOCANCEL |
														MB_ICONWARNING | MB_DEFBUTTON2 | MB_DONT_ASK_AGAIN,
										   IDS_SAVEREADONLY_FMT);
			}
		}
		switch (userChoice)
		{
			// Overwrite read-only file
			case IDYESTOALL:
				bApplyToAll = true;  // Don't ask again (no break here)
			case IDYES:
				CFile::GetStatus(strSavePath.c_str(), status);
				status.m_mtime = 0;		// Avoid unwanted changes
				status.m_attribute &= ~CFile::readOnly;
				CFile::SetStatus(strSavePath.c_str(), status);
				nRetVal = IDYES;
				break;

				// Save to new filename (single) /skip this item (multiple)
			case IDNO:
				if (!bMultiFile)
				{
					if (SelectFile(AfxGetMainWnd()->GetSafeHwnd(), s, false, strSavePath.c_str()))
					{
						strSavePath = s;
						nRetVal = IDNO;
					}
					else
						nRetVal = IDCANCEL;
				}
				else
					nRetVal = IDNO;
				break;

				// Cancel saving
			case IDCANCEL:
				nRetVal = IDCANCEL;
				break;
		}
	}
	return nRetVal;*/
}

/**
 * @brief Is specified file a project file?
 * @param [in] filepath Full path to file to check.
 * @return true if file is a projectfile.
 */
bool MainWindow::IsProjectFile(const QString& filepath) const
{
	QString ext;
	paths::SplitFilename(filepath, nullptr, nullptr, &ext);
	/*if (strutils::compare_nocase(ext, ProjectFile::PROJECTFILE_EXT) == 0)
		return true;
	else
		return false;*/
}

/*bool MainWindow::LoadProjectFile(const QString& sProject, ProjectFile &project)
{
	if (sProject.isEmpty())
		return false;

	try
	{
		project.Read(sProject);
	}
	catch (Poco::Exception& e)
	{
		QString sErr = _("Unknown error attempting to open project file");
		sErr += ucr::toTString(e.displayText());
		QString msg = strutils::format_string2(_("Cannot open file\n%1\n\n%2"), sProject, sErr);
		AfxMessageBox(msg.c_str(), MB_ICONSTOP);
		return false;
	}

	return true;
}

bool MainWindow::SaveProjectFile(const QString& sProject, const ProjectFile &project)
{
	try
	{
		project.Save(sProject);
	}
	catch (Poco::Exception& e)
	{
		QString sErr = _("Unknown error attempting to save project file");
		sErr += ucr::toTString(e.displayText());
		QString msg = strutils::format_string2(_("Cannot open file\n%1\n\n%2"), sProject, sErr);
		AfxMessageBox(msg.c_str(), MB_ICONSTOP);
		return false;
	}

	return true;
}*/

/**
 * @brief Read project and perform comparison specified
 * @param [in] sProject Full path to project file.
 * @return `true` if loading project file and starting compare succeeded.
 */
bool MainWindow::LoadAndOpenProjectFile(const QString& sProject, const QString& sReportFile)
{
	/*ProjectFile project;
	if (!LoadProjectFile(sProject, project))
		return false;

	PathContext tFiles;
	bool bLeftReadOnly = false;
	bool bMiddleReadOnly = false;
	bool bRightReadOnly = false;
	bool bRecursive = false;
	project.GetPaths(tFiles, bRecursive);
	bLeftReadOnly = project.GetLeftReadOnly();
	bMiddleReadOnly = project.GetMiddleReadOnly();
	bRightReadOnly = project.GetRightReadOnly();
	if (project.HasFilter())
	{
		String filter = project.GetFilter();
		filter = strutils::trim_ws(filter);
		m_pGlobalFileFilter->SetFilter(filter);
	}
	if (project.HasSubfolders())
		bRecursive = project.GetSubfolders() > 0;

	DWORD dwFlags[3] = {
			static_cast<DWORD>(tFiles.GetPath(0).empty() ? FFILEOPEN_NONE : FFILEOPEN_PROJECT),
			static_cast<DWORD>(tFiles.GetPath(1).empty() ? FFILEOPEN_NONE : FFILEOPEN_PROJECT),
			static_cast<DWORD>(tFiles.GetPath(2).empty() ? FFILEOPEN_NONE : FFILEOPEN_PROJECT)
	};
	if (bLeftReadOnly)
		dwFlags[0] |= FFILEOPEN_READONLY;
	if (tFiles.GetSize() == 2)
	{
		if (bRightReadOnly)
			dwFlags[1] |= FFILEOPEN_READONLY;
	}
	else
	{
		if (bMiddleReadOnly)
			dwFlags[1] |= FFILEOPEN_READONLY;
		if (bRightReadOnly)
			dwFlags[2] |= FFILEOPEN_READONLY;
	}

	GetOptionsMgr()->SaveOption(OPT_CMP_INCLUDE_SUBDIRS, bRecursive);

	bool rtn = GetMainFrame()->DoFileOpen(&tFiles, dwFlags, nullptr, sReportFile, bRecursive);

	AddToRecentProjectsMRU(sProject.c_str());
	return rtn;*/
}

/**
 * @brief Return windows language ID of current WinMerge GUI language
 */
/*WORD MainWindow::GetLangId() const
{
	return m_pLangDlg->GetLangId();
}

/**
 * @brief Lang aware version of CStatusBar::SetIndicators()
 */
/*void MainWindow::SetIndicators(CStatusBar &sb, const UINT *rgid, int n) const
{
	m_pLangDlg->SetIndicators(sb, rgid, n);
}


/**
 * @brief Adds specified file to the recent projects list.
 * @param [in] sPathName Path to project file
 */
/*void MainWindow::AddToRecentProjectsMRU(LPCTSTR sPathName)
{
	// sPathName will be added to the top of the MRU list.
	// If sPathName already exists in the MRU list, it will be moved to the top
	if (m_pRecentFileList != nullptr)    {
		m_pRecentFileList->Add(sPathName);
		m_pRecentFileList->WriteList();
	}
}*/

void MainWindow::SetupTempPath()
{
	/*QString instTemp = env::GetPerInstanceString(TempFolderPrefix);
	if (GetOptionsMgr()->GetBool(OPT_USE_SYSTEM_TEMP_PATH))
		env::SetTemporaryPath(paths::ConcatPath(env::GetSystemTempPath(), instTemp));
	else
		env::SetTemporaryPath(paths::ConcatPath(GetOptionsMgr()->GetString(OPT_CUSTOM_TEMP_PATH), instTemp));*/
}

/**
 * @brief Handles menu selection from recent projects list
 * @param [in] nID Menu ID of the selected item
 */
/*BOOL MainWindow::OnOpenRecentFile(UINT nID)
{
	return LoadAndOpenProjectFile(static_cast<const TCHAR *>(m_pRecentFileList->m_arrNames[nID-ID_FILE_PROJECT_MRU_FIRST]));
}*/

/**
 * @brief Return if doc is in Merging/Editing mode
 */
bool MainWindow::GetMergingMode() const
{
	//return m_bMergingMode;
}

/**
 * @brief Set doc to Merging/Editing mode
 */
void MainWindow::SetMergingMode(bool bMergingMode)
{
	/*m_bMergingMode = bMergingMode;
	GetOptionsMgr()->SaveOption(OPT_MERGE_MODE, m_bMergingMode);*/
}

/**
 * @brief Switch Merging/Editing mode and update
 * buffer read-only states accordingly
 */
void MainWindow::OnMergingMode()
{
	bool bMergingMode = GetMergingMode();

	/*if (!bMergingMode)
		LangMessageBox(IDS_MERGE_MODE, MB_ICONINFORMATION | MB_DONT_DISPLAY_AGAIN);
	SetMergingMode(!bMergingMode);*/
}

/**
 * @brief Update Menuitem for Merging Mode
 */
/*void MainWindow::OnUpdateMergingMode(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(true);
	pCmdUI->SetCheck(GetMergingMode());
}*/

/**
 * @brief Update MergingMode UI in statusbar
 */
/*void MainWindow::OnUpdateMergingStatus(CCmdUI *pCmdUI)
{
	String text = theApp.LoadString(IDS_MERGEMODE_MERGING);
	pCmdUI->SetText(text.c_str());
	pCmdUI->Enable(GetMergingMode());
}

UINT MainWindow::GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
{
	COptionsMgr *pOptions = GetOptionsMgr();
	String name = strutils::format(_T("%s/%s"), lpszSection, lpszEntry);
	if (!pOptions->Get(name).IsInt())
		pOptions->InitOption(name, nDefault);
	return pOptions->GetInt(name);
}*/

/*bool MainWindow::WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
{
	COptionsMgr *pOptions = GetOptionsMgr();
	QString name = strutils::format(_T("%s/%s"), lpszSection, lpszEntry);
	if (!pOptions->Get(name).IsInt())
		pOptions->InitOption(name, nValue);
	return pOptions->SaveOption(name, nValue) == COption::OPT_OK;
}

QString MainWindow::GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
	COptionsMgr *pOptions = GetOptionsMgr();
	String name = strutils::format(_T("%s/%s"), lpszSection, lpszEntry);
	if (!pOptions->Get(name).IsString())
		pOptions->InitOption(name, lpszDefault ? lpszDefault : _T(""));
	return pOptions->GetString(name).c_str();
}*/

bool MainWindow::WriteProfileString(QString& lpszSection, QString& lpszEntry, QVariant& lpszValue)
{
	//COptionsMgr *pOptions = GetOptionsMgr();
	if (lpszEntry != nullptr)
	{
		QString name = QString("%s/%s").arg(lpszSection, lpszEntry);
		// toDo: ???
		//if (! (m_options.value(name).userType() == QMetaType::QString))
		// if (!pOptions->Get(name).IsString())
			//m_options.setValue(name, !lpszValue.isNull() ? lpszValue : QString(""));
			//pOptions->InitOption(name, lpszValue ? lpszValue : _T(""));
		m_options.setValue(name, !lpszValue.isNull() ? lpszValue : QString(""));
		return true; //m_options.setValue(name, !lpszValue.isNull() ? lpszValue : QString("")) == COption::OPT_OK;
		// return pOptions->SaveOption(name, lpszValue ? lpszValue : _T("")) == COption::OPT_OK;
	}
	return true;
}

/*static void LoadToolbarImageList(int imageWidth, UINT nIDResource, UINT nIDResourceMask, bool bGrayscale, CImageList& ImgList);
static CPtrList &GetDocList(CMultiDocTemplate *pTemplate);
template<class DocClass>
DocClass * GetMergeDocForDiff(CMultiDocTemplate *pTemplate, CDirDoc *pDirDoc, int nFiles, bool bMakeVisible = true);

/**
 * @brief A table associating menuitem id, icon and menus to apply.
 */
/*const CMainFrame::MENUITEM_ICON CMainFrame::m_MenuIcons[] = {
		{ ID_FILE_OPENCONFLICT,			IDB_FILE_OPENCONFLICT,			CMainFrame::MENU_ALL },
		{ ID_FILE_NEW3,                 IDB_FILE_NEW3,                  CMainFrame::MENU_ALL },
		{ ID_EDIT_COPY,					IDB_EDIT_COPY,					CMainFrame::MENU_ALL },
		{ ID_EDIT_CUT,					IDB_EDIT_CUT,					CMainFrame::MENU_ALL },
		{ ID_EDIT_PASTE,				IDB_EDIT_PASTE,					CMainFrame::MENU_ALL },
		{ ID_EDIT_FIND,					IDB_EDIT_SEARCH,				CMainFrame::MENU_ALL },
		{ ID_WINDOW_CASCADE,			IDB_WINDOW_CASCADE,				CMainFrame::MENU_ALL },
		{ ID_WINDOW_TILE_HORZ,			IDB_WINDOW_HORIZONTAL,			CMainFrame::MENU_ALL },
		{ ID_WINDOW_TILE_VERT,			IDB_WINDOW_VERTICAL,			CMainFrame::MENU_ALL },
		{ ID_FILE_CLOSE,				IDB_WINDOW_CLOSE,				CMainFrame::MENU_ALL },
		{ ID_WINDOW_CHANGE_PANE,		IDB_WINDOW_CHANGEPANE,			CMainFrame::MENU_ALL },
		{ ID_EDIT_WMGOTO,				IDB_EDIT_GOTO,					CMainFrame::MENU_ALL },
		{ ID_EDIT_REPLACE,				IDB_EDIT_REPLACE,				CMainFrame::MENU_ALL },
		{ ID_VIEW_SELECTFONT,			IDB_VIEW_SELECTFONT,			CMainFrame::MENU_ALL },
		{ ID_APP_EXIT,					IDB_FILE_EXIT,					CMainFrame::MENU_ALL },
		{ ID_HELP_CONTENTS,				IDB_HELP_CONTENTS,				CMainFrame::MENU_ALL },
		{ ID_EDIT_SELECT_ALL,			IDB_EDIT_SELECTALL,				CMainFrame::MENU_ALL },
		{ ID_TOOLS_FILTERS,				IDB_TOOLS_FILTERS,				CMainFrame::MENU_ALL },
		{ ID_TOOLS_CUSTOMIZECOLUMNS,	IDB_TOOLS_COLUMNS,				CMainFrame::MENU_ALL },
		{ ID_TOOLS_GENERATEPATCH,		IDB_TOOLS_GENERATEPATCH,		CMainFrame::MENU_ALL },
		{ ID_PLUGINS_LIST,				IDB_PLUGINS_LIST,				CMainFrame::MENU_ALL },
		{ ID_COPY_FROM_LEFT,			IDB_COPY_FROM_LEFT,				CMainFrame::MENU_ALL },
		{ ID_COPY_FROM_RIGHT,			IDB_COPY_FROM_RIGHT,			CMainFrame::MENU_ALL },
		{ ID_FILE_PRINT,				IDB_FILE_PRINT,					CMainFrame::MENU_FILECMP },
		{ ID_TOOLS_GENERATEREPORT,		IDB_TOOLS_GENERATEREPORT,		CMainFrame::MENU_FILECMP },
		{ ID_EDIT_TOGGLE_BOOKMARK,		IDB_EDIT_TOGGLE_BOOKMARK,		CMainFrame::MENU_FILECMP },
		{ ID_EDIT_GOTO_NEXT_BOOKMARK,	IDB_EDIT_GOTO_NEXT_BOOKMARK,	CMainFrame::MENU_FILECMP },
		{ ID_EDIT_GOTO_PREV_BOOKMARK,	IDB_EDIT_GOTO_PREV_BOOKMARK,	CMainFrame::MENU_FILECMP },
		{ ID_EDIT_CLEAR_ALL_BOOKMARKS,	IDB_EDIT_CLEAR_ALL_BOOKMARKS,	CMainFrame::MENU_FILECMP },
		{ ID_VIEW_ZOOMIN,				IDB_VIEW_ZOOMIN,				CMainFrame::MENU_FILECMP },
		{ ID_VIEW_ZOOMOUT,				IDB_VIEW_ZOOMOUT,				CMainFrame::MENU_FILECMP },
		{ ID_MERGE_COMPARE,				IDB_MERGE_COMPARE,				CMainFrame::MENU_FOLDERCMP },
		{ ID_MERGE_COMPARE_LEFT1_LEFT2,		IDB_MERGE_COMPARE_LEFT1_LEFT2,	CMainFrame::MENU_FOLDERCMP },
		{ ID_MERGE_COMPARE_RIGHT1_RIGHT2,	IDB_MERGE_COMPARE_RIGHT1_RIGHT2,CMainFrame::MENU_FOLDERCMP },
		{ ID_MERGE_COMPARE_LEFT1_RIGHT2,	IDB_MERGE_COMPARE_LEFT1_RIGHT2,	CMainFrame::MENU_FOLDERCMP },
		{ ID_MERGE_COMPARE_LEFT2_RIGHT1,	IDB_MERGE_COMPARE_LEFT2_RIGHT1,	CMainFrame::MENU_FOLDERCMP },
		{ ID_MERGE_DELETE,				IDB_MERGE_DELETE,				CMainFrame::MENU_FOLDERCMP },
		{ ID_TOOLS_GENERATEREPORT,		IDB_TOOLS_GENERATEREPORT,		CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_LEFT_TO_RIGHT,	IDB_LEFT_TO_RIGHT,				CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_LEFT_TO_MIDDLE,	IDB_LEFT_TO_MIDDLE,				CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_RIGHT_TO_LEFT,	IDB_RIGHT_TO_LEFT,				CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_RIGHT_TO_MIDDLE,	IDB_RIGHT_TO_MIDDLE,			CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_MIDDLE_TO_LEFT,	IDB_MIDDLE_TO_LEFT,				CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_MIDDLE_TO_RIGHT,	IDB_MIDDLE_TO_RIGHT,			CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_LEFT_TO_BROWSE,	IDB_LEFT_TO_BROWSE,				CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_MIDDLE_TO_BROWSE,	IDB_MIDDLE_TO_BROWSE,			CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_RIGHT_TO_BROWSE,	IDB_RIGHT_TO_BROWSE,			CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_MOVE_LEFT_TO_BROWSE,	IDB_MOVE_LEFT_TO_BROWSE,		CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_MOVE_MIDDLE_TO_BROWSE,	IDB_MOVE_MIDDLE_TO_BROWSE,		CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_MOVE_RIGHT_TO_BROWSE,	IDB_MOVE_RIGHT_TO_BROWSE,		CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_DEL_LEFT,				IDB_LEFT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_DEL_MIDDLE,			IDB_MIDDLE,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_DEL_RIGHT,				IDB_RIGHT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_DEL_BOTH,				IDB_BOTH,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_DEL_ALL,				IDB_ALL,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_PATHNAMES_LEFT,	IDB_LEFT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_PATHNAMES_MIDDLE,	IDB_MIDDLE,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_PATHNAMES_RIGHT,	IDB_RIGHT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_PATHNAMES_BOTH,	IDB_BOTH,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_PATHNAMES_ALL,	IDB_ALL,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_LEFT_TO_CLIPBOARD, IDB_LEFT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_MIDDLE_TO_CLIPBOARD, IDB_MIDDLE,					CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_RIGHT_TO_CLIPBOARD, IDB_RIGHT,					CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_BOTH_TO_CLIPBOARD, IDB_BOTH,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_COPY_ALL_TO_CLIPBOARD, IDB_ALL,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_ZIP_LEFT,				IDB_LEFT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_ZIP_MIDDLE,			IDB_MIDDLE,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_ZIP_RIGHT,				IDB_RIGHT,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_ZIP_BOTH,				IDB_BOTH,						CMainFrame::MENU_FOLDERCMP },
		{ ID_DIR_ZIP_ALL,				IDB_ALL,						CMainFrame::MENU_FOLDERCMP }
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_WM_MENUCHAR()
ON_WM_MEASUREITEM()
ON_WM_INITMENUPOPUP()
ON_WM_INITMENU()
ON_WM_CREATE()
ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
ON_COMMAND(ID_HELP_GNULICENSE, OnHelpGnulicense)
ON_COMMAND(ID_OPTIONS, OnOptions)
ON_COMMAND(ID_VIEW_SELECTFONT, OnViewSelectfont)
ON_COMMAND(ID_VIEW_USEDEFAULTFONT, OnViewUsedefaultfont)
ON_COMMAND(ID_HELP_CONTENTS, OnHelpContents)
ON_WM_CLOSE()
ON_COMMAND(ID_TOOLS_GENERATEPATCH, OnToolsGeneratePatch)
ON_WM_DESTROY()
ON_COMMAND_RANGE(ID_UNPACK_MANUAL, ID_UNPACK_AUTO, OnPluginUnpackMode)
ON_UPDATE_COMMAND_UI_RANGE(ID_UNPACK_MANUAL, ID_UNPACK_AUTO, OnUpdatePluginUnpackMode)
ON_COMMAND_RANGE(ID_PREDIFFER_MANUAL, ID_PREDIFFER_AUTO, OnPluginPrediffMode)
ON_UPDATE_COMMAND_UI_RANGE(ID_PREDIFFER_MANUAL, ID_PREDIFFER_AUTO, OnUpdatePluginPrediffMode)
ON_UPDATE_COMMAND_UI(ID_RELOAD_PLUGINS, OnUpdateReloadPlugins)
ON_COMMAND(ID_RELOAD_PLUGINS, OnReloadPlugins)
ON_COMMAND(ID_HELP_GETCONFIG, OnSaveConfigData)
ON_COMMAND(ID_FILE_NEW, OnFileNew)
ON_COMMAND(ID_FILE_NEW3, OnFileNew3)
ON_COMMAND(ID_TOOLS_FILTERS, OnToolsFilters)
ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
ON_UPDATE_COMMAND_UI(ID_VIEW_TAB_BAR, OnUpdateViewTabBar)
ON_COMMAND(ID_VIEW_TAB_BAR, OnViewTabBar)
ON_UPDATE_COMMAND_UI(ID_VIEW_RESIZE_PANES, OnUpdateResizePanes)
ON_COMMAND(ID_VIEW_RESIZE_PANES, OnResizePanes)
ON_COMMAND(ID_FILE_OPENPROJECT, OnFileOpenProject)
ON_MESSAGE(WM_COPYDATA, OnCopyData)
ON_MESSAGE(WM_USER+1, OnUser1)
ON_COMMAND(ID_WINDOW_CLOSEALL, OnWindowCloseAll)
ON_UPDATE_COMMAND_UI(ID_WINDOW_CLOSEALL, OnUpdateWindowCloseAll)
ON_COMMAND(ID_FILE_SAVEPROJECT, OnSaveProject)
ON_WM_ACTIVATEAPP()
ON_COMMAND_RANGE(ID_TOOLBAR_NONE, ID_TOOLBAR_HUGE, OnToolbarSize)
ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLBAR_NONE, ID_TOOLBAR_HUGE, OnUpdateToolbarSize)
ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
ON_COMMAND(ID_HELP_RELEASENOTES, OnHelpReleasenotes)
ON_COMMAND(ID_HELP_TRANSLATIONS, OnHelpTranslations)
ON_COMMAND(ID_FILE_OPENCONFLICT, OnFileOpenConflict)
ON_COMMAND(ID_PLUGINS_LIST, OnPluginsList)
ON_UPDATE_COMMAND_UI(ID_STATUS_PLUGIN, OnUpdatePluginName)
ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDiffOptionsDropDown)
ON_COMMAND_RANGE(IDC_DIFF_WHITESPACE_COMPARE, IDC_DIFF_WHITESPACE_IGNOREALL, OnDiffWhitespace)
ON_UPDATE_COMMAND_UI_RANGE(IDC_DIFF_WHITESPACE_COMPARE, IDC_DIFF_WHITESPACE_IGNOREALL, OnUpdateDiffWhitespace)
ON_COMMAND(IDC_DIFF_CASESENSITIVE, OnDiffCaseSensitive)
ON_UPDATE_COMMAND_UI(IDC_DIFF_CASESENSITIVE, OnUpdateDiffCaseSensitive)
ON_COMMAND(IDC_DIFF_IGNOREEOL, OnDiffIgnoreEOL)
ON_UPDATE_COMMAND_UI(IDC_DIFF_IGNOREEOL, OnUpdateDiffIgnoreEOL)
ON_COMMAND(IDC_RECURS_CHECK, OnIncludeSubfolders)
ON_UPDATE_COMMAND_UI(IDC_RECURS_CHECK, OnUpdateIncludeSubfolders)
ON_COMMAND_RANGE(ID_COMPMETHOD_FULL_CONTENTS, ID_COMPMETHOD_SIZE, OnCompareMethod)
ON_UPDATE_COMMAND_UI_RANGE(ID_COMPMETHOD_FULL_CONTENTS, ID_COMPMETHOD_SIZE, OnUpdateCompareMethod)
ON_COMMAND_RANGE(ID_MRU_FIRST, ID_MRU_LAST, OnMRUs)
ON_UPDATE_COMMAND_UI(ID_MRU_FIRST, OnUpdateNoMRUs)
ON_UPDATE_COMMAND_UI(ID_NO_MRU, OnUpdateNoMRUs)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**
 * @brief MainFrame statusbar panels/indicators
 */
/*
static UINT StatusbarIndicators[] =
		{
				ID_SEPARATOR,           // Plugin name
				ID_SEPARATOR,           // status line indicator
				ID_SEPARATOR,           // Merge mode
				ID_SEPARATOR,           // Diff number
				ID_INDICATOR_CAPS,      // Caps Lock
				ID_INDICATOR_NUM,       // Num Lock
				ID_INDICATOR_OVR,       // Insert
		};

/**
  * @brief Return a const reference to a CMultiDocTemplate's list of documents.
  */
/*
static CPtrList &GetDocList(CMultiDocTemplate *pTemplate)
{
	struct Template : public CMultiDocTemplate
	{
	public:
		using CMultiDocTemplate::m_docList;
	};
	return static_cast<struct Template *>(pTemplate)->m_docList;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

/**
 * @brief MainFrame constructor. Loads settings from registry.
 * @todo Preference for logging?
 */
/*
CMainFrame::CMainFrame()
		: m_bFirstTime(true)
		, m_pDropHandler(nullptr)
		, m_bShowErrors(false)
{
}

CMainFrame::~CMainFrame()
{
	GetOptionsMgr()->SaveOption(OPT_TABBAR_AUTO_MAXWIDTH, m_wndTabBar.GetAutoMaxWidth());
	strdiff::Close();
}

#ifdef _UNICODE
const TCHAR CMainFrame::szClassName[] = _T("WinMergeWindowClassW");
#else
const TCHAR CMainFrame::szClassName[] = _T("WinMergeWindowClassA");
#endif
/**
 * @brief Change MainFrame window class name
 *        see http://support.microsoft.com/kb/403825/ja
 *//*
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASS wndcls;
	BOOL bRes = CMDIFrameWnd::PreCreateWindow(cs);
	HINSTANCE hInst = AfxGetInstanceHandle();
	// see if the class already exists
	if (!::GetClassInfo(hInst, szClassName, &wndcls))
	{
		// get default stuff
		::GetClassInfo(hInst, cs.lpszClass, &wndcls);
		// register a new class
		wndcls.lpszClassName = szClassName;
		wndcls.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
		::RegisterClass(&wndcls);
	}
	cs.lpszClass = szClassName;
	return bRes;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndMDIClient.SubclassWindow(m_hWndMDIClient);

	m_lfDiff = Options::Font::Load(GetOptionsMgr(), OPT_FONT_FILECMP);
	m_lfDir = Options::Font::Load(GetOptionsMgr(), OPT_FONT_DIRCMP);

	if (!CreateToolbar())
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndTabBar.Create(this))
	{
		TRACE0("Failed to create tab bar\n");
		return -1;      // fail to create
	}
	m_wndTabBar.SetAutoMaxWidth(GetOptionsMgr()->GetBool(OPT_TABBAR_AUTO_MAXWIDTH));

	if (!GetOptionsMgr()->GetBool(OPT_SHOW_TABBAR))
		CMDIFrameWnd::ShowControlBar(&m_wndTabBar, false, 0);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	theApp.SetIndicators(m_wndStatusBar, StatusbarIndicators,
						 countof(StatusbarIndicators));

	const int lpx = CClientDC(this).GetDeviceCaps(LOGPIXELSX);
	auto pointToPixel = [lpx](int point) { return MulDiv(point, lpx, 72); };
	m_wndStatusBar.SetPaneInfo(0, 0, SBPS_STRETCH | SBPS_NOBORDERS, 0);
	m_wndStatusBar.SetPaneInfo(1, ID_STATUS_PLUGIN, 0, pointToPixel(225));
	m_wndStatusBar.SetPaneInfo(2, ID_STATUS_MERGINGMODE, 0, pointToPixel(75));
	m_wndStatusBar.SetPaneInfo(3, ID_STATUS_DIFFNUM, 0, pointToPixel(112));

	if (!GetOptionsMgr()->GetBool(OPT_SHOW_STATUSBAR))
		CMDIFrameWnd::ShowControlBar(&m_wndStatusBar, false, 0);

	m_pDropHandler = new DropHandler(std::bind(&CMainFrame::OnDropFiles, this, std::placeholders::_1));
	RegisterDragDrop(m_hWnd, m_pDropHandler);

	return 0;
}

void CMainFrame::OnDestroy(void)
{
	if (m_pDropHandler != nullptr)
		RevokeDragDrop(m_hWnd);
}

static HMENU GetSubmenu(HMENU mainMenu, UINT nIDFirstMenuItem, bool bFirstSubmenu)
{
	int i;
	for (i = 0 ; i < ::GetMenuItemCount(mainMenu) ; i++)
		if (::GetMenuItemID(::GetSubMenu(mainMenu, i), 0) == nIDFirstMenuItem)
			break;
	HMENU menu = ::GetSubMenu(mainMenu, i);

	if (!bFirstSubmenu)
	{
		// look for last submenu
		for (i = ::GetMenuItemCount(menu) ; i >= 0  ; i--)
			if (::GetSubMenu(menu, i) != nullptr)
				return ::GetSubMenu(menu, i);
	}
	else
	{
		// look for first submenu
		for (i = 0 ; i < ::GetMenuItemCount(menu) ; i++)
			if (::GetSubMenu(menu, i) != nullptr)
				return ::GetSubMenu(menu, i);
	}

	// error, submenu not found
	return nullptr;
}

/**
 * @brief Find the scripts submenu from the main menu
 * As now this is the first submenu in "Edit" menu
 * We find the "Edit" menu by looking for a menu
 *  starting with ID_EDIT_UNDO.
 *//*
HMENU CMainFrame::GetScriptsSubmenu(HMENU mainMenu)
{
	return GetSubmenu(mainMenu, ID_PLUGINS_LIST, false);
}

/**
 * @brief Find the scripts submenu from the main menu
 * As now this is the first submenu in "Plugins" menu
 * We find the "Plugins" menu by looking for a menu
 *  starting with ID_UNPACK_MANUAL.
 *//*
HMENU CMainFrame::GetPrediffersSubmenu(HMENU mainMenu)
{
	return GetSubmenu(mainMenu, ID_PLUGINS_LIST, true);
}

/**
 * @brief Create a new menu for the view..
 * @param [in] view Menu view either MENU_DEFAULT, MENU_MERGEVIEW or MENU_DIRVIEW.
 * @param [in] ID Menu's resource ID.
 * @return Menu for the view.
 *//*
HMENU CMainFrame::NewMenu(int view, int ID)
{
	int menu_view, index;
	if (m_pMenus[view] == nullptr)
	{
		m_pMenus[view].reset(new BCMenu());
		if (m_pMenus[view] == nullptr)
			return nullptr;
	}

	switch (view)
	{
		case MENU_MERGEVIEW:
			menu_view = MENU_FILECMP;
			break;
		case MENU_DIRVIEW:
			menu_view = MENU_FOLDERCMP;
			break;
		case MENU_DEFAULT:
		default:
			menu_view = MENU_MAINFRM;
			break;
	};

	if (!m_pMenus[view]->LoadMenu(ID))
	{
		ASSERT(false);
		return nullptr;
	}

	if (view == MENU_IMGMERGEVIEW)
	{
		BCMenu *pMenu = new BCMenu;
		pMenu->LoadMenu(MAKEINTRESOURCE(IDR_POPUP_IMGMERGEVIEW));
		m_pMenus[view]->InsertMenu(4, MF_BYPOSITION | MF_POPUP, (UINT_PTR)pMenu->GetSubMenu(0)->m_hMenu, const_cast<TCHAR *>(LoadResString(IDS_IMAGE_MENU).c_str()));
	}

	// Load bitmaps to menuitems
	for (index = 0; index < countof(m_MenuIcons); index ++)
	{
		if (menu_view == (m_MenuIcons[index].menusToApply & menu_view))
		{
			m_pMenus[view]->ModifyODMenu(nullptr, m_MenuIcons[index].menuitemID, m_MenuIcons[index].iconResID);
		}
	}

	m_pMenus[view]->LoadToolbar(IDR_MAINFRAME);

	theApp.TranslateMenu(m_pMenus[view]->m_hMenu);

	return (m_pMenus[view]->Detach());

}
/**
* @brief Create new default (CMainFrame) menu.
*/
//HMENU CMainFrame::NewDefaultMenu(int ID /*=0*/)
/*{
	if (ID == 0)
		ID = IDR_MAINFRAME;
	return NewMenu( MENU_DEFAULT, ID );
}

/**
 * @brief Create new File compare (CMergeEditView) menu.
 *//*
HMENU CMainFrame::NewMergeViewMenu()
{
	return NewMenu( MENU_MERGEVIEW, IDR_MERGEDOCTYPE);
}

/**
 * @brief Create new Dir compare (CDirView) menu
 *//*
HMENU CMainFrame::NewDirViewMenu()
{
	return NewMenu(MENU_DIRVIEW, IDR_DIRDOCTYPE );
}

/**
 * @brief Create new File compare (CHexMergeView) menu.
 *//*
HMENU CMainFrame::NewHexMergeViewMenu()
{
	return NewMenu( MENU_HEXMERGEVIEW, IDR_MERGEDOCTYPE);
}

/**
 * @brief Create new Image compare (CImgMergeView) menu.
 *//*
HMENU CMainFrame::NewImgMergeViewMenu()
{
	return NewMenu( MENU_IMGMERGEVIEW, IDR_MERGEDOCTYPE);
}

/**
 * @brief Create new File compare (COpenView) menu.
 *//*
HMENU CMainFrame::NewOpenViewMenu()
{
	return NewMenu( MENU_OPENVIEW, IDR_MAINFRAME);
}

/**
 * @brief This handler ensures that the popup menu items are drawn correctly.
 *//*
void CMainFrame::OnMeasureItem(int nIDCtl,
							   LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	bool setflag = false;
	if (lpMeasureItemStruct->CtlType == ODT_MENU)
	{
		if (IsMenu(reinterpret_cast<HMENU>(static_cast<uintptr_t>(lpMeasureItemStruct->itemID))))
		{
			CMenu* cmenu =
					CMenu::FromHandle(reinterpret_cast<HMENU>(static_cast<uintptr_t>(lpMeasureItemStruct->itemID)));

			if (m_pMenus[MENU_DEFAULT]->IsMenu(cmenu))
			{
				m_pMenus[MENU_DEFAULT]->MeasureItem(lpMeasureItemStruct);
				setflag = true;
			}
		}
	}

	if (!setflag)
		CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

/**
 * @brief This handler ensures that keyboard shortcuts work.
 *//*
LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags,
							   CMenu* pMenu)
{
	LRESULT lresult;
	if(m_pMenus[MENU_DEFAULT]->IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	return lresult;
}

/**
 * @brief This handler updates the menus from time to time.
 *//*
void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	if (!bSysMenu)
	{
		if (BCMenu::IsMenu(pPopupMenu))
		{
			BCMenu::UpdateMenu(pPopupMenu);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnFileOpen()
{
	DoFileOpen();
}

/**
 * @brief Check for BOM, and also, if bGuessEncoding, try to deduce codepage
 *
 * Unpacks info from FileLocation & delegates all work to codepage_detect module
 *//*
static void
FileLocationGuessEncodings(FileLocation & fileloc, int iGuessEncoding)
{
	fileloc.encoding = GuessCodepageEncoding(fileloc.filepath, iGuessEncoding);
}

bool CMainFrame::ShowAutoMergeDoc(CDirDoc * pDirDoc,
								  int nFiles, const FileLocation ifileloc[],
								  const DWORD dwFlags[], const String strDesc[], const String& sReportFile /*= _T("")*///,
								  //const PackingInfo * infoUnpacker /*= nullptr*///)
/*{
	int pane;
	FileFilterHelper filterImg, filterBin;
	filterImg.UseMask(true);
	filterImg.SetMask(GetOptionsMgr()->GetString(OPT_CMP_IMG_FILEPATTERNS));
	filterBin.UseMask(true);
	filterBin.SetMask(GetOptionsMgr()->GetString(OPT_CMP_BIN_FILEPATTERNS));
	for (pane = 0; pane < nFiles; ++pane)
	{
		if (filterImg.includeFile(ifileloc[pane].filepath) && CImgMergeFrame::IsLoadable())
			return ShowImgMergeDoc(pDirDoc, nFiles, ifileloc, dwFlags, strDesc, sReportFile, infoUnpacker);
		else if (filterBin.includeFile(ifileloc[pane].filepath) && CHexMergeView::IsLoadable())
			return ShowHexMergeDoc(pDirDoc, nFiles, ifileloc, dwFlags, strDesc, sReportFile, infoUnpacker);
	}
	return ShowMergeDoc(pDirDoc, nFiles, ifileloc, dwFlags, strDesc, sReportFile, infoUnpacker);
}

std::array<bool, 3> GetROFromFlags(int nFiles, const DWORD dwFlags[])
{
	std::array<bool, 3> bRO = { false, false, false };
	for (int pane = 0; pane < nFiles; pane++)
	{
		if (dwFlags)
			bRO[pane] = ((dwFlags[pane] & FFILEOPEN_READONLY) > 0);
	}
	return bRO;
}

int GetActivePaneFromFlags(int nFiles, const DWORD dwFlags[])
{
	int nActivePane = -1;
	for (int pane = 0; pane < nFiles; ++pane)
	{
		if (dwFlags && (dwFlags[pane] & FFILEOPEN_SETFOCUS))
			nActivePane = pane;
	}
	return nActivePane;
}

/**
 * @brief Creates new MergeDoc instance and shows documents.
 * @param [in] pDirDoc Dir compare document to create a new Merge document for.
 * @param [in] ifilelocLeft Left side file location info.
 * @param [in] ifilelocRight Right side file location info.
 * @param [in] dwLeftFlags Left side flags.
 * @param [in] dwRightFlags Right side flags.
 * @param [in] infoUnpacker Plugin info.
 * @return success/failure
 *//*
bool CMainFrame::ShowMergeDoc(CDirDoc * pDirDoc,
							  int nFiles, const FileLocation ifileloc[],
							  const DWORD dwFlags[], const String strDesc[], const String& sReportFile /*= _T("")*///,
							  /*const PackingInfo * infoUnpacker /*= nullptr*///)
/*{
	if (m_pMenus[MENU_MERGEVIEW] == nullptr)
		theApp.m_pDiffTemplate->m_hMenuShared = NewMergeViewMenu();
	CMergeDoc * pMergeDoc = GetMergeDocForDiff<CMergeDoc>(theApp.m_pDiffTemplate, pDirDoc, nFiles, false);

	// Make local copies, so we can change encoding if we guess it below
	FileLocation fileloc[3];
	std::copy_n(ifileloc, nFiles, fileloc);

	ASSERT(pMergeDoc != nullptr);		// must ASSERT to get an answer to the question below ;-)
	if (pMergeDoc == nullptr)
		return false; // when does this happen ?

	// if an unpacker is selected, it must be used during LoadFromFile
	// MergeDoc must memorize it for SaveToFile
	// Warning : this unpacker may differ from the pDirDoc one
	// (through menu : "Plugins"->"Open with unpacker")
	pMergeDoc->SetUnpacker(infoUnpacker);

	// detect codepage
	int iGuessEncodingType = GetOptionsMgr()->GetInt(OPT_CP_DETECT);
	for (int pane = 0; pane < nFiles; pane++)
	{
		if (fileloc[pane].encoding.m_unicoding == -1)
			fileloc[pane].encoding.m_unicoding = ucr::NONE;
		if (fileloc[pane].encoding.m_unicoding == ucr::NONE && fileloc[pane].encoding.m_codepage == -1)
		{
			FileLocationGuessEncodings(fileloc[pane], iGuessEncodingType);
		}

		// TODO (Perry, 2005-12-04)
		// Should we do any unification if unicodings are different?


#ifndef _UNICODE
		// In ANSI (8-bit) build, character loss can occur in merging
		// if the two buffers use different encodings
		if (pane > 0 && fileloc[pane - 1].encoding.m_codepage != fileloc[pane].encoding.m_codepage)
		{
			CString msg;
			msg.Format(theApp.LoadString(IDS_SUGGEST_IGNORECODEPAGE).c_str(), fileloc[pane - 1].encoding.m_codepage,fileloc[pane].encoding.m_codepage);
			int msgflags = MB_YESNO | MB_ICONQUESTION | MB_DONT_ASK_AGAIN;
			// Two files with different codepages
			// Warn and propose to use the default codepage for both
			int userChoice = AfxMessageBox(msg, msgflags);
			if (userChoice == IDYES)
			{
				fileloc[pane - 1].encoding.SetCodepage(ucr::getDefaultCodepage());
				fileloc[pane - 1].encoding.m_bom = false;
				fileloc[pane].encoding.SetCodepage(ucr::getDefaultCodepage());
				fileloc[pane].encoding.m_bom = false;
			}
		}
#endif
	}

	// Note that OpenDocs() takes care of closing compare window when needed.
	bool bResult = pMergeDoc->OpenDocs(nFiles, fileloc, GetROFromFlags(nFiles, dwFlags).data(), strDesc);

	if (CChildFrame *pFrame = pMergeDoc->GetParentFrame())
	{
		if (!pFrame->IsActivated())
			pFrame->InitialUpdateFrame(pMergeDoc, true);
	}

	if (!bResult)
		return false;

	for (int pane = 0; pane < nFiles; pane++)
	{
		if (dwFlags)
		{
			bool bModified = (dwFlags[pane] & FFILEOPEN_MODIFIED) > 0;
			if (bModified)
			{
				pMergeDoc->m_ptBuf[pane]->SetModified(true);
				pMergeDoc->UpdateHeaderPath(pane);
			}
			if (dwFlags[pane] & FFILEOPEN_AUTOMERGE)
			{
				pMergeDoc->DoAutoMerge(pane);
			}
		}
	}

	pMergeDoc->MoveOnLoad(GetActivePaneFromFlags(nFiles, dwFlags));

	if (!sReportFile.empty())
		pMergeDoc->GenerateReport(sReportFile);

	return true;
}

bool CMainFrame::ShowHexMergeDoc(CDirDoc * pDirDoc, int nFiles, const FileLocation fileloc[],
								 const DWORD dwFlags[], const String strDesc[], const String& sReportFile /*= _T("")*///,
								 /*const PackingInfo * infoUnpacker /*= nullptr*///)
/*{
	if (m_pMenus[MENU_HEXMERGEVIEW] == nullptr)
		theApp.m_pHexMergeTemplate->m_hMenuShared = NewHexMergeViewMenu();
	CHexMergeDoc *pHexMergeDoc = GetMergeDocForDiff<CHexMergeDoc>(theApp.m_pHexMergeTemplate, pDirDoc, nFiles);
	if (pHexMergeDoc == nullptr)
		return false;

	if (!pHexMergeDoc->OpenDocs(nFiles, fileloc, GetROFromFlags(nFiles, dwFlags).data(), strDesc))
		return false;

	pHexMergeDoc->MoveOnLoad(GetActivePaneFromFlags(nFiles, dwFlags));

	if (!sReportFile.empty())
		pHexMergeDoc->GenerateReport(sReportFile);

	return true;
}

bool CMainFrame::ShowImgMergeDoc(CDirDoc * pDirDoc, int nFiles, const FileLocation fileloc[],
								 const DWORD dwFlags[], const String strDesc[], const String& sReportFile /*= _T("")*///,
//								 const PackingInfo * infoUnpacker /*= nullptr*/)
/*{
	CImgMergeFrame *pImgMergeFrame = new CImgMergeFrame();
	if (!CImgMergeFrame::menu.m_hMenu)
		CImgMergeFrame::menu.m_hMenu = NewImgMergeViewMenu();
	pImgMergeFrame->SetSharedMenu(CImgMergeFrame::menu.m_hMenu);

	pImgMergeFrame->SetDirDoc(pDirDoc);
	pDirDoc->AddMergeDoc(pImgMergeFrame);

	if (!pImgMergeFrame->OpenDocs(nFiles, fileloc, GetROFromFlags(nFiles, dwFlags).data(), strDesc, this))
		return ShowMergeDoc(pDirDoc, nFiles, fileloc, dwFlags, strDesc, sReportFile, infoUnpacker);

	for (int pane = 0; pane < nFiles; pane++)
	{
		if (dwFlags && (dwFlags[pane] & FFILEOPEN_AUTOMERGE))
			pImgMergeFrame->DoAutoMerge(pane);
	}

	pImgMergeFrame->MoveOnLoad(GetActivePaneFromFlags(nFiles, dwFlags));

	if (!sReportFile.empty())
		pImgMergeFrame->GenerateReport(sReportFile);

	return true;
}


/*
static bool AddToRecentDocs(const PathContext& paths, const unsigned flags[], bool recurse, const String& filter)
{
	String params, title;
	for (int nIndex = 0; nIndex < paths.GetSize(); ++nIndex)
	{
		if (flags && (flags[nIndex] & FFILEOPEN_READONLY))
		{
			switch (nIndex)
			{
				case 0: params += _T("/wl "); break;
				case 1: params += paths.GetSize() == 2 ? _T("/wr ") : _T("/wm "); break;
				case 2:	params += _T("/wr "); break;
			}
		}
		params += _T("\"") + paths[nIndex] + _T("\" ");

		String path = paths[nIndex];
		paths::normalize(path);
		title += paths::FindFileName(path);
		if (nIndex < paths.GetSize() - 1)
			title += _T(" - ");
	}
	if (recurse)
		params += _T("/r ");
	if (!filter.empty())
		params += _T("/f \"") + filter + _T("\" ");
	return JumpList::AddToRecentDocs(_T(""), params, title, params, 0);
}

/**
 * @brief Begin a diff: open dirdoc if it is directories, else open a mergedoc for editing.
 * @param [in] pszLeft Left-side path.
 * @param [in] pszRight Right-side path.
 * @param [in] dwLeftFlags Left-side flags.
 * @param [in] dwRightFlags Right-side flags.
 * @param [in] bRecurse Do we run recursive (folder) compare?
 * @param [in] pDirDoc Dir compare document to use.
 * @param [in] prediffer Prediffer plugin name.
 * @return `true` if opening files and compare succeeded, `false` otherwise.
 *//*
//bool CMainFrame::DoFileOpen(const PathContext * pFiles /*= nullptr*///,
							//const DWORD dwFlags[] /*= nullptr*/, const String strDesc[] /*= nullptr*/, const String& sReportFile /*= T("")*/, bool bRecurse /*= false*/, CDirDoc *pDirDoc/*= nullptr*/,
							//String prediffer /*= _T("")*/, const PackingInfo *infoUnpacker /*= nullptr*/)
/*{
	if (pDirDoc != nullptr && !pDirDoc->CloseMergeDocs())
		return false;

	FileTransform::g_UnpackerMode = static_cast<PLUGIN_MODE>(GetOptionsMgr()->GetInt(OPT_PLUGINS_UNPACKER_MODE));
	FileTransform::g_PredifferMode = static_cast<PLUGIN_MODE>(GetOptionsMgr()->GetInt(OPT_PLUGINS_PREDIFFER_MODE));

	Merge7zFormatMergePluginScope scope(infoUnpacker);

	PathContext tFiles;
	if (pFiles != nullptr)
		tFiles = *pFiles;
	bool bRO[3] = {0};
	if (dwFlags)
	{
		bRO[0] = (dwFlags[0] & FFILEOPEN_READONLY) != 0;
		bRO[1] = (dwFlags[1] & FFILEOPEN_READONLY) != 0;
		bRO[2] = (dwFlags[2] & FFILEOPEN_READONLY) != 0;
	};

	// pop up dialog unless arguments exist (and are compatible)
	paths::PATH_EXISTENCE pathsType = paths::GetPairComparability(tFiles, IsArchiveFile);
	if (pathsType == paths::DOES_NOT_EXIST)
	{
		if (m_pMenus[MENU_OPENVIEW] == nullptr)
			theApp.m_pOpenTemplate->m_hMenuShared = NewOpenViewMenu();
		COpenDoc *pOpenDoc = static_cast<COpenDoc *>(theApp.m_pOpenTemplate->CreateNewDocument());
		if (dwFlags)
		{
			pOpenDoc->m_dwFlags[0] = dwFlags[0];
			pOpenDoc->m_dwFlags[1] = dwFlags[1];
			pOpenDoc->m_dwFlags[2] = dwFlags[2];
		}
		pOpenDoc->m_files = tFiles;
		pOpenDoc->m_bRecurse = bRecurse;
		if (infoUnpacker)
			pOpenDoc->m_infoHandler = *infoUnpacker;
		CFrameWnd *pFrame = theApp.m_pOpenTemplate->CreateNewFrame(pOpenDoc, nullptr);
		theApp.m_pOpenTemplate->InitialUpdateFrame(pFrame, pOpenDoc);
		return true;
	}
	else
	{
		// Add trailing '\' for directories if its missing
		if (pathsType == paths::IS_EXISTING_DIR)
		{
			if (!paths::EndsWithSlash(tFiles[0]) && !IsArchiveFile(tFiles[0]))
				tFiles[0] = paths::AddTrailingSlash(tFiles[0]);
			if (!paths::EndsWithSlash(tFiles[1]) && !IsArchiveFile(tFiles[1]))
				tFiles[1] = paths::AddTrailingSlash(tFiles[1]);
			if (tFiles.GetSize() == 3 && !paths::EndsWithSlash(tFiles[2]) && !IsArchiveFile(tFiles[1]))
				tFiles[2] = paths::AddTrailingSlash(tFiles[2]);
		}

		//save the MRU left and right files.
		if (dwFlags)
		{
			if (!(dwFlags[0] & FFILEOPEN_NOMRU))
				addToMru(tFiles[0].c_str(), _T("Files\\Left"));
			if (!(dwFlags[1] & FFILEOPEN_NOMRU))
				addToMru(tFiles[1].c_str(), _T("Files\\Right"));
			if (tFiles.GetSize() == 3 && !(dwFlags[2] & FFILEOPEN_NOMRU))
				addToMru(tFiles[2].c_str(), _T("Files\\Option"));
		}
	}

	CTempPathContext *pTempPathContext = nullptr;
	if (pathsType == paths::IS_EXISTING_DIR)
	{
		DecompressResult res= DecompressArchive(m_hWnd, tFiles);
		if (res.pTempPathContext)
		{
			pathsType = res.pathsType;
			tFiles = res.files;
			pTempPathContext = res.pTempPathContext;
		}
	}

	// Determine if we want a new dirview open, now that we know if it was
	// an archive. Don't open a new dirview if we are comparing files.
	if (pDirDoc == nullptr)
	{
		if (pathsType == paths::IS_EXISTING_DIR)
		{
			CDirDoc::m_nDirsTemp = tFiles.GetSize();
			if (m_pMenus[MENU_DIRVIEW] == nullptr)
				theApp.m_pDirTemplate->m_hMenuShared = NewDirViewMenu();
			pDirDoc = static_cast<CDirDoc*>(theApp.m_pDirTemplate->OpenDocumentFile(nullptr));
		}
		else
		{
			pDirDoc = static_cast<CDirDoc*>(theApp.m_pDirTemplate->CreateNewDocument());
		}
	}

	// open the diff
	if (pathsType == paths::IS_EXISTING_DIR)
	{
		if (pDirDoc != nullptr)
		{
			// Anything that can go wrong inside InitCompare() will yield an
			// exception. There is no point in checking return value.
			pDirDoc->InitCompare(tFiles, bRecurse, pTempPathContext);

			pDirDoc->SetReportFile(sReportFile);
			pDirDoc->SetDescriptions(strDesc);
			pDirDoc->SetTitle(nullptr);
			for (int nIndex = 0; nIndex < tFiles.GetSize(); nIndex++)
				pDirDoc->SetReadOnly(nIndex, bRO[nIndex]);

			pDirDoc->Rescan();
		}
	}
	else
	{
		FileLocation fileloc[3];

		for (int nPane = 0; nPane < tFiles.GetSize(); nPane++)
			fileloc[nPane].setPath(tFiles[nPane]);

		if (!prediffer.empty())
		{
			String strBothFilenames = strutils::join(tFiles.begin(), tFiles.end(), _T("|"));
			pDirDoc->GetPluginManager().SetPrediffer(strBothFilenames, prediffer);
		}

		ShowAutoMergeDoc(pDirDoc, tFiles.GetSize(), fileloc, dwFlags, strDesc, sReportFile,
						 infoUnpacker);
	}

	if (pFiles != nullptr && (!dwFlags || !(dwFlags[0] & FFILEOPEN_NOMRU)))
	{
		String filter = GetOptionsMgr()->GetString(OPT_FILEFILTER_CURRENT);
		AddToRecentDocs(*pFiles, (unsigned *)dwFlags, bRecurse, filter);
	}

	return true;
}

void CMainFrame::UpdateFont(FRAMETYPE frame)
{
	if (frame == FRAME_FOLDER)
	{
		for (auto pDoc : GetAllDirDocs())
		{
			if (pDoc != nullptr)
			{
				CDirView *pView = pDoc->GetMainView();
				if (pView != nullptr)
					pView->SetFont(m_lfDir);
			}
		}
	}
	else
	{
		for (auto pDoc : GetAllMergeDocs())
		{
			CMergeDoc *pMergeDoc = dynamic_cast<CMergeDoc *>(pDoc);
			if (pMergeDoc != nullptr)
				for (auto& pView: pMergeDoc->GetViewList())
					pView->SetFont(m_lfDiff);
		}
	}
}

/**
 * @brief Select font for Merge/Dir view
 *
 * Shows font selection dialog to user, sets current font and saves
 * selected font properties to registry. Selects fon type to active
 * view (Merge/Dir compare). If there is no open views, then font
 * is selected for Merge view (for example user may want to change to
 * unicode font before comparing files).
 *//*
void CMainFrame::OnViewSelectfont()
{
	FRAMETYPE frame = GetFrameType(GetActiveFrame());
	CHOOSEFONT cf = { sizeof CHOOSEFONT };
	LOGFONT *lf = nullptr;
	cf.Flags = CF_INITTOLOGFONTSTRUCT|CF_FORCEFONTEXIST|CF_SCREENFONTS;
	if (frame == FRAME_FILE)
		cf.Flags |= CF_FIXEDPITCHONLY; // Only fixed-width fonts for merge view

	// CF_FIXEDPITCHONLY = 0x00004000L
	// in case you are a developer and want to disable it to test with, eg, a Chinese capable font
	if (frame == FRAME_FOLDER)
		lf = &m_lfDir;
	else
		lf = &m_lfDiff;

	cf.lpLogFont = lf;

	if (ChooseFont(&cf))
	{
		Options::Font::Save(GetOptionsMgr(), frame == FRAME_FOLDER ? OPT_FONT_DIRCMP : OPT_FONT_FILECMP, lf, true);
		UpdateFont(frame);
	}
}

/**
 * @brief Use default font for active view type
 *
 * Disable user-selected font for active view type (Merge/Dir compare).
 * If there is no open views, then Merge view font is changed.
 *//*
void CMainFrame::OnViewUsedefaultfont()
{
	FRAMETYPE frame = GetFrameType(GetActiveFrame());

	if (frame == FRAME_FOLDER)
	{
		Options::Font::Reset(GetOptionsMgr(), OPT_FONT_DIRCMP);
		m_lfDir = Options::Font::Load(GetOptionsMgr(), OPT_FONT_DIRCMP);
		Options::Font::Save(GetOptionsMgr(), OPT_FONT_DIRCMP, &m_lfDir, false);
	}
	else
	{
		Options::Font::Reset(GetOptionsMgr(), OPT_FONT_FILECMP);
		m_lfDiff = Options::Font::Load(GetOptionsMgr(), OPT_FONT_FILECMP);
		Options::Font::Save(GetOptionsMgr(), OPT_FONT_FILECMP, &m_lfDiff, false);
	}

	UpdateFont(frame);
}

/**
 * @brief Update any resources necessary after a GUI language change
 *//*
void CMainFrame::UpdateResources()
{
	m_wndStatusBar.SetPaneText(0, theApp.LoadString(AFX_IDS_IDLEMESSAGE).c_str());

	for (auto pDoc : GetAllDirDocs())
		pDoc->UpdateResources();
	for (auto pDoc : GetAllMergeDocs())
		pDoc->UpdateResources();
	for (auto pDoc : GetAllOpenDocs())
		pDoc->UpdateResources();
}

/*
void CMainFrame::ActivateFrame(int nCmdShow)
{
	if (!m_bFirstTime)
	{
		CMDIFrameWnd::ActivateFrame(nCmdShow);
		return;
	}

	m_bFirstTime = false;

	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wp);
	wp.rcNormalPosition.left=theApp.GetProfileInt(_T("Settings"), _T("MainLeft"),0);
	wp.rcNormalPosition.top=theApp.GetProfileInt(_T("Settings"), _T("MainTop"),0);
	wp.rcNormalPosition.right=theApp.GetProfileInt(_T("Settings"), _T("MainRight"),0);
	wp.rcNormalPosition.bottom=theApp.GetProfileInt(_T("Settings"), _T("MainBottom"),0);
	if (nCmdShow != SW_MINIMIZE && theApp.GetProfileInt(_T("Settings"), _T("MainMax"), FALSE))
		wp.showCmd = SW_MAXIMIZE;
	else
		wp.showCmd = nCmdShow;

	CRect dsk_rc,rc(wp.rcNormalPosition);

	dsk_rc.left = ::GetSystemMetrics(SM_XVIRTUALSCREEN);
	dsk_rc.top = ::GetSystemMetrics(SM_YVIRTUALSCREEN);
	dsk_rc.right = dsk_rc.left + ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
	dsk_rc.bottom = dsk_rc.top + ::GetSystemMetrics(SM_CYVIRTUALSCREEN);
	if (rc.Width() != 0 && rc.Height() != 0)
	{
		// Ensure top-left corner is on visible area,
		// 20 points margin is added to prevent "lost" window
		CPoint ptTopLeft(rc.TopLeft());
		ptTopLeft += CPoint(20, 20);

		if (dsk_rc.PtInRect(ptTopLeft))
			SetWindowPlacement(&wp);
		else
			CMDIFrameWnd::ActivateFrame(nCmdShow);
	}
	else
		CMDIFrameWnd::ActivateFrame(nCmdShow);
}

/**
 * @brief Called when mainframe is about to be closed.
 * This function is called when mainframe is to be closed (not for
 * file/compare windows.
 *//*
void CMainFrame::OnClose()
{
	if (theApp.GetActiveOperations())
		return;

	// Check if there are multiple windows open and ask for closing them
	bool bAskClosing = GetOptionsMgr()->GetBool(OPT_ASK_MULTIWINDOW_CLOSE);
	if (bAskClosing)
	{
		bool quit = AskCloseConfirmation();
		if (!quit)
			return;
	}

	// Save last selected filter
	String filter = theApp.m_pGlobalFileFilter->GetFilterNameOrMask();
	GetOptionsMgr()->SaveOption(OPT_FILEFILTER_CURRENT, filter);

	// save main window position
	WINDOWPLACEMENT wp;
	wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wp);
	theApp.WriteProfileInt(_T("Settings"), _T("MainLeft"),wp.rcNormalPosition.left);
	theApp.WriteProfileInt(_T("Settings"), _T("MainTop"),wp.rcNormalPosition.top);
	theApp.WriteProfileInt(_T("Settings"), _T("MainRight"),wp.rcNormalPosition.right);
	theApp.WriteProfileInt(_T("Settings"), _T("MainBottom"),wp.rcNormalPosition.bottom);
	theApp.WriteProfileInt(_T("Settings"), _T("MainMax"), (wp.showCmd == SW_MAXIMIZE));

	// Close Non-Document/View frame with confirmation
	CMDIChildWnd *pChild = static_cast<CMDIChildWnd *>(CWnd::FromHandle(m_hWndMDIClient)->GetWindow(GW_CHILD));
	while (pChild != nullptr)
	{
		CMDIChildWnd *pNextChild = static_cast<CMDIChildWnd *>(pChild->GetWindow(GW_HWNDNEXT));
		if (GetFrameType(pChild) == FRAME_IMGFILE)
		{
			if (!static_cast<CImgMergeFrame *>(pChild)->CloseNow())
				return;
		}
		pChild = pNextChild;
	}

	CMDIFrameWnd::OnClose();
}

/**
 * @brief Utility function to update CSuperComboBox format MRU
 *//*
void CMainFrame::addToMru(LPCTSTR szItem, LPCTSTR szRegSubKey, UINT nMaxItems)
{
	std::vector<CString> list;
	CString s;
	UINT cnt = AfxGetApp()->GetProfileInt(szRegSubKey, _T("Count"), 0);
	list.push_back(szItem);
	for (UINT i=0 ; i<cnt; ++i)
	{
		s = AfxGetApp()->GetProfileString(szRegSubKey, strutils::format(_T("Item_%d"), i).c_str());
		if (s != szItem)
			list.push_back(s);
	}
	cnt = list.size() > nMaxItems ? nMaxItems : static_cast<UINT>(list.size());
	for (UINT i=0 ; i<cnt; ++i)
		AfxGetApp()->WriteProfileString(szRegSubKey, strutils::format(_T("Item_%d"), i).c_str(), list[i]);
	// update count
	AfxGetApp()->WriteProfileInt(szRegSubKey, _T("Count"), cnt);
}

void CMainFrame::ApplyDiffOptions()
{
	for (auto pMergeDoc : GetAllMergeDocs())
	{
		// Re-read MergeDoc settings (also updates view settings)
		// and rescan using new options
		pMergeDoc->RefreshOptions();
		pMergeDoc->FlushAndRescan(true);
	}
}

/// Get list of OpenDocs (documents underlying edit sessions)
OpenDocList &CMainFrame::GetAllOpenDocs()
{
	return static_cast<OpenDocList &>(GetDocList(theApp.m_pOpenTemplate));
}

/// Get list of MergeDocs (documents underlying edit sessions)
MergeDocList &CMainFrame::GetAllMergeDocs()
{
	return static_cast<MergeDocList &>(GetDocList(theApp.m_pDiffTemplate));
}

/// Get list of DirDocs (documents underlying a scan)
DirDocList &CMainFrame::GetAllDirDocs()
{
	return static_cast<DirDocList &>(GetDocList(theApp.m_pDirTemplate));
}

/// Get list of HexMergeDocs (documents underlying edit sessions)
HexMergeDocList &CMainFrame::GetAllHexMergeDocs()
{
	return static_cast<HexMergeDocList &>(GetDocList(theApp.m_pHexMergeTemplate));
}

/**
 * @brief Obtain a merge doc to display a difference in files.
 * @return Pointer to CMergeDoc to use.
 *//*
template<class DocClass>
DocClass * GetMergeDocForDiff(CMultiDocTemplate *pTemplate, CDirDoc *pDirDoc, int nFiles, bool bMakeVisible)
{
	// Create a new merge doc
	DocClass::m_nBuffersTemp = nFiles;
	DocClass *pMergeDoc = static_cast<DocClass*>(pTemplate->OpenDocumentFile(nullptr, bMakeVisible));
	if (pMergeDoc != nullptr)
	{
		pDirDoc->AddMergeDoc(pMergeDoc);
		pMergeDoc->SetDirDoc(pDirDoc);
	}
	return pMergeDoc;
}

// Clear the item count in the main status pane
void CMainFrame::ClearStatusbarItemCount()
{
	m_wndStatusBar.SetPaneText(2, _T(""));
}

/**
 * @brief Generate patch from files selected.
 *
 * Creates a patch from selected files in active directory compare, or
 * active file compare. Files in file compare must be saved before
 * creating a patch.
 *//*
void CMainFrame::OnToolsGeneratePatch()
{
	CPatchTool patcher;
	patcher.CreatePatch();
}

void CMainFrame::OnDropFiles(const std::vector<String>& dropped_files)
{
	PathContext tFiles(dropped_files);
	const size_t fileCount = tFiles.GetSize();

	// If Ctrl pressed, do recursive compare
	bool recurse = !!::GetAsyncKeyState(VK_CONTROL) || GetOptionsMgr()->GetBool(OPT_CMP_INCLUDE_SUBDIRS);

	// If user has <Shift> pressed with one file selected,
	// assume it is an archive and set filenames to same
	if (::GetAsyncKeyState(VK_SHIFT) < 0 && fileCount == 1)
	{
		tFiles.SetRight(tFiles[0]);
	}

	// Check if they dropped a project file
	DWORD dwFlags[3] = {FFILEOPEN_NONE, FFILEOPEN_NONE, FFILEOPEN_NONE};
	if (fileCount == 1)
	{
		if (theApp.IsProjectFile(tFiles[0]))
		{
			theApp.LoadAndOpenProjectFile(tFiles[0]);
			return;
		}
		if (IsConflictFile(tFiles[0]))
		{
			DoOpenConflict(tFiles[0], nullptr, true);
			return;
		}
	}

	DoFileOpen(&tFiles, dwFlags, nullptr, _T(""), recurse);
}

void CMainFrame::OnPluginUnpackMode(UINT nID )
{
	switch (nID)
	{
		case ID_UNPACK_MANUAL:
			FileTransform::g_UnpackerMode = PLUGIN_MANUAL;
			break;
		case ID_UNPACK_AUTO:
			FileTransform::g_UnpackerMode = PLUGIN_AUTO;
			break;
	}
	GetOptionsMgr()->SaveOption(OPT_PLUGINS_UNPACKER_MODE, FileTransform::g_UnpackerMode);
}

void CMainFrame::OnUpdatePluginUnpackMode(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetOptionsMgr()->GetBool(OPT_PLUGINS_ENABLED));

	if (pCmdUI->m_nID == ID_UNPACK_MANUAL)
		pCmdUI->SetRadio(PLUGIN_MANUAL == FileTransform::g_UnpackerMode);
	if (pCmdUI->m_nID == ID_UNPACK_AUTO)
		pCmdUI->SetRadio(PLUGIN_AUTO == FileTransform::g_UnpackerMode);
}
void CMainFrame::OnPluginPrediffMode(UINT nID )
{
	switch (nID)
	{
		case ID_PREDIFFER_MANUAL:
			FileTransform::g_PredifferMode = PLUGIN_MANUAL;
			break;
		case ID_PREDIFFER_AUTO:
			FileTransform::g_PredifferMode = PLUGIN_AUTO;
			break;
	}
	PrediffingInfo infoPrediffer;
	for (auto pMergeDoc : GetAllMergeDocs())
		pMergeDoc->SetPrediffer(&infoPrediffer);
	for (auto pDirDoc : GetAllDirDocs())
		pDirDoc->GetPluginManager().SetPrediffSettingAll(FileTransform::g_PredifferMode);
	GetOptionsMgr()->SaveOption(OPT_PLUGINS_PREDIFFER_MODE, FileTransform::g_PredifferMode);
}

void CMainFrame::OnUpdatePluginPrediffMode(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetOptionsMgr()->GetBool(OPT_PLUGINS_ENABLED));

	if (pCmdUI->m_nID == ID_PREDIFFER_MANUAL)
		pCmdUI->SetRadio(PLUGIN_MANUAL == FileTransform::g_PredifferMode);
	if (pCmdUI->m_nID == ID_PREDIFFER_AUTO)
		pCmdUI->SetRadio(PLUGIN_AUTO == FileTransform::g_PredifferMode);
}
/**
 * @brief Called when "Reload Plugins" item is updated
 *//*
void CMainFrame::OnUpdateReloadPlugins(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetOptionsMgr()->GetBool(OPT_PLUGINS_ENABLED));
}

 /*
void CMainFrame::OnReloadPlugins()
{
	// delete all script interfaces
	// (interfaces will be created again automatically when WinMerge needs them)
	CAllThreadsScripts::GetActiveSet()->FreeAllScripts();

	// update the editor scripts submenu
	HMENU scriptsSubmenu = GetScriptsSubmenu(m_hMenuDefault);
	if (scriptsSubmenu != nullptr)
		CMergeEditView::createScriptsSubmenu(scriptsSubmenu);
	UpdatePrediffersMenu();
}

/** @brief Return active merge edit view, if can figure it out/is available */
/*CMergeEditView * CMainFrame::GetActiveMergeEditView()
{
	// NB: GetActiveDocument does not return the Merge Doc
	//     even when the merge edit view is in front
	// NB: CChildFrame::GetActiveView returns `nullptr` when location view active
	// So we have this rather complicated logic to try to get a merge edit view
	// We look at the front child window, which should be a frame
	// and we can get a MergeEditView from it, if it is a CChildFrame
	// (DirViews use a different frame type)
	CChildFrame * pFrame = dynamic_cast<CChildFrame *>(GetActiveFrame());
	if (pFrame == nullptr) return nullptr;
	// Try to get the active MergeEditView (ie, left or right)
	if (pFrame->GetActiveView() != nullptr && pFrame->GetActiveView()->IsKindOf(RUNTIME_CLASS(CMergeEditView)))
	{
		return dynamic_cast<CMergeEditView *>(pFrame->GetActiveView());
	}
	return pFrame->GetMergeDoc()->GetActiveMergeView();
}

void CMainFrame::UpdatePrediffersMenu()
{
	CMenu* menu = GetMenu();
	if (menu == nullptr)
	{
		return;
	}

	HMENU hMainMenu = menu->m_hMenu;
	HMENU prediffersSubmenu = GetPrediffersSubmenu(hMainMenu);
	if (prediffersSubmenu != nullptr)
	{
		CMergeEditView * pEditView = GetActiveMergeEditView();
		if (pEditView != nullptr)
			pEditView->createPrediffersSubmenu(prediffersSubmenu);
		else
		{
			// no view or dir view : display an empty submenu
			int i = GetMenuItemCount(prediffersSubmenu);
			while (i --)
				::DeleteMenu(prediffersSubmenu, 0, MF_BYPOSITION);
			::AppendMenu(prediffersSubmenu, MF_SEPARATOR, 0, nullptr);
		}
	}
}

/**
 * @brief Save WinMerge configuration and info to file
 *//*
void CMainFrame::OnSaveConfigData()
{
	CConfigLog configLog;
	String sError;

	if (configLog.WriteLogFile(sError))
	{
		String sFileName = configLog.GetFileName();
		theApp.OpenFileToExternalEditor(sFileName);
	}
	else
	{
		String sFileName = configLog.GetFileName();
		String msg = strutils::format_string2(_("Cannot open file\n%1\n\n%2"), sFileName, sError);
		AfxMessageBox(msg.c_str(), MB_OK | MB_ICONSTOP);
	}
}

/**
 * @brief Open two new empty docs, 'Scratchpads'
 *
 * Allows user to open two empty docs, to paste text to
 * compare from clipboard.
 * @note File filenames are set emptys and filedescriptors
 * are loaded from resource.
 * @sa CMergeDoc::OpenDocs()
 * @sa CMergeDoc::TrySaveAs()
 *//*
void CMainFrame::FileNew(int nPanes)
{
	CDirDoc *pDirDoc = static_cast<CDirDoc*>(theApp.m_pDirTemplate->CreateNewDocument());

	// Load emptyfile descriptors and open empty docs
	// Use default codepage
	DWORD dwFlags[3] = {0, 0, 0};
	String strDesc[3];
	FileLocation fileloc[3];
	if (nPanes == 2)
	{
		strDesc[0] = _("Untitled left");
		strDesc[1] = _("Untitled right");
		fileloc[0].encoding.SetCodepage(ucr::getDefaultCodepage());
		fileloc[1].encoding.SetCodepage(ucr::getDefaultCodepage());
		ShowMergeDoc(pDirDoc, 2, fileloc, dwFlags, strDesc);
	}
	else
	{
		strDesc[0] = _("Untitled left");
		strDesc[1] = _("Untitled middle");
		strDesc[2] = _("Untitled right");
		fileloc[0].encoding.SetCodepage(ucr::getDefaultCodepage());
		fileloc[1].encoding.SetCodepage(ucr::getDefaultCodepage());
		fileloc[2].encoding.SetCodepage(ucr::getDefaultCodepage());
		ShowMergeDoc(pDirDoc, 3, fileloc, dwFlags, strDesc);
	}
}

/**
 * @brief Open two new empty docs, 'Scratchpads'
 *
 * Allows user to open two empty docs, to paste text to
 * compare from clipboard.
 * @note File filenames are set emptys and filedescriptors
 * are loaded from resource.
 * @sa CMergeDoc::OpenDocs()
 * @sa CMergeDoc::TrySaveAs()
 *//*
void CMainFrame::OnFileNew()
{
	FileNew(2);
}

void CMainFrame::OnFileNew3()
{
	FileNew(3);
}

/**
 * @brief Open Filters dialog
 *//*
void CMainFrame::OnToolsFilters()
{
	String title = _("Filters");
	CPropertySheet sht(title.c_str());
	LineFiltersDlg lineFiltersDlg;
	FileFiltersDlg fileFiltersDlg;
	vector<FileFilterInfo> fileFilters;
	std::unique_ptr<LineFiltersList> lineFilters(new LineFiltersList());
	String selectedFilter;
	const String origFilter = theApp.m_pGlobalFileFilter->GetFilterNameOrMask();
	sht.AddPage(&fileFiltersDlg);
	sht.AddPage(&lineFiltersDlg);
	sht.m_psh.dwFlags |= PSH_NOAPPLYNOW; // Hide 'Apply' button since we don't need it

	// Make sure all filters are up-to-date
	theApp.m_pGlobalFileFilter->ReloadUpdatedFilters();

	theApp.m_pGlobalFileFilter->GetFileFilters(&fileFilters, selectedFilter);
	fileFiltersDlg.SetFilterArray(&fileFilters);
	fileFiltersDlg.SetSelected(selectedFilter);
	const bool lineFiltersEnabledOrig = GetOptionsMgr()->GetBool(OPT_LINEFILTER_ENABLED);
	lineFiltersDlg.m_bIgnoreRegExp = lineFiltersEnabledOrig;

	lineFilters->CloneFrom(theApp.m_pLineFilters.get());
	lineFiltersDlg.SetList(lineFilters.get());

	if (sht.DoModal() == IDOK)
	{
		String strNone = _("<None>");
		String path = fileFiltersDlg.GetSelected();
		if (path.find(strNone) != String::npos)
		{
			// Don't overwrite mask we already have
			if (!theApp.m_pGlobalFileFilter->IsUsingMask())
			{
				String sFilter(_T("*.*"));
				theApp.m_pGlobalFileFilter->SetFilter(sFilter);
				GetOptionsMgr()->SaveOption(OPT_FILEFILTER_CURRENT, sFilter);
			}
		}
		else
		{
			theApp.m_pGlobalFileFilter->SetFileFilterPath(path);
			theApp.m_pGlobalFileFilter->UseMask(false);
			String sFilter = theApp.m_pGlobalFileFilter->GetFilterNameOrMask();
			GetOptionsMgr()->SaveOption(OPT_FILEFILTER_CURRENT, sFilter);
		}
		bool linefiltersEnabled = lineFiltersDlg.m_bIgnoreRegExp;
		GetOptionsMgr()->SaveOption(OPT_LINEFILTER_ENABLED, linefiltersEnabled);

		// Check if compare documents need rescanning
		bool bFileCompareRescan = false;
		bool bFolderCompareRescan = false;
		CFrameWnd * pFrame = GetActiveFrame();
		FRAMETYPE frame = GetFrameType(pFrame);
		if (frame == FRAME_FILE)
		{
			if (lineFiltersEnabledOrig != linefiltersEnabled ||
				!theApp.m_pLineFilters->Compare(lineFilters.get()))
			{
				bFileCompareRescan = true;
			}
		}
		else if (frame == FRAME_FOLDER)
		{
			const String newFilter = theApp.m_pGlobalFileFilter->GetFilterNameOrMask();
			if (lineFiltersEnabledOrig != linefiltersEnabled ||
				!theApp.m_pLineFilters->Compare(lineFilters.get()) || origFilter != newFilter)
			{
				int res = LangMessageBox(IDS_FILTERCHANGED, MB_ICONWARNING | MB_YESNO);
				if (res == IDYES)
					bFolderCompareRescan = true;
			}
		}

		// Save new filters before (possibly) rescanning
		theApp.m_pLineFilters->CloneFrom(lineFilters.get());
		theApp.m_pLineFilters->SaveFilters();

		if (bFileCompareRescan)
		{
			for (auto pMergeDoc : GetAllMergeDocs())
				pMergeDoc->FlushAndRescan(true);
		}
		else if (bFolderCompareRescan)
		{
			for (auto pDirDoc : GetAllDirDocs())
				pDirDoc->Rescan();
		}
	}
}

/**
 * @brief Open Filters dialog.
 *//*
void CMainFrame::SelectFilter()
{
	OnToolsFilters();
}

/**
 * @brief Closes application with ESC.
 *
 * Application is closed if:
 * - 'Close Windows with ESC' option is enabled and
 *    there is no open document windows
 * - '-e' commandline switch is given
 *//*
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// Check if we got 'ESC pressed' -message
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		if (theApp.m_bEscShutdown && m_wndTabBar.GetItemCount() <= 1)
		{
			AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_APP_EXIT);
			return TRUE;
		}
		else if (GetOptionsMgr()->GetBool(OPT_CLOSE_WITH_ESC) && m_wndTabBar.GetItemCount() == 0)
		{
			AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_APP_EXIT);
			return FALSE;
		}
	}
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

/**
 * @brief Show/hide statusbar.
 *//*
void CMainFrame::OnViewStatusBar()
{
	bool bShow = !GetOptionsMgr()->GetBool(OPT_SHOW_STATUSBAR);
	GetOptionsMgr()->SaveOption(OPT_SHOW_STATUSBAR, bShow);

	CMDIFrameWnd::ShowControlBar(&m_wndStatusBar, bShow, 0);
}

/**
 * @brief Updates "Show Tabbar" menuitem.
 *//*
void CMainFrame::OnUpdateViewTabBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetOptionsMgr()->GetBool(OPT_SHOW_TABBAR));
}

/**
 * @brief Show/hide tabbar.
 *//*
void CMainFrame::OnViewTabBar()
{
	bool bShow = !GetOptionsMgr()->GetBool(OPT_SHOW_TABBAR);
	GetOptionsMgr()->SaveOption(OPT_SHOW_TABBAR, bShow);

	CMDIFrameWnd::ShowControlBar(&m_wndTabBar, bShow, 0);
}

/**
 * @brief Updates "Automatically Resize Panes" menuitem.
 *//*
void CMainFrame::OnUpdateResizePanes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetOptionsMgr()->GetBool(OPT_RESIZE_PANES));
}


/**
 * @brief Enable/disable automatic pane resizing.
 *//*
void CMainFrame::OnResizePanes()
{
	bool bResize = !GetOptionsMgr()->GetBool(OPT_RESIZE_PANES);
	GetOptionsMgr()->SaveOption(OPT_RESIZE_PANES, bResize);
	// TODO: Introduce a common merge frame superclass?
	CFrameWnd *pActiveFrame = GetActiveFrame();
	if (CChildFrame *pFrame = DYNAMIC_DOWNCAST(CChildFrame, pActiveFrame))
	{
		pFrame->UpdateAutoPaneResize();
		if (bResize)
			pFrame->UpdateSplitter();
	}
	else if (CHexMergeFrame *pFrame1 = DYNAMIC_DOWNCAST(CHexMergeFrame, pActiveFrame))
	{
		pFrame1->UpdateAutoPaneResize();
		if (bResize)
			pFrame1->UpdateSplitter();
	}
}

/**
 * @brief Open project-file.
 *//*
void CMainFrame::OnFileOpenProject()
{
	String sFilepath;

	// get the default projects path
	String strProjectPath = GetOptionsMgr()->GetString(OPT_PROJECTS_PATH);
	if (!SelectFile(GetSafeHwnd(), sFilepath, true, strProjectPath.c_str(), _T(""),
					_("WinMerge Project Files (*.WinMerge)|*.WinMerge||")))
		return;

	strProjectPath = paths::GetParentPath(sFilepath);
	// store this as the new project path
	GetOptionsMgr()->SaveOption(OPT_PROJECTS_PATH, strProjectPath);

	theApp.LoadAndOpenProjectFile(sFilepath.c_str());
}

/**
 * @brief Receive command line from another instance.
 *
 * This function receives command line when only single-instance
 * is allowed. New instance tried to start sends its command line
 * to here so we can open paths it was meant to.
 *//*
LRESULT CMainFrame::OnCopyData(WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT *pCopyData = (COPYDATASTRUCT*)lParam;
	LPCTSTR pchData = (LPCTSTR)pCopyData->lpData;
	// Bail out if data isn't zero-terminated
	DWORD cchData = pCopyData->cbData / sizeof(TCHAR);
	if (cchData == 0 || pchData[cchData - 1] != _T('\0'))
		return FALSE;
	ReplyMessage(TRUE);
	MergeCmdLineInfo cmdInfo(pchData);
	theApp.ApplyCommandLineConfigOptions(cmdInfo);
	theApp.ParseArgsAndDoOpen(cmdInfo, this);
	return TRUE;
}

LRESULT CMainFrame::OnUser1(WPARAM wParam, LPARAM lParam)
{
	CFrameWnd * pFrame = GetActiveFrame();
	if (pFrame != nullptr)
	{
		IMergeDoc *pMergeDoc = dynamic_cast<IMergeDoc *>(pFrame->GetActiveDocument());
		if (pMergeDoc == nullptr)
			pMergeDoc = dynamic_cast<IMergeDoc *>(pFrame);
		if (pMergeDoc != nullptr)
			pMergeDoc->CheckFileChanged();
	}
	return 0;
}

/**
 * @brief Close all open windows.
 *
 * Asks about saving unsaved files and then closes all open windows.
 *//*
void CMainFrame::OnWindowCloseAll()
{
	CMDIChildWnd *pChild = MDIGetActive();
	while (pChild != nullptr)
	{
		CDocument* pDoc;
		if ((pDoc = pChild->GetActiveDocument()) != nullptr)
		{
			if (!pDoc->SaveModified())
				return;
			pDoc->OnCloseDocument();
		}
		else if (GetFrameType(pChild) == FRAME_IMGFILE)
		{
			if (!static_cast<CImgMergeFrame *>(pChild)->CloseNow())
				return;
		}
		else
		{
			pChild->DestroyWindow();
		}
		pChild = MDIGetActive();
	}
	return;
}

/**
 * @brief Enables Window/Close All item if there are open windows.
 *//*
void CMainFrame::OnUpdateWindowCloseAll(CCmdUI* pCmdUI)
{
	const MergeDocList &mergedocs = GetAllMergeDocs();
	if (!mergedocs.IsEmpty())
	{
		pCmdUI->Enable(TRUE);
		return;
	}

	const DirDocList &dirdocs = GetAllDirDocs();
	pCmdUI->Enable(!dirdocs.IsEmpty());
}

/**
 * @brief Access to the singleton main frame (where we have some globals)
 *//*
CMainFrame * GetMainFrame()
{
	CWnd * mainwnd = AfxGetMainWnd();
	ASSERT(mainwnd != nullptr);
	CMainFrame *pMainframe = dynamic_cast<CMainFrame*>(mainwnd);
	ASSERT(pMainframe != nullptr);
	return pMainframe;
}

/**
 * @brief Opens dialog for user to Load, edit and save project files.
 * This dialog gets current compare paths and filter (+other properties
 * possible in project files) and initializes the dialog with them.
 *//*
void CMainFrame::OnSaveProject()
{
	if (m_pMenus[MENU_OPENVIEW] == nullptr)
		theApp.m_pOpenTemplate->m_hMenuShared = NewOpenViewMenu();
	COpenDoc *pOpenDoc = static_cast<COpenDoc *>(theApp.m_pOpenTemplate->CreateNewDocument());

	PathContext paths;
	CFrameWnd * pFrame = GetActiveFrame();
	FRAMETYPE frame = GetFrameType(pFrame);

	if (frame == FRAME_FILE)
	{
		CMergeDoc * pMergeDoc = static_cast<CMergeDoc *>(pFrame->GetActiveDocument());
		pOpenDoc->m_files = pMergeDoc->m_filePaths;
		for (size_t pane = 0; pane < pOpenDoc->m_files.size(); ++pane)
			pOpenDoc->m_dwFlags[pane] = FFILEOPEN_PROJECT | (pMergeDoc->m_ptBuf[pane]->GetReadOnly() ? FFILEOPEN_PROJECT : 0);
		pOpenDoc->m_bRecurse = GetOptionsMgr()->GetBool(OPT_CMP_INCLUDE_SUBDIRS);
		pOpenDoc->m_strExt = theApp.m_pGlobalFileFilter->GetFilterNameOrMask();
	}
	else if (frame == FRAME_FOLDER)
	{
		// Get paths currently in compare
		const CDirDoc * pDoc = static_cast<const CDirDoc*>(pFrame->GetActiveDocument());
		const CDiffContext& ctxt = pDoc->GetDiffContext();

		// Set-up the dialog
		for (int pane = 0; pane < ctxt.GetCompareDirs(); ++pane)
		{
			pOpenDoc->m_dwFlags[pane] = FFILEOPEN_PROJECT | (pDoc->GetReadOnly(pane) ? FFILEOPEN_READONLY : 0);
			pOpenDoc->m_files.SetPath(pane, paths::AddTrailingSlash(ctxt.GetNormalizedPath(pane)));
		}
		pOpenDoc->m_bRecurse = ctxt.m_bRecursive;
		pOpenDoc->m_strExt = static_cast<FileFilterHelper *>(ctxt.m_piFilterGlobal)->GetFilterNameOrMask();
	}

	CFrameWnd *pOpenFrame = theApp.m_pOpenTemplate->CreateNewFrame(pOpenDoc, nullptr);
	theApp.m_pOpenTemplate->InitialUpdateFrame(pOpenFrame, pOpenDoc);
}

/**
 * @brief Start flashing window if window is inactive.
 *//*
void CMainFrame::StartFlashing()
{
	CWnd * activeWindow = GetActiveWindow();
	if (activeWindow != this)
		FlashWindowEx(FLASHW_ALL | FLASHW_TIMERNOFG, 0, 0);
}

#if _MFC_VER > 0x0600
void CMainFrame::OnActivateApp(BOOL bActive, DWORD dwThreadID)
#else
void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask)
#endif
{
#if _MFC_VER > 0x0600
	CMDIFrameWnd::OnActivateApp(bActive, dwThreadID);
#else
	CMDIFrameWnd::OnActivateApp(bActive, hTask);
#endif

	CFrameWnd * pFrame = GetActiveFrame();
	if (pFrame != nullptr)
	{
		IMergeDoc *pMergeDoc = dynamic_cast<IMergeDoc *>(pFrame->GetActiveDocument());
		if (pMergeDoc == nullptr)
			pMergeDoc = dynamic_cast<IMergeDoc *>(pFrame);
		if (pMergeDoc != nullptr)
			PostMessage(WM_USER+1);
	}
}

BOOL CMainFrame::CreateToolbar()
{
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		return FALSE;
	}

	if (!m_wndReBar.Create(this))
	{
		return FALSE;
	}

	VERIFY(m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT|TBSTYLE_TRANSPARENT));

	// Remove this if you don't want tool tips or a resizable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
							 CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);

	m_wndReBar.AddBar(&m_wndToolBar);

	LoadToolbarImages();

	UINT nID, nStyle;
	int iImage;
	int index = m_wndToolBar.GetToolBarCtrl().CommandToIndex(ID_OPTIONS);
	m_wndToolBar.GetButtonInfo(index, nID, nStyle, iImage);
	nStyle |= TBSTYLE_DROPDOWN;
	m_wndToolBar.SetButtonInfo(index, nID, nStyle, iImage);

	if (!GetOptionsMgr()->GetBool(OPT_SHOW_TOOLBAR))
	{
		CMDIFrameWnd::ShowControlBar(&m_wndToolBar, false, 0);
	}

	return TRUE;
}

/** @brief Load toolbar images from the resource. *//*
void CMainFrame::LoadToolbarImages()
{
	const int toolbarSize = 16 << GetOptionsMgr()->GetInt(OPT_TOOLBAR_SIZE);
	CToolBarCtrl& BarCtrl = m_wndToolBar.GetToolBarCtrl();

	m_ToolbarImages[TOOLBAR_IMAGES_ENABLED].DeleteImageList();
	m_ToolbarImages[TOOLBAR_IMAGES_DISABLED].DeleteImageList();
	CSize sizeButton(0, 0);

	LoadToolbarImageList(toolbarSize,
						 toolbarSize <= 16 ? IDB_TOOLBAR_ENABLED : IDB_TOOLBAR_ENABLED32,
						 toolbarSize <= 16 ? IDB_TOOLBAR_ENABLED_MASK : IDB_TOOLBAR_ENABLED_MASK32,
						 false, m_ToolbarImages[TOOLBAR_IMAGES_ENABLED]);
	LoadToolbarImageList(toolbarSize,
						 toolbarSize <= 16 ? IDB_TOOLBAR_ENABLED : IDB_TOOLBAR_ENABLED32,
						 toolbarSize <= 16 ? IDB_TOOLBAR_ENABLED_MASK : IDB_TOOLBAR_ENABLED_MASK32,
						 true, m_ToolbarImages[TOOLBAR_IMAGES_DISABLED]);
	sizeButton = CSize(toolbarSize + 8, toolbarSize + 8);

	BarCtrl.SetButtonSize(sizeButton);
	BarCtrl.SetImageList(&m_ToolbarImages[TOOLBAR_IMAGES_ENABLED]);
	BarCtrl.SetDisabledImageList(&m_ToolbarImages[TOOLBAR_IMAGES_DISABLED]);
	m_ToolbarImages[TOOLBAR_IMAGES_ENABLED].Detach();
	m_ToolbarImages[TOOLBAR_IMAGES_DISABLED].Detach();

	// resize the rebar.
	REBARBANDINFO rbbi = { sizeof REBARBANDINFO };
	rbbi.fMask = RBBIM_CHILDSIZE;
	rbbi.cyMinChild = sizeButton.cy;
	m_wndReBar.GetReBarCtrl().SetBandInfo(0, &rbbi);
}


/**
 * @brief Load a transparent 24-bit color image list.
 *//*
static void LoadHiColImageList(UINT nIDResource, UINT nIDResourceMask, int nWidth, int nHeight, int nCount, bool bGrayscale, CImageList& ImgList)
{
	CBitmap bm, bmMask;
	bm.Attach(LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDResource), IMAGE_BITMAP, nWidth * nCount, nHeight, LR_DEFAULTCOLOR));
	bmMask.Attach(LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDResourceMask), IMAGE_BITMAP, nWidth * nCount, nHeight, LR_MONOCHROME));
	if (bGrayscale)
		GrayScale(&bm);
	VERIFY(ImgList.Create(nWidth, nHeight, ILC_COLORDDB|ILC_MASK, nCount, 0));
	int nIndex = ImgList.Add(&bm, &bmMask);
	ASSERT(-1 != nIndex);
}

/**
 * @brief Load toolbar image list.
 *//*
static void LoadToolbarImageList(int imageWidth, UINT nIDResource, UINT nIDResourceMask, bool bGrayscale,
								 CImageList& ImgList)
{
	const int ImageCount = 22;
	const int imageHeight = imageWidth - 1;
	LoadHiColImageList(nIDResource, nIDResourceMask, imageWidth, imageHeight, ImageCount, bGrayscale, ImgList);
}

/**
 * @brief Called when the document title is modified.
 *//*
void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CFrameWnd::OnUpdateFrameTitle(bAddToTitle);

	if (m_wndTabBar.m_hWnd != nullptr)
		m_wndTabBar.UpdateTabs();
}

/** @brief Show none/small/big/huge toolbar. *//*
void CMainFrame::OnToolbarSize(UINT id)
{
	if (id == ID_TOOLBAR_NONE)
	{
		GetOptionsMgr()->SaveOption(OPT_SHOW_TOOLBAR, false);
		CMDIFrameWnd::ShowControlBar(&m_wndToolBar, false, 0);
	}
	else
	{
		GetOptionsMgr()->SaveOption(OPT_SHOW_TOOLBAR, true);
		GetOptionsMgr()->SaveOption(OPT_TOOLBAR_SIZE, id - ID_TOOLBAR_SMALL);

		LoadToolbarImages();

		CMDIFrameWnd::ShowControlBar(&m_wndToolBar, true, 0);
	}
}

/** @brief Show none/small/big/huge toolbar. *//*
void CMainFrame::OnUpdateToolbarSize(CCmdUI *pCmdUI)
{
	if (!GetOptionsMgr()->GetBool(OPT_SHOW_TOOLBAR))
		pCmdUI->SetRadio(pCmdUI->m_nID == ID_TOOLBAR_NONE);
	else
		pCmdUI->SetRadio((pCmdUI->m_nID - ID_TOOLBAR_SMALL) == static_cast<UINT>(GetOptionsMgr()->GetInt(OPT_TOOLBAR_SIZE)));
}

/** @brief Lang aware version of CFrameWnd::OnToolTipText() *//*
BOOL CMainFrame::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	String strFullText;
	CString strTipText;
	UINT_PTR nID = pNMHDR->idFrom;
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
	}

	if (nID != 0) // will be zero on a separator
	{
		strFullText = theApp.LoadString(static_cast<UINT>(nID));
		// don't handle the message if no string resource found
		if (strFullText.empty())
			return FALSE;

		// this is the command id, not the button index
		AfxExtractSubString(strTipText, strFullText.c_str(), 1, '\n');
	}
#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, countof(pTTTA->szText));
	else
		_mbstowcsz(pTTTW->szText, strTipText, countof(pTTTW->szText));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, countof(pTTTA->szText));
	else
		lstrcpyn(pTTTW->szText, strTipText, countof(pTTTW->szText));
#endif
	*pResult = 0;

	// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
				   SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER);

	return TRUE;    // message was handled
}

/**
 * @brief Ask user for close confirmation when closing the mainframe.
 * This function asks if user wants to close multiple open windows when user
 * selects (perhaps accidentally) to close WinMerge (application).
 * @return true if user agreeds to close all windows.
 *//*
bool CMainFrame::AskCloseConfirmation()
{
	const DirDocList &dirdocs = GetAllDirDocs();
	const MergeDocList &mergedocs = GetAllMergeDocs();

	int ret = IDYES;
	const size_t count = dirdocs.GetCount() + mergedocs.GetCount();
	if (count > 1)
	{
		// Check that we don't have one empty dirdoc + mergedoc situation.
		// That happens since we open "hidden" dirdoc for every file compare.
		if (dirdocs.GetCount() == 1)
		{
			CDirDoc *pDoc = dirdocs.GetHead();
			if (!pDoc->HasDiffs())
				return true;
		}
		ret = LangMessageBox(IDS_CLOSEALL_WINDOWS, MB_YESNO | MB_ICONWARNING);
	}
	return (ret == IDYES);
}

/**
 * @brief Shows the release notes for user.
 * This function opens release notes HTML document into browser.
 *//*
void CMainFrame::OnHelpReleasenotes()
{
	const String sPath = paths::ConcatPath(env::GetProgPath(), RelNotes);
	ShellExecute(nullptr, _T("open"), sPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

/**
 * @brief Shows the translations page.
 * This function opens translations page URL into browser.
 *//*
void CMainFrame::OnHelpTranslations()
{
	ShellExecute(nullptr, _T("open"), TranslationsUrl, nullptr, nullptr, SW_SHOWNORMAL);
}

/**
 * @brief Called when user selects File/Open Conflict...
 *//*
void CMainFrame::OnFileOpenConflict()
{
	String conflictFile;
	if (SelectFile(GetSafeHwnd(), conflictFile))
	{
		DoOpenConflict(conflictFile);
	}
}

/**
 * @brief Select and open conflict file for resolving.
 * This function lets user to select conflict file to resolve.
 * Then we parse conflict file to two files to "merge" and
 * save resulting file over original file.
 *
 * Set left-side file read-only as it is the repository file which cannot
 * be modified anyway. Right-side file is user's file which is set as
 * modified by default so user can just save it and accept workspace
 * file as resolved file.
 * @param [in] conflictFile Full path to conflict file to open.
 * @param [in] checked If true, do not check if it really is project file.
 * @return `true` if conflict file was opened for resolving.
 *//*
//bool CMainFrame::DoOpenConflict(const String& conflictFile, const String strDesc[] /*= nullptr*///, bool checked /*= false*/)
/*{
	bool conflictCompared = false;

	if (!checked)
	{
		bool confFile = IsConflictFile(conflictFile);
		if (!confFile)
		{
			String message = strutils::format_string1(_("The file\n%1\nis not a conflict file."), conflictFile);
			AfxMessageBox(message.c_str(), MB_ICONSTOP);
			return false;
		}
	}

	// Create temp files and put them into the list,
	// from where they get deleted when MainFrame is deleted.
	String ext = paths::FindExtension(conflictFile);
	TempFilePtr wTemp(new TempFile());
	String workFile = wTemp->Create(_T("confw_"), ext);
	m_tempFiles.push_back(wTemp);
	TempFilePtr vTemp(new TempFile());
	String revFile = vTemp->Create(_T("confv_"), ext);
	m_tempFiles.push_back(vTemp);
	TempFilePtr bTemp(new TempFile());
	String baseFile = vTemp->Create(_T("confb_"), ext);
	m_tempFiles.push_back(bTemp);

	// Parse conflict file into two files.
	bool inners, threeWay;
	int iGuessEncodingType = GetOptionsMgr()->GetInt(OPT_CP_DETECT);
	bool success = ParseConflictFile(conflictFile, workFile, revFile, baseFile, iGuessEncodingType, inners, threeWay);

	if (success)
	{
		// Open two parsed files to WinMerge, telling WinMerge to
		// save over original file (given as third filename).
		theApp.m_strSaveAsPath = conflictFile;
		if (!threeWay)
		{
			String strDesc2[2] = {
					(strDesc && !strDesc[0].empty()) ? strDesc[0] : _("Theirs File"),
					(strDesc && !strDesc[2].empty()) ? strDesc[2] : _("Mine File") };
			DWORD dwFlags[2] = {FFILEOPEN_READONLY | FFILEOPEN_NOMRU, FFILEOPEN_NOMRU | FFILEOPEN_MODIFIED};
			PathContext tmpPathContext(revFile, workFile);
			conflictCompared = DoFileOpen(&tmpPathContext, dwFlags, strDesc2);
		}
		else
		{
			String strDesc3[3] = {
					(strDesc && !strDesc[0].empty()) ? strDesc[0] : _("Base File"),
					(strDesc && !strDesc[1].empty()) ? strDesc[1] : _("Theirs File"),
					(strDesc && !strDesc[2].empty()) ? strDesc[2] : _("Mine File") };
			PathContext tmpPathContext(baseFile, revFile, workFile);
			DWORD dwFlags[3] = {FFILEOPEN_READONLY | FFILEOPEN_NOMRU, FFILEOPEN_READONLY | FFILEOPEN_NOMRU, FFILEOPEN_NOMRU | FFILEOPEN_MODIFIED};
			conflictCompared = DoFileOpen(&tmpPathContext, dwFlags, strDesc3);
		}
	}
	else
	{
		LangMessageBox(IDS_ERROR_CONF_RESOLVE, MB_ICONSTOP);
	}
	return conflictCompared;
}

/**
 * @brief Get type of frame (File/Folder compare).
 * @param [in] pFrame Pointer to frame to check.
 * @return FRAMETYPE of the given frame.
*//*
CMainFrame::FRAMETYPE CMainFrame::GetFrameType(const CFrameWnd * pFrame) const
{
	bool bMergeFrame = !!pFrame->IsKindOf(RUNTIME_CLASS(CChildFrame));
	bool bHexMergeFrame = !!pFrame->IsKindOf(RUNTIME_CLASS(CHexMergeFrame));
	bool bImgMergeFrame = !!pFrame->IsKindOf(RUNTIME_CLASS(CImgMergeFrame));
	bool bDirFrame = !!pFrame->IsKindOf(RUNTIME_CLASS(CDirFrame));

	if (bMergeFrame)
		return FRAME_FILE;
	else if (bHexMergeFrame)
		return FRAME_HEXFILE;
	else if (bImgMergeFrame)
		return FRAME_IMGFILE;
	else if (bDirFrame)
		return FRAME_FOLDER;
	else
		return FRAME_OTHER;
}

/**
 * @brief Show the plugins list dialog.
 */
/*void CMainFrame::OnPluginsList()
{
	PluginsListDlg dlg;
	dlg.DoModal();
}

/*void CMainFrame::OnDiffOptionsDropDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTOOLBAR pToolBar = reinterpret_cast<LPNMTOOLBAR>(pNMHDR);
	ClientToScreen(&(pToolBar->rcButton));
	BCMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_DIFF_OPTIONS));
	theApp.TranslateMenu(menu.m_hMenu);
	CMenu* pPopup = menu.GetSubMenu(0);
	if (pPopup != nullptr)
	{
		pPopup->TrackPopupMenu(TPM_RIGHTALIGN | TPM_RIGHTBUTTON,
							   pToolBar->rcButton.right, pToolBar->rcButton.bottom, this);
	}
	*pResult = 0;
}
void CMainFrame::OnDiffWhitespace(UINT nID)
{
	GetOptionsMgr()->SaveOption(OPT_CMP_IGNORE_WHITESPACE, nID - IDC_DIFF_WHITESPACE_COMPARE);
	ApplyDiffOptions();
}

void CMainFrame::OnUpdateDiffWhitespace(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio((pCmdUI->m_nID - IDC_DIFF_WHITESPACE_COMPARE) == static_cast<UINT>(GetOptionsMgr()->GetInt(OPT_CMP_IGNORE_WHITESPACE)));
	pCmdUI->Enable();
}

void CMainFrame::OnDiffCaseSensitive()
{
	GetOptionsMgr()->SaveOption(OPT_CMP_IGNORE_CASE, !GetOptionsMgr()->GetBool(OPT_CMP_IGNORE_CASE));
	ApplyDiffOptions();
}

void CMainFrame::OnUpdateDiffCaseSensitive(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(!GetOptionsMgr()->GetBool(OPT_CMP_IGNORE_CASE));
	pCmdUI->Enable();
}

void CMainFrame::OnDiffIgnoreEOL()
{
	GetOptionsMgr()->SaveOption(OPT_CMP_IGNORE_EOL, !GetOptionsMgr()->GetBool(OPT_CMP_IGNORE_EOL));
	ApplyDiffOptions();
}

void CMainFrame::OnUpdateDiffIgnoreEOL(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetOptionsMgr()->GetBool(OPT_CMP_IGNORE_EOL));
	pCmdUI->Enable();
}

void CMainFrame::OnIncludeSubfolders()
{
	GetOptionsMgr()->SaveOption(OPT_CMP_INCLUDE_SUBDIRS, !GetOptionsMgr()->GetBool(OPT_CMP_INCLUDE_SUBDIRS));
	// Update all dirdoc settings
	for (auto pDirDoc : GetAllDirDocs())
		pDirDoc->RefreshOptions();
	for (auto pOpenDoc : GetAllOpenDocs())
		pOpenDoc->RefreshOptions();
}

void CMainFrame::OnUpdateIncludeSubfolders(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetOptionsMgr()->GetBool(OPT_CMP_INCLUDE_SUBDIRS));
	pCmdUI->Enable();
}

void CMainFrame::OnCompareMethod(UINT nID)
{
	GetOptionsMgr()->SaveOption(OPT_CMP_METHOD, nID - ID_COMPMETHOD_FULL_CONTENTS);
}

void CMainFrame::OnUpdateCompareMethod(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio((pCmdUI->m_nID - ID_COMPMETHOD_FULL_CONTENTS) == static_cast<UINT>(GetOptionsMgr()->GetInt(OPT_CMP_METHOD)));
	pCmdUI->Enable();
}

void CMainFrame::OnMRUs(UINT nID)
{
	std::vector<JumpList::Item> mrus = JumpList::GetRecentDocs(GetOptionsMgr()->GetInt(OPT_MRU_MAX));
	const size_t idx = nID - ID_MRU_FIRST;
	if (idx < mrus.size())
	{
		MergeCmdLineInfo cmdInfo((_T("\"") + mrus[idx].path + _T("\" ") + mrus[idx].params).c_str());
		theApp.ParseArgsAndDoOpen(cmdInfo, this);
	}
}*/