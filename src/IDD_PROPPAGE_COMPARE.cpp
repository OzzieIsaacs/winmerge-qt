#include "IDD_PROPPAGE_COMPARE.h"
#include "ui_IDD_PROPPAGE_COMPARE.h"
IDD_PROPPAGE_COMPARE::IDD_PROPPAGE_COMPARE(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COMPARE)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_COMPARE::~IDD_PROPPAGE_COMPARE()
{
	delete ui;
}
void IDD_PROPPAGE_COMPARE::on_pushButton_clicked()
{
}
