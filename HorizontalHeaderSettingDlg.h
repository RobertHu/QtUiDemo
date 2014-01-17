#ifndef HORIZONTALHEADERSETTINGDLG_H
#define HORIZONTALHEADERSETTINGDLG_H

#include <QDialog>
#include <QPair>

#include "ColumnObject.h"

class HorizontalHeaderSettingDlg : public QDialog
{
	Q_OBJECT
public:
	HorizontalHeaderSettingDlg(QMap<int,ColumnObject>& columnMap,const QPoint& point,QWidget* parent=0);
private:
	void SetSizeAnimation(const QSize& beginSize,const QSize& endSize);
private:
	enum MyEnum
	{							
		FRISTHEIGHT=100,LASTHEIGHT=400,DURATION=500
	};
};


#endif
