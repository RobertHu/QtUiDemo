#include "LotData.h"

LotData::LotData(){}
LotData::LotData(bool isDouble,const QVariant& stepLenth,const QVariant& miniValue,const QVariant& maxValue)
{
	m_IsDouble = isDouble;
	m_StepLenth = stepLenth;
	m_MiniValue = miniValue; 	
	m_MaxVaule = maxValue;
}

bool LotData::IsDouble()
{
	return m_IsDouble;
}
QVariant LotData::StepLenth()
{
	return m_StepLenth;
}
QVariant LotData::MiniValue()
{
	return m_MiniValue;
}
QVariant LotData::MaxValue()
{
	return m_MaxVaule;
}
