#ifndef IDD_PROPPAGE_COMPARE_FOLDER_H
#define IDD_PROPPAGE_COMPARE_FOLDER_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COMPARE_FOLDER;
}
class IDD_PROPPAGE_COMPARE_FOLDER : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COMPARE_FOLDER(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COMPARE_FOLDER();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();


private slots:
	bool OnInitDialog();
	void OnDefaults();
	void OnCbnSelchangeComparemethodcombo();
	void OnBnClickedRecursCheck();

private:
	Ui::IDD_PROPPAGE_COMPARE_FOLDER *ui;
	void UpdateControls();
};
#endif // IDD_PROPPAGE_COMPARE_FOLDER_H
