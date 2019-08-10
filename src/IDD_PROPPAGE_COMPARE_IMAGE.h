#ifndef IDD_PROPPAGE_COMPARE_IMAGE_H
#define IDD_PROPPAGE_COMPARE_IMAGE_H
#include <QDialog>
#include <QString>

namespace Ui {
class IDD_PROPPAGE_COMPARE_IMAGE;
}
class IDD_PROPPAGE_COMPARE_IMAGE : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COMPARE_IMAGE(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COMPARE_IMAGE();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

// Dialog Data
	//{{AFX_DATA(PropCompareImage)
	//enum { IDD = IDD_PROPPAGE_COMPARE_IMAGE };
	QString m_sFilePatterns;
	//}}AFX_DATA

private slots:
	void OnDefaults();

private:
	Ui::IDD_PROPPAGE_COMPARE_IMAGE *ui;
};
#endif // IDD_PROPPAGE_COMPARE_IMAGE_H
