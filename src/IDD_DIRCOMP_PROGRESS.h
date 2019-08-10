#ifndef IDD_DIRCOMP_PROGRESS_H
#define IDD_DIRCOMP_PROGRESS_H
#include <QDialog>
namespace Ui {
class IDD_DIRCOMP_PROGRESS;
}
class IDD_DIRCOMP_PROGRESS : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_DIRCOMP_PROGRESS(QWidget *parent = nullptr);
	~IDD_DIRCOMP_PROGRESS();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_DIRCOMP_PROGRESS *ui;
};
#endif // IDD_DIRCOMP_PROGRESS_H
