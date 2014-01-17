#include "PendingOrderTab.h"

PendingOrderTab::PendingOrderTab(OrderDataProviderBase* orderDataProvider,QSize& miniSize, QWidget* tabWidgetParent,QWidget* parent):QDialog(parent)
{
	m_BidBtn = new BidAskPriceButton(QSize(BIDASKWIDTH,BIDASKHEIGHT),"","",Qt::gray,true,this);
	m_AskBtn = new BidAskPriceButton(QSize(BIDASKWIDTH,BIDASKHEIGHT),"","",Qt::gray,false,this);;

	m_TypeLabel = new QLabel("Type",this);
	m_AccountLabel = new QLabel("Account",this);
	m_BuysellLabel = new QLabel("B/S",this);
	m_LotLabel = new QLabel("Lot",this);
	m_LimitPriceLabel = new QLabel("Limit price",this);
	m_StopPriceLabel = new QLabel("Stop price",this);
	m_TimeExpiredLabel = new QLabel("Time expired",this);

	m_TypeComboBox = new QComboBox(this);
	m_AccountComboBox = new QComboBox(this);
	m_BuyRadioBtn = new QRadioButton("Buy",this);
	m_SellRadioBtn = new QRadioButton("Sell",this);
	m_LotComboBox = new QSpinBox(this);
	m_LimitPriceSpinBox = new QSpinBox(this);
	m_LimitPriceCheckBox = new QCheckBox(this);
	m_StopPriceSpinBox = new QSpinBox(this);		
	m_StopPriceCheckBox = new QCheckBox(this);  
	m_OcoCheckBox = new QCheckBox("OCO",this);
	m_TimeExpiredComboBox = new QComboBox(this);

	m_OrderedList = new OrderListView(orderDataProvider->GetOrderDataList(),this);
	m_SubmitBtn = new QPushButton("Submit",this);
	m_CloseAllBtn = new QPushButton("Close All",this);
	m_ExitBtn = new QPushButton("Exit",this);

	m_LimitPriceCheckBox->setFixedWidth(20);
	m_StopPriceCheckBox->setFixedWidth(20);

	this->Init(miniSize,tabWidgetParent);
}

void PendingOrderTab::resizeEvent(QResizeEvent * event)
{
	QRect rect = m_OrderedList->geometry();
	int x = rect.x();
	int y = rect.y();
	int width = this->size().width()-x-CONTROLSGRAP;
	int height = this->size().height()-y-2*CONTROLSGRAP-m_CloseAllBtn->size().height();
	m_OrderedList->setGeometry(x,y,width,height);

	m_CloseAllBtn->setGeometry(x,y+height+CONTROLSGRAP,m_CloseAllBtn->size().width(),m_CloseAllBtn->size().height());
	m_ExitBtn->setGeometry(x+width-m_ExitBtn->size().width(),y+height+CONTROLSGRAP,m_ExitBtn->size().width(),m_ExitBtn->size().height());
	m_SubmitBtn->setGeometry(CONTROLSGRAP,this->size().height()-CONTROLSGRAP-m_SubmitBtn->size().height(),x-2*CONTROLSGRAP,m_SubmitBtn->size().height());

	QWidget::resizeEvent(event);
}

void PendingOrderTab::GetCurrentPriceSlot(const CurrentPriceData& currentPriceData)
{
	m_BidBtn->SetCenterCommPriceText(currentPriceData.GetCurrentCommPrice());
	m_BidBtn->SetCenterBidAskPriceText(currentPriceData.GetCurrentBidPrice());
	m_BidBtn->SetTrendStatus(currentPriceData.GetTrendStatus());
	m_AskBtn->SetCenterCommPriceText(currentPriceData.GetCurrentCommPrice());
	m_AskBtn->SetCenterBidAskPriceText(currentPriceData.GetCurrentAskPrice());
	m_AskBtn->SetTrendStatus(currentPriceData.GetTrendStatus());
}

