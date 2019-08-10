#include "IDD_WMGOTO.h"
#include "ui_IDD_WMGOTO.h"
IDD_WMGOTO::IDD_WMGOTO(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_WMGOTO)
{
	ui->setupUi(this);
}
IDD_WMGOTO::~IDD_WMGOTO()
{
	delete ui;
}
void IDD_WMGOTO::on_pushButton_clicked()
{
}
