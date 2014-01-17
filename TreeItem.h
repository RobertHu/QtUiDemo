#ifndef TREEITEM_H
#define	TREEITEM_H

#include <QList>
#include <QVariant>


class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

public:
   	int		Row() const;
    int		ChildCount() const;
    int		ColumnCount() const; 
	bool	IsChecked();
	void	AppendChild(TreeItem* childItem);
	void	RemoveChild(TreeItem* childItem);
	void	SetCheckState(bool state);

public:
    TreeItem*			ParentItem();
	TreeItem*			ChildItem(int row);	 
	QVariant			Data(int column) const;
	QList<TreeItem*>	GetChildItemList();
	QList<QVariant>		GetItemDataList();

public:	
	bool				m_Checked;
	
private: 
	TreeItem*			m_ParentItem;
    QList<TreeItem*>	m_ChildItemList;
    QList<QVariant>		m_ItemDataList;
    
};


#endif
