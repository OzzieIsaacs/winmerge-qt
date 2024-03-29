/**
 * @file  PropColors.cpp
 *
 * @brief Implementation of QPropMergeColors propertysheet
 */


#include "PropMergeColors.h"
#include "ui_QPropMergeColors.h"
#include "OptionsDef.h"
// #include "OptionsCustomColors.h"

QPropMergeColors::QPropMergeColors(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropMergeColors)
{
	ui->setupUi(this);
	connect(ui->IDC_DIFFERENCE_COLOR, SIGNAL(clicked()), this, SLOT(OnDifferenceColor()));
	connect(ui->IDC_DIFFERENCE_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnDifferenceDeletedColor()));
	connect(ui->IDC_SEL_DIFFERENCE_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnSelDifferenceDeletedColor()));
	connect(ui->IDC_SEL_DIFFERENCE_COLOR, SIGNAL(clicked()), this, SLOT(OnSelDifferenceColor()));
	//connect(ui->IDC_DIFFERENCE_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_DIFFERENCE_USE_TEXT_COLOR, IDC_DIFFERENCE_TEXT_COLOR>()));
	connect(ui->IDC_DIFFERENCE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnDifferenceTextColor()));
	//connect(ui->IDC_SEL_DIFFERENCE_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_SEL_DIFFERENCE_USE_TEXT_COLOR, IDC_SEL_DIFFERENCE_TEXT_COLOR>()));
	connect(ui->IDC_SEL_DIFFERENCE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnSelDifferenceTextColor()));
	connect(ui->IDC_TRIVIAL_DIFF_COLOR, SIGNAL(clicked()), this, SLOT(OnTrivialDiffColor()));
	connect(ui->IDC_TRIVIAL_DIFF_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnTrivialDiffDeletedColor()));
	connect(ui->IDC_COLORDEFAULTS_BTN, SIGNAL(clicked()), this, SLOT(OnDefaults()));

	//connect(ui->IDC_COLORSCHEME_GITHUBBITBUCKET, SIGNAL(clicked()), this, SLOT(OnColorSchemeButton<COLORSCHEME_GITHUBBITBUCKET>()));
	//connect(ui->IDC_TRIVIAL_DIFF_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_TRIVIAL_DIFF_USE_TEXT_COLOR, IDC_TRIVIAL_DIFF_TEXT_COLOR>()));
	connect(ui->IDC_TRIVIAL_DIFF_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnTrivialDiffTextColor()));
	connect(ui->IDC_MOVEDBLOCK_COLOR, SIGNAL(clicked()), this, SLOT(OnMovedColor()));
	connect(ui->IDC_MOVEDBLOCK_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnMovedDeletedColor()));
	//connect(ui->IDC_MOVEDBLOCK_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_MOVEDBLOCK_USE_TEXT_COLOR, IDC_MOVEDBLOCK_TEXT_COLOR>()));
	connect(ui->IDC_MOVEDBLOCK_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnMovedTextColor()));
	connect(ui->IDC_SEL_MOVEDBLOCK_COLOR, SIGNAL(clicked()), this, SLOT(OnSelMovedColor()));
	connect(ui->IDC_SEL_MOVEDBLOCK_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnSelMovedDeletedColor()));
	//connect(ui->IDC_SEL_MOVEDBLOCK_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_SEL_MOVEDBLOCK_USE_TEXT_COLOR, IDC_SEL_MOVEDBLOCK_TEXT_COLOR>()));
	connect(ui->IDC_SEL_MOVEDBLOCK_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnSelMovedTextColor()));
	connect(ui->IDC_SNP_COLOR, SIGNAL(clicked()), this, SLOT(OnSNPColor()));
	connect(ui->IDC_SNP_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnSNPDeletedColor()));
	//connect(ui->IDC_SNP_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_SNP_USE_TEXT_COLOR, IDC_SNP_TEXT_COLOR>()));
	connect(ui->IDC_SNP_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnSNPTextColor()));
	connect(ui->IDC_SEL_SNP_COLOR, SIGNAL(clicked()), this, SLOT(OnSelSNPColor()));
	connect(ui->IDC_SEL_SNP_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnSelSNPDeletedColor()));
	//connect(ui->IDC_SEL_SNP_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_SEL_SNP_USE_TEXT_COLOR, IDC_SEL_SNP_TEXT_COLOR>()));
	connect(ui->IDC_SEL_MOVEDBLOCK_TEXT_COLOR, SIGNAL(clicked()), this,SLOT( OnSelSNPTextColor()));
	connect(ui->IDC_SEL_SNP_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnSelSNPTextColor()));
	connect(ui->IDC_WORDDIFF_COLOR, SIGNAL(clicked()), this, SLOT(OnWordDiffColor()));
	connect(ui->IDC_WORDDIFF_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnWordDiffDeletedColor()));
	//connect(ui->IDC_WORDDIFF_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnSelMovedTextColor(OnUseTextColor<IDC_WORDDIFF_USE_TEXT_COLOR, IDC_WORDDIFF_TEXT_COLOR>()));
	connect(ui->IDC_WORDDIFF_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnWordDiffTextColor()));
	connect(ui->IDC_SEL_WORDDIFF_COLOR, SIGNAL(clicked()), this, SLOT(OnSelWordDiffColor()));
	connect(ui->IDC_SEL_WORDDIFF_DELETED_COLOR, SIGNAL(clicked()), this, SLOT(OnSelWordDiffDeletedColor()));
	//connect(ui->IDC_SEL_WORDDIFF_USE_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnUseTextColor<IDC_SEL_WORDDIFF_USE_TEXT_COLOR, IDC_SEL_WORDDIFF_TEXT_COLOR>()));
	connect(ui->IDC_SEL_WORDDIFF_TEXT_COLOR, SIGNAL(clicked()), this, SLOT(OnSelWordDiffTextColor()));

	m_options = options;
}
QPropMergeColors::~QPropMergeColors()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * (Property sheet calls this before displaying all property pages)
 */
