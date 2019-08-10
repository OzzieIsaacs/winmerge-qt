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

namespace Ui {
class QPropShell;
}
class QPropShell : public QDialog
{
	Q_OBJECT

public:
	explicit QPropShell(QWidget *parent = nullptr);
	~QPropShell();

// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

// Dialog Data
	// enum { IDD = IDD_PROPPAGE_SHELL };
	bool m_bContextAdded;
	bool m_bContextAdvanced;

private:
	Ui::QPropShell *ui;
	QSettings m_options;

	void OnAddToExplorer();
	void OnRegisterShellExtension();
	void OnUnregisterShellExtension();
	//void OnTimer(UINT_PTR nIDEvent);

	void GetContextRegValues();
	void AdvancedContextMenuCheck();
	void UpdateButtons();

	void SaveMergePath();

};
#endif // IDD_PROPPAGE_SHELL_H