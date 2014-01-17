#ifndef INSTANTORDERTAB_H
#define	INSTANTORDERTAB_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

#include "BidAskPriceButton.h"
#include "OrderListView.h"
#include "OrderDataProvider.h"
#include "CurrentPriceData.h"

class InstantOrderTab : public QDialog
{
	Q_OBJECT
public:
	InstantOrderTab(OrderDataProviderBase* orderDataProvider,QSize& miniSize,QWidget* tabWidgetParent,QWidget* parent=0);
	//overwrite:
protected:
	void resizeEvent(QResizeEvent * event);

signals:
	void AppendOrderRecordSignal(const OrderData&);
public slots:
	void SetCloseAllSlot();
	void PlaceAnOrderSlot(bool isBid);
	void GetCurrentPriceSlot(const CurrentPriceData&);

private:
	void Init(QSize& miniSize,QWidget* tabWidgetParent);
	void InitLayout(QSize& miniSize);
	void PlaceAnOrderBidAsk(bool isBid);
	void GetTopY(int& topY,int leftControlHeight,int rightControlHeight);

private:
	QLabel*					m_AccountLabel;
	QLabel*					m_LotLabel;
	QLineEdit*				m_AccountEdit;
	QSpinBox*				m_LotSpinBox;
	QDoubleSpinBox*			m_LotDoubleSpinBox;
	QPushButton*			m_CloseAllBtn;
	QPushButton*			m_ExitBtn;
 	BidAskPriceButton*		m_BidBtn;
	BidAskPriceButton*		m_AskBtn;
	OrderListView*			m_OrderedList;

private:
	QString  m_CommPrice;
	QString  m_BidPrice;
	QString  m_AskPrice;
private:
	OrderDataProviderBase*	m_OrderDataProvider;

};

#endif
