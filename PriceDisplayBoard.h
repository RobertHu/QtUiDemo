#ifndef PRICEDISPLAYBOARD_H
#define PRICEDISPLAYBOARD_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>

#include "PriceBox.h"
#include "TradeItem.h"
#include "CurrentPriceData.h"



class PriceDisplayBoard:public QWidget
{
	Q_OBJECT
public:
	explicit PriceDisplayBoard(const TradeItem& item,QWidget *parent = 0);
	
	//overwrite;
protected: 
	bool eventFilter(QObject* obj, QEvent* event);

signals:
	void SendCurrentPriceSignal(const CurrentPriceData&);

public slots:
	void	TurnOverSlot(bool isFront);

public:
	void	ChangeMarketInfo(int markInfo);
	QString GetTradingCode();
	void	RealTimeDisplay(const TradeItem& item);


private:
	void	InitDisplayBoard();
	void	LayoutDisplayBoard();
	void	SetBidAskStatus(const QString& time,const QPixmap& pic,Qt::GlobalColor color);
	QString GetTheSamePart(QString& str1,QString& str2);
	void	InitPriceBox(PriceBox* priceBox);

private:
	TradeItem		m_Item;
	QString			m_PrePrice;
	QString			m_PreTime; 
	bool			m_IsFront;

private:
	QLabel*			m_StatusBmp;
	QLabel*			m_CurrentPriceComm;
	PriceBox*		m_CurrentBidBox;
	PriceBox*		m_CurrentAskBox;
	QLabel*			m_HightLow;
	QLabel*			m_Hightest;
	QLabel*			m_Lowest;
	QGroupBox*		m_MainGroupBox;

	QLabel*			m_CurrentTime;
	QLabel*			m_StatusBmp2;
	QLabel*			m_CurrentPriceComm2;
	PriceBox*		m_CurrentBidBox2;
	PriceBox*		m_CurrentAskBox2;
	QComboBox*		m_OpenClose;
	QSpinBox*		m_Hands;
	QDoubleSpinBox*	m_DbHands;
	QGroupBox*		m_MainGroupBox2;

private:
	QString			m_StyleBlue;
	QString			m_StyleRed;
	QString			m_StyleGray;
	QPixmap			m_PixmapUp;
	QPixmap			m_PixmapDown;
	QPixmap			m_PixmapNULL;
};

#endif
