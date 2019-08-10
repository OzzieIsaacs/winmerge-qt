#include "IDD_PLUGINS_LIST.h"
#include "ui_IDD_PLUGINS_LIST.h"
IDD_PLUGINS_LIST::IDD_PLUGINS_LIST(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PLUGINS_LIST)
{
	ui->setupUi(this);
}
IDD_PLUGINS_LIST::~IDD_PLUGINS_LIST()
{
	delete ui;
}
void IDD_PLUGINS_LIST::on_pushButton_clicked()
{
}
