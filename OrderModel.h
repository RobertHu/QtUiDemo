#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QList>

#include "OrderData.h"

class OrderModel : public QAbstractTableModel
{
	Q_OBJECT
		
public:
	OrderModel(QList<OrderData>* orderDataList,QObject * parent = 0);
	//overwirte
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    bool insertRow(int position,const QModelIndex &index = QModelIndex());
    bool removeRow(int position,const QModelIndex &index = QModelIndex());

public slots:
	void AppendOrderRecordSlot(const OrderData& orderData);
private:
	enum MyEnum
	{
		COLUMNS = 3
	};

private:
	QList<OrderData>&	 m_OrderList;
	OrderData			 m_UpdatingItem;
};

#endif
