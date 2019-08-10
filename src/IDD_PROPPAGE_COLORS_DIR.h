#ifndef IDD_PROPPAGE_COLORS_DIR_H
#define IDD_PROPPAGE_COLORS_DIR_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COLORS_DIR;
}
class IDD_PROPPAGE_COLORS_DIR : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COLORS_DIR(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COLORS_DIR();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_COLORS_DIR *ui;
};
#endif // IDD_PROPPAGE_COLORS_DIR_H
