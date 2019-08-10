#ifndef IDD_FILEFILTERS_H
#define IDD_FILEFILTERS_H
#include <QDialog>
namespace Ui {
class IDD_FILEFILTERS;
}
class IDD_FILEFILTERS : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_FILEFILTERS(QWidget *parent = nullptr);
	~IDD_FILEFILTERS();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_FILEFILTERS *ui;
};
#endif // IDD_FILEFILTERS_H
