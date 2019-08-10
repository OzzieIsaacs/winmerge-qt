#ifndef IDD_PROPPAGE_COLORS_SYNTAX_H
#define IDD_PROPPAGE_COLORS_SYNTAX_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COLORS_SYNTAX;
}
class IDD_PROPPAGE_COLORS_SYNTAX : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COLORS_SYNTAX(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COLORS_SYNTAX();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_COLORS_SYNTAX *ui;
};
#endif // IDD_PROPPAGE_COLORS_SYNTAX_H
