#include "IDD_PROPPAGE_COMPARE_FOLDER.h"
#include "ui_IDD_PROPPAGE_COMPARE_FOLDER.h"
#include "OptionsDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const int Mega = 1024 * 1024;


IDD_PROPPAGE_COMPARE_FOLDER::IDD_PROPPAGE_COMPARE_FOLDER(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IDD_PROPPAGE_COMPARE_FOLDER)
{
	ui->setupUi(this);
	connect(ui->IDC_COMPAREFOLDER_DEFAULTS, SIGNAL(clicked()), this, SLOT(OnDefaults()));
	connect(ui->IDC_COMPAREMETHODCOMBO, SIGNAL(itemSelectionChanged()), this, SLOT(OnCbnSelchangeComparemethodcombo()));
	connect(ui->IDC_RECURS_CHECK, SIGNAL(clicked()), this, SLOT(OnBnClickedRecursCheck()));

}
IDD_PROPPAGE_COMPARE_FOLDER::~IDD_PROPPAGE_COMPARE_FOLDER()
{
	delete ui;
}

/**
 * @brief Reads options values from storage to UI.
 * Property sheet calls this before displaying GUI to load values
 * into members.
 */
void IDD_PROPPAGE_COMPARE_FOLDER::ReadOptions()
{
	// ToDo: Port
	/*m_compareMethod = GetOptionsMgr()->GetInt(OPT_CMP_METHOD);
	m_bStopAfterFirst = GetOptionsMgr()->GetBool(OPT_CMP_STOP_AFTER_FIRST);
	m_bIgnoreSmallTimeDiff = GetOptionsMgr()->GetBool(OPT_IGNORE_SMALL_FILETIME);
	m_bIncludeUniqFolders = GetOptionsMgr()->GetBool(OPT_CMP_WALK_UNIQUE_DIRS);
	m_bIncludeSubdirs = GetOptionsMgr()->GetBool(OPT_CMP_INCLUDE_SUBDIRS);
	m_bExpandSubdirs = GetOptionsMgr()->GetBool(OPT_DIRVIEW_EXPAND_SUBDIRS);
	m_bIgnoreReparsePoints = GetOptionsMgr()->GetBool(OPT_CMP_IGNORE_REPARSE_POINTS);
	m_nQuickCompareLimit = GetOptionsMgr()->GetInt(OPT_CMP_QUICK_LIMIT) / Mega ;
	m_nCompareThreads = GetOptionsMgr()->GetInt(OPT_CMP_COMPARE_THREADS);*/
}

/**
 * @brief Writes options values from UI to storage.
 * Property sheet calls this after dialog is closed with OK button to
 * store values in member variables.
 */
void IDD_PROPPAGE_COMPARE_FOLDER::WriteOptions()
{
	/*GetOptionsMgr()->SaveOption(OPT_CMP_METHOD, (int)m_compareMethod);
	GetOptionsMgr()->SaveOption(OPT_CMP_STOP_AFTER_FIRST, m_bStopAfterFirst);
	GetOptionsMgr()->SaveOption(OPT_IGNORE_SMALL_FILETIME, m_bIgnoreSmallTimeDiff);
	GetOptionsMgr()->SaveOption(OPT_CMP_WALK_UNIQUE_DIRS, m_bIncludeUniqFolders);
	GetOptionsMgr()->SaveOption(OPT_CMP_INCLUDE_SUBDIRS, m_bIncludeSubdirs);
	GetOptionsMgr()->SaveOption(OPT_DIRVIEW_EXPAND_SUBDIRS, m_bExpandSubdirs);
	GetOptionsMgr()->SaveOption(OPT_CMP_IGNORE_REPARSE_POINTS, m_bIgnoreReparsePoints);

	if (m_nQuickCompareLimit > 2000)
		m_nQuickCompareLimit = 2000;
	GetOptionsMgr()->SaveOption(OPT_CMP_QUICK_LIMIT, m_nQuickCompareLimit * Mega);
	GetOptionsMgr()->SaveOption(OPT_CMP_COMPARE_THREADS, m_nCompareThreads);*/
}

/**
 * @brief Called before propertysheet is drawn.
 */
bool IDD_PROPPAGE_COMPARE_FOLDER::OnInitDialog()
{
	/*OptionsPanel::OnInitDialog();
	CComboBox * combo = (CComboBox*) GetDlgItem(IDC_COMPAREMETHODCOMBO);

	String item = _("Full Contents");
	combo->AddString(item.c_str());
	item = _("Quick Contents");
	combo->AddString(item.c_str());
	item = _("Binary Contents");
	combo->AddString(item.c_str());
	item = _("Modified Date");
	combo->AddString(item.c_str());
	item = _("Modified Date and Size");
	combo->AddString(item.c_str());
	item = _("Size");
	combo->AddString(item.c_str());
	combo->SetCurSel(m_compareMethod);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE*/
}

/**
 * @brief Sets options to defaults
 */
void IDD_PROPPAGE_COMPARE_FOLDER::OnDefaults()
{
	/*m_compareMethod = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_METHOD);
	m_bStopAfterFirst = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_STOP_AFTER_FIRST);
	m_bIncludeUniqFolders = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_WALK_UNIQUE_DIRS);
	m_bIncludeSubdirs = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_INCLUDE_SUBDIRS);
	m_bExpandSubdirs = GetOptionsMgr()->GetDefault<bool>(OPT_DIRVIEW_EXPAND_SUBDIRS);
	m_bIgnoreReparsePoints = GetOptionsMgr()->GetDefault<bool>(OPT_CMP_IGNORE_REPARSE_POINTS);
	m_nQuickCompareLimit = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_QUICK_LIMIT) / Mega;
	m_nCompareThreads = GetOptionsMgr()->GetDefault<unsigned>(OPT_CMP_COMPARE_THREADS);
	UpdateData(FALSE);*/
}

/**
 * @brief Called when compare method dropdown selection is changed.
 * Enables / disables "Stop compare after first difference" checkbox.
 * That checkbox is valid only for quick contents compare method.
 */
void IDD_PROPPAGE_COMPARE_FOLDER::OnCbnSelchangeComparemethodcombo()
{
	UpdateControls();
}

void IDD_PROPPAGE_COMPARE_FOLDER::OnBnClickedRecursCheck()
{
	UpdateControls();
}

void IDD_PROPPAGE_COMPARE_FOLDER::UpdateControls()
{
	/*CComboBox * pCombo = (CComboBox*)GetDlgItem(IDC_COMPAREMETHODCOMBO);
	EnableDlgItem(IDC_COMPARE_STOPFIRST, pCombo->GetCurSel() == 1);
	EnableDlgItem(IDC_EXPAND_SUBDIRS, IsDlgButtonChecked(IDC_RECURS_CHECK) == 1);
	EnableDlgItem(IDC_COMPARE_THREAD_COUNT, pCombo->GetCurSel() <= 1 ? true : false); // true: fullcontent, quickcontent*/
}
