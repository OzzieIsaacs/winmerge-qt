#include "IDD_DIR_FILTER.h"
#include "ui_IDD_DIR_FILTER.h"
IDD_DIR_FILTER::IDD_DIR_FILTER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_DIR_FILTER)
{
	ui->setupUi(this);
}
IDD_DIR_FILTER::~IDD_DIR_FILTER()
{
	delete ui;
}
void IDD_DIR_FILTER::on_pushButton_clicked()
{
}
