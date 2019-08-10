#ifndef IDD_PROPPAGE_COLORS_WINMERGE_H
#define IDD_PROPPAGE_COLORS_WINMERGE_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COLORS_WINMERGE;
}
class IDD_PROPPAGE_COLORS_WINMERGE : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COLORS_WINMERGE(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COLORS_WINMERGE();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_COLORS_WINMERGE *ui;
};
#endif // IDD_PROPPAGE_COLORS_WINMERGE_H
