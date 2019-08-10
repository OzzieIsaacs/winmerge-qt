#ifndef IDD_TEST_FILTER_H
#define IDD_TEST_FILTER_H
#include <QDialog>
namespace Ui {
class IDD_TEST_FILTER;
}
class IDD_TEST_FILTER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_TEST_FILTER(QWidget *parent = nullptr);
	~IDD_TEST_FILTER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_TEST_FILTER *ui;
};
#endif // IDD_TEST_FILTER_H
