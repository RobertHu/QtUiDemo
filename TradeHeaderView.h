#ifndef TRADEHEADERVIEW_H
#define TRADEHEADERVIEW_H

#include <QHeaderView>

#include "ColumnObject.h"


class TradeHeaderView : public QHeaderView
{
	Q_OBJECT
public:
	TradeHeaderView(QMap<int,ColumnObject>& columnMap,Qt::Orientation orientation = Qt::Horizontal,QWidget* parent=0);
	//overwrite:
protected:
	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
	void mousePressEvent(QMouseEvent * event);
public slots:
	void HideThisColumn();
	void HideColumns();
	void SetThisColumnFont();

private:
	QPoint			m_CurrentPoint;
	int				m_HideIndex;
	int				m_LogicalIndex;	
private:
	QMap<int,ColumnObject>&		m_ColumnMap;
};



#endif
