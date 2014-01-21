#include "PriceDisplayBoard.h"

#include <QEvent>
#include <QLayout>
#include "Enum.h"
#include "Controls\QuotationBox_Control.h"
#include "Controls\InstantOrderQuotationBox_Control.h"


const QString PriceDisplayBoard::_boxStyle ="QGroupBox{background: qradialgradient(cx:0, cy:0, radius: 1,fx:0.5, fy:0.5, stop:0 white, stop:1 rgba(0,0,0, 50%));border-radius: 3px}";
const QString PriceDisplayBoard::_labelStyle="QLabel{font-size:18px}";
const QString PriceDisplayBoard::_priceUpPicturePath="images/up.png";
const QString PriceDisplayBoard::_priceDownPicturePath = "images/down.png";
const QString PriceDisplayBoard::_priceNormalPicturePath="";

PriceDisplayBoard::PriceDisplayBoard(const TradeItem& item,QWidget* parent):QWidget(parent),
	m_PixmapUp(_priceUpPicturePath),m_PixmapDown(_priceDownPicturePath),m_PixmapNULL(_priceNormalPicturePath)
{
	m_IsFront = true;
	m_Item = item;
	m_PrePrice = "0";
	m_PreTime = "00:00:00";
	this->InitDisplayBoard();
}

bool PriceDisplayBoard::eventFilter(QObject* obj, QEvent* event)
{
	if(event->type() == QEvent::MouseButtonDblClick)
	{
		if(_backBox->getOpenAndCloseOrderTypeCmb()==(QComboBox*)obj 
			|| _backBox->getIntegerLotSpinBox()==(QSpinBox*)obj 
			|| _backBox->getDoubleLotSpinBox()==(QDoubleSpinBox*)obj)
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
void PriceDisplayBoard::ChangeMarketInfo(MarkInfoType::MarkInfoType type)
{
	auto markInfoLabel = _frontBox->getMarkInfoLabel();
	auto highestLabel = _frontBox->getHighestLabel();
	auto lowestLabel = _frontBox->getLowestLabel();
	switch (type)
	{
	case MarkInfoType::HighLow:
		markInfoLabel->setText("H/L");
		highestLabel->setText(m_Item.m_PreviousHightPrice);
		lowestLabel->setText(m_Item.m_PreviousLowPrice);
		break;
	case MarkInfoType::PreClose:
		markInfoLabel->setText("P CIs");
		highestLabel->setText(m_Item.m_PreviousClosePrice);
		lowestLabel->setText(m_Item.m_PreviousChangedPrice);
		break;
	case MarkInfoType::InterestClose:
		markInfoLabel->setText("Rate");
		highestLabel->setText(m_Item.m_SellRate);
		lowestLabel->setText(m_Item.m_BuyRate);
		break;
	default:
		break;
	}
}
void PriceDisplayBoard::RealTimeDisplay(const TradeItem& item)
{	
	auto bid = item.m_CurrentBidPrice.toStdString();
	auto ask = item.m_CurrentAskPrice.toStdString();
	auto common_part = GetTheSamePart(bid,ask);
	QString currentBidPrice = QString::fromStdString(bid);
	QString currentAskPrice = QString::fromStdString(ask);
	QString currentCommPrice = QString::fromStdString(common_part);

	if(m_IsFront)
	{
		_frontBox->getBidBox()->SetText(currentBidPrice);
		_frontBox->getAskBox()->SetText(currentAskPrice);
		_frontBox->getPriceCommonPartLabel()->setText(currentCommPrice);

	}
	else
	{
		_backBox->getBidBox()->SetText(currentBidPrice);
		_backBox->getAskBox()->SetText(currentAskPrice);
		_backBox->getPriceCommonPartLabel()->setText(currentCommPrice);
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
	std::string bid = m_Item.m_CurrentBidPrice.toStdString();
	std::string ask = m_Item.m_CurrentAskPrice.toStdString();
	std::string common_part = GetTheSamePart(bid,ask);

	QString bidPrice = QString::fromStdString(bid);
	QString askPrice =QString::fromStdString(ask);
	QString priceComm = QString::fromStdString(common_part);

	Controls::QuotationInfo quotation=
	{
		m_Item.m_TradingCode,
		bidPrice,
		askPrice,
		priceComm,
		m_Item.m_CurrentTime,
		m_Item.m_PreviousHightPrice,
		m_Item.m_PreviousLowPrice
	};
	
	_frontBox = new Controls::QuotationBox(_boxStyle,_labelStyle,quotation,this);

	//front:

	//////rear:
	_backBox = new Controls::InstantOrderQuotationBox(_boxStyle,_labelStyle,quotation,m_Item.m_Double,this);
	setAttribute(Qt::WA_TranslucentBackground);

}
void PriceDisplayBoard::SetBidAskStatus(const QString& time,const QPixmap& pic,Qt::GlobalColor color)
{	
	if(m_IsFront)
	{
		_frontBox->getTimeStampLabel()->setText(time); 
		_frontBox->getPriceUpDownStatusLabel()->setPixmap(pic); 
		_frontBox->getBidBox()->SetBackGroundColor(color);
		_frontBox->getAskBox()->SetBackGroundColor(color);
	}
	else
	{
		_backBox->getPriceUpDownStatusLabel()->setPixmap(pic); 
		_backBox->getBidBox()->SetBackGroundColor(color);
		_backBox->getAskBox()->SetBackGroundColor(color);
	}

}



std::string PriceDisplayBoard::GetTheSamePart(std::string& bid,std::string& ask)
{
	if(bid.empty() || ask.empty())
	{
		return "";
	}
	std::string result;
	auto iterBid= bid.begin();
	auto iterAsk = ask.begin();
	for(;iterBid <bid.end()&&iterAsk < ask.end(); ++iterBid, ++iterAsk)
	{
		if(*iterBid!=*iterAsk)
		{
			break;
		}
		result.push_back(*iterBid);
	}
	if(result.empty())
	{
		return "";
	}
	bid=bid.substr(result.size());
	ask = ask.substr(result.size());
	return result;
}