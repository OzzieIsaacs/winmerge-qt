#include "PropShell.h"
#include "ui_QPropShell.h"
#include "Constants.h"
//#include "RegKey.h"
//#include "Environment.h"
#include "paths.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


QPropShell::QPropShell(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QPropShell) {
	ui->setupUi(this);

#ifndef BCM_SETSHIELD
#define BCM_SETSHIELD            (0x1600/*BCM_FIRST*/ + 0x000C)
#endif
	// ToDo: Port
	/*
	SendDlgItemMessage(IDC_REGISTER_SHELLEXTENSION, BCM_SETSHIELD, 0, TRUE);
	SendDlgItemMessage(IDC_UNREGISTER_SHELLEXTENSION, BCM_SETSHIELD, 0, TRUE);*/

	// Update shell extension checkboxes
	UpdateButtons();
	GetContextRegValues();
	AdvancedContextMenuCheck();
	// UpdatePage(false);

	// Todo: Port
	/*SetTimer(0, 1000, nullptr);*/
	connect(ui->IDC_EXPLORER_CONTEXT, SIGNAL(clicked()), this, SLOT(OnAddToExplorer()));
	connect(ui->IDC_REGISTER_SHELLEXTENSION, SIGNAL(clicked()), this, SLOT(OnRegisterShellExtension()));
	connect(ui->IDC_UNREGISTER_SHELLEXTENSION, SIGNAL(clicked()), this, SLOT(OnUnregisterShellExtension()));

}

QPropShell::~QPropShell()
{
	delete ui;
}

// registry values
// ToDo: Port
//static LPCTSTR f_RegValueEnabled = _T("ContextMenuEnabled");
//static LPCTSTR f_RegValuePath = _T("Executable");

static bool IsShellExtensionRegistered()
{
	// ToDo: Port
	/*
	HKEY hKey;
#ifdef _WIN64
	DWORD ulOptions = KEY_QUERY_VALUE;
#else
	auto Is64BitWindows = []() { BOOL f64 = FALSE; return IsWow64Process(GetCurrentProcess(), &f64) && f64; };
	DWORD ulOptions = KEY_QUERY_VALUE | (Is64BitWindows() ? KEY_WOW64_64KEY : 0);
#endif
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("CLSID\\{4E716236-AA30-4C65-B225-D68BBA81E9C2}"), 0, ulOptions, &hKey)) {
		RegCloseKey(hKey);
		return true;
	}*/
	return false;
}

static bool RegisterShellExtension(bool unregister)
{
	// ToDo: Port
	/*
	TCHAR szSystem32[260] = { 0 };
	TCHAR szSysWow64[260] = { 0 };
	GetSystemDirectory(szSystem32, sizeof(szSystem32) / sizeof(szSystem32[0]));
	GetSystemWow64Directory(szSysWow64, sizeof(szSysWow64) / sizeof(szSysWow64[0]));

	String progpath = env::GetProgPath();
	String regsvr32 = paths::ConcatPath(szSystem32, _T("regsvr32.exe"));
	String args;
	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpVerb = _T("runas");
	if (szSysWow64[0])
	{
		args = (unregister ? _T("/s /u \"") : _T("/s \"")) + paths::ConcatPath(progpath, _T("ShellExtensionX64.dll")) + _T("\"");
		sei.lpFile = regsvr32.c_str();
		sei.lpParameters = args.c_str();
		ShellExecuteEx(&sei);

		regsvr32 = paths::ConcatPath(szSysWow64, _T("regsvr32.exe"));
		args = (unregister ? _T("/s /u \"") : _T("/s \"")) + paths::ConcatPath(progpath, _T("ShellExtensionU.dll")) + _T("\"");
		sei.lpFile = regsvr32.c_str();
		sei.lpParameters = args.c_str();
		return !!ShellExecuteEx(&sei);
	}
	else
	{
		args = (unregister ? _T("/s /u \"") : _T("/s \"")) + paths::ConcatPath(progpath, _T("ShellExtensionU.dll")) + _T("\"");
		sei.lpFile = regsvr32.c_str();
		sei.lpParameters = args.c_str();
		return !!ShellExecuteEx(&sei);
	}*/
}



/**
 * @brief Reads options values from storage to UI.
 */
void QPropShell::ReadOptions()
{
	GetContextRegValues();
}

/**
 * @brief Writes options values from UI to storage.
 */
