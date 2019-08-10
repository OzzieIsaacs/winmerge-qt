#include "IDD_EDIT_REPLACE.h"
#include "ui_IDD_EDIT_REPLACE.h"
IDD_EDIT_REPLACE::IDD_EDIT_REPLACE(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_EDIT_REPLACE)
{
	ui->setupUi(this);
}
IDD_EDIT_REPLACE::~IDD_EDIT_REPLACE()
{
	delete ui;
}
void IDD_EDIT_REPLACE::on_pushButton_clicked()
{
}
