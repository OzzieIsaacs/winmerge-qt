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
namespace Ui {
class QPropEditor;
}
class QPropEditor : public QDialog
{
	Q_OBJECT

public:
	explicit QPropEditor(QWidget *parent = nullptr);
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

private:
	Ui::QPropEditor *ui;
	bool OnInitDialog();
	void OnLineDiffControlClicked();
	void OnEnKillfocusTabEdit();

};
#endif // IDD_PROPPAGE_EDITOR_H
