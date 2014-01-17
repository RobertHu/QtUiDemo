#ifndef LISTTAB_H
#define LISTTAB_H

#include <QWidget>

#include "TradeItem.h"
#include "TradeTable.h"
#include "ColumnObject.h"



class ListTab:public QWidget
{
	Q_OBJECT
public:
	explicit ListTab(QList<TradeItem>& itemList,const QString& columnJsonFile,QWidget* parent=0);
signals:
	void SendPriceSignal(TradeItem item);
public:
	TradeTable*	 GetTable();
private:
	TradeTable*  m_Table;
};

#endif




