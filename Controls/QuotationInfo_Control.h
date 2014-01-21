#ifndef _QUOTATIONINFO_CONTROL_H
#define _QUOTATIONINFO_CONTROL_H
#include <qstring.h>
namespace Controls
{
	struct  QuotationInfo
	{
		QString instrumentCode;
		QString bid;
		QString ask;
		QString commonPart;
		QString timestamp;
		QString previousHigh;
		QString previousLow;
	};
}
#endif
