/**
 * @file  PropCompareFolder.h
 *
 * @brief Declaration of PropCompareFolder propertysheet
 */
#pragma once

#ifndef IDD_PROPPAGE_COMPARE_FOLDER_H
#define IDD_PROPPAGE_COMPARE_FOLDER_H
#include <QDialog>
#include <QSettings>

namespace Ui {
class QPropCompareFolder;
}
class QPropCompareFolder : public QDialog
{
	Q_OBJECT

public:
	explicit QPropCompareFolder(QWidget *parent = nullptr);
	~QPropCompareFolder();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();


private slots:
	void OnDefaults();
	void OnCbnSelchangeComparemethodcombo(const QString&);
	void OnBnClickedRecursCheck();
	void UpdateControls();

private:
	Ui::QPropCompareFolder *ui;
	QSettings m_options;

};
#endif // IDD_PROPPAGE_COMPARE_FOLDER_H
