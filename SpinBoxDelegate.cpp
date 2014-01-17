#include "SpinBoxDelegate.h"

#include <QSpinBox>
#include "OrderModel.h"


SpinBoxDelegate::SpinBoxDelegate(QObject *parent) : QItemDelegate(parent)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem & option ,const QModelIndex & index ) const
{
	if(index.column()==2)
	{
		QSpinBox *spinBox = new QSpinBox(parent);
		spinBox->setFrame(false);
		spinBox->setMinimum(1);
		spinBox->setMaximum(100);
		return spinBox;
	}
   	return  QItemDelegate::createEditor(parent, option, index);
}
void SpinBoxDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
	if(index.column()==2)
	{
		QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
		spinBox->setValue(index.model()->data(index,Qt::DisplayRole).toInt());
	}
	else
		QItemDelegate::setEditorData(editor, index);
}
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
	if(index.column()==2)
	{
		QSpinBox *spinBox  = static_cast<QSpinBox*>(editor);
		spinBox->interpretText();
		int value = spinBox->value();     
		model->setData(index, value, Qt::EditRole);
	}
	else
		QItemDelegate::setModelData(editor, model, index);
}
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	if(index.column()==2)
		editor->setGeometry(option.rect);
	else
		QItemDelegate::updateEditorGeometry(editor,option,index);
}
