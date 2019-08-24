/**
 * @file  PropBackups.h
 *
 * @brief Declaration file for PropBackups propertyheet
 *
 */
#pragma once

#ifndef IDD_PROPPAGE_BACKUPS_H
#define IDD_PROPPAGE_BACKUPS_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropBackups;
}
class QPropBackups : public QDialog
{
	Q_OBJECT

public:
	explicit QPropBackups(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropBackups();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

	enum BACKUP_FOLDER
	{
		FOLDER_ORIGINAL = 0,
		FOLDER_GLOBAL,
	};

private slots:
	void OnBnClickedBackupBrowse();

private:
	Ui::QPropBackups *ui;
	QOptionsMgr* m_options;

};
#endif // IDD_PROPPAGE_BACKUPS_H
