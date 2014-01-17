#include "TableModel.h"

#include <QBrush>
#include <QColor>
#include <QFont>


TableModel::TableModel(const QList<TradeItem>& itemList,QMap<int,ColumnObject>& columnMap,QObject *parent) : m_ColumnMap(columnMap),QAbstractTableModel(parent)
{
	m_ItemList = itemList;
	int count = columnMap.count();
	for(int i=0;i<itemList.count();i++)
		m_PrePriceMap.insert(itemList[i].m_TradingCode,"0.0");
	for(int i=0;i<count;i++)
		m_FontMap.insert(i,ColumnFont());
}
QList<TradeItem>  TableModel::GetItemList()
{
	return m_ItemList;
}
void TableModel::ReLoadItemList(const QList<TradeItem>& itemList)
{
	m_ItemList.clear();
	int count =  itemList.count();
	for(int i=0;i<count;i++)
	{
		m_UpdatingItem = itemList[i];
		this->insertRow(i);
	}
}
void TableModel::SetUpdatingItem(const TradeItem& item)
{
	m_UpdatingItem = item;
}
void TableModel::SetPerPrice(const QString& tradingCode,const QString& prePrice)
{
	m_PrePriceMap[tradingCode] = prePrice;
}
QMap<QString,QString>   TableModel::GetPerPriceMap()
{
	return m_PrePriceMap;
}
void TableModel::SetFontBold(int index,bool bBold)
{
	if(m_FontMap.contains(index))
		m_FontMap[index].m_Bold = bBold;
}
void TableModel::SetFontItalic(int index,bool bItalic)
{
	if(m_FontMap.contains(index))
		m_FontMap[index].m_Italic = bItalic;
}
void TableModel::SetFontSize(int index,int fontSize)
{
	if(m_FontMap.contains(index))
		m_FontMap[index].m_FontSize = fontSize;
}
void TableModel::SetFontColor(int index,const QColor& fontColor)
{
	if(m_FontMap.contains(index))
		m_FontMap[index].m_FontColor = fontColor;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
	return m_ItemList.count();
}
int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
	return m_ColumnMap.count();
}
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

	if (index.row() >= m_ItemList.size() || index.row() < 0)
        return QVariant();
	
	TradeItem item = m_ItemList.at(index.row());
    if (role == Qt::DisplayRole) 
	{
		switch (index.column())
		{
		case 0:
			return item.m_TradingCode;
		case 1:
			return item.m_CurrentTime;
		case 3:
			return item.m_CurrentBidPrice;
		case 4:
			return item.m_CurrentAskPrice;
		case 5:
			return item.m_PreviousBidPrice;
		case 6:
			return item.m_PreviousAskPrice;
		case 7:
			return item.m_PreviousHightPrice;
		case 8:
			return item.m_PreviousLowPrice;
		case 9:
			return item.m_PreviousClosePrice;
		case 10:
			return item.m_PreviousChangedPrice;
		case 11:
			return item.m_OpenPrice;
		case 12:
			return item.m_BuyRate;
		case 13:
			return item.m_SellRate;
		default:
			break;
		}
    }
	if(role==Qt::TextAlignmentRole)
	{
		return Qt::AlignCenter;
	}
	if(role==Qt::ForegroundRole)
	{	
		QBrush brush;
		QColor color;
		if(item.m_CurrentBidPrice.toDouble()>m_PrePriceMap[item.m_TradingCode].toDouble())
			color = Qt::blue;
		else if(item.m_CurrentBidPrice.toDouble()<m_PrePriceMap[item.m_TradingCode].toDouble())
			color = Qt::red;
		else
			color = Qt::black;
		int columnIndex = index.column();
		if(columnIndex==3 || columnIndex==4)
			brush.setColor(color);
		else
			brush.setColor(m_FontMap[columnIndex].m_FontColor);
		return brush;
	}
	if(role==Qt::FontRole)
	{
		int columnIndex = index.column();
		if(m_FontMap.contains(columnIndex))
		{
			QFont font;
			font.setBold(m_FontMap[columnIndex].m_Bold);		//加粗;
			font.setPixelSize(m_FontMap[columnIndex].m_FontSize);	//字体大小;
			font.setItalic(m_FontMap[columnIndex].m_Italic);   //斜体;
			return font;
		}	
	}
    return QVariant();
}
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) 
		return m_ColumnMap[section].GetColumnText();

    return QVariant();
}
bool TableModel::insertRow(int position, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(index, position, position);
	m_ItemList.insert(position,m_UpdatingItem);
    endInsertRows();
    return true;
}
bool TableModel::removeRow(int position,const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(index, position, position);
    m_ItemList.removeAt(position);
    endRemoveRows();
    return true;
}
bool TableModel::moveRow(const QModelIndex & sourceParent, int sourceRow, const QModelIndex & destinationParent, int destinationChild)
{
    Q_UNUSED(sourceParent);
	int dest = destinationChild;
	if(sourceRow<destinationChild)
		dest += 1;
    beginMoveRows(sourceParent, sourceRow,sourceRow ,destinationParent,dest);
	m_ItemList.move(sourceRow,destinationChild);
    endMoveRows();
    return true;	
}
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index.isValid() && role == Qt::DisplayRole) 
	{
        int row = index.row();
        m_ItemList.replace(row, m_UpdatingItem);
        emit(dataChanged(index, index)); 
    }
	return true;	   
}
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}