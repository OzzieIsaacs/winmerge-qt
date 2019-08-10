#ifndef IDD_OPEN_H
#define IDD_OPEN_H
#include <QDialog>
namespace Ui {
class IDD_OPEN;
}
class IDD_OPEN : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_OPEN(QWidget *parent = nullptr);
	~IDD_OPEN();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_OPEN *ui;
};
#endif // IDD_OPEN_H