void QPropMergeColors::ReadOptions()
{
	//SerializeColors(READ_OPTIONS);
}

/**
 * @brief Writes options values from UI to storage.
 * (Property sheet calls this after displaying all property pages)
 */
void QPropMergeColors::WriteOptions()
{
	//SerializeColors(WRITE_OPTIONS);
}

/**
 * @brief Let user browse common color dialog, and select a color
 */
/*void QPropMergeColors::BrowseColor(CColorButton & colorButton)
{
	/*CColorDialog dialog(colorButton.GetColor());
	Options::CustomColors::Load(GetOptionsMgr(), m_cCustColors.data());
	dialog.m_cc.lpCustColors = m_cCustColors.data();

	if (dialog.DoModal() == IDOK)
		colorButton.SetColor(dialog.GetColor());
	Options::CustomColors::Save(GetOptionsMgr(), m_cCustColors.data());
}*/

/*void QPropMergeColors::UpdateTextColorButtonState(int checkboxId, CColorButton &btn)
{
	/*CheckDlgButton(checkboxId, btn.GetColor() != COLOR_NONE ? BST_CHECKED : BST_UNCHECKED);
	btn.ShowWindow(btn.GetColor() != COLOR_NONE ? SW_SHOW : SW_HIDE);
}*/

void QPropMergeColors::UpdateTextColorButtonsState()
{
	/*UpdateTextColorButtonState(IDC_DIFFERENCE_USE_TEXT_COLOR, m_cDiffText);
	UpdateTextColorButtonState(IDC_SEL_DIFFERENCE_USE_TEXT_COLOR, m_cSelDiffText);
	UpdateTextColorButtonState(IDC_TRIVIAL_DIFF_USE_TEXT_COLOR, m_cTrivialText);
	UpdateTextColorButtonState(IDC_MOVEDBLOCK_USE_TEXT_COLOR, m_cMovedText);
	UpdateTextColorButtonState(IDC_SEL_MOVEDBLOCK_USE_TEXT_COLOR, m_cSelMovedText);
	UpdateTextColorButtonState(IDC_SNP_USE_TEXT_COLOR, m_cSNPText);
	UpdateTextColorButtonState(IDC_SEL_SNP_USE_TEXT_COLOR, m_cSelSNPText);
	UpdateTextColorButtonState(IDC_WORDDIFF_USE_TEXT_COLOR, m_cWordDiffText);
	UpdateTextColorButtonState(IDC_SEL_WORDDIFF_USE_TEXT_COLOR, m_cSelWordDiffText);*/
}

/**
 * @brief User wants to change difference color
 */
void QPropMergeColors::OnDifferenceColor()
{
	//BrowseColor(m_cDiff);
}

/**
 * @brief User wants to change selected difference color
 */
void QPropMergeColors::OnSelDifferenceColor()
{
	//BrowseColor(m_cSelDiff);
}

/**
 * @brief User wants to change deleted difference color
 */
void QPropMergeColors::OnDifferenceDeletedColor()
{
	//BrowseColor(m_cDiffDeleted);
}

/**
 * @brief User wants to change selected & deleted difference color
 */
void QPropMergeColors::OnSelDifferenceDeletedColor()
{
	//BrowseColor(m_cSelDiffDeleted);
}

/**
 * @brief User wants to change difference text color
 */
void QPropMergeColors::OnDifferenceTextColor()
{
	//BrowseColor(m_cDiffText);
}

/**
 * @brief User wants to change selected difference text color
 */
void QPropMergeColors::OnSelDifferenceTextColor()
{
	//BrowseColor(m_cSelDiffText);
}

/**
 * @brief User wants to change trivial difference color
 */
