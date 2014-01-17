#include "HorizontalHeaderSettingDlg.h"

#include <QLayout>
#include <QPropertyAnimation>

#include "HorizontalHeaderSettingDlgListView.h"
#include "HorizontalHeaderSettingDlgModel.h"


HorizontalHeaderSettingDlg::HorizontalHeaderSettingDlg(QMap<int,ColumnObject>& columnMap,const QPoint& point, QWidget* parent):QDialog(parent)
{
    HorizontalHeaderSettingDlgListView* listView = new HorizontalHeaderSettingDlgListView(columnMap,this);
    HorizontalHeaderSettingDlgModel* itemModel = new HorizontalHeaderSettingDlgModel(columnMap,this);
	listView->setModel(itemModel);

	QGridLayout* layout = new QGridLayout();
	layout->addWidget(listView,0,Qt::AlignHCenter|Qt::AlignVCenter);
	setLayout(layout);
	this->move(point);
	this->SetSizeAnimation(QSize(LASTHEIGHT,FRISTHEIGHT),QSize(LASTHEIGHT,LASTHEIGHT));		  
	

	connect(listView,SIGNAL(SetHeaderColumnHideOrShow(int,bool)),parent->parent(),SLOT(SetHeaderColumnHideOrShow(int,bool)));
}

void HorizontalHeaderSettingDlg::SetSizeAnimation(const QSize& beginSize,const QSize& endSize)
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
	animation->setDuration(DURATION);
	animation->setStartValue(beginSize);
	animation->setEndValue(endSize);
	animation->start();
}