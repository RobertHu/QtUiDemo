#ifndef COLUMNOBJECT_H
#define COLUMNOBJECT_H

#include <QString>

class ColumnObject
{
public:
	ColumnObject(void);
	ColumnObject(const QString& columnText,bool bShow=true,bool bForbidHide=false,bool bPicture=false);
	~ColumnObject(void);

public:
	QString  GetColumnText();
	bool	 IsShow();
	bool	 IsForbidHide();
	bool	 IsPicture();
	void	 SetColumnText(const QString& columnText);
	void	 SetShow(bool bShow);
	void	 ForbidHide(bool bForbidHide);

private:
	QString  m_ColumnText;
	bool	 m_Show;
	bool	 m_ForbidHide;
	bool	 m_Picture;

};

#endif


