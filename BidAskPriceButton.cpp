#include "BidAskPriceButton.h"

#include <QPainter>
#include <QBrush>
#include <QPushButton>
#include <QFontMetrics>
#include <QFont>
#include <QGroupBox>
#include <QString>

#include "Enum.h"

BidAskPriceButton::BidAskPriceButton(const QSize& size,const QString& commPriceText,const QString& bidAskPriceText,int colorFlag,bool bBidPrice,QWidget *parent) : QWidget(parent)
{
	this->Init(size,commPriceText,bidAskPriceText,colorFlag,bBidPrice);
	this->Update();
}
BidAskPriceButton::~BidAskPriceButton()
{
}

QSizePolicy	BidAskPriceButton::sizePolicy() const
{
	QSizePolicy  sizePolicy;
	sizePolicy.setHorizontalPolicy(QSizePolicy::Fixed);
	sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
	return sizePolicy;
}
QSize BidAskPriceButton::minimumSizeHint() const
{
	return m_Size;
}
void BidAskPriceButton::mouseDoubleClickEvent(QMouseEvent * event)
{
	if(event->button()==Qt::LeftButton)
	{
		emit PlaceAnOrderSignal(m_IsBid);
	}

	QWidget::mouseDoubleClickEvent(event);
}


void BidAskPriceButton::SetSize(int width,int height)
{
	m_Size.setWidth(width);
	m_Size.setHeight(height);
	this->resize(m_Size);
	this->Update();
}
void BidAskPriceButton::SetSize(const QSize& size)
{
	m_Size.setWidth(size.width());
	m_Size.setHeight(size.height());
	this->resize(size);
	this->Update();
}
void BidAskPriceButton::SetFontSize(int fontSize)
{
	m_FontSize = fontSize;
	this->Update();
}
void BidAskPriceButton::SetLeftTopCornerText(const QString& text)
{
	m_LeftTopCornerLabel->setText(text);
	this->Update();
}
void BidAskPriceButton::SetLeftBottomCornerText(const QString& text)
{
	m_LeftBottomCornerLabel->setText(text);
	this->Update();
}
void BidAskPriceButton::SetCenterCommPriceText(const QString& text)
{
	m_CenterCommPriceLabel->setText(text);
	this->Update();
}
void BidAskPriceButton::SetCenterBidAskPriceText(const QString& text)
{
	m_CenterBidAskPriceLabel->setText(text);
	this->Update();
}
void BidAskPriceButton::SetBkColor(int colorFlag)
{
	m_ColorFlag = colorFlag;
	this->Update();
}
void BidAskPriceButton::SetFontSizeRatio(float ratio)
{
	m_FontSizeRatio = ratio;
	this->Update();
}
void BidAskPriceButton::SetTrendStatus(int trendStatus)
{
	m_TrendStatus = trendStatus;
	this->Update();
}

void BidAskPriceButton::Init(const QSize& size,const QString& commPriceText,const QString& bidAskPriceText,int colorFlag,bool bBidPrice)
{
	m_Size = size;
	m_FontSizeRatio = 0.8;
	m_FontSize = FONTSIZE;
	m_ColorFlag = colorFlag;
	m_IsBid = bBidPrice;
	m_TrendStatus = UP;
	
	m_UpPixmap = QPixmap("images/Up.png");
	m_DownPixmap = QPixmap("images/Down.png");
	m_KeepPixmap = QPixmap("");

	this->setFixedSize(m_Size);
	m_GroupBox = new QGroupBox(this);
	if(bBidPrice)
	{
		m_LeftTopCornerLabel = new QLabel("Bid",this);
		m_LeftBottomCornerLabel = new QLabel("Sell",this);
	}
	else
	{
		m_LeftTopCornerLabel = new QLabel("Ask",this);
		m_LeftBottomCornerLabel = new QLabel("Buy",this);	
	}
	m_CenterCommPriceLabel = new QLabel(commPriceText,this);
	m_CenterBidAskPriceLabel = new QLabel(bidAskPriceText,this);
	m_TrendPixmapLabel = new QLabel(this);
	switch (m_TrendStatus)
	{
	case UP:
		m_TrendPixmapLabel->setPixmap(m_UpPixmap);
		break;
	case DOWN:
		m_TrendPixmapLabel->setPixmap(m_DownPixmap);
		break;
	case KEEP:
	default:
		m_TrendPixmapLabel->setPixmap(m_KeepPixmap);
		break;
	}
		
	QString color = "gray";
	switch (m_ColorFlag)
	{
	case Qt::red:
		color = "red";
		break;
	case Qt::blue:
		color = "blue";
		break;
	case Qt::gray:
	default:
		color = "gray";
		break;
	}
	m_GroupBox->setGeometry(0,0,m_Size.width(),m_Size.height());
	QString groupBoxStyle = "QGroupBox{border-radius: 5px;background:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 "+ color +");}";
	m_GroupBox->setStyleSheet(groupBoxStyle);
}
void BidAskPriceButton::Update()
{
	QFont font;
	font.setPixelSize(m_FontSize);
	m_LeftTopCornerLabel->setFont(font);
	m_LeftBottomCornerLabel->setFont(font);
	QFontMetrics fm(font);
	int textHeight = fm.height();
	int textWidth = fm.width(m_LeftTopCornerLabel->text());
	m_LeftTopCornerLabel->setGeometry(2,0,textWidth,textHeight);
	textWidth = fm.width(m_LeftBottomCornerLabel->text());
	m_LeftBottomCornerLabel->setGeometry(2,m_Size.height()-textHeight,textWidth,textHeight);

	QFont font1;
	font1.setPixelSize(m_FontSize*m_FontSizeRatio);
	m_CenterCommPriceLabel->setFont(font1);
	QFontMetrics fm1(font1);
	int commWidth = fm1.width(m_CenterCommPriceLabel->text());
	int commHeight = fm1.height();

	QFont font2;
	font2.setPixelSize(m_FontSize/m_FontSizeRatio);
	m_CenterBidAskPriceLabel->setFont(font2);
	QFontMetrics fm2(font2);
	int bidAskWidth = fm2.width(m_CenterBidAskPriceLabel->text());
	int bidAskHeight = fm2.height();

	textWidth  = ( m_Size.width() - (commWidth + bidAskWidth) ) / 2;
	
	m_CenterCommPriceLabel->setGeometry(textWidth,(m_Size.height()-commHeight)/2,commWidth,commHeight);
	m_CenterBidAskPriceLabel->setGeometry(textWidth+commWidth,(m_Size.height()-bidAskHeight)/2,bidAskWidth,bidAskHeight);
	
	switch (m_TrendStatus)
	{
	case UP:
		m_TrendPixmapLabel->setPixmap(m_UpPixmap);
		break;
	case DOWN:
		m_TrendPixmapLabel->setPixmap(m_DownPixmap);
		break;
	case KEEP:
	default:
		m_TrendPixmapLabel->setPixmap(m_KeepPixmap);
		break;
	}
	m_TrendPixmapLabel->setGeometry(size().width()-15,0,15,15);

	//QString color = "gray";
	//switch (m_ColorFlag)
	//{
	//case RED:
	//	color = "red";
	//	break;
	//case BLUE:
	//	color = "blue";
	//	break;
	//case GRAY:
	//default:
	//	color = "gray";
	//	break;
	//}
	//m_GroupBox->setGeometry(0,0,m_Size.width(),m_Size.height());
	//QString groupBoxStyle = "QGroupBox{border-radius: 5px;background:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 "+ color +");}";
	//m_GroupBox->setStyleSheet(groupBoxStyle);
}
