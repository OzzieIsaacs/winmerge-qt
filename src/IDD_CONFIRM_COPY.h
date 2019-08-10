#ifndef IDD_CONFIRM_COPY_H
#define IDD_CONFIRM_COPY_H
#include <QDialog>
namespace Ui {
class IDD_CONFIRM_COPY;
}
class IDD_CONFIRM_COPY : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_CONFIRM_COPY(QWidget *parent = nullptr);
	~IDD_CONFIRM_COPY();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_CONFIRM_COPY *ui;
};
#endif // IDD_CONFIRM_COPY_H
