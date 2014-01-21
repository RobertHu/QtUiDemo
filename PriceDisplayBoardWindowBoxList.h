#ifndef PRICEDISPLAYBOARDWINDOWBOXLIST_H
#define	PRICEDISPLAYBOARDWINDOWBOXLIST_H

#include <QWidget>
#include <QListView>
#include "TradeItem.h"
#include "PriceDisplayBoardWindowBox.h"


class PriceDisplayBoardWindowBoxList:public QListView
{
	Q_OBJECT
public:
	explicit PriceDisplayBoardWindowBoxList(QList<TradeItem>& itemList,QWidget* parent=0); 
	
	//overwrite;
protected:
	void  mousePressEvent(QMouseEvent * event);

signals:
	void	AddSignal();
	void	OrderSignal(int);
	void	ChartSignal(int);
	void	DeleteSignal(int);
	void	MoveUpSignal(int);
	void	UpToTopSignal(int);
	void	MoveDownSignal(int);
	void	DownToBottomSignal(int);
public slots:
	void	AddSlot();
	void	OrderSlot(int);
	void	ChartSlot(int);
	void	DeleteSlot(int);
	void	MoveUpSlot(int);
	void	UpToTopSlot(int);
	void	MoveDownSlot(int);
	void	DownToBottomSlot(int); 
public  slots:
	void	HighestLowest();
	void	PreClose();
	void	InterestRate();
public slots:
	void	RealTimeDisplay(const TradeItem&);
	void	ReSizeSlot(int,int);
public:
	int		GetCounts();
private:
	void	InitList();
	void	Resize(); 
	void	Clear();

private:
	QList<TradeItem>&					m_ItemList;			 //ÒýÓÃ;
	QList<PriceDisplayBoardWindowBox*>  m_PriceDisplayBoardWindowBoxList;
	

};

#endif