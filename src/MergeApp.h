#pragma once
#include <QString>
// #include "OptionsMgr.h"

// #include "Common/UnicodeString.h"

/*#define _(x) tr(x)
#define N_(x) (x)*/


struct AboutInfo
{
	AboutInfo();
    QString copyright;
    QString version;
    QString developers;
    QString private_build;
    QString website;
};

// COptionsMgr * GetOptionsMgr();