void QPropShell::WriteOptions()
{
	SaveMergePath(); // saves context menu settings as well
}

/// Get registry values for ShellExtension
void QPropShell::GetContextRegValues()
{
	// ToDo: Port
	/*CRegKeyEx reg;
	LONG retVal = 0;
	retVal = reg.Open(HKEY_CURRENT_USER, RegDir);
	if (retVal != ERROR_SUCCESS)
	{
		String msg = strutils::format(_T("Failed to open registry key HKCU/%s:\n\t%d : %s"),
									  RegDir, retVal, GetSysError(retVal).c_str());
		LogErrorString(msg);
		return;
	}

	// Read bitmask for shell extension settings
	DWORD dwContextEnabled = reg.ReadDword(f_RegValueEnabled, 0);

	if (dwContextEnabled & CONTEXT_F_ENABLED)
		m_bContextAdded = true;

	if (dwContextEnabled & CONTEXT_F_ADVANCED)
		m_bContextAdvanced = true;*/
}

/// Set registry values for ShellExtension
void QPropShell::OnAddToExplorer()
{
	AdvancedContextMenuCheck();
	UpdateButtons();
}

/// Saves given path to registry for ShellExtension, and Context Menu settings
void QPropShell::SaveMergePath()
{
	// ToDo: Port
	/*
	TCHAR temp[MAX_PATH] = {0};
	LONG retVal = 0;
	GetModuleFileName(AfxGetInstanceHandle(), temp, MAX_PATH);

	CRegKeyEx reg;
	retVal = reg.Open(HKEY_CURRENT_USER, RegDir);
	if (retVal != ERROR_SUCCESS)
	{
		String msg = strutils::format(_T("Failed to open registry key HKCU/%s:\n\t%d : %s"),
									  RegDir, retVal, GetSysError(retVal).c_str());
		LogErrorString(msg);
		return;
	}

	// Save path to WinMerge(U).exe
	retVal = reg.WriteString(f_RegValuePath, temp);
	if (retVal != ERROR_SUCCESS)
	{
		String msg = strutils::format(_T("Failed to set registry value %s:\n\t%d : %s"),
									  f_RegValuePath, retVal, GetSysError(retVal).c_str());
		LogErrorString(msg);
	}

	// Determine bitmask for shell extension
	DWORD dwContextEnabled = reg.ReadDword(f_RegValueEnabled, 0);
	if (m_bContextAdded)
		dwContextEnabled |= CONTEXT_F_ENABLED;
	else
		dwContextEnabled &= ~CONTEXT_F_ENABLED;

	if (m_bContextAdvanced)
		dwContextEnabled |= CONTEXT_F_ADVANCED;
	else
		dwContextEnabled &= ~CONTEXT_F_ADVANCED;

	retVal = reg.WriteDword(f_RegValueEnabled, dwContextEnabled);
	if (retVal != ERROR_SUCCESS)
	{
		String msg = strutils::format(_T("Failed to set registry value %s to %d:\n\t%d : %s"),
									  f_RegValueEnabled, dwContextEnabled, retVal, GetSysError(retVal).c_str());
		LogErrorString(msg);
	}*/
}

/// Enable/Disable "Advanced menu" checkbox.
void QPropShell::AdvancedContextMenuCheck()
{
	// ToDo: Port easy
	/*
	if (!IsDlgButtonChecked(IDC_EXPLORER_CONTEXT))
	{
		CheckDlgButton(IDC_EXPLORER_ADVANCED, FALSE);
		m_bContextAdvanced = false;
	}*/
}

void QPropShell::UpdateButtons()
{
	// ToDo: Port easy
	/*
	bool registered = IsShellExtensionRegistered();
	EnableDlgItem(IDC_EXPLORER_CONTEXT, registered);
	EnableDlgItem(IDC_REGISTER_SHELLEXTENSION, !registered);
	EnableDlgItem(IDC_UNREGISTER_SHELLEXTENSION, registered);
	EnableDlgItem(IDC_EXPLORER_ADVANCED,
				  registered && IsDlgButtonChecked(IDC_EXPLORER_CONTEXT));*/
}

void QPropShell::OnRegisterShellExtension()
{
	RegisterShellExtension(false);
}

void QPropShell::OnUnregisterShellExtension()
{
	RegisterShellExtension(true);
}

/*void QPropShell::OnTimer(UINT_PTR nIDEvent)
{
	UpdateButtons();
}*/
