/**
 * @file  OptionsInit.cpp
 *
 * @brief Options initialisation.
 */

// #include <vector>
#include "OptionsDef.h"
//#include "OptionsMgr.h"
//#include "RegOptionsMgr.h"
#include "OptionsDiffOptions.h"
// #include "OptionsDiffColors.h"
//#include "OptionsFont.h"
/*#include "DiffWrapper.h" // CMP_CONTENT
#include "paths.h"
#include "Environment.h"
#include "FileTransform.h"*/
#include "Constants.h"

#include <QSettings>
// Functions to copy values set by installer from HKLM to HKCU.
/*static void CopyHKLMValues();
static bool OpenHKLM(HKEY *key, LPCTSTR relpath = nullptr);
static bool OpenHKCU(HKEY *key, LPCTSTR relpath = nullptr);
static void CopyFromLMtoCU(HKEY lmKey, HKEY cuKey, LPCTSTR valname);*/

namespace Options
{


void setInitalValue(QSettings& Settings,QString key, QVariant default_value)
{
	if (!Settings.contains(key))
	{
		Settings.setValue(key,default_value);
	}
}

/**
 * @brief Initialise options and set default values.
 *
 * @note Remember default values are what users see first time
 * using WinMerge and many users never change them. So pick
 * default values carefully!
 */
void Init()
{
	QSettings options;
	// Copy some values from HKLM to HKCU
	//CopyHKLMValues();

	//static_cast<CRegOptionsMgr *>(pOptions)->SetRegRootKey(_T("Thingamahoochie\\WinMerge\\"));

	/*LANGID LangId = GetUserDefaultLangID();
	if (PRIMARYLANGID(LangId) == LANG_JAPANESE)
	{
		// Default language to Japanese unless installer set it otherwise
		setInitalValue(options,OPT_SELECTED_LANGUAGE, 0x411);
	}
	else
	{*/
		// Default language to English unless installer set it otherwise
	setInitalValue(options,OPT_SELECTED_LANGUAGE, 0x409);

	// Initialise options (name, default value)
	setInitalValue(options,OPT_SHOW_UNIQUE_LEFT, true);
	setInitalValue(options,OPT_SHOW_UNIQUE_MIDDLE, true);
	setInitalValue(options,OPT_SHOW_UNIQUE_RIGHT, true);
	setInitalValue(options,OPT_SHOW_DIFFERENT, true);
	setInitalValue(options,OPT_SHOW_IDENTICAL, true);
	setInitalValue(options,OPT_SHOW_BINARIES, true);
	setInitalValue(options,OPT_SHOW_SKIPPED, false);
	setInitalValue(options,OPT_SHOW_DIFFERENT_LEFT_ONLY, true);
	setInitalValue(options,OPT_SHOW_DIFFERENT_MIDDLE_ONLY, true);
	setInitalValue(options,OPT_SHOW_DIFFERENT_RIGHT_ONLY, true);

	setInitalValue(options,OPT_SHOW_TOOLBAR, true);
	setInitalValue(options,OPT_SHOW_STATUSBAR, true);
	setInitalValue(options,OPT_SHOW_TABBAR, true);
//	setInitalValue(options,OPT_TOOLBAR_SIZE, GetSystemMetrics(SM_CXSMICON) < 24 ? 0 : 1);
	setInitalValue(options,OPT_RESIZE_PANES, false);

	setInitalValue(options,OPT_SYNTAX_HIGHLIGHT, true);
	setInitalValue(options,OPT_WORDWRAP, false);
	setInitalValue(options,OPT_VIEW_LINENUMBERS, false);
	setInitalValue(options,OPT_VIEW_WHITESPACE, false);
	setInitalValue(options,OPT_CONNECT_MOVED_BLOCKS, 0);
	setInitalValue(options,OPT_SCROLL_TO_FIRST, false);
	setInitalValue(options,OPT_VERIFY_OPEN_PATHS, true);
	setInitalValue(options,OPT_AUTO_COMPLETE_SOURCE, (int)1);
	setInitalValue(options,OPT_VIEW_FILEMARGIN, false);
	setInitalValue(options,OPT_DIFF_CONTEXT, (int)-1);
	setInitalValue(options,OPT_SPLIT_HORIZONTALLY, false);

	setInitalValue(options,OPT_WORDDIFF_HIGHLIGHT, true);
	setInitalValue(options,OPT_BREAK_SEPARATORS, _T(".,:;?[](){}<>`'!\"#$%&^~\\|@+-*/"));

	setInitalValue(options,OPT_BACKUP_FOLDERCMP, false);
	setInitalValue(options,OPT_BACKUP_FILECMP, true);
	setInitalValue(options,OPT_BACKUP_LOCATION, (int)0);
	setInitalValue(options,OPT_BACKUP_GLOBALFOLDER, _T(""));
	setInitalValue(options,OPT_BACKUP_ADD_BAK, true);
	setInitalValue(options,OPT_BACKUP_ADD_TIME, false);

	setInitalValue(options,OPT_DIRVIEW_SORT_COLUMN, (int)-1);
	setInitalValue(options,OPT_DIRVIEW_SORT_COLUMN3, (int)-1);
	setInitalValue(options,OPT_DIRVIEW_SORT_ASCENDING, true);
	setInitalValue(options,OPT_SHOW_SELECT_FILES_AT_STARTUP, false);
	setInitalValue(options,OPT_DIRVIEW_EXPAND_SUBDIRS, false);

	setInitalValue(options,OPT_REPORTFILES_REPORTTYPE, 0);
	setInitalValue(options,OPT_REPORTFILES_COPYTOCLIPBOARD, false);
	setInitalValue(options,OPT_REPORTFILES_INCLUDEFILECMPREPORT, false);

	setInitalValue(options,OPT_AUTOMATIC_RESCAN, false);
	setInitalValue(options,OPT_ALLOW_MIXED_EOL, false);
	setInitalValue(options,OPT_TAB_SIZE, (int)4);
	setInitalValue(options,OPT_TAB_TYPE, (int)0);	// 0 means tabs inserted

//	setInitalValue(options,OPT_EXT_EDITOR_CMD, paths::ConcatPath(env::GetWindowsDirectory(), _T("NOTEPAD.EXE")));
	setInitalValue(options,OPT_USE_RECYCLE_BIN, true);
	setInitalValue(options,OPT_SINGLE_INSTANCE, false);
	setInitalValue(options,OPT_MERGE_MODE, false);
	// OPT_WORDDIFF_HIGHLIGHT is initialized above
	setInitalValue(options,OPT_BREAK_ON_WORDS, false);
	setInitalValue(options,OPT_BREAK_TYPE, 1);

	setInitalValue(options,OPT_CLOSE_WITH_ESC, true);
	setInitalValue(options,OPT_CLOSE_WITH_OK, false);
	setInitalValue(options,OPT_IGNORE_SMALL_FILETIME, false);
	setInitalValue(options,OPT_ASK_MULTIWINDOW_CLOSE, false);
	setInitalValue(options,OPT_PRESERVE_FILETIMES, false);
	setInitalValue(options,OPT_TREE_MODE, true);

//	setInitalValue(options,OPT_CMP_METHOD, (int)CMP_CONTENT);
	setInitalValue(options,OPT_CMP_MOVED_BLOCKS, false);
	setInitalValue(options,OPT_CMP_MATCH_SIMILAR_LINES, false);
	setInitalValue(options,OPT_CMP_STOP_AFTER_FIRST, false);
	setInitalValue(options,OPT_CMP_QUICK_LIMIT, 4 * 1024 * 1024); // 4 Megs
	setInitalValue(options,OPT_CMP_COMPARE_THREADS, -1);
	setInitalValue(options,OPT_CMP_WALK_UNIQUE_DIRS, false);
	setInitalValue(options,OPT_CMP_IGNORE_REPARSE_POINTS, false);
	setInitalValue(options,OPT_CMP_IGNORE_CODEPAGE, true);
	setInitalValue(options,OPT_CMP_INCLUDE_SUBDIRS, true);

	setInitalValue(options,OPT_CMP_BIN_FILEPATTERNS, _T("*.bin;*.frx"));

	setInitalValue(options,OPT_CMP_IMG_FILEPATTERNS, _T("*.bmp;*.cut;*.dds;*.exr;*.g3;*.gif;*.hdr;*.ico;*.iff;*.lbm;*.j2k;*.j2c;*.jng;*.jp2;*.jpg;*.jif;*.jpeg;*.jpe;*.jxr;*.wdp;*.hdp;*.koa;*.mng;*.pcd;*.pcx;*.pfm;*.pct;*.pict;*.pic;*.png;*.pbm;*.pgm;*.ppm;*.psd;*.ras;*.sgi;*.rgb;*.rgba;*.bw;*.tga;*.targa;*.tif;*.tiff;*.wap;*.wbmp;*.wbm;*.webp;*.xbm;*.xpm"));
	setInitalValue(options,OPT_CMP_IMG_SHOWDIFFERENCES, true);
	setInitalValue(options,OPT_CMP_IMG_OVERLAYMOVE, 0);
	setInitalValue(options,OPT_CMP_IMG_OVERLAYALPHA, 30);
	setInitalValue(options,OPT_CMP_IMG_DRAGGING_MODE, 1);
	setInitalValue(options,OPT_CMP_IMG_ZOOM, 1000);
	setInitalValue(options,OPT_CMP_IMG_USEBACKCOLOR, true);
	setInitalValue(options,OPT_CMP_IMG_BACKCOLOR, 0xFFFFFF);
	setInitalValue(options,OPT_CMP_IMG_DIFFBLOCKSIZE, 8);
	setInitalValue(options,OPT_CMP_IMG_DIFFCOLORALPHA, 70);
	setInitalValue(options,OPT_CMP_IMG_THRESHOLD, 0);

	setInitalValue(options,OPT_PROJECTS_PATH, _T(""));
	setInitalValue(options,OPT_USE_SYSTEM_TEMP_PATH, true);
	setInitalValue(options,OPT_CUSTOM_TEMP_PATH, _T(""));

	setInitalValue(options,OPT_LINEFILTER_ENABLED, false);
	setInitalValue(options,OPT_FILEFILTER_CURRENT, _T("*.*"));
	// CMainFrame initializes this when it is empty.
//	setInitalValue(options,OPT_FILTER_USERPATH, paths::ConcatPath(env::GetMyDocuments(), DefaultRelativeFilterPath));
	setInitalValue(options,OPT_FILEFILTER_SHARED, false);

	setInitalValue(options,OPT_CP_DEFAULT_MODE, (int)0);
	//setInitalValue(options,OPT_CP_DEFAULT_CUSTOM, (int)GetACP());

	/*if (PRIMARYLANGID(LangId) == LANG_JAPANESE)
		setInitalValue(options,OPT_CP_DETECT, (int)(50932 << 16) | 3);
	else if (LangId == MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED))
		setInitalValue(options,OPT_CP_DETECT, (int)(50936 << 16) | 3);
	else if (PRIMARYLANGID(LangId) == LANG_KOREAN)
		setInitalValue(options,OPT_CP_DETECT, (int)(50949 << 16) | 3);
	else if (LangId == MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL))
		setInitalValue(options,OPT_CP_DETECT, (int)(50950 << 16) | 3);
	else*/
		setInitalValue(options,OPT_CP_DETECT, (int)(50001 << 16) | 1);

	setInitalValue(options,OPT_ARCHIVE_ENABLE, 1); // Enable by default
	setInitalValue(options,OPT_ARCHIVE_PROBETYPE, false);
	setInitalValue(options,OPT_ARCHIVE_FILTER_INDEX, 1);

	setInitalValue(options,OPT_PLUGINS_ENABLED, true);
	setInitalValue(options,OPT_PLUGINS_DISABLED_LIST, _T(""));
	//setInitalValue(options,OPT_PLUGINS_UNPACKER_MODE, PLUGIN_MANUAL);
	//setInitalValue(options,OPT_PLUGINS_PREDIFFER_MODE, PLUGIN_MANUAL);
	setInitalValue(options,OPT_PLUGINS_UNPACK_DONT_CHECK_EXTENSION, false);

	setInitalValue(options,OPT_PATCHCREATOR_PATCH_STYLE, 0);
	setInitalValue(options,OPT_PATCHCREATOR_CONTEXT_LINES, 0);
	setInitalValue(options,OPT_PATCHCREATOR_CASE_SENSITIVE, true);
	setInitalValue(options,OPT_PATCHCREATOR_EOL_SENSITIVE, true);
	setInitalValue(options,OPT_PATCHCREATOR_IGNORE_BLANK_LINES, false);
	//setInitalValue(options,OPT_PATCHCREATOR_WHITESPACE, WHITESPACE_COMPARE_ALL);
	setInitalValue(options,OPT_PATCHCREATOR_OPEN_TO_EDITOR, false);
	setInitalValue(options,OPT_PATCHCREATOR_INCLUDE_CMD_LINE, false);

	setInitalValue(options,OPT_TABBAR_AUTO_MAXWIDTH, true);
	setInitalValue(options,OPT_ACTIVE_FRAME_MAX, true);
	setInitalValue(options,OPT_ACTIVE_PANE, 0);

	setInitalValue(options,OPT_MRU_MAX, 9);


	//Options::DiffOptions::SetDefaults(pOptions);
	//Options::DiffColors::SetDefaults(pOptions);
	//Options::Font::SetDefaults(pOptions);
}

}

