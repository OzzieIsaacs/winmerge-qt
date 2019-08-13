//
// Created
//

#include "QOptionsMgr.h"

QOptionsMgr::QOptionsMgr(){

}

QOptionsMgr::~QOptionsMgr(){
}

void QOptionsMgr::setDefault(QString key, QVariant val){

	if(!defaultItems.contains(key)){
		defaultItems.insert(key, val);
	}

}

QVariant QOptionsMgr::getDefault(QString key){
	return defaultItems.value(key);
}