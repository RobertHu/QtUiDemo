#ifndef HORIZONTALHEADERSETTINGDLGLISTVIEW_H
#define	HORIZONTALHEADERSETTINGDLGLISTVIEW_H

#include <QListView>

#include "ColumnObject.h"

class HorizontalHeaderSettingDlgListView : public QListView
{
	Q_OBJECT
public:
	HorizontalHeaderSettingDlgListView(QMap<int,ColumnObject>& columnMap,QWidget* parent=0);
	//overwrite:
protected:
	void mouseDoubleClickEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
signals:
	void SetHeaderColumnHideOrShow(int column,bool bShow);
private:
	void DoMouseEvent(QMouseEvent * event);
private:
	QIcon					m_IconHide;
	QIcon					m_IconShow;
private:
	enum MyEnum
	{
		ICONWIDTH=40,ICONHEIGHT=40,SPACE=0
	};
private:
	QMap<int,ColumnObject>&	 m_ColumnMap;
};


#endif
