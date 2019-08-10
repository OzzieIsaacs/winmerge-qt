#ifndef FILECOMPARE_H
#define FILECOMPARE_H

#include <QString>
#include "resultitem.h"

class FileCompare
{
public:
    FileCompare(const QString &side1, const QString &side2);
    ResultItem Compare();

private:
    QString mSide1;
    QString mSide2;
};

#endif // FILECOMPARE_H