void PendingOrderTab::Init(QSize& miniSize,QWidget* tabWidgetParent)
{
	this->InitLayout(miniSize);

	QString btnStyle = "QPushButton{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:0.5, stop: 0 #eeeeee, stop: 1 gray);}";
	m_CloseAllBtn->setStyleSheet(btnStyle);
	m_ExitBtn->setStyleSheet(btnStyle);
	m_SubmitBtn->setStyleSheet(btnStyle);

	connect(m_ExitBtn,SIGNAL(clicked()),tabWidgetParent,SLOT(accept()));

}
void PendingOrderTab::InitLayout(QSize& miniSize)
{

	int rightX = BIDASKWIDTH + 2*CONTROLSGRAP;
	int topY = m_BidBtn->size().height() + 3*CONTROLSGRAP;

	m_BidBtn->setGeometry(CONTROLSGRAP,CONTROLSGRAP,BIDASKWIDTH,BIDASKHEIGHT);
	m_AskBtn->setGeometry(rightX,CONTROLSGRAP,BIDASKWIDTH,BIDASKHEIGHT);

	m_TypeLabel->setGeometry(CONTROLSGRAP,topY,m_TypeLabel->size().width(),m_TypeLabel->size().height());
	m_TypeComboBox->setGeometry(rightX,topY,BIDASKWIDTH,m_TypeComboBox->size().height());

	this->GetTopY(topY,m_TypeLabel->size().height(),m_TypeComboBox->size().height());

	m_AccountLabel->setGeometry(CONTROLSGRAP,topY,m_AccountLabel->size().width(),m_AccountLabel->size().height());
	m_AccountComboBox->setGeometry(rightX,topY,BIDASKWIDTH,m_AccountComboBox->size().height());
	
	this->GetTopY(topY,m_AccountLabel->size().height(), m_AccountComboBox->size().height());// ? m_AccountLabel->size().height() : m_AccountComboBox->size().height());
	
	m_BuysellLabel->setGeometry(CONTROLSGRAP,topY,m_BuysellLabel->size().width(),m_BuysellLabel->size().height());
	m_BuyRadioBtn->setGeometry(rightX,topY,m_BuyRadioBtn->size().width(),m_BuyRadioBtn->size().height());
	m_SellRadioBtn->setGeometry(rightX+BIDASKWIDTH/2+CONTROLSGRAP,topY,m_SellRadioBtn->size().width(),m_SellRadioBtn->size().height());
	
	this->GetTopY(topY,m_BuysellLabel->size().height(),m_BuyRadioBtn->size().height());// ? m_BuysellLabel->size().height() : m_BuyRadioBtn->size().height());
	
	m_LotLabel->setGeometry(CONTROLSGRAP,topY,m_LotLabel->size().width(),m_LotLabel->size().height());
	m_LotComboBox->setGeometry(rightX,topY,BIDASKWIDTH,m_LotComboBox->size().height());

	this->GetTopY(topY,m_LotLabel->size().height(),m_LotComboBox->size().height());// ? m_LotLabel->size().height() : m_LotComboBox->size().height());
	
	m_LimitPriceLabel->setGeometry(CONTROLSGRAP,topY,m_LimitPriceLabel->size().width(),m_LimitPriceLabel->size().height());
	m_LimitPriceCheckBox->setGeometry(rightX,topY,m_LimitPriceCheckBox->size().width(),m_LimitPriceCheckBox->size().height());
	m_LimitPriceSpinBox->setGeometry(rightX+m_LimitPriceCheckBox->size().width(),topY,BIDASKWIDTH-m_LimitPriceCheckBox->size().width(),m_LimitPriceSpinBox->size().height());
	
	topY += CONTROLSGRAP + (m_LimitPriceLabel->size().height()>m_LimitPriceSpinBox->size().height() ? m_LimitPriceLabel->size().height() : m_LimitPriceSpinBox->size().height());
	m_StopPriceLabel->setGeometry(CONTROLSGRAP,topY,m_StopPriceLabel->size().width(),m_StopPriceLabel->size().height());
	m_StopPriceCheckBox->setGeometry(rightX,topY,m_StopPriceCheckBox->size().width(),m_StopPriceCheckBox->size().height());
	m_StopPriceSpinBox->setGeometry(rightX+m_StopPriceCheckBox->size().width(),topY,BIDASKWIDTH-m_StopPriceCheckBox->size().width(),m_StopPriceSpinBox->size().height());
	
	this->GetTopY(topY,m_StopPriceLabel->size().height(),m_StopPriceSpinBox->size().height());// ? m_StopPriceLabel->size().height():m_StopPriceSpinBox->size().height());
	
	m_OcoCheckBox->setGeometry(rightX,topY,m_OcoCheckBox->size().width(),m_OcoCheckBox->size().height());
	
	topY += CONTROLSGRAP + m_OcoCheckBox->size().height();
	
	m_TimeExpiredLabel->setGeometry(CONTROLSGRAP,topY,m_TimeExpiredLabel->size().width(),m_TimeExpiredLabel->size().height());
	m_TimeExpiredComboBox->setGeometry(rightX,topY,BIDASKWIDTH,m_TimeExpiredComboBox->size().height());
	
	this->GetTopY(topY,m_TimeExpiredLabel->size().height(),m_TimeExpiredComboBox->size().height());// ? m_TimeExpiredLabel->size().height() : m_TimeExpiredComboBox->size().height());
	
	m_OrderedList->setGeometry(3*CONTROLSGRAP+2*BIDASKWIDTH,CONTROLSGRAP,this->size().width()-4*CONTROLSGRAP-2*BIDASKWIDTH,topY-CONTROLSGRAP);

	m_SubmitBtn->setGeometry(CONTROLSGRAP,topY,CONTROLSGRAP+2*BIDASKWIDTH,m_SubmitBtn->size().height());
	m_CloseAllBtn->setGeometry(3*CONTROLSGRAP+2*BIDASKWIDTH,topY,m_CloseAllBtn->size().width(),m_CloseAllBtn->size().height());
	m_ExitBtn->setGeometry(this->size().width()-CONTROLSGRAP-m_ExitBtn->size().width(),topY,m_ExitBtn->size().width(),m_ExitBtn->size().height());

	topY += CONTROLSGRAP + m_SubmitBtn->size().height();
	int miniWidth = 5*CONTROLSGRAP+2*BIDASKWIDTH+m_CloseAllBtn->size().width()+m_ExitBtn->size().width();

	if(miniSize.width()<miniWidth)
		miniSize.setWidth(miniWidth);
	if(miniSize.height()<topY)
		miniSize.setHeight(topY);
}

void PendingOrderTab::GetTopY(int& topY,int leftControlHeight,int rightControlHeight)
{
	topY += CONTROLSGRAP + (leftControlHeight > rightControlHeight ? leftControlHeight : rightControlHeight );
}


