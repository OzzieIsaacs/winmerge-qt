#ifndef IDD_GENERATE_PATCH_H
#define IDD_GENERATE_PATCH_H
#include <QDialog>
namespace Ui {
class IDD_GENERATE_PATCH;
}
class IDD_GENERATE_PATCH : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_GENERATE_PATCH(QWidget *parent = nullptr);
	~IDD_GENERATE_PATCH();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_GENERATE_PATCH *ui;
};
#endif // IDD_GENERATE_PATCH_H
