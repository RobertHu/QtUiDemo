#include "OrderModel.h"

OrderModel::OrderModel(QList<OrderData>* orderDataList,QObject * parent) : m_OrderList(*orderDataList),QAbstractTableModel(parent)
{
}

int OrderModel::rowCount(const QModelIndex &parent) const
{
	return m_OrderList.count();	
}
int OrderModel::columnCount(const QModelIndex &parent) const
{
	return COLUMNS;
}
QVariant OrderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
	if (index.row() >= m_OrderList.size() || index.row() < 0)
        return QVariant();
	if(role==Qt::TextAlignmentRole)
	{
		return Qt::AlignCenter;
	}
	OrderData orderData = m_OrderList[index.row()];
	if(role == Qt::DisplayRole)
	{	
		if(index.column()==1)
			return orderData.GetOpenOrder();
	}
	if(role==Qt::CheckStateRole && index.column()==0)
	{
		return (orderData.IsClose()) ? (Qt::Checked) : (Qt::Unchecked);
	}
	if(role==Qt::DisplayRole && index.column()==2)
	{
		return orderData.GetLot();
	}
	if(role==Qt::TextColorRole && index.column()==1)
	{
		return QColor(orderData.IsBid() ? Qt::blue : Qt::red );
	}

	return QVariant();
}
QVariant OrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

	if (orientation == Qt::Horizontal) 	
	{
		switch (section)
		{
		case 0:
			return "Close";
		case 1:
			return "Open Order";
		case 2:
			return "Lot";
		default:
			break;
		}
	}

	return QVariant();
}
Qt::ItemFlags OrderModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	if(index.column()==0)
		flags |= (Qt::ItemIsUserCheckable);
	else if(index.column()==2)
		flags |= Qt::ItemIsEditable;

	return  flags;
}
bool OrderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(index.isValid() )
	{
		if(role==Qt::CheckStateRole && index.column()==0)
		{
			m_OrderList[index.row()].SetClose(!m_OrderList[index.row()].IsClose());
			emit dataChanged(index,index);
			return true;
		}
		if(role==Qt::EditRole && index.column()==2)
		{
			m_OrderList[index.row()].SetLot(value.toInt());
			emit dataChanged(index,index);
			return true;
		}

	}

	return false;
}
bool OrderModel::insertRow(int position,const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(index, position, position);
	m_OrderList.insert(position,m_UpdatingItem);
    endInsertRows();
	emit dataChanged(index,index);
    return true;
}
bool OrderModel::removeRow(int position,const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(index, position, position);
    m_OrderList.removeAt(position);
    endRemoveRows();
	emit dataChanged(index,index);
    return true;
}

void OrderModel::AppendOrderRecordSlot(const OrderData& orderData)
{
	m_UpdatingItem = orderData;
	insertRow(m_OrderList.count());
}

