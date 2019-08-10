#ifndef RESULTITEM_H
#define RESULTITEM_H

#include <QString>

class ResultItem
{
public:
    enum ResultCode
    {
        Identical = 0,
        Different
    };

    QString name;
    ResultCode result;
};

#endif // RESULTITEM_H
