#include "IDD_TEST_FILTER.h"
#include "ui_IDD_TEST_FILTER.h"
IDD_TEST_FILTER::IDD_TEST_FILTER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_TEST_FILTER)
{
	ui->setupUi(this);
}
IDD_TEST_FILTER::~IDD_TEST_FILTER()
{
	delete ui;
}
void IDD_TEST_FILTER::on_pushButton_clicked()
{
}
