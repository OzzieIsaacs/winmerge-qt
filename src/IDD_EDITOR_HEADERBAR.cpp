#include "IDD_EDITOR_HEADERBAR.h"
#include "ui_IDD_EDITOR_HEADERBAR.h"
IDD_EDITOR_HEADERBAR::IDD_EDITOR_HEADERBAR(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_EDITOR_HEADERBAR)
{
	ui->setupUi(this);
}
IDD_EDITOR_HEADERBAR::~IDD_EDITOR_HEADERBAR()
{
	delete ui;
}
void IDD_EDITOR_HEADERBAR::on_pushButton_clicked()
{
}
