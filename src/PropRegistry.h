/////////////////////////////////////////////////////////////////////////////
//    License (GPLv2+):
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
/////////////////////////////////////////////////////////////////////////////
/**
 * @file  PropRegistry.h
 *
 * @brief Declaration file PropRegistry
 */

#ifndef IDD_PROPPAGE_SYSTEM_H
#define IDD_PROPPAGE_SYSTEM_H
#include <QDialog>
#include <QSettings>
#include "QOptionsMgr.h"

namespace Ui {
class QPropRegistry;
}
/**
 * @brief Property page for system options; used in options property sheet.
 *
 * This class implements property sheet for what we consider System-options.
 * It allows user to select options like whether to use Recycle Bin for
 * deleted files and External text editor.
 */
class QPropRegistry : public QDialog
{
	Q_OBJECT

public:
	explicit QPropRegistry(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropRegistry();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	void OnBrowseEditor();
	void OnBrowseFilterPath();
	void OnBrowseTmpFolder();

private:
	Ui::QPropRegistry *ui;
	QOptionsMgr* m_options;

};
#endif // IDD_PROPPAGE_SYSTEM_H
