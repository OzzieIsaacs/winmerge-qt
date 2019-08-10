#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include "opendialog.h"

OpenDialog::OpenDialog(QWidget *parent)
    : QDialog(parent)
{
    mUI.setupUi(this);

    connect(mUI.mBtnBrowse1, SIGNAL(clicked()), this, SLOT(SelectLeftItem()));
    connect(mUI.mBtnBrowse2, SIGNAL(clicked()), this, SLOT(SelectRightItem()));
}

void OpenDialog::SelectLeftItem()
{
    QString selected = QFileDialog::getExistingDirectory(this,
                       tr("Select left directory to open"));

    if (!selected.isNull())
    {
        mUI.mItem1Edit->setText(selected);
    }
}

void OpenDialog::SelectRightItem()
{
    QString selected = QFileDialog::getExistingDirectory(this,
                       tr("Select right directory to open"));

    if (!selected.isNull())
    {
        mUI.mItem2Edit->setText(selected);
    }
}

QString OpenDialog::GetLeftItem() const
{
    return mUI.mItem1Edit->text();
}

QString OpenDialog::GetRightItem() const
{
    return mUI.mItem2Edit->text();
}
