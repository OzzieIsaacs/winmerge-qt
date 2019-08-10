#ifndef IDD_DIR_FILTER_H
#define IDD_DIR_FILTER_H
#include <QDialog>
namespace Ui {
class IDD_DIR_FILTER;
}
class IDD_DIR_FILTER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_DIR_FILTER(QWidget *parent = nullptr);
	~IDD_DIR_FILTER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_DIR_FILTER *ui;
};
#endif // IDD_DIR_FILTER_H
