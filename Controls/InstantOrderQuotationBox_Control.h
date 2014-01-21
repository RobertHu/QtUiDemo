#ifndef _INSTANTORDERQUOTATIONBOX_CONTROL_H
#define _INSTANTORDERQUOTATIONBOX_CONTROL_H
#include "QuotationInfo_Control.h"
#include "QuotationBoxCommon_Control.h"
class QSpinBox;
class QDoubleSpinBox;
namespace Controls
{
	class InstantOrderQuotationBox:public QuotationBoxCommon
    {
	public:
		InstantOrderQuotationBox(const QString& boxStyle,const QString& labelStyle,const QuotationInfo& quotation,bool isLotInDouble,QWidget* parent=nullptr);

		QComboBox* getOpenAndCloseOrderTypeCmb()
		{
			return _openAndCloseOrderTypes;
		}

		QSpinBox* getIntegerLotSpinBox()
		{
			return _integerLotSpinBox;
		}

		QDoubleSpinBox* getDoubleLotSpinBox()
		{
			return _doubleLotSpinBox;
		}

	private:
		InstantOrderQuotationBox(const InstantOrderQuotationBox&);
		InstantOrderQuotationBox& operator=(const InstantOrderQuotationBox&);
		QComboBox* _openAndCloseOrderTypes;
		QSpinBox* _integerLotSpinBox;
		QDoubleSpinBox* _doubleLotSpinBox;

    };
}
#endif