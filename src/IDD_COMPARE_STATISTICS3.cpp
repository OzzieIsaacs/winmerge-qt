#include "IDD_COMPARE_STATISTICS3.h"
#include "ui_IDD_COMPARE_STATISTICS3.h"
IDD_COMPARE_STATISTICS3::IDD_COMPARE_STATISTICS3(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_COMPARE_STATISTICS3)
{
	ui->setupUi(this);
}
IDD_COMPARE_STATISTICS3::~IDD_COMPARE_STATISTICS3()
{
	delete ui;
}
void IDD_COMPARE_STATISTICS3::on_pushButton_clicked()
{
}
