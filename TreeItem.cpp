#include "TreeItem.h"


TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    m_ParentItem = parent;
    m_ItemDataList = data;
	m_Checked = false;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_ChildItemList);
}

int TreeItem::Row() const
{
    if (m_ParentItem)
        return m_ParentItem->m_ChildItemList.indexOf(const_cast<TreeItem*>(this));
    return 0;
}
int TreeItem::ChildCount() const
{	
	return m_ChildItemList.count();
}
int TreeItem::ColumnCount() const
{
	return m_ItemDataList.count();
}
bool TreeItem::IsChecked()
{
	return m_Checked;
}
void TreeItem::AppendChild(TreeItem *item)
{
	m_ChildItemList.append(item);
}
void TreeItem::RemoveChild(TreeItem* item)
{
	m_ChildItemList.removeAll(item);
}
void TreeItem::SetCheckState(bool state)
{
	m_Checked = state;
}

TreeItem *TreeItem::ParentItem()
{
    return m_ParentItem;
}
TreeItem *TreeItem::ChildItem(int row)
{
    return m_ChildItemList.value(row);
}
QVariant TreeItem::Data(int column) const
{
    return m_ItemDataList.value(column);
}
QList<TreeItem*> TreeItem::GetChildItemList()
{
   return m_ChildItemList;
}
QList<QVariant> TreeItem::GetItemDataList()
{
   return m_ItemDataList;
}