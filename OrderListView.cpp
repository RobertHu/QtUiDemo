#include "OrderListView.h"

#include <QHeaderView>

#include "OrderModel.h"
#include "SpinBoxDelegate.h"

OrderListView::OrderListView(QList<OrderData>* orderDataList,QWidget* parent) : QTableView(parent)
{
	OrderModel* model = new OrderModel(orderDataList);
	this->setModel(model);
	SpinBoxDelegate* delegate = new SpinBoxDelegate;
	//this->setItemDelegate(delegate);
	this->setItemDelegateForColumn(2,delegate);

	this->setSelectionBehavior(QAbstractItemView::SelectItems);
	this->verticalHeader()->setVisible(false);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->resizeColumnsToContents();
	this->resizeRowsToContents();
	this->horizontalHeader()->setStretchLastSection(true);
	this->setAlternatingRowColors(true);
	this->setMouseTracking(true);
	this->setStyleSheet("QTableView{background-color: white;alternate-background-color: gray;}");
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{height:28px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 gray);}");

	connect(this,SIGNAL(AppendOrderRecordSignal(const OrderData&)),model,SLOT(AppendOrderRecordSlot(const OrderData&)));
}
void OrderListView::mouseMoveEvent(QMouseEvent * event)
{
	QModelIndex index = indexAt(event->pos());
	if(index.isValid() && index.row()>=0)
		this->setSelection(this->visualRect(index),QItemSelectionModel::SelectCurrent);
}
