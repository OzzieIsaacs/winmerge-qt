#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include "openfilesdialog.h"

OpenFilesDialog::OpenFilesDialog(QWidget *parent)
    : QDialog(parent)
{
    mUI.setupUi(this);

    connect(mUI.mBtnBrowse1, SIGNAL(clicked()), this, SLOT(SelectLeftItem()));
    connect(mUI.mBtnBrowse2, SIGNAL(clicked()), this, SLOT(SelectRightItem()));
}

void OpenFilesDialog::SelectLeftItem()
{
    QString selected = QFileDialog::getOpenFileName(this,
                       tr("Select left file to open"));

    if (!selected.isNull())
    {
        mUI.mItem1Edit->setText(selected);
    }
}

void OpenFilesDialog::SelectRightItem()
{
    QString selected = QFileDialog::getOpenFileName(this,
                       tr("Select right file to open"));

    if (!selected.isNull())
    {
        mUI.mItem2Edit->setText(selected);
    }
}

QString OpenFilesDialog::GetLeftItem() const
{
    return mUI.mItem1Edit->text();
}

QString OpenFilesDialog::GetRightItem() const
{
    return mUI.mItem2Edit->text();
}
