
#include <QtWidgets/QApplication>

#include "TabsDialog.h"
#include "TradeItem.h"
#include "ColumnObject.h"

#include <qlist.h>

#include <QTextCodec>

#include <QJsonObject>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	QList<TradeItem> itemList;

	TradeItem item("");
	item.m_TradingCode = "d LLG";
	item.m_CurrentTime = "15:50:36";
	item.m_CurrentBidPrice = "85.32";
	item.m_CurrentAskPrice = "85.65";
	item.m_PreviousBidPrice = "52.16" ;
	item.m_PreviousAskPrice = "53.65";
	item.m_PreviousHightPrice = "56.52";
	item.m_PreviousLowPrice = "50.62";
	item.m_PreviousClosePrice = "15.63";
	item.m_PreviousChangedPrice = "16.23";
	item.m_OpenPrice = "16.52";
	item.m_BuyRate = "0.052";
	item.m_SellRate = "0.063";
	item.m_Double = false;

	TradeItem pair1 = item;
	item.m_TradingCode = "d LLS";
	item.m_Double = true;
	TradeItem pair2 = item;
	item.m_TradingCode = "p GSD";
	item.m_Double = false;
	TradeItem pair3 = item;
	item.m_TradingCode = "d CAD";
	item.m_Double = false;
	TradeItem pair4 = item;
	item.m_TradingCode = "d GBP";
	item.m_Double = true;
	TradeItem pair5 = item;
	item.m_TradingCode = "d AUD";
	item.m_Double = true;
	TradeItem pair6 = item;
	item.m_TradingCode = "d CADAUD";
	TradeItem pair7 = item;
	item.m_TradingCode = "d CHF";
	TradeItem pair8 = item;
	item.m_TradingCode = "d EUR";
	TradeItem pair9 = item;
	item.m_TradingCode = "HKG";
	TradeItem pair10 = item;
	item.m_TradingCode = "JPY";
	TradeItem pair11 = item;
	item.m_TradingCode = "CHF";
	TradeItem pair12 = item;
	item.m_TradingCode = "p HKD";
	TradeItem pair13 = item;


	itemList.append(pair1);
	itemList.append(pair2);
	itemList.append(pair3);
	itemList.append(pair4);
	itemList.append(pair5);
	itemList.append(pair6);
	itemList.append(pair7);
	itemList.append(pair8);
	itemList.append(pair9);
	itemList.append(pair10);
	itemList.append(pair11);
	itemList.append(pair12);
//	itemList.append(pair13);


	//调用接口;
	TabsDialog dlg(itemList,"Column.json");
	dlg.show();
					
	return a.exec();
}
