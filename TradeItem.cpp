#include "TradeItem.h"


TradeItem::TradeItem()
{
}
TradeItem::TradeItem(const QString& tradingCode):m_TradingCode(tradingCode)
{
}

TradeItem::~TradeItem(void)
{
}
TradeItem& TradeItem::operator=(const TradeItem& item)
{
	if(this==&item)
		return (*this);
	this->m_TradingCode = item.m_TradingCode;
	this->m_CurrentTime = item.m_CurrentTime;
	this->m_CurrentBidPrice = item.m_CurrentBidPrice;
	this->m_CurrentAskPrice = item.m_CurrentAskPrice;
	this->m_PreviousBidPrice = item.m_PreviousBidPrice;
	this->m_PreviousAskPrice = item.m_PreviousAskPrice;
	this->m_PreviousHightPrice = item.m_PreviousHightPrice;
	this->m_PreviousLowPrice = item.m_PreviousLowPrice;
	this->m_PreviousClosePrice = item.m_PreviousClosePrice;
	this->m_PreviousChangedPrice = item.m_PreviousChangedPrice;
	this->m_OpenPrice = item.m_OpenPrice;
	this->m_BuyRate = item.m_BuyRate;
	this->m_SellRate = item.m_SellRate;
	this->m_Double = item.m_Double;

	return *this;
}
