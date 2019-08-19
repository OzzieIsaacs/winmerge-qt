#ifndef MAINFRM_H
#define MAINFRM_H

#include <QMainWindow>
#include <QFile>
#include "Common/tchar.h"
#include <memory>
#include "QOptionsMgr.h"
#include "MergeCmdLineInfo.h"
#include "FileFilterHelper.h"
// #include <QMenuBar>

// class COptionsMgr;
//class FileFilterHelper;

namespace Ui {
class MainWindow;
}

enum { IDLE_TIMER = 9754 };

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	Ui::MainWindow *ui;
	// std::unique_ptr<COptionsMgr> m_pOptions;
	// QString m_sSettingsFile;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void SetNeedIdleTimer();
	void SetupTempPath();
	bool GetMergingMode() const;
	void SetMergingMode(bool bMergingMode);
	bool IsReallyIdle() const;
	void OpenFileToExternalEditor(const QString& file, int nLineNumber = 1);
	bool CreateBackup(bool bFolder, const QString& pszPath);
	int HandleReadonlySave(QString& strSavePath, bool bMultiFile, bool &bApplyToAll);
	FileFilterHelper * GetGlobalFileFilter() { return m_pGlobalFileFilter.get(); }

	QMenuBar* NewDirViewMenu();
	QMenuBar* NewMergeViewMenu();
	QMenuBar* NewHexMergeViewMenu();
	QMenuBar* NewImgMergeViewMenu();
	QMenuBar* NewOpenViewMenu();
	QMenuBar* NewDefaultMenu(int ID = 0);
	bool m_bNeedIdleTimer;
	/*CMultiDocTemplate* m_pOpenTemplate;
	CMultiDocTemplate* m_pDiffTemplate;
	CMultiDocTemplate* m_pHexMergeTemplate;
	CMultiDocTemplate* m_pDirTemplate;*/
	std::unique_ptr<FileFilterHelper> m_pGlobalFileFilter;
	// std::unique_ptr<SyntaxColors> m_pSyntaxColors; /**< Syntax color container */
	// std::unique_ptr<CCrystalTextMarkers> m_pMarkers; /**< Marker container */
	QString m_strSaveAsPath; /**< "3rd path" where output saved if given */
	bool m_bEscShutdown; /**< If commandline switch -e given ESC closes appliction */
	// SyntaxColors * GetMainSyntaxColors() { return m_pSyntaxColors.get(); }
	// CCrystalTextMarkers * GetMainMarkers() const { return m_pMarkers.get(); }
	MergeCmdLineInfo::ExitNoDiff m_bExitIfNoDiff; /**< Exit if files are identical? */
  	// std::unique_ptr<LineFiltersList> m_pLineFilters; /**< List of linefilters */
	// std::unique_ptr<FilterCommentsManager> m_pFilterCommentsManager;



	virtual bool WriteProfileString(QString& lpszSection, QString& lpszEntry, QVariant& lpszValue);

	// Public implementation data
	bool m_bFirstTime; /**< If first time frame activated, get  pos from reg */


public slots:
    void on_pushButton_clicked();
	void OnAppAbout();
	void OnFileOpen();
	void OnToolbarSize(unsigned id);
	void OnHelp();
	void ShowHelp();
	void OnHelpGnulicense();
	void OnHelpReleasenotes();
	void OnHelpTranslations();
	void OnFileOpenProject();
	void OnOptions();
	void OnMergingMode();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void OpenFileOrUrl(QFile& file, const TCHAR* szUrl);

protected:
	virtual bool OnIdle(long int lCount);
	void InitializeFileFilters();
	void UpdateDefaultCodepage(int cpDefaultMode, int cpCustomCodepage);
	void UpdateCodepageModule();
	bool IsProjectFile(const QString& filepath) const;
	bool LoadAndOpenProjectFile(const QString& sFilepath, const QString& sReportFile = "");
	void ApplyCommandLineConfigOptions(MergeCmdLineInfo & cmdInfo);

	enum
	{
		MENU_DEFAULT,
		MENU_MERGEVIEW,
		MENU_DIRVIEW,
		MENU_HEXMERGEVIEW,
		MENU_IMGMERGEVIEW,
		MENU_OPENVIEW,
		MENU_COUNT, // Add new items before this item
	};
	/**
	 * Menu frames - for which frame(s) the menu is.
	 */
	enum
	{
		MENU_MAINFRM = 0x000001,
		MENU_FILECMP = 0x000002,
		MENU_FOLDERCMP = 0x000004,
		MENU_ALL = MENU_MAINFRM | MENU_FILECMP | MENU_FOLDERCMP
	};

	/**
	 * A structure attaching a menu item, icon and menu types to apply to.
	 */
	struct MENUITEM_ICON
	{
		int menuitemID;   /**< Menu item's ID. */
		int iconResID;    /**< Icon's resource ID. */
		int menusToApply; /**< For which menus to apply. */
	};


private:
	QOptionsMgr m_options;
	bool m_bMergingMode; /**< Merging or Edit mode */

	QMenuBar NewMenu(int view, int ID);
	bool CreateToolbar();
	void LoadToolbarImages();

};

#endif // MAINFRM_H
