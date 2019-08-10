#include <StdAfx.h>
#include "Merge.h"
#include "TrDialogs.h"

IMPLEMENT_DYNAMIC(CTrDialog, CDialog)
IMPLEMENT_DYNAMIC(CTrPropertyPage, CPropertyPage)
IMPLEMENT_DYNAMIC(CTrDialogBar, CDialogBar)

BOOL CTrDialog::OnInitDialog()
{
	theApp.TranslateDialog(m_hWnd);
	CDialog::OnInitDialog();
	return TRUE;
}

BOOL CTrPropertyPage::OnInitDialog()
{
	theApp.TranslateDialog(m_hWnd);
	CPropertyPage::OnInitDialog();
	return TRUE;
}

BOOL CTrDialogBar::Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName,
	UINT nStyle, UINT nID)
{
	BOOL bSucceeded = CDialogBar::Create(pParentWnd, lpszTemplateName, nStyle, nID);
	if (bSucceeded)
		theApp.TranslateDialog(m_hWnd);
	return bSucceeded;
}

BOOL CTrDialogBar::Create(CWnd* pParentWnd, UINT nIDTemplate,
	UINT nStyle, UINT nID)
{
	BOOL bSucceeded = CDialogBar::Create(pParentWnd, nIDTemplate, nStyle, nID);
	if (bSucceeded)
		theApp.TranslateDialog(m_hWnd);
	return bSucceeded;
}
