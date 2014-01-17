#ifndef TABLEITEMDELEGATE_H
#define TABLEITEMDELEGATE_H

#include <QItemDelegate>
#include <QMap>

#include "ColumnObject.h"


class TableItemDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	TableItemDelegate(QMap<int,ColumnObject>& m_ColumnMap,QObject* parent=0);
	
	//overwrite:
public:
	void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
private:
	QPixmap m_UpPixmap;
	QPixmap m_DownPixmap;
	int     m_PictureLogicalIndex;

};


#endif