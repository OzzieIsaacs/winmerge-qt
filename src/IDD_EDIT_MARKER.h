#ifndef IDD_EDIT_MARKER_H
#define IDD_EDIT_MARKER_H
#include <QDialog>
namespace Ui {
class IDD_EDIT_MARKER;
}
class IDD_EDIT_MARKER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_EDIT_MARKER(QWidget *parent = nullptr);
	~IDD_EDIT_MARKER();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_EDIT_MARKER *ui;
};
#endif // IDD_EDIT_MARKER_H
