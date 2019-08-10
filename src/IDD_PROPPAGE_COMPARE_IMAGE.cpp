#include "IDD_PROPPAGE_COMPARE_IMAGE.h"
#include "ui_IDD_PROPPAGE_COMPARE_IMAGE.h"
IDD_PROPPAGE_COMPARE_IMAGE::IDD_PROPPAGE_COMPARE_IMAGE(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COMPARE_IMAGE)
{
	ui->setupUi(this);
}
IDD_PROPPAGE_COMPARE_IMAGE::~IDD_PROPPAGE_COMPARE_IMAGE()
{
	delete ui;

	connect(ui->IDC_COMPAREIMAGE_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));
}

/**
 * @brief Sets options to defaults
 */
void IDD_PROPPAGE_COMPARE_IMAGE::OnDefaults()
{
	//m_sFilePatterns = GetOptionsMgr()->GetDefault<String>(OPT_CMP_IMG_FILEPATTERNS);
	//UpdateData(false);
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void IDD_PROPPAGE_COMPARE_IMAGE::ReadOptions()
{
	//m_sFilePatterns = GetOptionsMgr()->GetString(OPT_CMP_IMG_FILEPATTERNS);
}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void IDD_PROPPAGE_COMPARE_IMAGE::WriteOptions()
{
	//GetOptionsMgr()->SaveOption(OPT_CMP_IMG_FILEPATTERNS, m_sFilePatterns);
}

