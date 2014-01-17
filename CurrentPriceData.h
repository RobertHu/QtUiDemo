#ifndef CURRENTPRICEDATA_H
#define CURRENTPRICEDATA_H

#include <QString>

class CurrentPriceData
{
public:
	CurrentPriceData(int status,const QString& commPrice,const QString& bidPrice,const QString& askPrice);

public:
	int		GetTrendStatus() const;
	QString GetCurrentCommPrice() const;
	QString GetCurrentBidPrice() const;
	QString GetCurrentAskPrice() const;
private:
	int		m_TrendStatus;
	QString m_CurrentCommPrice;
	QString m_CurrentBidPrice;
	QString m_CurrentAskPrice;


};

#endif
