#include "IDD_SHARED_FILTER.h"
#include "ui_IDD_SHARED_FILTER.h"
IDD_SHARED_FILTER::IDD_SHARED_FILTER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_SHARED_FILTER)
{
	ui->setupUi(this);
}
IDD_SHARED_FILTER::~IDD_SHARED_FILTER()
{
	delete ui;
}
void IDD_SHARED_FILTER::on_pushButton_clicked()
{
}
