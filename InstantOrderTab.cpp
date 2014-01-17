#include "InstantOrderTab.h"
#include <QDate>

#include "Enum.h"
#include "OrderDataProvider.h"
#include "CurrentPriceData.h"



InstantOrderTab::InstantOrderTab(OrderDataProviderBase* orderDataProvider,QSize& miniSize,QWidget* tabWidgetParent,QWidget* parent) : QDialog(parent)
{
	m_CommPrice = "";
	m_BidPrice = "";
	m_AskPrice = "";
	m_OrderDataProvider = orderDataProvider;

	m_BidBtn = new BidAskPriceButton(QSize(BIDASKWIDTH,BIDASKHEIGHT),m_CommPrice,m_BidPrice,Qt::blue,true,this);
	m_AskBtn = new BidAskPriceButton(QSize(BIDASKWIDTH,BIDASKHEIGHT),m_CommPrice,m_AskPrice,Qt::red,false,this);
	m_AccountLabel = new QLabel("Accout",this);

	m_LotLabel = new QLabel("Lot",this);
	m_AccountEdit = new QLineEdit(orderDataProvider->GetTradingCode(),this);
	if(orderDataProvider->GetLotData().IsDouble())
	{
		m_LotDoubleSpinBox = new QDoubleSpinBox(this);
		m_LotDoubleSpinBox->setSingleStep(orderDataProvider->GetLotData().StepLenth().toDouble());
		m_LotDoubleSpinBox->setMinimum(orderDataProvider->GetLotData().MiniValue().toDouble());
		m_LotDoubleSpinBox->setMaximum(orderDataProvider->GetLotData().MaxValue().toDouble());
	}
	else
	{
		m_LotSpinBox = new QSpinBox(this);
		m_LotSpinBox->setSingleStep(orderDataProvider->GetLotData().StepLenth().toInt());
		m_LotSpinBox->setMinimum(orderDataProvider->GetLotData().MiniValue().toInt());
		m_LotSpinBox->setMaximum(orderDataProvider->GetLotData().MaxValue().toInt());
	
	}
	m_AccountEdit->setEnabled(false);

	m_OrderedList = new OrderListView(orderDataProvider->GetOrderDataList(),this);
	m_CloseAllBtn = new QPushButton("Close All",this);
	m_ExitBtn = new QPushButton("Exit",this);

	this->Init(miniSize,tabWidgetParent);
}
void InstantOrderTab::resizeEvent(QResizeEvent * event)
{
	QRect rect = m_OrderedList->geometry();
	int x = rect.x();
	int y = rect.y();
	int width = this->size().width()-x-CONTROLSGRAP;
	int height = this->size().height()-y-2*CONTROLSGRAP-m_CloseAllBtn->size().height();
	m_OrderedList->setGeometry(x,y,width,height);

	m_CloseAllBtn->setGeometry(x,y+height+CONTROLSGRAP,m_CloseAllBtn->size().width(),m_CloseAllBtn->size().height());
	m_ExitBtn->setGeometry(x+width-m_ExitBtn->size().width(),y+height+CONTROLSGRAP,m_ExitBtn->size().width(),m_ExitBtn->size().height());

	QWidget::resizeEvent(event);
}
void InstantOrderTab::SetCloseAllSlot()
{
	//int count = m_OrderDataList.count();
	//for(int i=0;i<count;i++)
	//	m_OrderDataList[i].SetClose(true);
	//this->update();
}
void InstantOrderTab::PlaceAnOrderSlot(bool isBid)
{
	this->PlaceAnOrderBidAsk(isBid);
}
void InstantOrderTab::GetCurrentPriceSlot(const CurrentPriceData& currentPriceData)
{
	m_CommPrice = currentPriceData.GetCurrentCommPrice();
	m_BidPrice = currentPriceData.GetCurrentBidPrice();
	m_AskPrice = currentPriceData.GetCurrentAskPrice();

	m_BidBtn->SetCenterCommPriceText(m_CommPrice);
	m_BidBtn->SetCenterBidAskPriceText(m_BidPrice);
	m_BidBtn->SetTrendStatus(currentPriceData.GetTrendStatus());
	m_AskBtn->SetCenterCommPriceText(m_CommPrice);
	m_AskBtn->SetCenterBidAskPriceText(m_AskPrice);
	m_AskBtn->SetTrendStatus(currentPriceData.GetTrendStatus());
}

