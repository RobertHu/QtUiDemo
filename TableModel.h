#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>

#include "TradeItem.h"
#include "ColumnObject.h"



class TableModel : public QAbstractTableModel
{
	typedef struct MyStruct
	{
		MyStruct():m_Bold(false),m_Italic(false),m_FontSize(FONTSIZE),m_FontColor(QColor(Qt::black)){}
		bool	m_Bold;
		bool	m_Italic;
		int		m_FontSize;
		QColor  m_FontColor;
	}ColumnFont;

	Q_OBJECT
public:
    TableModel(const QList<TradeItem>& itemList,QMap<int,ColumnObject>& columnMap,QObject *parent = 0);

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
	bool moveRow(const QModelIndex & sourceParent, int sourceRow,const QModelIndex & destinationParent, int destinationChild);

public:
	QList<TradeItem>		GetItemList();	
	void					ReLoadItemList(const QList<TradeItem>& itemList);
	void					SetUpdatingItem(const TradeItem& item);
	void					SetPerPrice(const QString& tradingCode,const QString& prePrice);
	QMap<QString,QString>   GetPerPriceMap();
public:
	void					SetFontBold(int index,bool bBold);
	void					SetFontItalic(int index,bool bItalic);
	void					SetFontSize(int index,int fontSize);
	void					SetFontColor(int index,const QColor& fontColor);
private:
	enum MyEnum
	{
		FONTSIZE = 15	 //初始字体大小;
	};
private:
	QList<TradeItem>		m_ItemList;
	TradeItem				m_UpdatingItem;
	QMap<QString,QString>	m_PrePriceMap;

private:
	QMap<int,ColumnFont>		m_FontMap;
	QMap<int,ColumnObject>&		m_ColumnMap;
	

};


#endif

