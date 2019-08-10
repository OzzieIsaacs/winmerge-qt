#ifndef IDD_SAVECLOSING_H
#define IDD_SAVECLOSING_H
#include <QDialog>
namespace Ui {
class IDD_SAVECLOSING;
}
class IDD_SAVECLOSING : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_SAVECLOSING(QWidget *parent = nullptr);
	~IDD_SAVECLOSING();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_SAVECLOSING *ui;
};
#endif // IDD_SAVECLOSING_H
