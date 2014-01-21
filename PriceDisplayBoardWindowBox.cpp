#include "PriceDisplayBoardWindowBox.h"

#include <QMenu>
#include <QApplication>

#include "Enum.h"

PriceDisplayBoardWindowBox::PriceDisplayBoardWindowBox(const TradeItem& item,QWidget* parent):QWidget(parent)
{
	m_IsFront = true;
	m_OrderIndex = 0;
	m_PriceDisplayBoard = new PriceDisplayBoard(item,this);
	m_OrderDataProvider = new OrderDataProvider(item.m_TradingCode);
	m_OrderDataProvider->SetLotData(LotData(item.m_Double,2,10,100));   ///-------note:...

	setFixedSize(WIDTH,HEIGHT);

	connect(this,SIGNAL(TurnOverSignal(bool)),m_PriceDisplayBoard,SLOT(TurnOverSlot(bool)));

	connect(this,SIGNAL(OrderSignal(int)),parent,SLOT(OrderSlot(int)));
	connect(this,SIGNAL(ChartSignal(int)),parent,SLOT(ChartSlot(int)));
	connect(this,SIGNAL(DeleteSignal(int)),parent,SLOT(DeleteSlot(int)));	
	connect(this,SIGNAL(AddSignal()),parent,SLOT(AddSlot()));
	connect(this,SIGNAL(MoveUpSignal(int)),parent,SLOT(MoveUpSlot(int)));
	connect(this,SIGNAL(UpToTopSignal(int)),parent,SLOT(UpToTopSlot(int)));
	connect(this,SIGNAL(MoveDownSignal(int)),parent,SLOT(MoveDownSlot(int)));
	connect(this,SIGNAL(DownToBottomSignal(int)),parent,SLOT(DownToBottomSlot(int)));
}
void PriceDisplayBoardWindowBox::SetOrderIndex(int index)
{
	m_OrderIndex = index;
}
int	 PriceDisplayBoardWindowBox::GetOrderIndex()
{
	return m_OrderIndex;
}
PriceDisplayBoard* PriceDisplayBoardWindowBox::GetPriceDisplayBoard()
{
	return m_PriceDisplayBoard;
}
OrderDataProviderBase*	PriceDisplayBoardWindowBox::GetOrderDataProvider()
{
	return m_OrderDataProvider;
}

void PriceDisplayBoardWindowBox::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) 
	{	
		this->TurnOver();
		emit TurnOverSignal(m_IsFront);
	}

}
void PriceDisplayBoardWindowBox::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		QMenu * popupMenu = new QMenu(this);
		QString menuStyle = "QMenu { font-size:18px; color:white; background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #555555);}" ;
		popupMenu->setStyleSheet(menuStyle);

		popupMenu->addAction(tr("&Order"), this, SLOT(Order()),QKeySequence(Qt::CTRL + Qt::Key_O));
		popupMenu->addAction(tr("&Chart"),this,SLOT(Chart()),QKeySequence(Qt::CTRL + Qt::Key_C));
		popupMenu->addSeparator();
		popupMenu->addAction(tr("&Delete"),this,SLOT(Delete()),QKeySequence(Qt::CTRL + Qt::Key_D));
		popupMenu->addAction(tr("&Add"),this,SLOT(Add()),QKeySequence(Qt::CTRL + Qt::Key_A));
		popupMenu->addAction(tr("&Move&Up"),this,SLOT(MoveUp()),QKeySequence(Qt::CTRL + Qt::Key_M,Qt::CTRL + Qt::Key_U));
		popupMenu->addAction(tr("&UpTo&Top"),this,SLOT(UpToTop()),QKeySequence(Qt::CTRL + Qt::Key_U,Qt::CTRL + Qt::Key_T));
		popupMenu->addAction(tr("&Move&Down"),this,SLOT(MoveDown()),QKeySequence(Qt::CTRL + Qt::Key_M,Qt::CTRL + Qt::Key_D));
		popupMenu->addAction(tr("&DownTo&Bottom"),this,SLOT(DownToBottom()),QKeySequence(Qt::CTRL + Qt::Key_D,Qt::CTRL + Qt::Key_B));
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
void PriceDisplayBoardWindowBox::Order()
{
	emit OrderSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::Chart()
{
	emit ChartSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::Delete()
{ 
	emit DeleteSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::Add()
{
	emit AddSignal();
}
void PriceDisplayBoardWindowBox::MoveUp()
{
	emit MoveUpSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::UpToTop()
{
	emit UpToTopSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::MoveDown()
{	
	emit MoveDownSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::DownToBottom()
{
	emit DownToBottomSignal(m_OrderIndex);
}
void PriceDisplayBoardWindowBox::HighestLowest()
{
	m_PriceDisplayBoard->ChangeMarketInfo(MarkInfoType::HighLow);
}
void PriceDisplayBoardWindowBox::PreClose()
{
	m_PriceDisplayBoard->ChangeMarketInfo(MarkInfoType::PreClose);
}
void PriceDisplayBoardWindowBox::InterestRate()
{
	m_PriceDisplayBoard->ChangeMarketInfo(MarkInfoType::InterestClose );
}
void PriceDisplayBoardWindowBox::TurnOver()
{	
	int stepLenth;		
	if(m_IsFront)
	{
		int moveLenth = -(HEIGHT+GRAP);
		for(stepLenth = 0;stepLenth>=moveLenth;stepLenth-=TRUNOVERRATE)	 
		{
			qApp->processEvents();	
			m_PriceDisplayBoard->move(0,stepLenth);
			_sleep(10);
		}
		if(stepLenth<moveLenth)
			m_PriceDisplayBoard->move(0,moveLenth);
	}
	else
	{
		for(stepLenth=-(HEIGHT+GRAP);stepLenth<=0;stepLenth+=TRUNOVERRATE)	
		{
			qApp->processEvents(); 
			m_PriceDisplayBoard->move(0,stepLenth);
			_sleep(10);
		}
		if(stepLenth>0)
		   m_PriceDisplayBoard->move(0,0);
		
	}
	m_IsFront = !m_IsFront;
}