#ifndef IDD_COMPARE_STATISTICS_H
#define IDD_COMPARE_STATISTICS_H
#include <QDialog>
namespace Ui {
class IDD_COMPARE_STATISTICS;
}
class IDD_COMPARE_STATISTICS : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_COMPARE_STATISTICS(QWidget *parent = nullptr);
	~IDD_COMPARE_STATISTICS();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_COMPARE_STATISTICS *ui;
};
#endif // IDD_COMPARE_STATISTICS_H
