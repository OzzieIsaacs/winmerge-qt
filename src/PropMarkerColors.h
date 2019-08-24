/**
 * @file  PropMarkerColors.h
 *
 * @brief Declaration file for PropMarkerColors propertyheet
 *
 */
#pragma once

#ifndef IDD_PROPPAGE_COLORS_MARKER_H
#define IDD_PROPPAGE_COLORS_MARKER_H
#include <QDialog>
#include <QSettings>
#include <array>
#include "QOptionsMgr.h"
//#include "ColorButton.h"

namespace Ui {
class QPropMarkerColors;
}
class QPropMarkerColors : public QDialog
{
	Q_OBJECT

public:
	explicit QPropMarkerColors(QWidget *parent = nullptr, QOptionsMgr* options = nullptr);
	~QPropMarkerColors();

	// Implement IOptionsPanel
	virtual void ReadOptions();
	virtual void WriteOptions();

private slots:
	//typedef enum { SET_DEFAULTS, READ_OPTIONS, LOAD_COLORS } OPERATION;

	//void BrowseColorAndSave(CColorButton & colorButton, int colorIndex);
	//void SerializeColorsToFromScreen(OPERATION op);
	// void SerializeColorToFromScreen(OPERATION op, CColorButton & btn, int colorIndex);
	//void OnMarkerColors(unsigned int nID);

private:
	Ui::QPropMarkerColors *ui;
	QOptionsMgr* m_options;

};
#endif // IDD_PROPPAGE_COLORS_MARKER_H
