#ifndef _QUOTATIONBOX_CONTROL_H
#define _QUOTATIONBOX_CONTROL_H
#include "QuotationInfo_Control.h"
#include "QuotationBoxCommon_Control.h"

namespace Controls
{
	class QuotationBox:public QuotationBoxCommon
    {
	public:
		QuotationBox(const QString& boxStyle,const QString& labelStyle,const QuotationInfo& quotationInfo,QWidget* parent=nullptr);
		QLabel* getTimeStampLabel()
		{
			return _timestamp;
		}

		QLabel* getMarkInfoLabel()
		{
			return _markInfo;
		}

		QLabel* getHighestLabel()
		{
			return _highest;
		}

		QLabel* getLowestLabel()
		{
			return _lowest;
		}

	private:
		QuotationBox(const QuotationBox&);
		QuotationBox& operator=(const QuotationBox&);
		
		QLabel* _timestamp;
		QLabel* _markInfo;
		QLabel* _highest;
		QLabel* _lowest;
		
    };
}
#endif
