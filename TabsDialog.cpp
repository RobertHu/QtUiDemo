#include "TabsDialog.h"

#include <QLayout>
#include <QMap>
#include <QPair>

#include "UpdateThread.h"
#include "GridTab.h"
#include "ListTab.h"
#include "PriceDisplayBoardWindowBoxList.h"
#include "ColumnObject.h"
#include "Enum.h"


TabsDialog::TabsDialog(QList<TradeItem>& itemList,const QString& columnJsonFile,QWidget *parent):QDialog(parent)
{
	ListTab* listTab = new ListTab(itemList,columnJsonFile,parent);
	GridTab* gridTab = new GridTab(itemList,parent);
	
	m_TabWidget = new QTabWidget;

	m_TabWidget->addTab(gridTab,tr("Card View"));
	m_TabWidget->addTab(listTab,tr("List View"));
	
	m_TabWidget->setMovable(true);
	m_TabWidget->setTabPosition(QTabWidget::South);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_TabWidget);
	mainLayout->setMargin(5);
    setLayout(mainLayout); 
	
	TradeTable*  tradeTable = listTab->GetTable();
	PriceDisplayBoardWindowBoxList*  displayBoardList = gridTab->GetListViewPort()->GetList();
	UpdateThread* realTimeUpdateThread = new UpdateThread(itemList);  //注:itemList为引用参数，listTab或gridTab及UpdataThread线程均可修改此QList的内容与顺序;
	
	connect(realTimeUpdateThread,SIGNAL(SendPriceSignal(const TradeItem&)),displayBoardList,SLOT(RealTimeDisplay(const TradeItem&)));
	connect(realTimeUpdateThread,SIGNAL(SendPriceSignal(const TradeItem&)),tradeTable,SLOT(RealTimeDisplay(const TradeItem&)));
	realTimeUpdateThread->start();

	connect(displayBoardList,SIGNAL(AddSignal()),tradeTable,SLOT(AddSlot()));
	connect(displayBoardList,SIGNAL(OrderSignal(int)),tradeTable,SLOT(OrderSlot(int)));	 //可注释掉;
	connect(displayBoardList,SIGNAL(ChartSignal(int)),tradeTable,SLOT(ChartSlot(int)));	 //可注释掉;
	connect(displayBoardList,SIGNAL(DeleteSignal(int)),tradeTable,SLOT(DeleteSlot(int)));
	connect(displayBoardList,SIGNAL(MoveUpSignal(int)),tradeTable,SLOT(MoveUpSlot(int)));
	connect(displayBoardList,SIGNAL(UpToTopSignal(int)),tradeTable,SLOT(UpToTopSlot(int)));
	connect(displayBoardList,SIGNAL(MoveDownSignal(int)),tradeTable,SLOT(MoveDownSlot(int)));
	connect(displayBoardList,SIGNAL(DownToBottomSignal(int)),tradeTable,SLOT(DownToBottomSlot(int)));
	
	connect(tradeTable,SIGNAL(AddSignal()),displayBoardList,SLOT(AddSlot()));
	connect(tradeTable,SIGNAL(OrderSignal(int)),displayBoardList,SLOT(OrderSlot(int)));
	connect(tradeTable,SIGNAL(ChartSignal(int)),displayBoardList,SLOT(ChartSlot(int)));
	connect(tradeTable,SIGNAL(DeleteSignal(int)),displayBoardList,SLOT(DeleteSlot(int)));
	connect(tradeTable,SIGNAL(MoveUpSignal(int)),displayBoardList,SLOT(MoveUpSlot(int)));
	connect(tradeTable,SIGNAL(UpToTopSignal(int)),displayBoardList,SLOT(UpToTopSlot(int)));
	connect(tradeTable,SIGNAL(MoveDownSignal(int)),displayBoardList,SLOT(MoveDownSlot(int)));
	connect(tradeTable,SIGNAL(DownToBottomSignal(int)),displayBoardList,SLOT(DownToBottomSlot(int)));

//	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding) ;
}

TabsDialog::~TabsDialog(void)
{
}
