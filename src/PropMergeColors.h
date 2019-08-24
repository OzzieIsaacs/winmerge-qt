/**
 * @file  PropColors.h
 *
 * @brief Declaration file for PropMergeColors propertyheet
 *
 */
#pragma once

#ifndef IDD_PROPPAGE_COLORS_WINMERGE_H
#define IDD_PROPPAGE_COLORS_WINMERGE_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"
//#include "ColorButton.h"

namespace Ui {
class QPropMergeColors;
}
class QPropMergeColors : public QDialog
{
	Q_OBJECT

public:
	explicit QPropMergeColors(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropMergeColors();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();


private slots:
	// static const COLORREF COLOR_NONE = 0xffffffff;
	//typedef enum { SET_DEFAULTS, WRITE_OPTIONS, READ_OPTIONS } OPERATION;
	//typedef enum { COLORSCHEME_GITHUBBITBUCKET} COLORSCHEME;

	/*void BrowseColor(CColorButton & colorButton);
	void SerializeColors(OPERATION op);
	void SerializeColor(OPERATION op, CColorButton & btn, const QString& optionName);
	void UpdateTextColorButtonState(int checkboxId, CColorButton &btn);*/
	void UpdateTextColorButtonsState();
	void SetColorScheme(int scheme);

	// std::array<COLORREF, CustomColorsAmount> m_cCustColors;


	void OnDifferenceColor();
	void OnDifferenceDeletedColor();
	void OnSelDifferenceDeletedColor();
	void OnSelDifferenceColor();
	void OnDifferenceTextColor();
	void OnSelDifferenceTextColor();
	void OnTrivialDiffColor();
	void OnTrivialDiffDeletedColor();
	void OnTrivialDiffTextColor();
	void OnMovedColor();
	void OnMovedDeletedColor();
	void OnMovedTextColor();
	void OnSelMovedColor();
	void OnSelMovedDeletedColor();
	void OnSelMovedTextColor();
	void OnSNPColor();
	void OnSNPDeletedColor();
	void OnSNPTextColor();
	void OnSelSNPColor();
	void OnSelSNPDeletedColor();
	void OnSelSNPTextColor();
	void OnWordDiffColor();
	void OnWordDiffDeletedColor();
	void OnWordDiffTextColor();
	void OnSelWordDiffColor();
	void OnSelWordDiffDeletedColor();
	void OnSelWordDiffTextColor();
	/*template<int checkbox_id, int colorbutton_id>
	void OnUseTextColor();
	template<int scheme>
	void OnColorSchemeButton();*/
	void OnDefaults();

private:
	Ui::QPropMergeColors *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROPPAGE_COLORS_WINMERGE_H
