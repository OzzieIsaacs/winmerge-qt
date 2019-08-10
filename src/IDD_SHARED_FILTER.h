#ifndef IDD_SHARED_FILTER_H
#define IDD_SHARED_FILTER_H
#include <QDialog>
namespace Ui {
class IDD_SHARED_FILTER;
}
class IDD_SHARED_FILTER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_SHARED_FILTER(QWidget *parent = nullptr);
	~IDD_SHARED_FILTER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_SHARED_FILTER *ui;
};
#endif // IDD_SHARED_FILTER_H
