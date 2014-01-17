#ifndef DATAPROVIDERBASE_H
#define DATAPROVIDERBASE_H

#include <QString>
#include <QList>

#include "LotData.h"
#include "OrderData.h"
#include "AccountData.h"



class OrderDataProviderBase
{
public:
	virtual QString				GetTradingCode() = 0; 
	virtual LotData				GetLotData() = 0;
	virtual QList<OrderData>*	GetOrderDataList() = 0;
	virtual QList<AccountData>* GetAccountDataList() = 0;
public:
	virtual void SetLotData(const LotData& lotData) = 0;
	virtual void SetOrderDataList(const QList<OrderData>& orderDataList) = 0;
	virtual void SetAccountDataList(const QList<AccountData>& accountDataList) = 0;


};

#endif
