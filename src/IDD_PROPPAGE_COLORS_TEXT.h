#ifndef IDD_PROPPAGE_COLORS_TEXT_H
#define IDD_PROPPAGE_COLORS_TEXT_H
// #include "ColorButton.h"
#include <array>
#include <QDialog>

class SyntaxColors;

namespace Ui {
class IDD_PROPPAGE_COLORS_TEXT;
}
class IDD_PROPPAGE_COLORS_TEXT : public QDialog
{
	Q_OBJECT

public:
	explicit IDD_PROPPAGE_COLORS_TEXT(QWidget *parent = nullptr);
	~IDD_PROPPAGE_COLORS_TEXT();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private:
	SyntaxColors *m_pTempColors;
	//std::array<COLORREF, 16> m_cCustColors;

private:
	Ui::IDD_PROPPAGE_COLORS_TEXT *ui;
	typedef enum { SET_DEFAULTS, READ_OPTIONS, LOAD_COLORS } OPERATION;

	//void BrowseColorAndSave(CColorButton & colorButton, int colorIndex);
	void SerializeColorsToFromScreen(OPERATION op);
	//void SerializeColorToFromScreen(OPERATION op, CColorButton & btn, int colorIndex);
	void EnableColorButtons(bool bEnable);

	// Generated message map functions
	//{{AFX_MSG(PropTextColors)
	void OnWhitespaceBackgroundColor();
	void OnRegularBackgroundColor();
	void OnRegularTextColor();
	void OnSelectionBackgroundColor();
	void OnSelectionTextColor();
	void OnMarginBackgroundColor();
	void OnDefaultsStandardColors();

};
#endif // IDD_PROPPAGE_COLORS_TEXT_H
