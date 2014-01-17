#include "TradeHeaderView.h"

#include <QPainter>
#include <QMouseEvent>
#include <QMenu>

#include "HorizontalHeaderSettingDlg.h"
#include "SetFontDlg.h"


TradeHeaderView::TradeHeaderView(QMap<int,ColumnObject>& columnMap,Qt::Orientation orientation,QWidget* parent):m_ColumnMap(columnMap),QHeaderView(orientation,parent)
{
	this->setSectionsMovable(true);	 //列标题可拖放;
	this->setSectionsClickable(true);
}
void TradeHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex); 
    painter->restore();
}
void TradeHeaderView::mousePressEvent(QMouseEvent * event)
{
	if(event->button()==Qt::RightButton) 
	{
		int width = 0;
		for(int i=0;i<count();i++)
		{
			if(!isSectionHidden(i))
				width += sectionSize(i);
		}
		if(width<event->x())
		{
			QHeaderView::mousePressEvent(event);
			return ;
		}
		QMenu * popupMenu = new QMenu(this);
		QString menuStyle = "QMenu { font-size:16px; color:blue; background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 #111111);}" ;
		popupMenu->setStyleSheet(menuStyle);
		
		QAction* hideThisColumn = new QAction(tr("&Hide this Columns"),this);
		QAction* hideColumns = new QAction(tr("&Hide Columns..."), this);
		QAction* setThisColumnFont = new QAction(tr("&Set this Column Font..."),this);
		connect(hideThisColumn,SIGNAL(triggered()), this, SLOT(HideThisColumn()));
		connect(hideColumns,SIGNAL(triggered()), this, SLOT(HideColumns()));
		connect(setThisColumnFont,SIGNAL(triggered()), this, SLOT(SetThisColumnFont()));
		
		m_LogicalIndex = logicalIndexAt(event->pos()); 
		if(!(m_LogicalIndex==0 || m_LogicalIndex==2))
			popupMenu->addAction(hideThisColumn);
		popupMenu->addAction(hideColumns);
		popupMenu->addAction(setThisColumnFont);

		m_CurrentPoint = QCursor::pos();
		popupMenu->exec(m_CurrentPoint);
	}
	QHeaderView::mousePressEvent(event);
}
void TradeHeaderView::HideThisColumn()
{
	setSectionHidden(m_LogicalIndex,true);
	m_ColumnMap[m_LogicalIndex].SetShow(false);
}
void TradeHeaderView::HideColumns()
{
	HorizontalHeaderSettingDlg dlg(m_ColumnMap,m_CurrentPoint,this);
	dlg.exec();
}
void TradeHeaderView::SetThisColumnFont()
{
	SetFontDlg dlg(m_LogicalIndex,this);
	dlg.exec();
}