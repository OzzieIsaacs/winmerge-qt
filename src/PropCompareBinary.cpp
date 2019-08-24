/**
 * @file  PropCompareBinary.cpp
 *
 * @brief Implementation of PropCompareBinary propertysheet
 */

#include "PropCompareBinary.h"
#include "ui_QPropCompareBinary.h"
#include "OptionsDef.h"
//#include "heksedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/*class Heksedit
{
public:
	// ToDo: Port
	/*explicit Heksedit(CWnd *pwndParent)
	{
		pv = LoadLibrary(_T("Frhed\\hekseditU.dll"));
		if (pv == nullptr)
		{
			LangMessageBox(IDS_FRHED_NOTINSTALLED, MB_OK);
			return;
		}
		wnd.Create(_T("heksedit"), nullptr, 0, CRect(), pwndParent, 1);
		get_interface()->read_ini_data();
		get_interface()->get_settings()->bSaveIni = true;
	}

	IHexEditorWindow *get_interface()
	{
		//return reinterpret_cast<IHexEditorWindow *>(::GetWindowLongPtr(wnd.m_hWnd, GWLP_USERDATA));
	}

private:
	// HMODULE pv;
	// CWnd wnd;
};*/


QPropCompareBinary::QPropCompareBinary(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropCompareBinary)
{
	ui->setupUi(this);

	connect(ui->IDC_COMPAREBINARY_VIEWSETTINGS, SIGNAL(clicked()), this, SLOT(OnViewSettings()));
	connect(ui->IDC_COMPAREBINARY_BINARYMODE, SIGNAL(clicked()), this, SLOT(OnBinaryMode()));
	connect(ui->IDC_COMPAREBINARY_CHARACTERSET, SIGNAL(clicked()), this, SLOT(OnCharacterSet()));
	connect(ui->IDC_COMPAREBINARY_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));
	
	m_options = options;

}
QPropCompareBinary::~QPropCompareBinary()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void QPropCompareBinary::ReadOptions()
{
	ui->IDC_COMPAREBINARY_PATTERNS->setText(m_options->value(OPT_CMP_BIN_FILEPATTERNS).toString());
	//m_sFilePatterns = GetOptionsMgr()->GetString(OPT_CMP_BIN_FILEPATTERNS);
}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void QPropCompareBinary::WriteOptions()
{
	m_options->setValue(OPT_CMP_BIN_FILEPATTERNS,  ui->IDC_COMPAREBINARY_PATTERNS->toPlainText());
	//GetOptionsMgr()->SaveOption(OPT_CMP_BIN_FILEPATTERNS, m_sFilePatterns);
}

/**
 * @brief Show Frhed view settings dialog
 */
void QPropCompareBinary::OnViewSettings()
{
	// ToDo: Port Heksedit
	/*Heksedit heksedit(this);
	if (heksedit.get_interface())
		heksedit.get_interface()->CMD_view_settings();*/
}

/**
 * @brief Show Frhed binary mode dialog
 */
void QPropCompareBinary::OnBinaryMode()
{
	/*Heksedit heksedit(this);
	if (heksedit.get_interface())
		heksedit.get_interface()->CMD_binarymode();*/
}

/**
 * @brief Show Frhed characterset dialog
 */
void QPropCompareBinary::OnCharacterSet()
{
	/*Heksedit heksedit(this);
	if (heksedit.get_interface())
		heksedit.get_interface()->CMD_character_set();*/
}

/**
 * @brief Sets options to defaults
 */
void QPropCompareBinary::OnDefaults()
{
	//m_sFilePatterns = GetOptionsMgr()->GetDefault<String>(OPT_CMP_BIN_FILEPATTERNS);
	//UpdateData(false);
}
