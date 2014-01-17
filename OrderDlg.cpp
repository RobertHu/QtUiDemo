#include "OrderDlg.h"

#include <QLayout>

#include "InstantOrderTab.h"
#include "PendingOrderTab.h"
#include "Enum.h"

OrderDlg::OrderDlg(OrderDataProviderBase* orderDataProvider,QWidget* parent) : QDialog(parent)
{
	this->setWindowTitle(orderDataProvider->GetTradingCode());

	QSize miniSize;
	m_TabWidget = new QTabWidget;

	InstantOrderTab* instantOrder = new InstantOrderTab(orderDataProvider,miniSize,this);
	PendingOrderTab* pendingOrder = new PendingOrderTab(orderDataProvider,miniSize,this);

	m_TabWidget->addTab(instantOrder,"Instant Order");
	m_TabWidget->addTab(pendingOrder,"Pending Order");

	m_TabWidget->setMovable(true);
	m_TabWidget->setTabPosition(QTabWidget::North);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_TabWidget);
	mainLayout->setMargin(MARGINSIZE);
    setLayout(mainLayout);

	QString tabBarStyle = "QTabBar::tab {min-width:100px;color: white;background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 gray);border: 2px solid;border-top-left-radius: 10px;border-top-right-radius: 10px;padding:5px;}	\
                           QTabBar::tab:!selected {margin-top: 5px;} \
                           QTabBar::tab:selected {color: blue;}";

	m_TabWidget->setStyleSheet(tabBarStyle);
                          
	miniSize.setWidth(miniSize.width()+2*5);
	miniSize.setHeight(miniSize.height()+2*5+m_TabWidget->tabBar()->size().height()+5);
	this->setMinimumSize(miniSize);

	connect(this,SIGNAL(SendCurrentPriceSignal(const CurrentPriceData&)),instantOrder,SLOT(GetCurrentPriceSlot(const CurrentPriceData&)));
	connect(this,SIGNAL(SendCurrentPriceSignal(const CurrentPriceData&)),pendingOrder,SLOT(GetCurrentPriceSlot(const CurrentPriceData&)));
}
OrderDlg::~OrderDlg()
{
	m_TabWidget->deleteLater();
}
void OrderDlg::accept()
{
	//.....


	QDialog::accept();
}