#include "PriceDisplayBoard.h"

#include <QEvent>
#include <QLayout>

#include "Enum.h"



PriceDisplayBoard::PriceDisplayBoard(const TradeItem& item,QWidget* parent):QWidget(parent)
{
	m_IsFront = true;
	m_Item = item;
	m_PrePrice = "0";
	m_PreTime = "00:00:00";

	m_PixmapUp = QPixmap("images/up.png");
	m_PixmapDown = QPixmap("images/down.png");
	m_PixmapNULL = QPixmap("");

	m_StyleBlue = "QPushButton{background-color:blue;border-radius: 5px;border-style: outset}";
	m_StyleRed = "QPushButton{background-color:red;border-radius: 5px;border-style: outset}";
	m_StyleGray = "QPushButton{border-radius: 5px;border-style: outset}";

	this->InitDisplayBoard();
}

bool PriceDisplayBoard::eventFilter(QObject* obj, QEvent* event)
{
	if(event->type() == QEvent::MouseButtonDblClick)
	{
		if(m_OpenClose==(QComboBox*)obj || m_Hands==(QSpinBox*)obj || m_DbHands==(QDoubleSpinBox*)obj)
			return true;
	}
	return false;
}

void PriceDisplayBoard::TurnOverSlot(bool isFront)
{
	m_IsFront = isFront;
}


QString PriceDisplayBoard:: GetTradingCode()
{
	return m_Item.m_TradingCode;
}
void PriceDisplayBoard::ChangeMarketInfo(int markInfo)
{
	switch (markInfo)
	{
	case HIGHTLOW:
		m_HightLow->setText("H/L");
		m_Hightest->setText(m_Item.m_PreviousHightPrice);
		m_Lowest->setText(m_Item.m_PreviousLowPrice);
		break;
	case PRECLOSE:
		m_HightLow->setText("P CIs");
		m_Hightest->setText(m_Item.m_PreviousClosePrice);
		m_Lowest->setText(m_Item.m_PreviousChangedPrice);
		break;
	case INTERESTCLOSE:
		m_HightLow->setText("Rate");
		m_Hightest->setText(m_Item.m_SellRate);
		m_Lowest->setText(m_Item.m_BuyRate);
		break;
	default:
		break;
	}
}
void PriceDisplayBoard::RealTimeDisplay(const TradeItem& item)
{	
	QString currentBidPrice = item.m_CurrentBidPrice;
	QString currentAskPrice = item.m_CurrentAskPrice;
	QString currentCommPrice = this->GetTheSamePart(currentBidPrice,currentAskPrice);  

	if(m_IsFront)
	{
		m_CurrentBidBox->SetText(currentBidPrice);
		m_CurrentAskBox->SetText(currentAskPrice);
		m_CurrentPriceComm->setText(currentCommPrice);

	}
	else
	{
		m_CurrentBidBox2->SetText(currentBidPrice);
		m_CurrentAskBox2->SetText(currentAskPrice);
		m_CurrentPriceComm2->setText(currentCommPrice);
	}

	int status;
	if(currentBidPrice.toDouble() > m_PrePrice.toDouble())
		status = Qt::blue;
	else if(currentBidPrice.toDouble() < m_PrePrice.toDouble())
		status = Qt::red;
	else
		status = Qt::gray;
	
	switch(status)
	{	
	case Qt::blue:
		this->SetBidAskStatus(item.m_CurrentTime,m_PixmapUp,Qt::blue);
		break;
		
	case Qt::red: 
		this->SetBidAskStatus(item.m_CurrentTime,m_PixmapDown,Qt::red);
		break;
		
	case Qt::gray:	
	default:
		this->SetBidAskStatus(m_PreTime,m_PixmapNULL,Qt::gray);
		break;
	}
	
	m_PrePrice = currentBidPrice;
	m_PreTime = item.m_CurrentTime;	

	update();

	emit SendCurrentPriceSignal(CurrentPriceData(status,currentCommPrice,currentBidPrice,currentAskPrice));
}

