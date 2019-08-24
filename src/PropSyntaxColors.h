/**
 * @file  PropSyntaxColors.h
 *
 * @brief Declaration file for PropSyntaxColors propertyheet
 *
 */

#pragma once

#ifndef IDD_PROPPAGE_COLORS_SYNTAX_H
#define IDD_PROPPAGE_COLORS_SYNTAX_H
// #include "SyntaxColors.h"
#include <array>
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropSyntaxColors;
}
class QPropSyntaxColors : public QDialog
{
	Q_OBJECT

public:
	explicit QPropSyntaxColors(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropSyntaxColors();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	/* template<unsigned colorIndex>				// ToDo: !??
	void OnBnClickedEcolor();
	void OnBnClickedEcolorsBdefaults();
	template<unsigned ctlId, unsigned colorIndex> // ToDo: !??
	void OnBnClickedBoldButton();*/

	void BrowseColorAndSave(unsigned colorIndex);
	int GetCheckVal(unsigned int nColorIndex);

private:
	Ui::QPropSyntaxColors *ui;
	QOptionsMgr* m_options;

	/*std::array<CColorButton, COLORINDEX_LAST + 1> m_colorButtons;
	std::array<int, COLORINDEX_LAST + 1> m_nBolds;

	SyntaxColors *m_pTempColors;
	std::array<COLORREF, 16> m_cCustColors;*/

};
#endif // IDD_PROPPAGE_COLORS_SYNTAX_H
