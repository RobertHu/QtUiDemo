#ifndef PRICEDISPLAYBOARD_H
#define PRICEDISPLAYBOARD_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <string>
#include "PriceBox.h"
#include "TradeItem.h"
#include "CurrentPriceData.h"
#include "Enum.h"

namespace Controls
{
	class QuotationBox;
	class InstantOrderQuotationBox;
}


class PriceDisplayBoard:public QWidget
{
	Q_OBJECT
public:
	explicit PriceDisplayBoard(const TradeItem& item,QWidget *parent = 0);
	void	ChangeMarketInfo(MarkInfoType::MarkInfoType type);
	QString GetTradingCode();
	void	RealTimeDisplay(const TradeItem& item);
	
protected: 
	bool eventFilter(QObject* obj, QEvent* event);

private:
	Controls::QuotationBox* _frontBox;
	Controls::InstantOrderQuotationBox* _backBox;
	void	InitDisplayBoard();
	void	LayoutDisplayBoard();
	void	SetBidAskStatus(const QString& time,const QPixmap& pic,Qt::GlobalColor color);
	std::string GetTheSamePart(std::string& bid,std::string& ask);
	TradeItem		m_Item;
	QString			m_PrePrice;
	QString			m_PreTime; 
	bool			m_IsFront;

	QPixmap			m_PixmapUp;
	QPixmap			m_PixmapDown;
	QPixmap			m_PixmapNULL;
	static const QString _boxStyle;
	static const QString _labelStyle;
	static const QString _priceUpPicturePath;
	static const QString _priceDownPicturePath;
	static const QString _priceNormalPicturePath;
	
signals:
	void SendCurrentPriceSignal(const CurrentPriceData&);

public slots:
	void	TurnOverSlot(bool isFront);
};

#endif
