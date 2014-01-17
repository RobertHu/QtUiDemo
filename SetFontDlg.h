#ifndef SETFONTDLG_H
#define	SETFONTDLG_H

#include <QDialog>

class SetFontDlg : public QDialog
{
	Q_OBJECT
public:
	SetFontDlg(int logicalIndex,QWidget* parent=0);
signals:
	void SetBoldSignal(int index,bool bBold);
	void SetItalicSignal(int index,bool bItalic);
	void SetFontSizeSignal(int index,int fontSize);
	void SetFontColorSignal(int index,const QColor& fontColor);
public slots:
	void SetBold(int status);
	void SetItalic(int status);
	void SetFontSize(int fontSize);
	void SetFontColor(int fontColor);
private:
	int m_LogicalIndex;


};


#endif
