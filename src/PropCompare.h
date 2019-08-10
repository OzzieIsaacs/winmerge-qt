#ifndef IDD_PROPPAGE_COMPARE_H
#define IDD_PROPPAGE_COMPARE_H
#include <QDialog>
#include <QSettings>

namespace Ui {
class QPropCompare;
}
class QPropCompare : public QDialog
{
	Q_OBJECT

public:
	explicit QPropCompare(QWidget *parent = nullptr);
	~QPropCompare();

// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	void OnDefaults();
private:
	Ui::QPropCompare *ui;
	QSettings m_options;
};
#endif // IDD_PROPPAGE_COMPARE_H
