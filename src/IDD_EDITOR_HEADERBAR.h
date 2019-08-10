#ifndef IDD_EDITOR_HEADERBAR_H
#define IDD_EDITOR_HEADERBAR_H
#include <QDialog>
namespace Ui {
class IDD_EDITOR_HEADERBAR;
}
class IDD_EDITOR_HEADERBAR : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_EDITOR_HEADERBAR(QWidget *parent = nullptr);
	~IDD_EDITOR_HEADERBAR();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_EDITOR_HEADERBAR *ui;
};
#endif // IDD_EDITOR_HEADERBAR_H
