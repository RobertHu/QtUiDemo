#include "HorizontalHeaderSettingDlgModel.h"

HorizontalHeaderSettingDlgModel::HorizontalHeaderSettingDlgModel(QMap<int,ColumnObject>& columnMap,QObject * parent) : QStandardItemModel(parent)
{
	QIcon showIcon("images/button-show.png");
	QIcon hideIcon("images/button-hide.png");
	int columnCount = columnMap.count();
	QIcon icon;
	QBrush brush;
	for(int i=0;i<columnCount;i++)
	{
		QStandardItem* item;

		if(columnMap[i].IsShow()) 
		{
			icon = showIcon;
			brush.setColor(QColor(Qt::black));
		}
		else 
		{
			icon = hideIcon;
			brush.setColor(QColor(Qt::gray));
		}
		item = new QStandardItem(icon,columnMap[i].GetColumnText());
		item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled) ^ (Qt::ItemIsEditable));
		item->setForeground(brush);
		if(columnMap[i].IsForbidHide())
		{	
			item->setBackground(QBrush(QColor(Qt::gray)));
			item->setToolTip("Forbid to hide !");
		}
		this->appendRow(item);
	}
}	