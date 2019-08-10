#include "IDD_EDIT_MARKER.h"
#include "ui_IDD_EDIT_MARKER.h"
IDD_EDIT_MARKER::IDD_EDIT_MARKER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_EDIT_MARKER)
{
	ui->setupUi(this);
}
IDD_EDIT_MARKER::~IDD_EDIT_MARKER()
{
	delete ui;
}
void IDD_EDIT_MARKER::on_pushButton_clicked()
{
}
