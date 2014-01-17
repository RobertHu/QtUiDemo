#include "HorizontalHeaderSettingDlgListView.h"

#include <QMouseEvent>
#include <QStandardItemModel>

HorizontalHeaderSettingDlgListView::HorizontalHeaderSettingDlgListView(QMap<int,ColumnObject>& columnMap,QWidget* parent):m_ColumnMap(columnMap),QListView(parent)
{
	//this->setEditTriggers(QAbstractItemView::NoEditTriggers); 
	//this->setSelectionMode(QAbstractItemView::SingleSelection);
	//setDragDropOverwriteMode(false);

	this->setSpacing(SPACE);
	this->setIconSize(QSize(ICONWIDTH,ICONHEIGHT));
//	this->setDropIndicatorShown(true);
	this->setAlternatingRowColors(true);

	this->m_IconHide = QIcon("images/button-hide.png");
	this->m_IconShow = QIcon("images/button-show.png");

	QString style = "QListView::item:selected {border: 1px solid #666666;}"
					"QListView::item:selected:!active{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #EEEEEE, stop: 1 #111111);}"
					"QListView::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #111111, stop: 1 #EEEEEE);}";
	this->setStyleSheet(style);
	this->setFocusPolicy(Qt::NoFocus);
	this->setMouseTracking(true);
	this->setToolTip("Double-Click to Hide or Show.");

}

void HorizontalHeaderSettingDlgListView::mouseDoubleClickEvent(QMouseEvent * event)
{
	this->DoMouseEvent(event);
	QListView::mouseDoubleClickEvent(event);
}
void HorizontalHeaderSettingDlgListView::mousePressEvent(QMouseEvent * event)
{
	if(event->button()==Qt::LeftButton && event->pos().x()<ICONWIDTH)
		this->DoMouseEvent(event);
	QListView::mousePressEvent(event);
}
void HorizontalHeaderSettingDlgListView::mouseMoveEvent(QMouseEvent * event)
{
	QModelIndex index = indexAt(event->pos());
	if(index.isValid() && index.row()>=0)
		this->setSelection(this->visualRect(index),QItemSelectionModel::SelectCurrent);
}
void HorizontalHeaderSettingDlgListView::DoMouseEvent(QMouseEvent * event)
{
	if(event->button()==Qt::LeftButton)
	{
		QModelIndex index = indexAt(event->pos());
		if(index.isValid())
		{
			QStandardItem *item = ((QStandardItemModel*)model())->itemFromIndex(index);
			QBrush brush;
			int column = index.row();
			if(item->foreground().color()==QColor(Qt::black))
			{
				if(m_ColumnMap[column].IsForbidHide())
				{
					return ;
				}
			   	item->setIcon(m_IconHide);
				brush.setColor(Qt::darkGray);
				emit SetHeaderColumnHideOrShow(column,false);
			}
			else
			{
				item->setIcon(m_IconShow);
				brush.setColor(QColor(Qt::black));
				emit SetHeaderColumnHideOrShow(column,true);
			}
			item->setForeground(brush);
			m_ColumnMap[column].SetShow(!m_ColumnMap[column].IsShow());
		}
	}
}
