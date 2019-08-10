#include "IDD_PROPPAGE_COLORS_DIR.h"
#include "ui_IDD_PROPPAGE_COLORS_DIR.h"
IDD_PROPPAGE_COLORS_DIR::IDD_PROPPAGE_COLORS_DIR(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COLORS_DIR)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_COLORS_DIR::~IDD_PROPPAGE_COLORS_DIR()
{
	delete ui;
}
void IDD_PROPPAGE_COLORS_DIR::on_pushButton_clicked()
{
}
