#ifndef IDD_SELECTUNPACKER_H
#define IDD_SELECTUNPACKER_H
#include <QDialog>
namespace Ui {
class IDD_SELECTUNPACKER;
}
class IDD_SELECTUNPACKER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_SELECTUNPACKER(QWidget *parent = nullptr);
	~IDD_SELECTUNPACKER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_SELECTUNPACKER *ui;
};
#endif // IDD_SELECTUNPACKER_H
