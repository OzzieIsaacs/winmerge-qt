#ifndef IDD_PROPPAGE_COMPARE_H
#define IDD_PROPPAGE_COMPARE_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COMPARE;
}
class IDD_PROPPAGE_COMPARE : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COMPARE(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COMPARE();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_COMPARE *ui;
};
#endif // IDD_PROPPAGE_COMPARE_H
