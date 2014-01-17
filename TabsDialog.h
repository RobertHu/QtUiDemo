#pragma once

#include <QDialog> 
#include <QMouseEvent>
#include <QTabWidget>

#include "TradeItem.h"
#include "ColumnObject.h"

class TabsDialog : 	public QDialog
{
	Q_OBJECT

public:
	explicit TabsDialog(QList<TradeItem>& itemList,const QString& columnJsonFile,QWidget *parent = 0);
	~TabsDialog(void);
	
private:
	QTabWidget * m_TabWidget;

};



