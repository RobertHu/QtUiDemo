#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include <QTreeView>
#include <QListView>
#include <QStringListModel>

#include "TreeModel.h"



class AddItem : public QDialog
{
	Q_OBJECT

public:
	AddItem(QMap<int,QString>& itemMap,QWidget *parent);
	~AddItem();

	//overwrite:
public slots:
	void accept();

private slots: 
	void RemovedSelectedItems();
	void RemoveAllItems();
	void AddSelectedItems();
	void AddAllItems();

	void MoveUp();	
	void MoveDown();
	void MoveUpToTop();
	void MoveDownToBotton();
	void Synchronous();

private:
	void SetBtnEnableOrDisable();
	void SetSizeAnimation(const QSize& beginSize,const QSize& endSize);

private:
	QTreeView* 			m_TreeView;
	TreeModel*			m_TreeModel;

	QListView* 			m_ListView;
	QStringListModel*	m_ListModel;
	QStringList			m_StringList;

	QMap<int,QString>&  m_ItemMap;	 //ÒýÓÃ;

private:
	QPushButton*	m_BtnDelete;
	QPushButton*	m_BtnDeleteAll;
	QPushButton*	m_BtnAdd;
	QPushButton*	m_BtnAddAll;
	
	QPushButton*	m_BtnUp;
	QPushButton*	m_BtnDown;
	QPushButton*	m_BtnTop;
	QPushButton*	m_BtnBottom;
	QPushButton*	m_BtnSync;
};

#endif // ADDITEM_H