/**
 * @brief Copy some HKLM values to HKCU.
 * The installer sets HKLM values for "all users". This function copies
 * few of those values for "user" values. E.g. enabling ShellExtension
 * initially for user is done by this function.
 */
/*static void CopyHKLMValues()
{
	HKEY LMKey;
	HKEY CUKey;
	if (OpenHKLM(&LMKey))
	{
		if (OpenHKCU(&CUKey))
		{
			CopyFromLMtoCU(LMKey, CUKey, _T("ContextMenuEnabled"));
			CopyFromLMtoCU(LMKey, CUKey, _T("Executable"));
			RegCloseKey(CUKey);
		}
		RegCloseKey(LMKey);
	}
	if (OpenHKLM(&LMKey, _T("Locale")))
	{
		if (OpenHKCU(&CUKey, _T("Locale")))
		{
			CopyFromLMtoCU(LMKey, CUKey, _T("LanguageId"));
			RegCloseKey(CUKey);
		}
		RegCloseKey(LMKey);
	}
}

/**
 * @brief Open HKLM registry key.
 * @param [out] key Pointer to open HKLM key.
 * @param [in] relpath Relative registry path (to WinMerge reg path) to open, or nullptr.
 * @return true if opening succeeded.
 *//*
static bool OpenHKLM(HKEY *key, LPCTSTR relpath)
{
	TCHAR valuename[256];
	if (relpath)
		wsprintf(valuename, _T("%s\\%s"), RegDir, relpath);
	else
		lstrcpy(valuename, RegDir);
	LONG retval = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			valuename, 0, KEY_READ, key);
	if (retval == ERROR_SUCCESS)
	{
		return true;
	}
	return false;
}
*/
/**
 * @brief Open HKCU registry key.
 * Opens the HKCU key for WinMerge. If the key does not exist, creates one.
 * @param [out] key Pointer to open HKCU key.
 * @param [in] relpath Relative registry path (to WinMerge reg path) to open, or nullptr.
 * @return true if opening succeeded.
 */
