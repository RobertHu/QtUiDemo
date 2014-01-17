#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>


#include "TreeItem.h"


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QString& data, QObject *parent = 0);
    ~TreeModel();

	//overwrite:
public:
    QVariant		data(const QModelIndex &index, int role) const;
    Qt::ItemFlags	flags(const QModelIndex &index) const;
    QVariant		headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;
    QModelIndex		index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    QModelIndex		parent(const QModelIndex &index) const;
    int				rowCount(const QModelIndex &parent = QModelIndex()) const;
    int				columnCount(const QModelIndex &parent = QModelIndex()) const;
	bool			setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);  
	bool			removeRow(int row, const QModelIndex & parent = QModelIndex());
	bool			insertRow(int row, const QModelIndex & parent = QModelIndex());


public:
	QString		GetCheckedItemData(bool bAll); 
	TreeItem*	GetRootItem();
	TreeItem*	GetTreeItem(const QModelIndex& index);
	void		AppendListToTree(const QStringList& strlist);
	void		RemoveListFromTree(QStringList& strlist,bool bAll = false);
	void		RemoveList(const QStringList& removeList);
	void		ResetTreeModel(const QStringList& removeList);

private:
    void			SetupModelData(const QStringList &lines);
	void			SetStringList(TreeItem *item,QStringList& strList,bool bAll);
	QModelIndex		TreeItemToModelIndex(TreeItem* item);
	void			SetParentChildStringMap();
	void			AppendParentItem(const QStringList& strlist);

private:
    TreeItem*						m_RootItem;
	QString							m_AppendItemString;
	QMap<QString,QList<QString> >	m_ParentChildStringMap;

};


#endif
