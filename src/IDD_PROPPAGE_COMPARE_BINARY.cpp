#include "IDD_PROPPAGE_COMPARE_BINARY.h"
#include "ui_IDD_PROPPAGE_COMPARE_BINARY.h"
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


IDD_PROPPAGE_COMPARE_BINARY::IDD_PROPPAGE_COMPARE_BINARY(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COMPARE_BINARY)
{
	ui->setupUi(this);

	connect(ui->IDC_COMPAREBINARY_VIEWSETTINGS, SIGNAL(clicked()), this, SLOT(OnViewSettings()));
	connect(ui->IDC_COMPAREBINARY_BINARYMODE, SIGNAL(clicked()), this, SLOT(OnBinaryMode()));
	connect(ui->IDC_COMPAREBINARY_CHARACTERSET, SIGNAL(clicked()), this, SLOT(OnCharacterSet()));
	connect(ui->IDC_COMPAREBINARY_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));

}
IDD_PROPPAGE_COMPARE_BINARY::~IDD_PROPPAGE_COMPARE_BINARY()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void IDD_PROPPAGE_COMPARE_BINARY::ReadOptions()
{
	//m_sFilePatterns = GetOptionsMgr()->GetString(OPT_CMP_BIN_FILEPATTERNS);
}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void IDD_PROPPAGE_COMPARE_BINARY::WriteOptions()
{
	//GetOptionsMgr()->SaveOption(OPT_CMP_BIN_FILEPATTERNS, m_sFilePatterns);
}

/**
 * @brief Show Frhed view settings dialog
 */
void IDD_PROPPAGE_COMPARE_BINARY::OnViewSettings()
{
	/*Heksedit heksedit(this);
	if (heksedit.get_interface())
		heksedit.get_interface()->CMD_view_settings();*/
}

/**
 * @brief Show Frhed binary mode dialog
 */
void IDD_PROPPAGE_COMPARE_BINARY::OnBinaryMode()
{
	/*Heksedit heksedit(this);
	if (heksedit.get_interface())
		heksedit.get_interface()->CMD_binarymode();*/
}

/**
 * @brief Show Frhed characterset dialog
 */
void IDD_PROPPAGE_COMPARE_BINARY::OnCharacterSet()
{
	/*Heksedit heksedit(this);
	if (heksedit.get_interface())
		heksedit.get_interface()->CMD_character_set();*/
}

/**
 * @brief Sets options to defaults
 */
void IDD_PROPPAGE_COMPARE_BINARY::OnDefaults()
{
	//m_sFilePatterns = GetOptionsMgr()->GetDefault<String>(OPT_CMP_BIN_FILEPATTERNS);
	//UpdateData(false);
}
