#include "OrderDataProvider.h"

OrderDataProvider::OrderDataProvider(const QString& tradingCode)
{
	m_TradingCode = tradingCode;
	m_OrderDataList = new QList<OrderData>();
	m_AccountDataList = new QList<AccountData>();
}
QString OrderDataProvider::GetTradingCode()
{
	return m_TradingCode;
}
LotData OrderDataProvider::GetLotData()
{
	return m_LotData;
}
QList<OrderData>* OrderDataProvider::GetOrderDataList()
{
	return m_OrderDataList;
}
QList<AccountData>* OrderDataProvider::GetAccountDataList()
{
	return m_AccountDataList;
}
void OrderDataProvider::SetLotData(const LotData& lotData)
{
	m_LotData = lotData;
}
void OrderDataProvider::SetOrderDataList(const QList<OrderData>& orderDataList)
{
	int count = orderDataList.count();
	for(int i=0;i<count;i++)
		m_OrderDataList->append(orderDataList[i]);
}
void OrderDataProvider::SetAccountDataList(const QList<AccountData>& accountDataList)
{
	int count = accountDataList.count();
	for(int i=0;i<count;i++)
		m_AccountDataList->append(accountDataList[i]);
}