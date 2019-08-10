#pragma once

#ifdef Q_OS_WIN
	#include <windows.h>
	#include "UnicodeString.h"
#endif
#include <QString>

//class COptionsMgr;

namespace Options { namespace Font {


//void InitializeLogFont(LOGFONT &logfont, int lfHeight, int lfCharSet, int lfPitchAndFamily, String lfFaceName);
void SetDefaults(COptionsMgr *pOptionsMgr);
LOGFONT Load(const COptionsMgr *pOptionsMgr, const QString& name);
void Save(COptionsMgr *pOptionsMgr, const QString& name, const LOGFONT* lf, bool bUseCustom);
void Reset(COptionsMgr *pOptionsMgr, const QString& name);

}}
