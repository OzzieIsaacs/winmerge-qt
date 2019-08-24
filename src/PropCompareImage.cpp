/**
 * @file  PropCompareImage.cpp
 *
 * @brief Implementation of PropCompareImage propertysheet
 */

#include "PropCompareImage.h"
#include "ui_QPropCompareImage.h"
#include "OptionsDef.h"

QPropCompareImage::QPropCompareImage(QWidget *parent, QOptionsMgr* options) :
	QDialog(parent),
	ui(new Ui::QPropCompareImage)
{
	ui->setupUi(this);
	m_options = options;
}
QPropCompareImage::~QPropCompareImage()
{
	delete ui;

	connect(ui->IDC_COMPAREIMAGE_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));
}

/**
 * @brief Sets options to defaults
 */
void QPropCompareImage::OnDefaults()
{
	// ToDo: Read Default Values
	//m_sFilePatterns = GetOptionsMgr()->GetDefault<String>(OPT_CMP_IMG_FILEPATTERNS);
	//UpdateData(false);
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void QPropCompareImage::ReadOptions()
{
	ui->IDC_COMPAREIMAGE_PATTERNS->setText(m_options->value(OPT_CMP_IMG_FILEPATTERNS).toString());
	//m_sFilePatterns = GetOptionsMgr()->GetString(OPT_CMP_IMG_FILEPATTERNS);
}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void QPropCompareImage::WriteOptions()
{
	m_options->setValue(OPT_CMP_IMG_FILEPATTERNS, ui->IDC_COMPAREIMAGE_PATTERNS->toPlainText());
	//GetOptionsMgr()->SaveOption(OPT_CMP_IMG_FILEPATTERNS, m_sFilePatterns);
}

