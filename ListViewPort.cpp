#include "ListViewPort.h"

#include <QLayout>

#include "Enum.h"

ListViewPort::ListViewPort(QList<TradeItem>& itemList,QWidget* parent) : QWidget(parent)
{
	m_List = new  PriceDisplayBoardWindowBoxList(itemList,this);
	QGridLayout* layout = new QGridLayout(this);
	layout->addWidget(m_List);
	layout->setMargin(0);
	layout->setSpacing(0);
	setLayout(layout);
}
QSizePolicy	ListViewPort::sizePolicy() const
{
	QSizePolicy  sizePolicy;
	sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
	return sizePolicy;
}
QSize ListViewPort::minimumSizeHint() const
{
	return QSize(WIDTH,HEIGHT);
}




PriceDisplayBoardWindowBoxList* ListViewPort::GetList()
{
	return m_List;
}