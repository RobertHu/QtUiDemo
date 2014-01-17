#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QItemDelegate>

class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SpinBoxDelegate(QObject *parent = 0);

public:
	//��˫��������ĳһ��Ԫ��ʱ��������������������һ��Editor
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
	// ���ڰ�ģ�͵����ݴ��ݸ�������Ŀؼ�
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
    // �����ύ�޸ĵ�����
	void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif
