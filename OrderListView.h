#ifndef ORDERLISTVIEW_H
#define ORDERLISTVIEW_H

#include <QTableView>
#include <QMouseEvent>


#include "OrderData.h"




class OrderListView : public QTableView
{
	Q_OBJECT
public:
	OrderListView(QList<OrderData>* orderDataList,QWidget* parent = 0);
protected:
	void mouseMoveEvent(QMouseEvent * event);

signals:
	void AppendOrderRecordSignal(const OrderData&);

};

#endif
