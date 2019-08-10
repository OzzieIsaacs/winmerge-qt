#include "IDD_FILEFILTERS.h"
#include "ui_IDD_FILEFILTERS.h"
IDD_FILEFILTERS::IDD_FILEFILTERS(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_FILEFILTERS)
{
	ui->setupUi(this);
}
IDD_FILEFILTERS::~IDD_FILEFILTERS()
{
	delete ui;
}
void IDD_FILEFILTERS::on_pushButton_clicked()
{
}
