#include "TableItemDelegate.h"

#include <QPainter>

#include "TableModel.h"
#include "TradeItem.h"

TableItemDelegate::TableItemDelegate(QMap<int,ColumnObject>& m_ColumnMap,QObject* parent):QItemDelegate(parent)
{
	m_UpPixmap = QPixmap("images/Up.png");
	m_DownPixmap = QPixmap("images/Down.png");
	for(int i=0;i<m_ColumnMap.count();i++)
	{
		if(m_ColumnMap[i].IsPicture())
		{
			m_PictureLogicalIndex = i;
			break;
		}
	}
}	
void TableItemDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const
{
	if(index.column()==m_PictureLogicalIndex)
	{
		const QAbstractItemModel* model = index.model();
		QVariant var = model->data(index,Qt::CheckStateRole);
		if(var.isNull())
			var = false;
		TableModel* tableModel = ((TableModel*)model);
		TradeItem item = tableModel->GetItemList().at(index.row());
		double perPrice = tableModel->GetPerPriceMap()[item.m_TradingCode].toDouble();
		double currentPrice = item.m_CurrentBidPrice.toDouble();
		QPixmap pixmap;
		if(currentPrice<perPrice)
			pixmap =  m_DownPixmap;
		else if(currentPrice>perPrice)
			pixmap = m_UpPixmap;
		else
			pixmap = QPixmap("");
		painter->drawPixmap(option.rect,pixmap);
	}

	QItemDelegate::paint(painter,option,index);
}