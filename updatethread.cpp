#include "updatethread.h"
#include <QTime>
#include <QTimer>

UpdateThread::UpdateThread(QList<TradeItem>& itemList,QObject *parent) : m_ItemList(itemList),QThread(parent)
{
}

UpdateThread::~UpdateThread()
{

}

void UpdateThread::run()
{	
	static bool bStart = false;
	if(!bStart)
	{
		QTimer* timer = new QTimer;
		connect(timer,SIGNAL(timeout()),SLOT(Update()));
		timer->start(200);
		bStart = true;
	}
	this->exec();
}

void UpdateThread::Update()	  ////≤‚ ‘÷Æ”√;
{
	QTime t;
	t= QTime::currentTime();
	qsrand(t.msec()+t.second()*1000);
	int n = qrand()%6;
	
	QString bid = "85";
	bid += QString(".6%0").arg(n);
	QString ask = "85";
	ask += QString(".3%0").arg(n);
	
	QList<TradeItem> list;
	for(int i=0;i<m_ItemList.count();i++)
	{	
		TradeItem  item = m_ItemList[i];
		item.m_CurrentAskPrice = ask;
		item.m_CurrentBidPrice = bid;
		item.m_CurrentTime = t.toString();
		list.append(item);
	}

	for(int i=0;i<list.count();i++)
		emit SendPriceSignal(list[i]);	  
	
}

