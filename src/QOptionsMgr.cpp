//
// Created
//

#include "QOptionsMgr.h"

QOptionsMgr::QOptionsMgr(){

}

QOptionsMgr::~QOptionsMgr(){
}

// set default value for given key and writes default value if key is not existing
void QOptionsMgr::setDefault(QString key, QVariant val){

	if(!defaultItems.contains(key)){
		defaultItems.insert(key, val);
	}
	if (!contains(key))
	{
		setValue(key,val);
	}
}

// Get default value for given key
QVariant QOptionsMgr::getDefault(QString key){
	return defaultItems.value(key);
}

// Reset parameter to default in storage
void QOptionsMgr::Reset(QString key){
	setValue(key,getDefault(key));
}

void QOptionsMgr::SetSerializing(bool){
}

int QOptionsMgr::Set(QString key, QVariant val){
	if(contains(key)){
		setValue(key,val);
		return OPT_OK;
	}
	else
	{
		return OPT_UNKNOWN_TYPE;
	}

}

QString QOptionsMgr::ExpandShortName(const QString & shortname) const {
	QString keyname(shortname);
	if (contains(shortname)){
		return keyname;
	} else {
		return QString("");
	}
}