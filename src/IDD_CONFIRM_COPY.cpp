#include "IDD_CONFIRM_COPY.h"
#include "ui_IDD_CONFIRM_COPY.h"
IDD_CONFIRM_COPY::IDD_CONFIRM_COPY(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_CONFIRM_COPY)
{
	ui->setupUi(this);
}
IDD_CONFIRM_COPY::~IDD_CONFIRM_COPY()
{
	delete ui;
}
void IDD_CONFIRM_COPY::on_pushButton_clicked()
{
}
