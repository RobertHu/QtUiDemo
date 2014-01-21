#include "PriceDisplayBoardWindowBoxList.h"

#include <QApplication>
#include <QScrollBar>
#include <QMouseEvent>
#include <QMenu>
#include <QStringList>
#include <QLayout>

#include "Enum.h"
#include "AddItem.h"
#include "OrderDlg.h"
#include "OrderDataProvider.h"
#include "CurrentPriceData.h"
#include "GridTab.h"


PriceDisplayBoardWindowBoxList::PriceDisplayBoardWindowBoxList(QList<TradeItem>& itemList,QWidget* parent):m_ItemList(itemList),QListView(parent)
{	
	this->setBackgroundRole(QPalette::Window);
	this->InitList();
}

void PriceDisplayBoardWindowBoxList::InitList()
{
	QListIterator<TradeItem> it(m_ItemList);
	int i=0;
	while(it.hasNext())
	{
		PriceDisplayBoardWindowBox* item = new PriceDisplayBoardWindowBox(it.next(),this);
		item->show();
		item->SetOrderIndex(i);
		item->move(0,i*HEIGHT+(i+1)*GRAP);
		m_PriceDisplayBoardWindowBoxList.append(item); //½«TradeItem×ª»»³ÉGritItem;
		i++;
	}
}

void PriceDisplayBoardWindowBoxList::Resize()
{
	int itemCount = m_PriceDisplayBoardWindowBoxList.count();
	int width = ((QWidget*)(parent()->parent()))->size().width() - ((GridTab*)(parent()->parent()))->GetVScrollBar()->width();
	int column = width/WIDTH;
	column = width/WIDTH==0 ? 1 : column;	//if(width < WIDTH) => column = 1;
	int row = itemCount/column;
	row = itemCount%column==0 ? row : (row+1) ;
	ReSizeSlot(row,column);
}

void PriceDisplayBoardWindowBoxList::Clear()
{
	while(m_PriceDisplayBoardWindowBoxList.count()>0)
		m_PriceDisplayBoardWindowBoxList[0]->Delete();
	m_ItemList.clear();
}

void PriceDisplayBoardWindowBoxList::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		QMenu * popupMenu = new QMenu(this);
		QString menuStyle = "QMenu { font-size:18px; color:white; background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #333333);}" ;
		popupMenu->setStyleSheet(menuStyle);

		popupMenu->addAction(tr("&Add"),this,SLOT(Add()),QKeySequence(Qt::CTRL + Qt::Key_A));
		popupMenu->addSeparator();

		QAction* highestLowest = new QAction(tr("&HighestLowest"), this);
		connect(highestLowest,SIGNAL(triggered()), this, SLOT(HighestLowest()));
		QAction* preClose = new QAction(tr("&PreClose"), this);
		connect(preClose,SIGNAL(triggered()), this, SLOT(PreClose()));
		QAction* interestRate = new QAction(tr("&InterestRate"), this);
		connect(interestRate,SIGNAL(triggered()), this, SLOT(InterestRate()));

		QActionGroup* infoGroup = new QActionGroup(this);
		infoGroup->addAction(highestLowest);
		infoGroup->addAction(preClose);
		infoGroup->addAction(interestRate);

		QMenu* marketInfo = popupMenu->addMenu(tr("&MarketInformations"));
		marketInfo->addAction(highestLowest);
		marketInfo->addAction(preClose);
		marketInfo->addAction(interestRate);

		popupMenu->exec(event->globalPos());
	}
}
void PriceDisplayBoardWindowBoxList::AddSlot()
{
	QMap<int,QString> itemMap,temp;
	int count = m_PriceDisplayBoardWindowBoxList.count();
	for(int i=0;i<count;i++)
	{
		itemMap.insert(m_PriceDisplayBoardWindowBoxList[i]->GetOrderIndex(),m_PriceDisplayBoardWindowBoxList[i]->GetPriceDisplayBoard()->GetTradingCode());
	}
	temp = itemMap;
	AddItem	dlg(itemMap,this);

	if(QDialog::Accepted==dlg.exec())
	{
		if(itemMap.isEmpty())
		{
			this->Clear();
			emit AddSignal();
			return ;
		}
		if(temp==itemMap)
			return ;

		qApp->processEvents();	

		this->Clear();
		QList<TradeItem> itemList; 

		TradeItem item("");
		item.m_TradingCode = " ";
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

		QMapIterator<int,QString> it(itemMap);
		while(it.hasNext())
		{
			it.next();
			item.m_TradingCode = it.value();
			itemList.append(item);
		}
		m_ItemList = itemList;
		this->InitList() ;
		this->Resize();

		emit AddSignal();	
	}
}
void PriceDisplayBoardWindowBoxList::OrderSlot(int index)
{	
	PriceDisplayBoard* price = m_PriceDisplayBoardWindowBoxList[index]->GetPriceDisplayBoard();
	OrderDataProviderBase* orderDataProvider = m_PriceDisplayBoardWindowBoxList[index]->GetOrderDataProvider();
	OrderDlg dlg(orderDataProvider,this);
	connect(price,SIGNAL(SendCurrentPriceSignal(const CurrentPriceData&)),&dlg,SIGNAL(SendCurrentPriceSignal(const CurrentPriceData&)));
	if(QDialog::Accepted==dlg.exec())
	{
		emit OrderSignal(index);
	}
}
void PriceDisplayBoardWindowBoxList::ChartSlot(int index)
{
	///.....
	//QMessageBox::about(this,"ddd","chart");

}
void PriceDisplayBoardWindowBoxList::DeleteSlot(int index)
{
	int count = m_PriceDisplayBoardWindowBoxList.count();
	QString tradingCode = m_PriceDisplayBoardWindowBoxList[index]->GetPriceDisplayBoard()->GetTradingCode();
	for(int i=0;i<m_ItemList.count();i++)
	{
		if(tradingCode==m_ItemList[i].m_TradingCode)
		{
			m_ItemList.removeAt(i);
			break;
		}
	}
	m_PriceDisplayBoardWindowBoxList[index]->deleteLater();
	m_PriceDisplayBoardWindowBoxList.removeAt(index);
	if(index<count-1)
	{
		for(int i = index;i<count-1;i++)
			m_PriceDisplayBoardWindowBoxList[i]->SetOrderIndex(i);
	}
	this->Resize();
	emit DeleteSignal(index);
}

