//
// Created by
//

#ifndef QOPTIONSMGR_H
#define QOPTIONSMGR_H

#include <QSettings>
#include <QString>
#include <QVariant>
#include <QHash>

class QOptionsMgr : public QSettings
{
public:
	QOptionsMgr();
	~QOptionsMgr();

	void setDefault(QString key, QVariant val);
	QVariant getDefault(QString key);

private:
	QHash<QString, QVariant> defaultItems;

};
#endif //QOPTIONSMGR_H