/**
 * @file  PropArchive.h
 *
 * @brief Declaration file for PropArchive propertyheet
 *
 */
#pragma once

#ifndef PROPARCHIVE_H
#define PROPARCHIVE_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropArchive;
}
class QPropArchive : public QDialog
{
	Q_OBJECT

public:
	explicit QPropArchive(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropArchive();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	void UpdateControls();
	void OnEnableClicked();

private:
	Ui::QPropArchive *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROP_ARCHIVE_H
