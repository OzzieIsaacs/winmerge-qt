#pragma once

#ifdef Q_OS_WIN
	// #include <windows.h>
	// #include "UnicodeString.h"
#endif
#include <QString>
#include "QOptionsMgr.h"

//class COptionsMgr;

namespace Options { namespace Font {


void InitializeLogFont(QFont &logfont, int lfHeight, int lfCharSet, int lfPitchAndFamily, QString lfFaceName);
void SetDefaults(QOptionsMgr *pOptionsMgr);
QFont* Load(const QOptionsMgr *pOptionsMgr, const QString& name);
void Save(QOptionsMgr *pOptionsMgr, const QString& name, const QFont* lf, bool bUseCustom);
void Reset(QOptionsMgr *pOptionsMgr, const QString& name);

}}
