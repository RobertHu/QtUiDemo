#ifndef ORDERDATAPROVIDER_H
#define ORDERDATAPROVIDER_H

#include "OrderDataProviderBase.h"

class OrderDataProvider : public OrderDataProviderBase
{
public:
	OrderDataProvider(const QString& tradingCode);
public:
	QString				GetTradingCode();
	LotData				GetLotData();
	QList<OrderData>*	GetOrderDataList();
	QList<AccountData>* GetAccountDataList();
public:
	void				SetLotData(const LotData& lotData);
	void				SetOrderDataList(const QList<OrderData>& orderDataList);
	void				SetAccountDataList(const QList<AccountData>& accountDataList);


private:
	QString				m_TradingCode;
	LotData				m_LotData;
	QList<OrderData>*	m_OrderDataList;
	QList<AccountData>*	m_AccountDataList;

};



#endif
