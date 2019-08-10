#ifndef IDD_ENCODINGERROR_H
#define IDD_ENCODINGERROR_H
#include <QDialog>
namespace Ui {
class IDD_ENCODINGERROR;
}
class IDD_ENCODINGERROR : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_ENCODINGERROR(QWidget *parent = nullptr);
	~IDD_ENCODINGERROR();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_ENCODINGERROR *ui;
};
#endif // IDD_ENCODINGERROR_H
