#ifndef IDD_PROPPAGE_CODEPAGE_H
#define IDD_PROPPAGE_CODEPAGE_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_CODEPAGE;
}
class IDD_PROPPAGE_CODEPAGE : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_CODEPAGE(QWidget *parent = nullptr);
	~IDD_PROPPAGE_CODEPAGE();
private slots:
	void on_pushButton_clicked();
private:
	Ui::IDD_PROPPAGE_CODEPAGE *ui;
};
#endif // IDD_PROPPAGE_CODEPAGE_H