void QPropMergeColors::OnTrivialDiffColor()
{
	//BrowseColor(m_cTrivial);
}

/**
 * @brief User wants to change deleted trivial difference color
 */
void QPropMergeColors::OnTrivialDiffDeletedColor()
{
	//BrowseColor(m_cTrivialDeleted);
}

void QPropMergeColors::OnTrivialDiffTextColor()
{
	//BrowseColor(m_cTrivialText);
}

void QPropMergeColors::OnMovedColor()
{
	//BrowseColor(m_cMoved);
}

void QPropMergeColors::OnMovedDeletedColor()
{
	//BrowseColor(m_cMovedDeleted);
}

void QPropMergeColors::OnMovedTextColor()
{
	//BrowseColor(m_cMovedText);
}

void QPropMergeColors::OnSelMovedColor()
{
	//BrowseColor(m_cSelMoved);
}

void QPropMergeColors::OnSelMovedDeletedColor()
{
	//BrowseColor(m_cSelMovedDeleted);
}

void QPropMergeColors::OnSelMovedTextColor()
{
	//BrowseColor(m_cSelMovedText);
}

void QPropMergeColors::OnSNPColor()
{
	//BrowseColor(m_cSNP);
}

void QPropMergeColors::OnSNPDeletedColor()
{
	//BrowseColor(m_cSNPDeleted);
}

void QPropMergeColors::OnSNPTextColor()
{
	//BrowseColor(m_cSNPText);
}

void QPropMergeColors::OnSelSNPColor()
{
	//BrowseColor(m_cSelSNP);
}

void QPropMergeColors::OnSelSNPDeletedColor()
{
	//BrowseColor(m_cSelSNPDeleted);
}

void QPropMergeColors::OnSelSNPTextColor()
{
	//BrowseColor(m_cSelSNPText);
}

/**
 * @brief User wants to change word difference color
 */
void QPropMergeColors::OnWordDiffColor()
{
	//BrowseColor(m_cWordDiff);
}
/**
 * @brief User wants to change word difference deleted color
 */
void QPropMergeColors::OnWordDiffDeletedColor()
{
	//BrowseColor(m_cWordDiffDeleted);
}

/**
 * @brief User wants to change selected word difference color
 */
void QPropMergeColors::OnSelWordDiffColor()
{
	//BrowseColor(m_cSelWordDiff);
}

/**
 * @brief User wants to change word difference deleted color
 */
void QPropMergeColors::OnSelWordDiffDeletedColor()
{
	//BrowseColor(m_cSelWordDiffDeleted);
}

/**
 * @brief User wants to change word difference text color
 */
void QPropMergeColors::OnWordDiffTextColor()
{
	//BrowseColor(m_cWordDiffText);
}

/**
 * @brief User wants to change selected word difference text color
 */
void QPropMergeColors::OnSelWordDiffTextColor()
{
	//BrowseColor(m_cSelWordDiffText);
}

