#include "IDD_OPEN.h"
#include "ui_IDD_OPEN.h"
IDD_OPEN::IDD_OPEN(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_OPEN)
{
	ui->setupUi(this);
}
IDD_OPEN::~IDD_OPEN()
{
	delete ui;
}
void IDD_OPEN::on_pushButton_clicked()
{
}
