#include "IDD_DIRCOMP_PROGRESS.h"
#include "ui_IDD_DIRCOMP_PROGRESS.h"
IDD_DIRCOMP_PROGRESS::IDD_DIRCOMP_PROGRESS(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_DIRCOMP_PROGRESS)
{
	ui->setupUi(this);
}
IDD_DIRCOMP_PROGRESS::~IDD_DIRCOMP_PROGRESS()
{
	delete ui;
}
void IDD_DIRCOMP_PROGRESS::on_pushButton_clicked()
{
}
