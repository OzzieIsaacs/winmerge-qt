#ifndef IDD_DIRCMP_REPORT_H
#define IDD_DIRCMP_REPORT_H
#include <QDialog>
namespace Ui {
class IDD_DIRCMP_REPORT;
}
class IDD_DIRCMP_REPORT : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_DIRCMP_REPORT(QWidget *parent = nullptr);
	~IDD_DIRCMP_REPORT();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_DIRCMP_REPORT *ui;
};
#endif // IDD_DIRCMP_REPORT_H
