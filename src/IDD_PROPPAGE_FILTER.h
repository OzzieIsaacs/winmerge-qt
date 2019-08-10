#ifndef IDD_PROPPAGE_FILTER_H
#define IDD_PROPPAGE_FILTER_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_FILTER;
}
class IDD_PROPPAGE_FILTER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_FILTER(QWidget *parent = nullptr);
	~IDD_PROPPAGE_FILTER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_FILTER *ui;
};
#endif // IDD_PROPPAGE_FILTER_H
