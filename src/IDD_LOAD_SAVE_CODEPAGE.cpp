#include "IDD_LOAD_SAVE_CODEPAGE.h"
#include "ui_IDD_LOAD_SAVE_CODEPAGE.h"
IDD_LOAD_SAVE_CODEPAGE::IDD_LOAD_SAVE_CODEPAGE(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_LOAD_SAVE_CODEPAGE)
{
	ui->setupUi(this);
}
IDD_LOAD_SAVE_CODEPAGE::~IDD_LOAD_SAVE_CODEPAGE()
{
	delete ui;
}
void IDD_LOAD_SAVE_CODEPAGE::on_pushButton_clicked()
{
}