void PriceDisplayBoard::InitDisplayBoard()
{  
	this->LayoutDisplayBoard();									   
	this->setFixedSize(WIDTH,2*(HEIGHT+GRAP));
	this->show();
}
void PriceDisplayBoard::LayoutDisplayBoard()
{
	QString groupBoxStyle = "QGroupBox{background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white, stop:1 rgba(0,0,0, 50%));border-radius: 3px}";
	QString label_style = "QLabel{font-size:18px}";

 
	QString bidPrice = m_Item.m_CurrentBidPrice;
	QString askPrice = m_Item.m_CurrentAskPrice;
	QString priceComm = this->GetTheSamePart(bidPrice,askPrice);

	//front:
	QLabel* tradingCode = new QLabel(m_Item.m_TradingCode,this);	
	tradingCode->setStyleSheet(label_style);
	m_StatusBmp = new QLabel("",this);								
	m_StatusBmp->setPixmap(QPixmap("images/up.png"));
	m_CurrentPriceComm = new QLabel(priceComm,this);				
	m_CurrentPriceComm->setStyleSheet(label_style);

	m_CurrentBidBox = new PriceBox(bidPrice,this);
	this->InitPriceBox(m_CurrentBidBox);
	m_CurrentAskBox = new PriceBox(askPrice,this);
	this->InitPriceBox(m_CurrentAskBox);

	m_CurrentTime = new QLabel(m_Item.m_CurrentTime,this);			
	m_HightLow = new QLabel("H/L",this);							
	m_Hightest = new QLabel(m_Item.m_PreviousHightPrice,this);		
	m_Lowest = new QLabel(m_Item.m_PreviousLowPrice,this);			

	m_Lowest->setFixedWidth(60);
	tradingCode->setFixedWidth(120);
	m_Lowest->setAlignment(Qt::AlignCenter);
	m_Hightest->setAlignment(Qt::AlignCenter);

	QGridLayout* gridLayout = new QGridLayout(this);
	QVBoxLayout* halfFrontLayout1 = new QVBoxLayout();
	QVBoxLayout* halfFrontLayout2 = new QVBoxLayout();
	QVBoxLayout* halfFrontLayout3 = new QVBoxLayout();
	QVBoxLayout* halfFrontLayout4 = new QVBoxLayout();
	QVBoxLayout* halfFrontLayout5 = new QVBoxLayout();

	halfFrontLayout1->addWidget(tradingCode,0,Qt::AlignTop);
	halfFrontLayout1->addWidget(m_CurrentTime,0,Qt::AlignBottom);

	halfFrontLayout2->addWidget(m_StatusBmp,0,Qt::AlignTop);
	halfFrontLayout2->addWidget(new QLabel(""),0,Qt::AlignBottom);

	halfFrontLayout3->addWidget(m_CurrentPriceComm,0,Qt::AlignTop);
	halfFrontLayout3->addWidget(m_HightLow,0,Qt::AlignBottom);

	halfFrontLayout4->addWidget(m_CurrentBidBox,0,Qt::AlignTop);
	halfFrontLayout4->addWidget(m_Hightest,0,Qt::AlignBottom);

	halfFrontLayout5->addWidget(m_CurrentAskBox,0,Qt::AlignTop|Qt::AlignRight);
	halfFrontLayout5->addWidget(m_Lowest,0,Qt::AlignBottom|Qt::AlignRight);
	
	gridLayout->addLayout(halfFrontLayout1,0,0);
	gridLayout->addLayout(halfFrontLayout2,0,1);
	gridLayout->addLayout(halfFrontLayout3,0,2);
	gridLayout->addLayout(halfFrontLayout4,0,3);
	gridLayout->addLayout(halfFrontLayout5,0,4);

	gridLayout->setAlignment(Qt::AlignHCenter);
	gridLayout->setAlignment(Qt::AlignVCenter);
 
	m_MainGroupBox = new QGroupBox(this);
	m_MainGroupBox->setLayout(gridLayout);
	m_MainGroupBox->setAlignment(Qt::AlignCenter);
	m_MainGroupBox->setStyleSheet(groupBoxStyle);
 
	//////rear:
	QLabel* tradingCode2 = new QLabel(m_Item.m_TradingCode,this);
	tradingCode2->setFixedWidth(120);
	tradingCode2->setStyleSheet(label_style);
	m_StatusBmp2 = new QLabel("",this);								  
	m_StatusBmp2->setPixmap(QPixmap("images/up.png"));
	m_CurrentPriceComm2 = new QLabel(priceComm,this);				 
	m_CurrentPriceComm2->setStyleSheet(label_style);

	m_CurrentBidBox2 = new PriceBox(bidPrice,this);
	this->InitPriceBox(m_CurrentBidBox2);
	m_CurrentBidBox2->SetCornerText("B ");
	m_CurrentAskBox2 = new PriceBox(askPrice,this);
	this->InitPriceBox(m_CurrentAskBox2);
	m_CurrentAskBox2->SetCornerText("S ");

	m_OpenClose = new QComboBox(this);								  
	m_Hands = new QSpinBox(this);									  
	m_DbHands = new QDoubleSpinBox(this);							  
	m_OpenClose->installEventFilter(this);
	m_Hands->installEventFilter(this);
	m_DbHands->installEventFilter(this);
		
	m_DbHands->setFixedWidth(60);
	m_Hands->setFixedWidth(60);
	m_OpenClose->setFixedWidth(80);

	QGridLayout* gridLayout2 = new QGridLayout(this);

	QVBoxLayout* halfRearLayout1 = new QVBoxLayout();
	QVBoxLayout* halfRearLayout2 = new QVBoxLayout();
	QVBoxLayout* halfRearLayout3 = new QVBoxLayout();
	QVBoxLayout* halfRearLayout4 = new QVBoxLayout();
	QVBoxLayout* halfRearLayout5 = new QVBoxLayout();
	halfRearLayout1->addWidget(tradingCode2,0,Qt::AlignTop);
	halfRearLayout1->addWidget(m_OpenClose,0,Qt::AlignBottom);
	halfRearLayout2->addWidget(m_StatusBmp2,0,Qt::AlignTop);
	halfRearLayout2->addWidget(new QLabel(""),0,Qt::AlignBottom);
	halfRearLayout3->addWidget(m_CurrentPriceComm2,0,Qt::AlignTop);
	halfRearLayout3->addWidget(new QLabel(""),0,Qt::AlignBottom);
	halfRearLayout4->addWidget(m_CurrentBidBox2,0,Qt::AlignTop);
	halfRearLayout4->addWidget(new QLabel(""),0,Qt::AlignBottom);
	halfRearLayout5->addWidget(m_CurrentAskBox2,0,Qt::AlignTop|Qt::AlignRight);
	if( ! m_Item.m_Double)
	{
		halfRearLayout5->addWidget(m_Hands,0,Qt::AlignBottom|Qt::AlignRight);
		m_DbHands->setHidden(true);
	}
	else
	{
		halfRearLayout5->addWidget(m_DbHands,0,Qt::AlignBottom|Qt::AlignRight);
		m_Hands->setHidden(true);
	}

	gridLayout2->addLayout(halfRearLayout1,0,0);
	gridLayout2->addLayout(halfRearLayout2,0,1);
	gridLayout2->addLayout(halfRearLayout3,0,2);
	gridLayout2->addLayout(halfRearLayout4,0,3);
	gridLayout2->addLayout(halfRearLayout5,0,4);

	gridLayout2->setAlignment(Qt::AlignHCenter);
	gridLayout2->setAlignment(Qt::AlignVCenter);
 
	m_MainGroupBox2 = new QGroupBox(this);
	m_MainGroupBox2->setLayout(gridLayout2);
	m_MainGroupBox2->setAlignment(Qt::AlignCenter);
	m_MainGroupBox2->setStyleSheet(groupBoxStyle);
 	
	m_MainGroupBox->setFixedSize(WIDTH,HEIGHT);
	m_MainGroupBox2->setFixedSize(WIDTH,HEIGHT);

	m_MainGroupBox->move(0,0);	
	m_MainGroupBox2->move(0,HEIGHT+GRAP);

	setAttribute(Qt::WA_TranslucentBackground);

	m_Hands->setToolTip("the Maximnu value is 10,000 !");
	m_DbHands->setToolTip("the Maximnu value is 9,999.99 !");


}
void PriceDisplayBoard::SetBidAskStatus(const QString& time,const QPixmap& pic,Qt::GlobalColor color)
{	
	if(m_IsFront)
	{
		m_CurrentTime->setText(time); 
		m_StatusBmp->setPixmap(pic); 
		m_CurrentBidBox->SetBackGroundColor(color);
		m_CurrentAskBox->SetBackGroundColor(color);
	}
	else
	{
		m_StatusBmp2->setPixmap(pic); 
		m_CurrentBidBox2->SetBackGroundColor(color);
		m_CurrentAskBox2->SetBackGroundColor(color);
	}

}

void PriceDisplayBoard::InitPriceBox(PriceBox* priceBox)
{
	priceBox->SetSize(60,30);
	priceBox->SetRadius(15);
	priceBox->SetFontSize(16);
}

QString PriceDisplayBoard::GetTheSamePart(QString& str1,QString& str2)
{
   int pos = 0;
   int lenStr1 = str1.length();
   int lenStr2 = str2.length();
   if(lenStr1<=0 || lenStr2<=0)
	   return "";
   int len = (lenStr1 >= lenStr2) ? lenStr2 : lenStr1;
   while(len>pos)
   {
		if(str1[pos]==str2[pos])
			pos++;
		else
			break;
   }
   
   if(pos==0)
	   return "";

   QString res = str1.left(pos);

   str1 = str1.right(lenStr1-pos);
   str2 = str2.right(lenStr2-pos);


   return res;
}