/*template<int checkbox_id, int colorbutton_id>
void QPropMergeColors::OnUseTextColor()
{
	CColorButton *cButton = dynamic_cast<CColorButton *>(GetDlgItem(colorbutton_id));
	if (IsDlgButtonChecked(checkbox_id) != 0)
	{
		cButton->ShowWindow(SW_SHOW);
		cButton->SetColor(0);
	}
	else
	{
		cButton->ShowWindow(SW_HIDE);
		cButton->SetColor(COLOR_NONE);
	}
}

void QPropMergeColors::SerializeColors(OPERATION op)
{
	/*SerializeColor(op, m_cDiff, OPT_CLR_DIFF);
	SerializeColor(op, m_cDiffDeleted, OPT_CLR_DIFF_DELETED);
	SerializeColor(op, m_cSelDiff, OPT_CLR_SELECTED_DIFF);

	SerializeColor(op, m_cDiffText, OPT_CLR_DIFF_TEXT);
	SerializeColor(op, m_cSelDiffDeleted, OPT_CLR_SELECTED_DIFF_DELETED);
	SerializeColor(op, m_cSelDiffText, OPT_CLR_SELECTED_DIFF_TEXT);

	SerializeColor(op, m_cTrivial, OPT_CLR_TRIVIAL_DIFF);
	SerializeColor(op, m_cTrivialDeleted, OPT_CLR_TRIVIAL_DIFF_DELETED);
	SerializeColor(op, m_cTrivialText, OPT_CLR_TRIVIAL_DIFF_TEXT);

	SerializeColor(op, m_cMoved, OPT_CLR_MOVEDBLOCK);
	SerializeColor(op, m_cMovedDeleted, OPT_CLR_MOVEDBLOCK_DELETED);
	SerializeColor(op, m_cMovedText, OPT_CLR_MOVEDBLOCK_TEXT);

	SerializeColor(op, m_cSNP, OPT_CLR_SNP);
	SerializeColor(op, m_cSNPDeleted, OPT_CLR_SNP_DELETED);
	SerializeColor(op, m_cSNPText, OPT_CLR_SNP_TEXT);

	SerializeColor(op, m_cSelMoved, OPT_CLR_SELECTED_MOVEDBLOCK);
	SerializeColor(op, m_cSelMovedDeleted, OPT_CLR_SELECTED_MOVEDBLOCK_DELETED);
	SerializeColor(op, m_cSelMovedText, OPT_CLR_SELECTED_MOVEDBLOCK_TEXT);

	SerializeColor(op, m_cSelSNP, OPT_CLR_SELECTED_SNP);
	SerializeColor(op, m_cSelSNPDeleted, OPT_CLR_SELECTED_SNP_DELETED);
	SerializeColor(op, m_cSelSNPText, OPT_CLR_SELECTED_SNP_TEXT);

	SerializeColor(op, m_cWordDiff, OPT_CLR_WORDDIFF);
	SerializeColor(op, m_cWordDiffDeleted, OPT_CLR_WORDDIFF_DELETED);
	SerializeColor(op, m_cWordDiffText, OPT_CLR_WORDDIFF_TEXT);

	SerializeColor(op, m_cSelWordDiff, OPT_CLR_SELECTED_WORDDIFF);
	SerializeColor(op, m_cSelWordDiffDeleted, OPT_CLR_SELECTED_WORDDIFF_DELETED);
	SerializeColor(op, m_cSelWordDiffText, OPT_CLR_SELECTED_WORDDIFF_TEXT);
}

void QPropMergeColors::SerializeColor(OPERATION op, CColorButton & btn, const String& optionName)
{
	switch (op)
	{
		case SET_DEFAULTS:
			btn.SetColor(GetOptionsMgr()->GetDefault<unsigned>(optionName));
			return;

		case WRITE_OPTIONS:
			GetOptionsMgr()->SaveOption(optionName, (unsigned)btn.GetColor());
			return;

		case READ_OPTIONS:
			// Set colors for buttons, do NOT invalidate
			btn.SetColor(GetOptionsMgr()->GetInt(optionName), false);
			return;
	}
}*/

void QPropMergeColors::SetColorScheme(int scheme)
{
	/*struct ColorScheme {
		CColorButton *button;
		COLORREF color;
	};

	ColorScheme github_bitbucket[] = {
			{&m_cDiff,               RGB(221,255,221)},
			{&m_cDiffDeleted,        RGB(224,224,255)},
			{&m_cDiffText,           COLOR_NONE},
			{&m_cSelDiff,            RGB(255,221,221)},
			{&m_cSelDiffDeleted,     RGB(240, 192, 192)},
			{&m_cSelDiffText,        COLOR_NONE},
			{&m_cTrivial,            RGB(251,242,191)},
			{&m_cTrivialDeleted,     RGB(233,233,233)},
			{&m_cTrivialText,        COLOR_NONE},
			{&m_cMoved,              RGB(240,216,192)},
			{&m_cMovedDeleted,       RGB(192, 192, 192)},
			{&m_cMovedText,          COLOR_NONE},
			{&m_cSelMoved,           RGB(248,112,78)},
			{&m_cSelMovedDeleted,    RGB(252, 181, 163)},
			{&m_cSelMovedText,       COLOR_NONE},
			{&m_cSNP,                RGB(251,250,223)},
			{&m_cSNPDeleted,         RGB(233, 233, 233)},
			{&m_cSNPText,            COLOR_NONE},
			{&m_cSelSNP,             RGB(239,183,180)},
			{&m_cSelSNPDeleted,      RGB(240, 224, 224)},
			{&m_cSelSNPText,         COLOR_NONE},
			{&m_cWordDiff,           RGB(170,255,170)},
			{&m_cWordDiffDeleted,    RGB(160,230,160)},
			{&m_cWordDiffText,       COLOR_NONE},
			{&m_cSelWordDiff,        RGB(255,170,170)},
			{&m_cSelWordDiffDeleted, RGB(230,150,140)},
			{&m_cSelWordDiffText,    COLOR_NONE},
	};

	if (scheme == COLORSCHEME_GITHUBBITBUCKET)
	{
		for (int i = 0; i < sizeof(github_bitbucket)/sizeof(github_bitbucket[0]); ++i)
			github_bitbucket[i].button->SetColor(github_bitbucket[i].color);
	}

	UpdateTextColorButtonsState();*/
}
/*
template<int scheme>
void QPropMergeColors::OnColorSchemeButton()
{
	SetColorScheme(scheme);
}*/

/**
 * @brief Resets colors to defaults
 */
void QPropMergeColors::OnDefaults()
{
	//SerializeColors(SET_DEFAULTS);
	UpdateTextColorButtonsState();
}
