#include "IDD_EDIT_FIND.h"
#include "ui_IDD_EDIT_FIND.h"
IDD_EDIT_FIND::IDD_EDIT_FIND(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_EDIT_FIND)
{
	ui->setupUi(this);
}
IDD_EDIT_FIND::~IDD_EDIT_FIND()
{
	delete ui;
}
void IDD_EDIT_FIND::on_pushButton_clicked()
{
}
