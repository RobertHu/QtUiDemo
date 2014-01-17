#ifndef BIDASKPRICEBUTTON_H
#define BIDASKPRICEBUTTON_H

#include <QWidget>
#include <QSize>
#include <QLabel>
#include <QGroupBox>
#include <QMouseEvent>

class BidAskPriceButton : public QWidget
{
	Q_OBJECT

public:
	BidAskPriceButton(const QSize& size,const QString& commPriceText,const QString& bidAskPriceText,int colorFlag,bool bBidPrice=true,QWidget *parent=0);
	~BidAskPriceButton();
	//overwrite;
protected:
	QSizePolicy	sizePolicy() const;
	QSize	minimumSizeHint() const;
	void	mouseDoubleClickEvent(QMouseEvent * event);
signals:
	void  PlaceAnOrderSignal(bool bBid);
public:
	void  SetSize(int width,int height);
	void  SetSize(const QSize& size);
	void  SetFontSize(int fontSize);
	void  SetLeftTopCornerText(const QString& text);
	void  SetLeftBottomCornerText(const QString& text);
	void  SetCenterCommPriceText(const QString& text);
	void  SetCenterBidAskPriceText(const QString& text);
	void  SetBkColor(int colorFlag);
	void  SetFontSizeRatio(float ratio);
	void  SetTrendStatus(int trendStatus);
private: 
	void Update();
	void Init(const QSize& size,const QString& commPriceText,const QString& bidAskPriceText,int colorFlag,bool bBidPrice);
	
private:
	enum 
	{
		FONTSIZE = 16,
	};

private:
	QSize		m_Size;
	int			m_FontSize;
	float		m_FontSizeRatio;  //建议在(0,1)之间的小数;
	int			m_ColorFlag;
	int			m_IsBid; 	
	int			m_TrendStatus;

	QPixmap		m_UpPixmap;
	QPixmap		m_DownPixmap;
	QPixmap		m_KeepPixmap;

private:
	QLabel*		m_LeftTopCornerLabel;
	QLabel*		m_LeftBottomCornerLabel;
	QLabel*		m_CenterCommPriceLabel;
	QLabel*		m_CenterBidAskPriceLabel;
	QLabel*		m_TrendPixmapLabel;
	QGroupBox*	m_GroupBox;



	

};

#endif // PAINTERWIDGET_H
