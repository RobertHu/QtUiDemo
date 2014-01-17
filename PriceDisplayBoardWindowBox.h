#ifndef PRICEDISPLAYBOARDWINDOWBOX_H
#define	PRICEDISPLAYBOARDWINDOWBOX_H

#include <QWidget>
#include "TradeItem.h"
#include <QMouseEvent>

#include "PriceDisplayBoard.h"
#include "OrderDataProvider.h"

class PriceDisplayBoardWindowBox:public QWidget
{
	Q_OBJECT
public:
	explicit PriceDisplayBoardWindowBox(const TradeItem& item,QWidget* parent = 0);

public:
	void				SetOrderIndex(int index);
	int					GetOrderIndex();
	PriceDisplayBoard*	GetPriceDisplayBoard();
	OrderDataProviderBase*	GetOrderDataProvider();
	
	//overwrite;
protected: 
	void	mouseDoubleClickEvent(QMouseEvent * event);
	void	mousePressEvent(QMouseEvent * event);

signals:
	void	TurnOverSignal(bool);
	void	AddSignal();
	void	OrderSignal(int);
	void	ChartSignal(int);
	void	DeleteSignal(int);
	void	MoveUpSignal(int);
	void	MoveDownSignal(int);
	void	UpToTopSignal(int);
	void	DownToBottomSignal(int);

public slots:
	void	Order();
	void	Chart();
	void	Delete();
	void	Add();
	void	MoveUp();
	void	UpToTop();
	void	MoveDown();
	void	DownToBottom();
public slots:
	void	HighestLowest();
	void	PreClose();
	void	InterestRate();

private:
	void	TurnOver();

private:
	bool					m_IsFront;  //是否显示的是正面;
	int						m_OrderIndex;
	PriceDisplayBoard*		m_PriceDisplayBoard;
	OrderDataProviderBase*	m_OrderDataProvider;


};

#endif