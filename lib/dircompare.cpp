#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QList>
#include <QStringList>
#include <QtDebug>
#include "dircompare.h"
#include "filecompare.h"
#include "resultitem.h"

DirCompare::DirCompare(const QString &item1, const QString &item2)
{
    mDir1 = new QDir(item1);
    mDir2 = new QDir(item2);
}

DirCompare::~DirCompare()
{
    delete mDir1;
    delete mDir2;
}

void DirCompare::DoCompare()
{
    const QFileInfoList side1 = mDir1->entryInfoList(QDir::NoFilter,
                                QDir::Name | QDir::DirsFirst);
    const QFileInfoList side2 = mDir2->entryInfoList(QDir::NoFilter,
                                QDir::Name | QDir::DirsFirst);

    mResults.clear();

    QFileInfoList::const_iterator iter = side1.constBegin();
    QFileInfoList::const_iterator iter2 = side2.constBegin();
    while (iter != side1.constEnd() && iter2 != side2.constEnd())
    {
        const QFileInfo inf1 = *iter;
        const bool side1IsFile = inf1.isFile();
        const QFileInfo inf2 = *iter2;
        const bool side2IsFile = inf2.isFile();

        if (side1IsFile && side2IsFile)
        {
            if (inf1.fileName() == inf2.fileName())
            {
                qDebug() << "Comparing: " << inf1.fileName() << " and " << inf2.fileName();
                FileCompare compare(inf1.absoluteFilePath(), inf2.absoluteFilePath());
                ResultItem item = compare.Compare();
                mResults << item;
                ++iter;
                ++iter2;
            }
            else
            {
                qDebug() << "Skipping one-side item: " << inf1.fileName();
                ++iter;
            }
        }
        else
        {
            if (!side1IsFile)
            {
                qDebug() << "Skipping left-side dir: " << inf1.baseName();
                ++iter;
            }
            if (!side2IsFile)
            {
                qDebug() << "Skipping right-side dir: " << inf2.baseName();
                ++iter2;
            }
        }
    }
}

QList<ResultItem> DirCompare::GetResults() const
{
    return mResults;
}
