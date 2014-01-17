#ifndef ORDERDATALIST_H
#define ORDERDATALIST_H

#include <QString>
#include <QVariant>

class OrderData
{
public:
	OrderData();
	OrderData(bool close,const QString& openOrder,int lot);
public:
	bool		IsClose();
	bool		IsBid();
	QString		GetOpenOrder();
	QVariant	GetLot();
	void		SetClose(bool bClose);
	void		SetBid(bool bBid);
	void		SetOpenOrder(const QString& openOrder);
	void		SetLot(QVariant lot);
private:
	bool		m_Close;
	bool		m_Bid;
	QString		m_OpenOrder;
	QVariant	m_Lot;
};

#endif
