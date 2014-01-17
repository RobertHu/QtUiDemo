#ifndef	HORIZONTALHEADERSETTINGDLGMODEL_H
#define	HORIZONTALHEADERSETTINGDLGMODEL_H

#include <QStandardItemModel>

#include "ColumnObject.h"

class HorizontalHeaderSettingDlgModel : public QStandardItemModel
{
	Q_OBJECT
public:
	HorizontalHeaderSettingDlgModel(QMap<int,ColumnObject>& columnMap,QObject * parent = 0);
};


#endif
