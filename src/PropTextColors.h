/**
 * @file  PropTextColors.h
 *
 * @brief Declaration file for PropTextColors propertyheet
 *
 */
#pragma once

#ifndef IDD_PROPPAGE_COLORS_TEXT_H
#define IDD_PROPPAGE_COLORS_TEXT_H
// #include "ColorButton.h"
#include <array>
#include <QDialog>
#include "QOptionsMgr.h"

class SyntaxColors;

namespace Ui {
class QPropTextColors;
}
class QPropTextColors : public QDialog
{
	Q_OBJECT

public:
	explicit QPropTextColors(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropTextColors();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	// Generated message map functions
	//{{AFX_MSG(PropTextColors)
	void OnWhitespaceBackgroundColor();
	void OnRegularBackgroundColor();
	void OnRegularTextColor();
	void OnSelectionBackgroundColor();
	void OnSelectionTextColor();
	void OnMarginBackgroundColor();
	void OnDefaultsStandardColors();

private:
	SyntaxColors *m_pTempColors;
	//std::array<COLORREF, 16> m_cCustColors;

	Ui::QPropTextColors *ui;
	QOptionsMgr* m_options;

	typedef enum { SET_DEFAULTS, READ_OPTIONS, LOAD_COLORS } OPERATION;

	//void BrowseColorAndSave(CColorButton & colorButton, int colorIndex);
	void SerializeColorsToFromScreen(OPERATION op);
	//void SerializeColorToFromScreen(OPERATION op, CColorButton & btn, int colorIndex);
	void EnableColorButtons(bool bEnable);



};
#endif // IDD_PROPPAGE_COLORS_TEXT_H
