#ifndef OPENDIALOG_H
#define OPENDIALOG_H

#include <QDialog>
#include "ui_opendialog.h"

class QWidget;

class OpenDialog : public QDialog
{
    Q_OBJECT

public:
    OpenDialog(QWidget * parent = NULL);
    QString GetLeftItem() const;
    QString GetRightItem() const;

protected slots:
    void SelectLeftItem();
    void SelectRightItem();

private:
    Ui::mOpenDlg mUI;
};

#endif // OPENDIALOG_H
