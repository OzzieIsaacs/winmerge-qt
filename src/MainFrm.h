#ifndef MAINFRM_H
#define MAINFRM_H

#include <QMainWindow>
#include <QFile>
#include "Common/tchar.h"
#include <memory>
#include <QSettings>
// #include <QMenuBar>

class COptionsMgr;

namespace Ui {
class MainWindow;
}

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

	virtual bool WriteProfileString(QString& lpszSection, QString& lpszEntry, QVariant& lpszValue);

public slots:
    void on_pushButton_clicked();
	void OnAppAbout();
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


private:
	QSettings m_options;
};

#endif // MAINFRM_H