void InstantOrderTab::Init(QSize& miniSize,QWidget* tabWidgetParent)
{
	this->InitLayout(miniSize);

	QString btnStyle = "QPushButton{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:0.5, stop: 0 #eeeeee, stop: 1 gray);}";
	m_CloseAllBtn->setStyleSheet(btnStyle);
	m_ExitBtn->setStyleSheet(btnStyle);

	connect(m_ExitBtn,SIGNAL(clicked()),tabWidgetParent,SLOT(accept()));

	connect(m_CloseAllBtn,SIGNAL(clicked()),this,SLOT(SetCloseAllSlot()));
	connect(m_BidBtn,SIGNAL(PlaceAnOrderSignal(bool)),this,SLOT(PlaceAnOrderSlot(bool)));
	connect(m_AskBtn,SIGNAL(PlaceAnOrderSignal(bool)),this,SLOT(PlaceAnOrderSlot(bool)));
	connect(this,SIGNAL(AppendOrderRecordSignal(const OrderData&)),m_OrderedList,SIGNAL(AppendOrderRecordSignal(const OrderData&)));
}

void InstantOrderTab::InitLayout(QSize& miniSize)
{
	m_BidBtn->setGeometry(CONTROLSGRAP,CONTROLSGRAP,BIDASKWIDTH,BIDASKHEIGHT);
	m_AskBtn->setGeometry(BIDASKWIDTH+2*CONTROLSGRAP,CONTROLSGRAP,BIDASKWIDTH,BIDASKHEIGHT);
	
	int topY = 3*CONTROLSGRAP + BIDASKHEIGHT;
	int rightX = 2*CONTROLSGRAP + BIDASKWIDTH;
	
	m_AccountLabel->setGeometry(CONTROLSGRAP,topY,m_AccountLabel->size().width(),m_AccountLabel->size().height());
	m_AccountEdit->setGeometry(rightX,topY,BIDASKWIDTH,m_AccountEdit->size().height());
	
	this->GetTopY(topY,m_AccountLabel->size().height(),m_AccountEdit->size().height());

	m_LotLabel->setGeometry(CONTROLSGRAP,topY,m_LotLabel->size().width(),m_LotLabel->size().height());
	if(m_OrderDataProvider->GetLotData().IsDouble())
	{
		m_LotDoubleSpinBox->setGeometry(rightX,topY,BIDASKWIDTH,m_LotDoubleSpinBox->size().height());
		this->GetTopY(topY,m_LotLabel->size().height(),m_LotDoubleSpinBox->size().height());
	}
	else
	{
		m_LotSpinBox->setGeometry(rightX,topY,BIDASKWIDTH,m_LotSpinBox->size().height());
		this->GetTopY(topY,m_LotLabel->size().height(),m_LotSpinBox->size().height());
	}
	m_OrderedList->setGeometry(2*BIDASKWIDTH+3*CONTROLSGRAP,CONTROLSGRAP,this->size().width()-2*BIDASKWIDTH-4*CONTROLSGRAP,topY-CONTROLSGRAP);
	m_CloseAllBtn->setGeometry(3*CONTROLSGRAP+2*BIDASKWIDTH,topY,m_CloseAllBtn->size().width(),m_CloseAllBtn->size().height());
	m_ExitBtn->setGeometry(this->size().width()-CONTROLSGRAP-m_ExitBtn->size().width(),topY,m_ExitBtn->size().width(),m_ExitBtn->size().height());

	int miniWidth = 5*CONTROLSGRAP+2*BIDASKWIDTH+m_CloseAllBtn->size().width()+m_ExitBtn->size().width();

	if(miniSize.width()<miniWidth)
		miniSize.setWidth(miniWidth);
	if(miniSize.height()<topY)
		miniSize.setHeight(topY);
}
void InstantOrderTab::PlaceAnOrderBidAsk(bool isBid)
{
	OrderData orderData;
	QVariant lot;
	if(m_OrderDataProvider->GetLotData().IsDouble()) 
	{
		lot = m_LotDoubleSpinBox->value(); 
		orderData.SetLot(lot);
	}
	else
	{
		lot = m_LotSpinBox->value();
		orderData.SetLot(lot);
	} 
	orderData.SetClose(false); 
	orderData.SetBid(isBid);

	QString date = QDate::currentDate().toString(Qt::ISODate);
	QString strLot = QString(" %1").arg(lot.toString());
	QString strPrice = isBid ? "S "+m_CommPrice+m_BidPrice : "B "+m_CommPrice+m_AskPrice;

	QString openOrder = date + strLot + strPrice ;
	orderData.SetOpenOrder(openOrder);
	
	emit AppendOrderRecordSignal(orderData);
}
void InstantOrderTab::GetTopY(int& topY,int leftControlHeight,int rightControlHeight)
{
	topY += CONTROLSGRAP + (leftControlHeight > rightControlHeight ? leftControlHeight : rightControlHeight );
}

