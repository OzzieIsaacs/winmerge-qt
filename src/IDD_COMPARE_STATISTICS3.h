#ifndef IDD_COMPARE_STATISTICS3_H
#define IDD_COMPARE_STATISTICS3_H
#include <QDialog>
namespace Ui {
class IDD_COMPARE_STATISTICS3;
}
class IDD_COMPARE_STATISTICS3 : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_COMPARE_STATISTICS3(QWidget *parent = nullptr);
	~IDD_COMPARE_STATISTICS3();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_COMPARE_STATISTICS3 *ui;
};
#endif // IDD_COMPARE_STATISTICS3_H
