/**
 * @file  PropCodepage.h
 *
 * @brief Declaration of PropCodepage class
 */
#pragma once

#ifndef IDD_PROPPAGE_CODEPAGE_H
#define IDD_PROPPAGE_CODEPAGE_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropCodepage;
}
class QPropCodepage : public QDialog
{
	Q_OBJECT

public:
	explicit QPropCodepage(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropCodepage();

// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	void GetEncodingCodePageFromNameString();
	void OnCpSystem();
	void OnCpCustom();
	void OnCpUi();
	void OnDetectCodepage2();
	void OnDetectAutodetecttype(const QString&);

private:
	Ui::QPropCodepage *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROPPAGE_CODEPAGE_H
