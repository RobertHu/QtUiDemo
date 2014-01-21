#include "QuotationBoxCommon_Control.h"
#include "../PriceBox.h"
namespace Controls
{
	void QuotationBoxCommon::initPriceBox(PriceBox* box)
	{
		box->SetSize(60,30);
		box->SetRadius(15);
		box->SetFontSize(16);
	}
}