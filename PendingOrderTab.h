#ifndef PENDINGORDERTAB_H
#define	PENDINGORDERTAB_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QPushButton>

#include "OrderListView.h"
#include "BidAskPriceButton.h"
#include "Enum.h"
#include "OrderDataProvider.h"
#include "CurrentPriceData.h"

class PendingOrderTab : public QDialog
{
	Q_OBJECT
public:
	PendingOrderTab(OrderDataProviderBase* orderDataProvider,QSize& miniSize,QWidget* tabWidgetParent,QWidget* parent=0);
	//overwrite:
protected:
	void resizeEvent(QResizeEvent * event);

public slots:
	void GetCurrentPriceSlot(const CurrentPriceData&);

private:
	void Init(QSize& miniSize,QWidget* tabWidgetParent);
	void InitLayout(QSize& miniSize);
	void GetTopY(int& topY,int leftControlHeight,int rightControlHeight);

private:
	BidAskPriceButton*  m_BidBtn;
	BidAskPriceButton*	m_AskBtn;

	QLabel*			m_TypeLabel;
	QLabel*			m_AccountLabel;
	QLabel*			m_BuysellLabel;
	QLabel*			m_LotLabel;
	QLabel*			m_LimitPriceLabel;
	QLabel*			m_StopPriceLabel;
	QLabel*			m_TimeExpiredLabel;

	QComboBox*		m_TypeComboBox;
	QComboBox*		m_AccountComboBox;
	QRadioButton*	m_BuyRadioBtn;
	QRadioButton*	m_SellRadioBtn;
	QSpinBox*		m_LotComboBox;
	QSpinBox*		m_LimitPriceSpinBox;
	QCheckBox*		m_LimitPriceCheckBox;
	QSpinBox*		m_StopPriceSpinBox;
	QCheckBox*		m_StopPriceCheckBox;
	QCheckBox*		m_OcoCheckBox;
	QComboBox*		m_TimeExpiredComboBox;

	OrderListView*  m_OrderedList;
	QPushButton*	m_SubmitBtn;
	QPushButton*	m_CloseAllBtn;
	QPushButton*	m_ExitBtn;

};

#endif
