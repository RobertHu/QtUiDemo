#include "GridTab.h"
#include <QLayout>
#include <QDialog>
#include <qstackedwidget.h>

#include "Enum.h"
#include "PriceDisplayBoardWindowBoxList.h"


GridTab::GridTab(QList<TradeItem>& itemList,QWidget *parent):QWidget(parent)
{	
	m_VScrollBar = new QScrollBar(Qt::Vertical,this);
	m_ListViewPort = new ListViewPort(itemList,this);


	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_ListViewPort);
	layout->addWidget(m_VScrollBar);
	layout->setMargin(0);
	layout->setSpacing(0);	
	setLayout(layout);

	QString vScrollBarStyle = "QScrollBar:vertical{ width:20px; background:rgba(0,0,0,0%); margin:0px,0px,0px,0px; padding-top:21px; padding-bottom:21px; }"
							  "QScrollBar::handle:vertical{width:20px;background:rgba(0,0,0,20%);border-radius:4px;min-height:20;}"
							  "QScrollBar::handle:vertical:hover{width:20px;background:qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 #eeeeee, stop: 1 #555555);border-radius:4px;min-height:20;}"
							  "QScrollBar::add-line:vertical{height:21px;width:20px;background:qlineargradient(x1:0, y1:0, x2:1, y2:1, stop: 0 #555555, stop: 1 #eeeeee);subcontrol-position:bottom;}"
							  "QScrollBar::sub-line:vertical{height:21px;width:20px;background:qlineargradient(x1:1, y1:1, x2:0, y2:0, stop: 0 #555555, stop: 1 #eeeeee);subcontrol-position:top;}"
							  "QScrollBar::add-line:vertical:hover{height:21px;width:20px;border-image:url(images/ListTab/4.png);subcontrol-position:bottom;}"
							  "QScrollBar::sub-line:vertical:hover{height:21px;width:20px;border-image:url(images/ListTab/2.png);subcontrol-position:top;}"
							  "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(0,0,0,10%);border-radius:4px;}";
//	m_VScrollBar->setStyleSheet(vScrollBarStyle);

	connect(m_VScrollBar,SIGNAL(valueChanged(int)),this,SLOT(DisplayViewPort(int)));
	connect(this,SIGNAL(SendReSizeSignal(int,int)),m_ListViewPort->GetList(),SLOT(ReSizeSlot(int,int)));
}
void GridTab::resizeEvent(QResizeEvent * event)
{
	
	int count = m_ListViewPort->GetList()->GetCounts();
	int width = this->size().width()-m_VScrollBar->width();
	int column = width/WIDTH==0 ? 1 : width/WIDTH;
	int row = count/column;
	row = count%column==0 ? row : (row+1) ;
	
	if(height()>=row*HEIGHT)
	{
		m_VScrollBar->setMinimum(0);
		m_VScrollBar->setMaximum(0);
		m_VScrollBar->setHidden(true);
	}
	else
	{
		m_VScrollBar->setHidden(false);
		int itemHeight = HEIGHT+GRAP;
		m_VScrollBar->setMinimum(0);
		int max = row*itemHeight-height();
		int pageStep = height()-max;
		m_VScrollBar->setMaximum(max);
		m_VScrollBar->setPageStep(pageStep);
		m_VScrollBar->setSingleStep(10);
	}

	int listViewHeight = row*(HEIGHT+GRAP);
	listViewHeight = listViewHeight > this->size().height() ? listViewHeight : this->size().height();
	m_ListViewPort->GetList()->resize(this->size().width(),listViewHeight);
	
	emit SendReSizeSignal(row,column);

	QWidget::resizeEvent(event);
}
void GridTab::DisplayViewPort(int len)
{
	m_ListViewPort->GetList()->move(0,-len);
}

ListViewPort*  GridTab::GetListViewPort()
{
	return m_ListViewPort;
}
QScrollBar*	GridTab::GetVScrollBar()
{
	return m_VScrollBar;
}



