#ifndef IDD_LOAD_SAVE_CODEPAGE_H
#define IDD_LOAD_SAVE_CODEPAGE_H
#include <QDialog>
namespace Ui {
class IDD_LOAD_SAVE_CODEPAGE;
}
class IDD_LOAD_SAVE_CODEPAGE : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_LOAD_SAVE_CODEPAGE(QWidget *parent = nullptr);
	~IDD_LOAD_SAVE_CODEPAGE();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_LOAD_SAVE_CODEPAGE *ui;
};
#endif // IDD_LOAD_SAVE_CODEPAGE_H
