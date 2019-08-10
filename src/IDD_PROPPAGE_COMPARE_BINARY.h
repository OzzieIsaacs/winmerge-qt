#ifndef IDD_PROPPAGE_COMPARE_BINARY_H
#define IDD_PROPPAGE_COMPARE_BINARY_H
#include <QDialog>
namespace Ui {
class IDD_PROPPAGE_COMPARE_BINARY;
}
class IDD_PROPPAGE_COMPARE_BINARY : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COMPARE_BINARY(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COMPARE_BINARY();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private:
	Ui::IDD_PROPPAGE_COMPARE_BINARY *ui;
	void OnViewSettings();
	void OnBinaryMode();
	void OnCharacterSet();
	void OnDefaults();

};
#endif // IDD_PROPPAGE_COMPARE_BINARY_H
