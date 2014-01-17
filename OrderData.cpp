#include "OrderData.h"

OrderData::OrderData()
{
}
OrderData::OrderData(bool close,const QString& openOrder,int lot):m_Close(close),m_OpenOrder(openOrder),m_Lot(lot)
{
}

bool OrderData::IsClose()
{
	return m_Close;
}
bool OrderData::IsBid()
{
	return m_Bid;
}
QString OrderData::GetOpenOrder()
{
	return m_OpenOrder;
}
QVariant OrderData::GetLot()
{
	return m_Lot;
}
void OrderData::SetClose(bool bClose)
{
	m_Close = bClose;
}
void OrderData::SetBid(bool bBid)
{
	m_Bid = bBid;
}
void OrderData::SetOpenOrder(const QString& openOrder)
{
	m_OpenOrder = openOrder;
}
void OrderData::SetLot(QVariant lot)
{
	m_Lot = lot;
}
