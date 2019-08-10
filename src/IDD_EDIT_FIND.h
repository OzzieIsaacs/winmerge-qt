#ifndef IDD_EDIT_FIND_H
#define IDD_EDIT_FIND_H
#include <QDialog>
namespace Ui {
class IDD_EDIT_FIND;
}
class IDD_EDIT_FIND : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_EDIT_FIND(QWidget *parent = nullptr);
	~IDD_EDIT_FIND();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_EDIT_FIND *ui;
};
#endif // IDD_EDIT_FIND_H
