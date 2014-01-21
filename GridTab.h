#ifndef GRIDTAB_H
#define GRIDTAB_H

#include <QWidget>
#include "Tradeitem.h"

#include <QScrollBar>

#include "ListViewPort.h"


class GridTab:public QWidget
{
	Q_OBJECT
public:
	 explicit GridTab(QList<TradeItem>& itemList, QWidget *parent = 0);
	 //overwrite:							 
protected:
	 void  resizeEvent(QResizeEvent * event);
	 void wheelEvent(QWheelEvent * event);

signals:
	void SendReSizeSignal(int row,int column);
public slots:
	void DisplayViewPort(int len);


public:
	ListViewPort*	GetListViewPort();
	QScrollBar*		GetVScrollBar();
private:
	QScrollBar*		m_VScrollBar;
	ListViewPort*	m_ListViewPort;

}; 

#endif


