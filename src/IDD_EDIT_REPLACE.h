#ifndef IDD_EDIT_REPLACE_H
#define IDD_EDIT_REPLACE_H
#include <QDialog>
namespace Ui {
class IDD_EDIT_REPLACE;
}
class IDD_EDIT_REPLACE : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_EDIT_REPLACE(QWidget *parent = nullptr);
	~IDD_EDIT_REPLACE();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_EDIT_REPLACE *ui;
};
#endif // IDD_EDIT_REPLACE_H
