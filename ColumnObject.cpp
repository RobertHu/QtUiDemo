#include "ColumnObject.h"


ColumnObject::ColumnObject(void)
{
}
ColumnObject::ColumnObject(const QString& columnText,bool bShow,bool bForbidHide,bool bPicture)
{
	m_ColumnText = columnText;
	m_Show = bShow;
	m_ForbidHide = bForbidHide;
	m_Picture = bPicture;
}

ColumnObject::~ColumnObject(void)
{
}

QString  ColumnObject::GetColumnText()
{
	return m_ColumnText;
}
bool ColumnObject::IsShow()
{
	return m_Show;
}
bool ColumnObject::IsForbidHide()
{
	return m_ForbidHide;
}
bool ColumnObject::IsPicture()
{
	return m_Picture;
}
void ColumnObject::SetColumnText(const QString& columnText)
{
	m_ColumnText = columnText;
}
void ColumnObject::SetShow(bool bShow)
{
	m_Show = bShow;
}
void ColumnObject::ForbidHide(bool bForbidHide)
{
	m_ForbidHide = bForbidHide;
}
