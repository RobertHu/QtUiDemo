#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>
#include "TradeItem.h"
#include <qlist.h>


class UpdateThread : public QThread
{
	Q_OBJECT

public:
	UpdateThread(QList<TradeItem>& itemList,QObject *parent=0);
	~UpdateThread();

	//overwrite;
protected:
	void run() Q_DECL_OVERRIDE;

signals:
	void SendPriceSignal(const TradeItem& item);

private slots:
	void Update();

private:
	QList<TradeItem>&	m_ItemList;

};

#endif // UPDATETHREAD_H
