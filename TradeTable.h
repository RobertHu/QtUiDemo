#ifndef TRADETABLE_H
#define TRADETABLE_H

#include <QTableView>


#include "TradeItem.h"
#include "TableItemDelegate.h"
#include "TableModel.h"
#include "ColumnObject.h"


class TradeTable : public QTableView
{
	Q_OBJECT
public:
	TradeTable(QList<TradeItem>& itemList,const QString& columnJsonFile,QWidget* parent=0);
	~TradeTable();
	//overwrite:
protected:
	void  mousePressEvent(QMouseEvent * event);
	void  mouseMoveEvent(QMouseEvent * event);

public slots:
	void SetHeaderColumnHideOrShow(int column,bool bShow);

 	void SetBold(int index,bool bBold);
	void SetItalic(int index,bool bItalic);
	void SetFontSize(int index,int fontSize);
	void SetFontColor(int index,const QColor& fontColor);

	void RealTimeDisplay(const TradeItem& item);

signals:
	void	AddSignal();
	void	OrderSignal(int);
	void	ChartSignal(int);
	void	DeleteSignal(int);
	void	MoveUpSignal(int);
	void	UpToTopSignal(int);
	void	MoveDownSignal(int);
	void	DownToBottomSignal(int);
public slots:
	void	AddSlot();
	void	OrderSlot();
	void	ChartSlot();
	void	DeleteSlot(int);
	void	MoveUpSlot(int);
	void	UpToTopSlot(int);
	void	MoveDownSlot(int);
	void	DownToBottomSlot(int);

private slots:
	void	Order();
	void	Chart();
	void	Add();
	void	Delete();
	void	MoveUp();
	void	UpToTop();
	void	MoveDown();
	void	DownToBottom();

private:
	bool    LoadColumnJson();
	bool	SaveColumnJson();

private:
	TableItemDelegate*			m_Delegate;
	TableModel*					m_TableModel;
	QList<TradeItem>&			m_ItemList;
	int							m_SelectedIndex;
	QString						m_ColumnJsonFile;
	QMap<int,ColumnObject>		m_ColumnMap;

};


#endif
