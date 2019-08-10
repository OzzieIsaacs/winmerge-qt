#ifndef DIRCOMPARE_H
#define DIRCOMPARE_H

#include <QList>
#include "resultitem.h"

class QString;
class QDir;

class DirCompare
{
public:
    DirCompare(const QString &item1, const QString &item2);
    ~DirCompare();

    void DoCompare();
    QList<ResultItem> GetResults() const;

private:
    QDir *mDir1;
    QDir *mDir2;
    QList<ResultItem> mResults;
};

#endif // DIRCOMPARE_H
