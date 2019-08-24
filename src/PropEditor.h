/**
 * @file  PropEditor.h
 *
 * @brief Declaration file for PropEditor propertyheet
 *
 */
#pragma once

#ifndef IDD_PROPPAGE_EDITOR_H
#define IDD_PROPPAGE_EDITOR_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropEditor;
}
class QPropEditor : public QDialog
{
	Q_OBJECT

public:
	explicit QPropEditor(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropEditor();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	// Implementation methods
	void LoadBreakTypeStrings();
	//void UpdateDataToWindow() { UpdateData(false); }
	//void UpdateDataFromWindow() { UpdateData(true); }
	void UpdateLineDiffControls();
	void OnLineDiffControlClicked();
	void OnEnKillfocusTabEdit();

private:
	Ui::QPropEditor *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROPPAGE_EDITOR_H
