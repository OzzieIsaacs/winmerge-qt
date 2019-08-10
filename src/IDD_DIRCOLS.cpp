#include "IDD_DIRCOLS.h"
#include "ui_IDD_DIRCOLS.h"
IDD_DIRCOLS::IDD_DIRCOLS(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_DIRCOLS)
{
	ui->setupUi(this);
}
IDD_DIRCOLS::~IDD_DIRCOLS()
{
	delete ui;
}
void IDD_DIRCOLS::on_pushButton_clicked()
{
}
