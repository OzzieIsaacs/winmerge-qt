#include "IDD_PROPPAGE_FILTER.h"
#include "ui_IDD_PROPPAGE_FILTER.h"
IDD_PROPPAGE_FILTER::IDD_PROPPAGE_FILTER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_FILTER)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_FILTER::~IDD_PROPPAGE_FILTER()
{
	delete ui;
}
void IDD_PROPPAGE_FILTER::on_pushButton_clicked()
{
}
