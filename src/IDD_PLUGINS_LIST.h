#ifndef IDD_PLUGINS_LIST_H
#define IDD_PLUGINS_LIST_H
#include <QDialog>
namespace Ui {
class IDD_PLUGINS_LIST;
}
class IDD_PLUGINS_LIST : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PLUGINS_LIST(QWidget *parent = nullptr);
	~IDD_PLUGINS_LIST();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PLUGINS_LIST *ui;
};
#endif // IDD_PLUGINS_LIST_H
