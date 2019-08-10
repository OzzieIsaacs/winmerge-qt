#ifndef IDD_DIRCOLS_H
#define IDD_DIRCOLS_H
#include <QDialog>
namespace Ui {
class IDD_DIRCOLS;
}
class IDD_DIRCOLS : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_DIRCOLS(QWidget *parent = nullptr);
	~IDD_DIRCOLS();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_DIRCOLS *ui;
};
#endif // IDD_DIRCOLS_H