void PriceDisplayBoardWindowBoxList::MoveUpSlot(int index)
{
	if(index>0)
	{
		m_PriceDisplayBoardWindowBoxList.move(index,index-1);
		m_PriceDisplayBoardWindowBoxList[index]->SetOrderIndex(index);
		m_PriceDisplayBoardWindowBoxList[index-1]->SetOrderIndex(index-1);
		emit MoveUpSignal(index);
	}
	this->Resize();
}
void PriceDisplayBoardWindowBoxList::UpToTopSlot(int index)
{
	if(index>0)
	{
		m_PriceDisplayBoardWindowBoxList.move(index,0);
		for(int i=0;i<m_PriceDisplayBoardWindowBoxList.count();i++)
		{
			m_PriceDisplayBoardWindowBoxList[i]->SetOrderIndex(i);
		} 
		emit UpToTopSignal(index);
	}
	this->Resize();
}
void PriceDisplayBoardWindowBoxList::MoveDownSlot(int index)
{
	if(index < m_PriceDisplayBoardWindowBoxList.count()-1)
	{
		m_PriceDisplayBoardWindowBoxList.move(index,index+1);
		m_PriceDisplayBoardWindowBoxList[index]->SetOrderIndex(index);
		m_PriceDisplayBoardWindowBoxList[index+1]->SetOrderIndex(index+1);
		emit MoveDownSignal(index);
	}
	this->Resize();
}
void PriceDisplayBoardWindowBoxList::DownToBottomSlot(int index)
{
	int rearIndex = m_PriceDisplayBoardWindowBoxList.count() - 1;
	if(index < rearIndex)
	{
		m_PriceDisplayBoardWindowBoxList.move(index,rearIndex);
		for(int i = index;i<=rearIndex;i++)
			m_PriceDisplayBoardWindowBoxList[i]->SetOrderIndex(i);
		emit DownToBottomSignal(index);
	}
	this->Resize();
}

void PriceDisplayBoardWindowBoxList::HighestLowest()
{
	for(int i=0;i<m_PriceDisplayBoardWindowBoxList.count();i++)
	{
		m_PriceDisplayBoardWindowBoxList[i]->HighestLowest();
	}
}

void PriceDisplayBoardWindowBoxList::PreClose()
{
	for(int i=0;i<m_PriceDisplayBoardWindowBoxList.count();i++)
	{
		m_PriceDisplayBoardWindowBoxList[i]->PreClose();
	}
}

void PriceDisplayBoardWindowBoxList::InterestRate()
{
	for(int i=0;i<m_PriceDisplayBoardWindowBoxList.count();i++)
	{
		m_PriceDisplayBoardWindowBoxList[i]->InterestRate();
	}
}

void PriceDisplayBoardWindowBoxList::RealTimeDisplay(const TradeItem& item)
{
	for(int i=0;i<m_PriceDisplayBoardWindowBoxList.count();i++)
	{
		if(m_PriceDisplayBoardWindowBoxList[i]->GetPriceDisplayBoard()->GetTradingCode()==item.m_TradingCode)
		{
			m_PriceDisplayBoardWindowBoxList[i]->GetPriceDisplayBoard()->RealTimeDisplay(item);
			m_PriceDisplayBoardWindowBoxList[i]->GetPriceDisplayBoard()->update();
			break;
		}
	}
}

void PriceDisplayBoardWindowBoxList::ReSizeSlot(int row,int column)
{
	int x=0,y=0;
	int itemIndex = 0;
	int itemHeight = HEIGHT+GRAP;
	int itemWidth = WIDTH+GRAP;
	int edgePad = 2*GRAP;
	for(int i=0;i<row;i++)
	{
		y = i * itemHeight + edgePad;
		for(int j=0;j<column;j++) 
		{
			x = j * itemWidth + edgePad;		  
			if(itemIndex < m_PriceDisplayBoardWindowBoxList.count())
			{
				m_PriceDisplayBoardWindowBoxList[itemIndex++]->move(x,y);
			}
		}
	}

}


int PriceDisplayBoardWindowBoxList::GetCounts()
{
	return m_PriceDisplayBoardWindowBoxList.count();
}
