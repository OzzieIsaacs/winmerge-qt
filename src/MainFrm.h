#ifndef MAINFRM_H
#define MAINFRM_H

#include <QMainWindow>
#include <QFile>
#include "Common/tchar.h"
#include "Common/OptionsMgr.h"
#include <memory>

class COptionsMgr;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	Ui::MainWindow *ui;
	std::unique_ptr<COptionsMgr> m_pOptions;
	QString m_sSettingsFile;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	COptionsMgr * GetMergeOptionsMgr() { return static_cast<COptionsMgr *> (m_pOptions.get()); }

private slots:
    void on_pushButton_clicked();
	void AboutWinMerge();
	void OnHelpGnulicense();
	void OnHelpReleasenotes();
	void OnHelpTranslations();
	void OnFileOpenProject();
	void OnOptions();
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void OpenFileOrUrl(QFile& file, const TCHAR* szUrl);

};

#endif // MAINFRM_H
