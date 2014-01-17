#ifndef LOTDATA_H
#define LOTDATA_H

#include <QVariant>

class LotData
{
public:
	LotData();
	LotData(bool isDouble,const QVariant& stepLenth,const QVariant& maxValue,const QVariant& miniValue);
public:
	bool		IsDouble();
	QVariant	StepLenth();
	QVariant	MaxValue();
	QVariant	MiniValue();
	
private:
	bool		m_IsDouble;
	QVariant	m_StepLenth;
	QVariant	m_MiniValue;
	QVariant	m_MaxVaule;
};

#endif

