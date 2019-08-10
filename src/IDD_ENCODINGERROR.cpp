#include "IDD_ENCODINGERROR.h"
#include "ui_IDD_ENCODINGERROR.h"
IDD_ENCODINGERROR::IDD_ENCODINGERROR(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_ENCODINGERROR)
{
	ui->setupUi(this);
}
IDD_ENCODINGERROR::~IDD_ENCODINGERROR()
{
	delete ui;
}
void IDD_ENCODINGERROR::on_pushButton_clicked()
{
}
