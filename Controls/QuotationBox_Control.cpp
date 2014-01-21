#include "QuotationBox_Control.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include "../PriceBox.h"
#include "../Enum.h"
namespace Controls
{

	QuotationBox::QuotationBox(const QString& boxStyle,const QString& labelStyle,const QuotationInfo& quotationInfo,QWidget* parent)
	{
		QLabel* tradingCode = new QLabel(quotationInfo.instrumentCode,parent);	
		tradingCode->setStyleSheet(labelStyle);
		_priceUpDownStatus = new QLabel("",parent);								
		_priceUpDownStatus->setPixmap(QPixmap("images/up.png"));
		_priceCommonPart = new QLabel(quotationInfo.commonPart,parent);				
		_priceCommonPart->setStyleSheet(labelStyle);

		_bidBox = new PriceBox(quotationInfo.bid,parent);
		initPriceBox(_bidBox);
		_askBox = new PriceBox(quotationInfo.ask,parent);
		initPriceBox(_askBox);
		_timestamp = new QLabel(quotationInfo.timestamp,parent);			
		_markInfo = new QLabel("H/L",parent);							
		_highest = new QLabel(quotationInfo.previousHigh,parent);		
		_lowest = new QLabel(quotationInfo.previousLow,parent);			
		_lowest->setFixedWidth(60);
		tradingCode->setFixedWidth(120);
		_lowest->setAlignment(Qt::AlignCenter);
		_highest->setAlignment(Qt::AlignCenter);

		QGridLayout* mainLayout = new QGridLayout(parent);
		QVBoxLayout* instrumentCodeAndTimePart = new QVBoxLayout();
		QVBoxLayout* priceUpDownStatusPart = new QVBoxLayout();
		QVBoxLayout* priceCommonPart = new QVBoxLayout();
		QVBoxLayout* bidPricePart = new QVBoxLayout();
		QVBoxLayout* askPricePart = new QVBoxLayout();

		instrumentCodeAndTimePart->addWidget(tradingCode,0,Qt::AlignTop);
		instrumentCodeAndTimePart->addWidget(_timestamp,0,Qt::AlignBottom);

		priceUpDownStatusPart->addWidget(_priceUpDownStatus,0,Qt::AlignTop);
		priceUpDownStatusPart->addWidget(new QLabel(""),0,Qt::AlignBottom);

		priceCommonPart->addWidget(_priceCommonPart,0,Qt::AlignTop);
		priceCommonPart->addWidget(_markInfo,0,Qt::AlignBottom);

		bidPricePart->addWidget(_bidBox,0,Qt::AlignTop);
		bidPricePart->addWidget(_highest,0,Qt::AlignBottom);

		askPricePart ->addWidget(_askBox,0,Qt::AlignTop|Qt::AlignRight);
		askPricePart ->addWidget(_lowest,0,Qt::AlignBottom|Qt::AlignRight);

		mainLayout->addLayout(instrumentCodeAndTimePart,0,0);
		mainLayout->addLayout(priceUpDownStatusPart ,0,1);
		mainLayout->addLayout(priceCommonPart ,0,2);
		mainLayout->addLayout(bidPricePart ,0,3);
		mainLayout->addLayout(askPricePart ,0,4);

		mainLayout->setAlignment(Qt::AlignHCenter);
		mainLayout->setAlignment(Qt::AlignVCenter);

		_mainControl= new QGroupBox(parent);
		_mainControl->setLayout(mainLayout);
		_mainControl->setAlignment(Qt::AlignCenter);
		_mainControl->setStyleSheet(boxStyle);
		_mainControl->setFixedSize(WIDTH,HEIGHT);
		_mainControl->move(0,0);	
	}
}