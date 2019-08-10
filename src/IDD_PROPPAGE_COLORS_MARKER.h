#ifndef IDD_PROPPAGE_COLORS_MARKER_H
#define IDD_PROPPAGE_COLORS_MARKER_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COLORS_MARKER;
}
class IDD_PROPPAGE_COLORS_MARKER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COLORS_MARKER(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COLORS_MARKER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_COLORS_MARKER *ui;
};
#endif // IDD_PROPPAGE_COLORS_MARKER_H
