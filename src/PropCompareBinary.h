/**
 * @file  PropCompareBinary.h
 *
 * @brief Declaration of PropCompareBinary propertysheet
 */
#ifndef IDD_PROPPAGE_COMPARE_BINARY_H
#define IDD_PROPPAGE_COMPARE_BINARY_H
#include <QDialog>
#include <QSettings>
namespace Ui {
class QPropCompareBinary;
}
class QPropCompareBinary : public QDialog
{
	Q_OBJECT

public:
	explicit QPropCompareBinary(QWidget *parent = nullptr);
	~QPropCompareBinary();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	void OnViewSettings();
	void OnBinaryMode();
	void OnCharacterSet();
	void OnDefaults();

private:
	Ui::QPropCompareBinary *ui;
	QSettings m_options;
};
#endif // IDD_PROPPAGE_COMPARE_BINARY_H
