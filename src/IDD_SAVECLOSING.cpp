#include "IDD_SAVECLOSING.h"
#include "ui_IDD_SAVECLOSING.h"
IDD_SAVECLOSING::IDD_SAVECLOSING(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_SAVECLOSING)
{
	ui->setupUi(this);
}
IDD_SAVECLOSING::~IDD_SAVECLOSING()
{
	delete ui;
}
void IDD_SAVECLOSING::on_pushButton_clicked()
{
}
