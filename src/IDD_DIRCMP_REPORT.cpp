#include "IDD_DIRCMP_REPORT.h"
#include "ui_IDD_DIRCMP_REPORT.h"
IDD_DIRCMP_REPORT::IDD_DIRCMP_REPORT(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_DIRCMP_REPORT)
{
	ui->setupUi(this);
}
IDD_DIRCMP_REPORT::~IDD_DIRCMP_REPORT()
{
	delete ui;
}
void IDD_DIRCMP_REPORT::on_pushButton_clicked()
{
}
