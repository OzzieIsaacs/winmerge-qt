#include "IDD_GENERATE_PATCH.h"
#include "ui_IDD_GENERATE_PATCH.h"
IDD_GENERATE_PATCH::IDD_GENERATE_PATCH(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_GENERATE_PATCH)
{
	ui->setupUi(this);
}
IDD_GENERATE_PATCH::~IDD_GENERATE_PATCH()
{
	delete ui;
}
void IDD_GENERATE_PATCH::on_pushButton_clicked()
{
}
