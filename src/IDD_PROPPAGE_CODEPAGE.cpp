#include "IDD_PROPPAGE_CODEPAGE.h"
#include "ui_IDD_PROPPAGE_CODEPAGE.h"
IDD_PROPPAGE_CODEPAGE::IDD_PROPPAGE_CODEPAGE(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_CODEPAGE)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_CODEPAGE::~IDD_PROPPAGE_CODEPAGE()
{
	delete ui;
}
void IDD_PROPPAGE_CODEPAGE::on_pushButton_clicked()
{
}
