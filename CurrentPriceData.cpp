#include "CurrentPriceData.h"
#include "Enum.h"

CurrentPriceData::CurrentPriceData(int status,const QString& commPrice,const QString& bidPrice,const QString& askPrice)
{
	switch (status)
	{
	case Qt::blue:
		m_TrendStatus = UP;
		break;
	case Qt::red:
		m_TrendStatus = DOWN;
		break;
	case Qt::gray:
	default:
		m_TrendStatus = KEEP;
		break;
	}
	
	m_CurrentCommPrice = commPrice;
	m_CurrentBidPrice = bidPrice;
	m_CurrentAskPrice = askPrice;
}
int	CurrentPriceData::GetTrendStatus() const
{
	return m_TrendStatus;
}
QString CurrentPriceData::GetCurrentCommPrice() const
{
	return m_CurrentCommPrice;
}
QString CurrentPriceData::GetCurrentBidPrice() const
{
	return m_CurrentBidPrice;
}
QString CurrentPriceData::GetCurrentAskPrice() const
{
	return m_CurrentAskPrice;
}