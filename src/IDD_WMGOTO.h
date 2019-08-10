#ifndef IDD_WMGOTO_H
#define IDD_WMGOTO_H
#include <QDialog>
namespace Ui {
class IDD_WMGOTO;
}
class IDD_WMGOTO : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_WMGOTO(QWidget *parent = nullptr);
	~IDD_WMGOTO();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_WMGOTO *ui;
};
#endif // IDD_WMGOTO_H
