#include "TreeModel.h"

#include <QStringList>



TreeModel::TreeModel(const QString& data, QObject *parent) : QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "UnSelected" ;

    m_RootItem = new TreeItem(rootData);
    this->SetupModelData(data.split(QString("\n")));

	this->SetParentChildStringMap();
}

TreeModel::~TreeModel()
{
	if(m_RootItem)
		delete m_RootItem;
}

//overwrite;
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

	TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

	if (role==Qt::CheckStateRole && index.column()==0)
		return static_cast<int>( item->IsChecked() ? Qt::Checked : Qt::Unchecked );

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->Data(index.column());
}
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

	if (index.column()==0)   //如果是第一列的结点，则使其有显示checkbox的能力  
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;  

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_RootItem->Data(section);
    return QVariant();
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_RootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->ChildItem(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->ParentItem();

    if (parentItem == m_RootItem)
        return QModelIndex();

    return createIndex(parentItem->Row(), 0, parentItem);
}
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

	TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = m_RootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->ChildCount();
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->ColumnCount();
    else
        return m_RootItem->ColumnCount();
}
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role==Qt::CheckStateRole && index.column()==0)
	{
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
		if (value==Qt::Unchecked)
		{
		//	m_checkedList.removeOne(index);
			item->SetCheckState(false);
			emit(dataChanged(index, index));

			//如果其父节点选中的话，取消勾选父节点;
			QModelIndex parentIndex = parent(index);
			if(parentIndex.isValid())
			{
				TreeItem *parentItem = static_cast<TreeItem*>(parentIndex.internalPointer());
				parentItem->SetCheckState(false);
				emit(dataChanged(parentIndex,parentIndex));
			}
		}
		else if(value==Qt::Checked)
		{
		//	m_checkedList.append(index);
			item->SetCheckState(true);
			emit(dataChanged(index, index));

			//-如果当前节点的其它同级节点都是选中的话，也选中其父节点;
			QModelIndex parentIndex = parent(index);
			if(parentIndex.isValid())
			{
				TreeItem *parentItem = static_cast<TreeItem*>(parentIndex.internalPointer());
				int childCount = rowCount(parentIndex);
				bool bAllChecked = true;
				if(childCount>0)
				{
					for (int i=0; i<childCount; i++)
					{
						 QModelIndex child = this->index(i, 0, parentIndex);
						 TreeItem *item = static_cast<TreeItem*>(child.internalPointer());
						 if(!item->IsChecked())
						 {
							 bAllChecked = false;
							 break;
						 }
					}
					if(bAllChecked)
						parentItem->SetCheckState(true);
					else
						parentItem->SetCheckState(false);
				}
				emit(dataChanged(parentIndex,parentIndex));
			}//-
		}
		int childCount = rowCount(index);
		if (childCount > 0)	//判断是否有子节点
		{
			for (int i=0; i<childCount; i++)
			{
				//获得子节点的index
				QModelIndex child = this->index(i, 0, index);
				//递归，改变子节点的checkbox状态
				setData(child, value, Qt::CheckStateRole);
			}
		}
	}

	return true;
}
bool TreeModel::removeRow(int row, const QModelIndex & parent)
{	
	TreeItem* parentItem;
	if(parent==QModelIndex())
		parentItem = m_RootItem;
	else
		parentItem = static_cast<TreeItem*>(parent.internalPointer()); 

	if(row<0 || row>parentItem->ChildCount()-1)
		return false;	

	beginRemoveRows(parent, row, row);
		parentItem->RemoveChild(parentItem->ChildItem(row));
	endRemoveRows();

	return true;
}
bool TreeModel::insertRow(int row, const QModelIndex & parent)
{
	TreeItem* parentItem;
	if(parent==QModelIndex())
		parentItem = m_RootItem;
	else
		parentItem = static_cast<TreeItem*>(parent.internalPointer()); 

	if(row!=parentItem->ChildCount())
		row = parentItem->ChildCount();

	QList<QVariant> childValueList;
	childValueList.append(m_AppendItemString);
	TreeItem* newChildItem = new TreeItem(childValueList,parentItem);

	beginInsertRows(parent, row, row);
		parentItem->AppendChild(newChildItem);
	endInsertRows();

	return true;
}

QString TreeModel::GetCheckedItemData(bool bAll)
{
	QStringList checkedStrList;
	QString res = "";
	this->SetStringList(m_RootItem, checkedStrList,bAll);
	
	for (int i=0; i<checkedStrList.size(); i++)
	{
		res += (checkedStrList[i] + QString("\n"));
	}
	return res;
}

TreeItem* TreeModel::GetRootItem()
{
	return m_RootItem;
}

TreeItem* TreeModel::GetTreeItem(const QModelIndex& index)
{
	return 	static_cast<TreeItem*>(index.internalPointer());
}

void TreeModel::AppendListToTree(const QStringList& strlist)
{
	if(strlist.count()==0)
		return ;
	this->AppendParentItem(strlist);	

	int count = m_RootItem->ChildCount();
	for(int i = 0;i<strlist.count();i++)
	{
		for(int j=0;j<count;j++)
		{
			QString parentString = m_RootItem->ChildItem(j)->Data(0).toString();
			if(m_ParentChildStringMap[parentString].contains(strlist[i]))
			{
				QModelIndex index = TreeItemToModelIndex(m_RootItem->ChildItem(j));
				m_AppendItemString = strlist[i];
				insertRow(index.row(),index);
			}
		}
	}
}

