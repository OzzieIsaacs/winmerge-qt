/**
 * @file  PropCompareImage.h
 *
 * @brief Declaration of PropCompareImage propertysheet
 */
#pragma once

#ifndef IDD_PROPPAGE_COMPARE_IMAGE_H
#define IDD_PROPPAGE_COMPARE_IMAGE_H
#include <QDialog>
#include <QString>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropCompareImage;
}
class QPropCompareImage : public QDialog
{
	Q_OBJECT

public:
	explicit QPropCompareImage(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropCompareImage();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

// Dialog Data
	//{{AFX_DATA(PropCompareImage)
	//enum { IDD = IDD_PROPPAGE_COMPARE_IMAGE };
	// QString m_sFilePatterns;
	//}}AFX_DATA

private slots:
	void OnDefaults();

private:
	Ui::QPropCompareImage *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROPPAGE_COMPARE_IMAGE_H
