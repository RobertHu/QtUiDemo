#include "ListTab.h"

#include <QLayout>


ListTab::ListTab(QList<TradeItem>& itemList,const QString& columnJsonFile,QWidget *parent):QWidget(parent)
{	
	m_Table = new TradeTable(itemList,columnJsonFile,this);
	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->addWidget(m_Table);
	gridLayout->setMargin(0);
	setLayout(gridLayout);
}
TradeTable*  ListTab::GetTable()
{
	return 	 m_Table;
}


