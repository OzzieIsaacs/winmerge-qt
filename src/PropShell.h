/**
 * @file  PropShell.h
 *
 * @brief Declaration of Shell options dialog class
 */
#pragma once

#ifndef IDD_PROPPAGE_SHELL_H
#define IDD_PROPPAGE_SHELL_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropShell;
}
class QPropShell : public QDialog
{
	Q_OBJECT

public:
	explicit QPropShell(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropShell();

// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

// Dialog Data
	// enum { IDD = IDD_PROPPAGE_SHELL };
	bool m_bContextAdded;
	bool m_bContextAdvanced;

private slots:
	// Implementation methods
	void OnAddToExplorer();
	void OnRegisterShellExtension();
	void OnUnregisterShellExtension();

private:
	Ui::QPropShell *ui;
	QOptionsMgr* m_options;

	//void OnTimer(UINT_PTR nIDEvent);

	void GetContextRegValues();
	void AdvancedContextMenuCheck();
	void UpdateButtons();

	void SaveMergePath();

};
#endif // IDD_PROPPAGE_SHELL_H
