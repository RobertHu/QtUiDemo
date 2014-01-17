#pragma once

#include <qstring.h>


class TradeItem
{

public:
	TradeItem();
	TradeItem(const QString& tradingCode);
	~TradeItem();
	TradeItem& operator=(const TradeItem& item);
public:
	QString m_TradingCode;
	QString m_CurrentTime;
	QString m_CurrentBidPrice;
	QString m_CurrentAskPrice;
	QString m_PreviousBidPrice;
	QString m_PreviousAskPrice;
	QString m_PreviousHightPrice;
	QString m_PreviousLowPrice;
	QString m_PreviousClosePrice;
	QString m_PreviousChangedPrice;
	QString m_OpenPrice;
	QString m_BuyRate;
	QString m_SellRate;
	bool	m_Double;//手数是否是double类型;
};
