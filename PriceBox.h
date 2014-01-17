#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QSize>

class PriceBox : public QWidget
{
	Q_OBJECT

public:
	PriceBox(QWidget *parent=0);
	PriceBox(const QString& text,QWidget *parent=0);
	~PriceBox();
protected:
	void paintEvent(QPaintEvent* event);
	QSizePolicy	sizePolicy() const;
	QSize	minimumSizeHint() const;

public:
	QSize GetSize();
	void  SetSize(int width,int height);
	void  SetSize(const QSize& size);
	void  SetRadius(int radius);
	void  SetShowWidget(bool bShow);
	bool  IsShowWidget();
	QColor GetBackGroundColor();
	void  SetBackGroundColor(const QColor& color);
	void  SetText(const QString& text);
	QString GetText();
	void  SetShowFrame(bool bShow);
	bool  IsShowFrame();
	void  SetCornerText(const QString& text);
	QString GetCornerText();
	void  SetFontSize(int fontSize);
	int   GetFontSize();


private:
	void Init(QWidget* parent);

private:
	int		m_Radius;	//Բ�ǰ뾶;
	QSize	m_Size;
	QColor  m_Color;
	bool    m_ShowWidget;
	QString m_Text;
	bool    m_ShowFrame;
	QString m_CornerText;
};

#endif // PAINTERWIDGET_H
