#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H

#include <QString>

class AccountData
{
public:
	AccountData();
public:
	int		GetAccountID();
	QString GetAccountName();


private:
	int			m_AccountID;
	QString		m_AccountName;


};


#endif
