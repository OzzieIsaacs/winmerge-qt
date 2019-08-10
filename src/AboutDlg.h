#ifndef QABOUTDLG_H
#define QABOUTDLG_H

#include <QDialog>
#include "MergeApp.h"


namespace Ui {
class QAboutDlg;
}
class QAboutDlg : public QDialog
{
	Q_OBJECT

public:
    explicit QAboutDlg(QWidget *parent = nullptr);
    ~QAboutDlg();

    AboutInfo m_info;
private slots:
	void OnBnClickedOpenContributors();
	void onClickedOk();
	void OnClickedWWW();
private:
    Ui::QAboutDlg *ui;
};
#endif // ABOUTDIALOG_H
