#include "IDD_PROPPAGE_COLORS_SYNTAX.h"
#include "ui_IDD_PROPPAGE_COLORS_SYNTAX.h"
IDD_PROPPAGE_COLORS_SYNTAX::IDD_PROPPAGE_COLORS_SYNTAX(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COLORS_SYNTAX)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_COLORS_SYNTAX::~IDD_PROPPAGE_COLORS_SYNTAX()
{
	delete ui;
}
void IDD_PROPPAGE_COLORS_SYNTAX::on_pushButton_clicked()
{
}
