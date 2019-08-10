#include "IDD_COMPARE_STATISTICS.h"
#include "ui_IDD_COMPARE_STATISTICS.h"
IDD_COMPARE_STATISTICS::IDD_COMPARE_STATISTICS(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_COMPARE_STATISTICS)
{
	ui->setupUi(this);
}
IDD_COMPARE_STATISTICS::~IDD_COMPARE_STATISTICS()
{
	delete ui;
}
void IDD_COMPARE_STATISTICS::on_pushButton_clicked()
{
}