void TreeModel::RemoveListFromTree(QStringList& strlist,bool bAll)
{
	this->SetStringList(m_RootItem,strlist,bAll);
	QStringList removeList = strlist;
	this->RemoveList(removeList);
}

void TreeModel::RemoveList(const QStringList& removeList)
{
	for(int i=0;i<removeList.count();i++)
	{
		for(int j=0;j<m_RootItem->GetChildItemList().count();j++)
		{
			TreeItem* parentItem = m_RootItem->GetChildItemList()[j];
			QModelIndex parentIndex = this->TreeItemToModelIndex(parentItem);
			for(int k = 0;k<parentItem->ChildCount();k++)
			{
				if(parentItem->ChildItem(k)->Data(0).toString()==removeList[i])
				{
					removeRow(k,parentIndex);
					k -= 1;
				}
			}
		} 
	}
	for(int i=0;i<m_RootItem->GetChildItemList().count();i++)
	{
		if(m_RootItem->GetChildItemList()[i]->ChildCount()==0)
		{
			QModelIndex index = parent(this->TreeItemToModelIndex(m_RootItem->GetChildItemList()[i]));
			if(index==QModelIndex()) 
			{
				removeRow(i,index);
				i -= 1;
			}
		}
	}
}

void TreeModel::ResetTreeModel(const QStringList& removeList)
{
	if(removeList.count()==0)
		return ;
	QMapIterator<QString,QList<QString> >it(m_ParentChildStringMap);
	while(it.hasNext())
	{
		it.next();
		this->AppendListToTree(it.value());
	}
	this->RemoveList(removeList);	
}

void TreeModel::SetupModelData(const QStringList &lines)
{
    QList<TreeItem*> parentItemList;
    QList<int> subItemIndexList;
	parentItemList.append(m_RootItem);
    subItemIndexList.append(0);

    int number = 0;
    while (number < lines.count())
	{
        int position = 0;
        while (position < lines[number].length()) 
		{
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty())
		{
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > subItemIndexList.last()) 
			{
                 if (parentItemList.last()->ChildCount() > 0) 
				{
                    parentItemList << parentItemList.last()->ChildItem(parentItemList.last()->ChildCount()-1);
                    subItemIndexList << position;
                }
            }
			else
			{
                while (position < subItemIndexList.last() && parentItemList.count() > 0) 
				{
                    parentItemList.pop_back();
                    subItemIndexList.pop_back();
                }
            }

            parentItemList.last()->AppendChild(new TreeItem(columnData, parentItemList.last()));
        }
        number++;
    }
}
void TreeModel::SetStringList(TreeItem *item,QStringList& strList,bool bAll)
{
	 if(!m_RootItem)
		 return ;
	
	 int childCount = item->ChildCount();
	 if(childCount <= 0)
	 {
		 if((bAll&m_RootItem->ChildCount()>0) || item->IsChecked())
			strList.append(item->Data(0).toString());
	 }
	 else
	 {
		for (int i=0; i<childCount; i++)
		{
			TreeItem *child = item->ChildItem(i);
			SetStringList(child, strList,bAll);
		}
	 }
}
QModelIndex TreeModel::TreeItemToModelIndex(TreeItem* item)
{
	for(int i=0;i<m_RootItem->ChildCount();i++)
	{
		TreeItem* parentItem = m_RootItem->ChildItem(i);
		QModelIndex parentIndex = index(i,0);
		if(parentItem==item)
			return parentIndex;
		int childCount = parentItem->ChildCount();
		if(childCount>0)
		{
			for(int i=0;i<childCount;i++)
			{
				TreeItem* childItem = parentItem->ChildItem(i);
				QModelIndex childIndex = index(i,0,parentIndex);
				if(item==childItem)
					return childIndex;
			}
		}
	}
	return QModelIndex();			
}

void TreeModel::SetParentChildStringMap()
{
	int count = m_RootItem->ChildCount();
	for(int i=0;i<count;i++)
	{	
		QString parentString;
		QList<QString> childList;
		TreeItem* parentItem = m_RootItem->ChildItem(i);
		parentString = parentItem->Data(0).toString();
		int childCounts = parentItem->ChildCount();
		for(int j=0;j<childCounts;j++)
		{
			childList.append(parentItem->ChildItem(j)->Data(0).toString());
		}
		m_ParentChildStringMap.insert(parentString,childList);
	}
}
void TreeModel::AppendParentItem(const QStringList& strlist)
{
	QStringList appendStringList;
	QMapIterator<QString,QList<QString> >it(m_ParentChildStringMap);
	while(it.hasNext())
	{
		it.next();
		for(int i=0;i<strlist.count();i++)
		{
			if(it.value().contains(strlist[i]))
			{
				appendStringList.append(it.key());
				break;
			}
		}
	}
	appendStringList.removeDuplicates();
	if(appendStringList.count()>0)
	{
		if(m_RootItem->ChildCount()==0)
		{
			for(int i=0;i<appendStringList.count();i++)
			{
				m_AppendItemString = appendStringList[i];
				insertRow(i,TreeItemToModelIndex(m_RootItem));
			}
		}
		else
		{
			for(int i=0;i<appendStringList.count();i++)
			{
				int j=0;
				int count = m_RootItem->ChildCount();
				for(;j<count;j++)
				{
					if(appendStringList[i]==m_RootItem->ChildItem(j)->Data(0).toString())
						break;
				}
				if(j==count)
				{
					m_AppendItemString = appendStringList[i];
					insertRow(count,TreeItemToModelIndex(m_RootItem));
				}
			}
		}
		
	}
	
}