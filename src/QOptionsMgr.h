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
	void Reset(QString key);
	void SetSerializing(bool val);
	int Set(QString key, QVariant val);
	QString ExpandShortName(const QString & shortname) const;

	enum
	{
		OPT_OK				= 0, /**< All good. */
		OPT_ERR				= 1, /**< General error. */
		OPT_WRONG_TYPE		= 2, /**< Option type was wrong. */
		OPT_UNKNOWN_TYPE	= 3, /**< Given option type is not known. */
		OPT_NOTFOUND		= 4, /**< Option name not found. */
	};

private:
	QHash<QString, QVariant> defaultItems;

};
#endif //QOPTIONSMGR_H