/*static bool OpenHKCU(HKEY *key, LPCTSTR relpath)
{
	TCHAR valuename[256];
	if (relpath)
		wsprintf(valuename, _T("%s\\%s"), RegDir, relpath);
	else
		lstrcpy(valuename, RegDir);
	LONG retval = RegOpenKeyEx(HKEY_CURRENT_USER,
			valuename, 0, KEY_ALL_ACCESS, key);
	if (retval == ERROR_SUCCESS)
	{
		return true;
	}
	else if (retval == ERROR_FILE_NOT_FOUND)
	{
		retval = RegCreateKeyEx(HKEY_CURRENT_USER,
			valuename, 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, key, nullptr);
		if (retval == ERROR_SUCCESS)
			return true;
	}
	return false;
}

/**
 * @brief Copy value from HKLM to HKCU.
 * @param [in] lmKey HKLM key from where to copy.
 * @param [in] cuKey HKCU key to where to copy.
 * @param [in] valname Name of the value to copy.
 */
/*static void CopyFromLMtoCU(HKEY lmKey, HKEY cuKey, LPCTSTR valname)
{
	DWORD len = 0;
	LONG retval = RegQueryValueEx(cuKey, valname, 0, nullptr, nullptr, &len);
	if (retval == ERROR_FILE_NOT_FOUND)
	{
		retval = RegQueryValueEx(lmKey, valname, 0, nullptr, nullptr, &len);
		if (retval == ERROR_SUCCESS)
		{
			DWORD type = 0;
			std::vector<BYTE> buf(len);
			retval = RegQueryValueEx(lmKey, valname, 0, &type, &buf[0], &len);
			if (retval == ERROR_SUCCESS)
			{
				RegSetValueEx(cuKey, valname , 0, type,
					&buf[0], len);
			}
		}
	}
}*/
