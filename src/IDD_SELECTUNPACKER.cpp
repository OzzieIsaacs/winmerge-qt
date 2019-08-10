#include "IDD_SELECTUNPACKER.h"
#include "ui_IDD_SELECTUNPACKER.h"
IDD_SELECTUNPACKER::IDD_SELECTUNPACKER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_SELECTUNPACKER)
{
	ui->setupUi(this);
}
IDD_SELECTUNPACKER::~IDD_SELECTUNPACKER()
{
	delete ui;
}
void IDD_SELECTUNPACKER::on_pushButton_clicked()
{
}
