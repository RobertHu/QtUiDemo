#ifndef _QUOTATIONBOXCOMMON_CONTROL_H
#define _QUOTATIONBOXCOMMON_CONTROL_H
class QGroupBox;
class QWidget;
class QLabel;
class PriceBox;
class QComboBox;
namespace Controls
{
    class QuotationBoxCommon
    {
	public:
		PriceBox* getBidBox()
		{
			return _bidBox;
		}

		PriceBox* getAskBox()
		{
			return _askBox;
		}

		QLabel* getPriceUpDownStatusLabel()
		{
			return _priceUpDownStatus;
		}

		QLabel* getPriceCommonPartLabel()
		{
			return _priceCommonPart;
		}

	protected:
		QGroupBox* _mainControl;
		QLabel* _priceUpDownStatus;
		QLabel* _priceCommonPart;
		PriceBox* _bidBox;
		PriceBox* _askBox;
		void initPriceBox(PriceBox* box);
    };
    
}
#endif