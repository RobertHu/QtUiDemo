#ifndef LISTVIEWPORT_H
#define LISTVIEWPORT_H

#include <QWidget>
#include <QSizePolicy>


#include "Tradeitem.h"
#include "PriceDisplayBoardWindowBoxList.h"

class ListViewPort : public QWidget
{
	Q_OBJECT
public:
	ListViewPort(QList<TradeItem>& itemList,QWidget* parent=0);
	//overwrite:
protected:
	QSizePolicy	sizePolicy() const;
	QSize minimumSizeHint() const;

public :
	PriceDisplayBoardWindowBoxList*  GetList();
private:
	PriceDisplayBoardWindowBoxList*  m_List;
	
};

#endif

