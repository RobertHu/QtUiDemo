#include "InstantOrderQuotationBox_Control.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qgroupbox.h>
#include "../Enum.h"
#include "../PriceBox.h"
namespace Controls
{

	InstantOrderQuotationBox::InstantOrderQuotationBox(const QString& boxStyle,const QString& labelStyle,const QuotationInfo& quotation,bool isLotInDouble,QWidget* parent)
	{
		QLabel* tradingCode2 = new QLabel(quotation.instrumentCode,parent);
		tradingCode2->setFixedWidth(120);
		tradingCode2->setStyleSheet(labelStyle);
		_priceUpDownStatus = new QLabel("",parent);								  
		_priceUpDownStatus->setPixmap(QPixmap("images/up.png"));
		_priceCommonPart = new QLabel(quotation.commonPart,parent);				 
		_priceCommonPart->setStyleSheet(labelStyle);

		_bidBox = new PriceBox(quotation.bid,parent);
		initPriceBox(_bidBox);
		_bidBox->SetCornerText("B ");
		_askBox = new PriceBox(quotation.ask,parent);
		initPriceBox(_askBox);
		_askBox->SetCornerText("S ");

		_openAndCloseOrderTypes = new QComboBox(parent);								  
		_integerLotSpinBox = new QSpinBox(parent);									  
		_doubleLotSpinBox = new QDoubleSpinBox(parent);							  
		_openAndCloseOrderTypes->installEventFilter(parent);
		_integerLotSpinBox->installEventFilter(parent);
		_doubleLotSpinBox->installEventFilter(parent);

		_doubleLotSpinBox->setFixedWidth(60);
		_integerLotSpinBox->setFixedWidth(60);
		_openAndCloseOrderTypes->setFixedWidth(80);

		QGridLayout* gridLayout2 = new QGridLayout(parent);

		QVBoxLayout* halfRearLayout1 = new QVBoxLayout();
		QVBoxLayout* halfRearLayout2 = new QVBoxLayout();
		QVBoxLayout* halfRearLayout3 = new QVBoxLayout();
		QVBoxLayout* halfRearLayout4 = new QVBoxLayout();
		QVBoxLayout* halfRearLayout5 = new QVBoxLayout();
		halfRearLayout1->addWidget(tradingCode2,0,Qt::AlignTop);
		halfRearLayout1->addWidget(_openAndCloseOrderTypes,0,Qt::AlignBottom);
		halfRearLayout2->addWidget(_priceUpDownStatus,0,Qt::AlignTop);
		halfRearLayout2->addWidget(new QLabel(""),0,Qt::AlignBottom);
		halfRearLayout3->addWidget(_priceCommonPart,0,Qt::AlignTop);
		halfRearLayout3->addWidget(new QLabel(""),0,Qt::AlignBottom);
		halfRearLayout4->addWidget(_bidBox,0,Qt::AlignTop);
		halfRearLayout4->addWidget(new QLabel(""),0,Qt::AlignBottom);
		halfRearLayout5->addWidget(_askBox,0,Qt::AlignTop|Qt::AlignRight);
		if(!isLotInDouble)
		{
			halfRearLayout5->addWidget(_integerLotSpinBox,0,Qt::AlignBottom|Qt::AlignRight);
			_doubleLotSpinBox->setHidden(true);
		}
		else
		{
			halfRearLayout5->addWidget(_doubleLotSpinBox,0,Qt::AlignBottom|Qt::AlignRight);
			_integerLotSpinBox->setHidden(true);
		}

		gridLayout2->addLayout(halfRearLayout1,0,0);
		gridLayout2->addLayout(halfRearLayout2,0,1);
		gridLayout2->addLayout(halfRearLayout3,0,2);
		gridLayout2->addLayout(halfRearLayout4,0,3);
		gridLayout2->addLayout(halfRearLayout5,0,4);

		gridLayout2->setAlignment(Qt::AlignHCenter);
		gridLayout2->setAlignment(Qt::AlignVCenter);

		_mainControl= new QGroupBox(parent);
		_mainControl->setLayout(gridLayout2);
		_mainControl->setAlignment(Qt::AlignCenter);
		_mainControl->setStyleSheet(boxStyle);
		_mainControl->setFixedSize(WIDTH,HEIGHT);
		_mainControl->move(0,HEIGHT+GRAP);
		_integerLotSpinBox->setToolTip("the Maximnu value is 10,000 !");
		_doubleLotSpinBox->setToolTip("the Maximnu value is 9,999.99 !");
	}
}