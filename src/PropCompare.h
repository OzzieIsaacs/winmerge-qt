#ifndef IDD_PROPPAGE_COMPARE_H
#define IDD_PROPPAGE_COMPARE_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropCompare;
}
class QPropCompare : public QDialog
{
	Q_OBJECT

public:
	explicit QPropCompare(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropCompare();

// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	void OnDefaults();
private:
	Ui::QPropCompare *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROPPAGE_COMPARE_H
