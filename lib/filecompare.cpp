#include <QFile>
#include "xdiff.h"
#include "filecompare.h"

FileCompare::FileCompare(const QString &side1, const QString &side2)
    : mSide1(side1)
    , mSide2(side2)
{
}

ResultItem FileCompare::Compare()
{
    mmfile_t block[2];

    QFile cmpfile1(mSide1);
    QFile cmpfile2(mSide2);

    const unsigned file1size = cmpfile1.size();
    const unsigned file2size = cmpfile2.size();
    int success = xdl_init_mmfile(&block[0], file1size, XDL_MMF_ATOMIC);
    success = xdl_init_mmfile(&block[1], file2size, XDL_MMF_ATOMIC);

    char *data1 = (char *) xdl_mmfile_writeallocate(&block[0], 999);
    char *data2 = (char *) xdl_mmfile_writeallocate(&block[1], 999);

    cmpfile1.open(QIODevice::ReadOnly);
    memcpy(data1, cmpfile1.readAll().constData(), file1size);
    cmpfile1.close();

    cmpfile2.open(QIODevice::ReadOnly);
    memcpy(data2, cmpfile2.readAll().constData(), file2size);
    cmpfile2.close();

    int result = xdl_mmfile_cmp(&block[0], &block[1]);

    xdl_free_mmfile(&block[0]);
    xdl_free_mmfile(&block[1]);

    ResultItem res;
    res.name = cmpfile1.fileName();
    if (result == 0)
        res.result = ResultItem::Identical;
    else
        res.result = ResultItem::Different;
    return res;
}
