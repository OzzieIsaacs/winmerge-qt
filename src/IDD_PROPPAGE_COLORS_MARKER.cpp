#include "IDD_PROPPAGE_COLORS_MARKER.h"
#include "ui_IDD_PROPPAGE_COLORS_MARKER.h"
IDD_PROPPAGE_COLORS_MARKER::IDD_PROPPAGE_COLORS_MARKER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COLORS_MARKER)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_COLORS_MARKER::~IDD_PROPPAGE_COLORS_MARKER()
{
	delete ui;
}
void IDD_PROPPAGE_COLORS_MARKER::on_pushButton_clicked()
{
}
