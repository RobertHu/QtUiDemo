#ifndef ORDERDLG_H
#define ORDERDLG_H

#include <QDialog>
#include <QString>
#include <QTabwidget>

#include "OrderDataProvider.h"
#include "CurrentPriceData.h"

class OrderDlg : public QDialog
{
	Q_OBJECT
public:
	OrderDlg(OrderDataProviderBase* orderDataProvider,QWidget* parent=0);
	~OrderDlg();

	//overwrite:
public slots:
	void accept();

signals:
	void SendCurrentPriceSignal(const CurrentPriceData&);



private:
	QTabWidget*	 m_TabWidget;

};

#endif