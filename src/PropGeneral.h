/**
 * @file  PropGeneral.h
 *
 * @brief Implementation file for PropGeneral propertyheet
 *
 */
#ifndef IDD_PROPPAGE_GENERAL_H
#define IDD_PROPPAGE_GENERAL_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropGeneral;
}
class QPropGeneral : public QDialog
{
	Q_OBJECT

public:
	explicit QPropGeneral(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropGeneral();

	virtual void ReadOptions();
	virtual void WriteOptions();

	//enum { IDD = IDD_PROPPAGE_GENERAL };
	/*CWinThread *m_pLoadLanguagesThread;
	std::vector<std::pair<LANGID, String>> m_langs;
	CComboBox	m_ctlLangList;*/

private:
	Ui::QPropGeneral *ui;
	QOptionsMgr* m_options;
};
#endif // IDD_PROPPAGE_GENERAL_H
