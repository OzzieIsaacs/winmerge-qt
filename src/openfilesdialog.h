#ifndef OPENFILESDIALOG_H
#define OPENFILESDIALOG_H

#include <QDialog>
#include "ui_openfilesdialog.h"

class QWidget;

class OpenFilesDialog : public QDialog
{
    Q_OBJECT

public:
    OpenFilesDialog(QWidget * parent = NULL);
    QString GetLeftItem() const;
    QString GetRightItem() const;

protected slots:
    void SelectLeftItem();
    void SelectRightItem();

private:
    Ui::mOpenFilesDlg mUI;
};

#endif // OPENFILESDIALOG_H
