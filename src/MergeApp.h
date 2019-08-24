#pragma once
#include <QString>

struct AboutInfo
{
	AboutInfo();
    QString copyright;
    QString version;
    QString developers;
    QString private_build;
    QString website;
};

int GetSystemError();


#ifdef Q_OS_LINUX
	#define Q_ERROR_ALREAD_EXISTS 0			// ToDo which error occurs?
#else
	#define Q_ERROR_ALREAD_EXISTS ERROR_ALREADY_EXISTS
#endif