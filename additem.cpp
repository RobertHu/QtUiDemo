#include "additem.h"

#include <QFile>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QPropertyAnimation>



AddItem::AddItem(QMap<int,QString>& itemMap,QWidget *parent) : m_ItemMap(itemMap),QDialog(parent)
{
	QFile file("./tradeItems.txt");
	file.open(QIODevice::ReadOnly);
	m_TreeModel = new TreeModel(file.readAll());
	file.close();
	m_TreeView = new QTreeView(this);
	m_TreeView->setModel(m_TreeModel);
	m_TreeView->setColumnHidden(1, true);
	m_TreeView->setHeaderHidden(true);

	m_ListModel = new QStringListModel(m_StringList);
	m_ListView = new QListView(this);
	m_ListView->setModel(m_ListModel);
	m_ListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QMapIterator<int, QString> it(m_ItemMap);
	while (it.hasNext())
	{
		it.next();
		m_StringList += it.value();
	}

	m_ListModel->setStringList(m_StringList);
	m_TreeModel->RemoveList(m_StringList);

	QString btnStyleNormal = "QPushButton{border-image: url(images/button-normal.png);} ";
	QString btnStylePressed = "QPushButton:pressed{border-image: url(images/button-down.png);} ";
	QString btnStyleHover = "QPushButton:hover{border-image: url(images/button-mouseover.png);} ";
	QString btnStyle = btnStyleNormal + btnStylePressed + btnStyleHover;

	m_BtnDelete = new QPushButton(tr("<"),this);
	m_BtnDeleteAll = new QPushButton(tr("<<"),this);
	m_BtnAdd = new QPushButton(tr(">"),this);
	m_BtnAddAll = new QPushButton(tr(">>"),this);
	
	m_BtnUp = new QPushButton(tr("Up"),this);
	m_BtnDown = new QPushButton(tr("Down"),this);
	m_BtnTop = new QPushButton(tr("Up To Top"),this);
	m_BtnBottom = new QPushButton(tr("Down To Bottom"),this);
	m_BtnSync = new QPushButton(tr("Synchronize"),this);
	
	QPushButton* btnOK = new QPushButton(tr("OK"),this);
	btnOK->setDefault(true);
	QPushButton* btnCancel = new QPushButton(tr("Cancel"),this);
	connect(btnOK,SIGNAL(clicked()),this,SLOT(accept()));
	
	connect(btnCancel,SIGNAL(clicked()),this,SLOT(reject()));

	m_BtnDelete->setStyleSheet(btnStyle);
	m_BtnDelete->setMinimumSize(60,30);
	m_BtnDeleteAll->setStyleSheet(btnStyle);
	m_BtnDeleteAll->setMaximumSize(100,30);
	m_BtnAdd->setStyleSheet(btnStyle);
	m_BtnAdd->setMaximumSize(100,30);
	m_BtnAddAll->setStyleSheet(btnStyle);
	m_BtnAddAll->setMaximumSize(100,30);
	
	m_BtnUp->setStyleSheet(btnStyle);
	m_BtnUp->setMaximumSize(120,30);
	m_BtnDown->setStyleSheet(btnStyle);
	m_BtnDown->setMaximumSize(120,30);
	m_BtnTop->setStyleSheet(btnStyle);
	m_BtnTop->setMaximumSize(120,30);
	m_BtnBottom->setStyleSheet(btnStyle);
	m_BtnBottom->setMinimumSize(120,30);
	m_BtnSync->setStyleSheet(btnStyle);
	m_BtnSync->setMaximumSize(120,30);
	btnOK->setStyleSheet(btnStyle);
	btnOK->setMaximumSize(120,30);
	btnCancel->setStyleSheet(btnStyle);
	btnCancel->setMaximumSize(120,30);
	
	QVBoxLayout* vLayout1 = new QVBoxLayout(this);
	vLayout1->addWidget(m_BtnDelete);
	vLayout1->addWidget(m_BtnDeleteAll);
	vLayout1->addWidget(m_BtnAdd);
	vLayout1->addWidget(m_BtnAddAll);
	
	QVBoxLayout* vLayout2 = new QVBoxLayout(this);
	vLayout2->addWidget(m_BtnUp);
	vLayout2->addWidget(m_BtnDown);
	vLayout2->addWidget(m_BtnTop);
	vLayout2->addWidget(m_BtnBottom);
	vLayout2->addWidget(m_BtnSync);
	vLayout2->addWidget(btnOK);
	vLayout2->addWidget(btnCancel);
	
	QGroupBox* btnsBox1 = new QGroupBox(this);
	btnsBox1->setLayout(vLayout1);
	QGroupBox* btnsBox2 = new QGroupBox(this);
	btnsBox2->setLayout(vLayout2);
	
	QGridLayout* gLayout = new QGridLayout(this);
	gLayout->addWidget(m_TreeView,0,0);
	gLayout->addWidget(btnsBox1,0,1);
	gLayout->addWidget(m_ListView,0,2);
	gLayout->addWidget(btnsBox2,0,3);
	setLayout(gLayout);
	this->SetSizeAnimation(QSize(400,400),QSize(700,400));
	m_ListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	
	connect(m_BtnDelete,SIGNAL(clicked()),this,SLOT(RemovedSelectedItems()));
	connect(m_BtnDeleteAll,SIGNAL(clicked()),this,SLOT(RemoveAllItems()));
	connect(m_BtnAdd,SIGNAL(clicked()),this,SLOT(AddSelectedItems()));
	connect(m_BtnAddAll,SIGNAL(clicked()),this,SLOT(AddAllItems()));
	
	connect(m_BtnUp,SIGNAL(clicked()),this,SLOT(MoveUp()));
	connect(m_BtnDown,SIGNAL(clicked()),this,SLOT(MoveDown()));
	connect(m_BtnTop,SIGNAL(clicked()),this,SLOT(MoveUpToTop()));
	connect(m_BtnBottom,SIGNAL(clicked()),this,SLOT(MoveDownToBotton()));
	connect(m_BtnSync,SIGNAL(clicked()),this,SLOT(Synchronous()));
	
	this->SetBtnEnableOrDisable();
}

AddItem::~AddItem()
{

}

//"<"
void AddItem::RemovedSelectedItems()
{
	QStringList removedStrList;
	foreach(const QModelIndex& index,m_ListView->selectionModel()->selectedIndexes())
	{
		QString removedString = m_ListModel->data(index,Qt::DisplayRole).toString();
		removedStrList.append(removedString);
		m_StringList.removeAll(removedString);
	}
	m_ListModel->setStringList(m_StringList);
	m_TreeModel->AppendListToTree(removedStrList);//
	this->SetBtnEnableOrDisable();
}

//"<<"
void AddItem::RemoveAllItems()
{
	int sum = m_ListModel->rowCount();
	for(int i=0;i<sum;i++)
	{
		m_ListModel->removeRow(0);
	}
	m_TreeModel->AppendListToTree(m_StringList);
	m_StringList.clear();
	this->SetBtnEnableOrDisable();
}

//">"
void AddItem::AddSelectedItems()
{
	QStringList addSelectedItemList;
	m_TreeModel->RemoveListFromTree(addSelectedItemList);
	m_StringList = m_ListModel->stringList() + addSelectedItemList;
	m_StringList.removeDuplicates();
	m_ListModel->setStringList(m_StringList);
	this->SetBtnEnableOrDisable();
}

//">>"
void AddItem::AddAllItems()
{
	QStringList addAllItemList;
	m_TreeModel->RemoveListFromTree(addAllItemList,true);
	m_StringList = m_ListModel->stringList();
	m_StringList += addAllItemList;
	m_StringList.removeDuplicates();
	m_ListModel->setStringList(m_StringList);
	this->SetBtnEnableOrDisable();
}

void AddItem::MoveUp()
{
	QModelIndex index = m_ListView->currentIndex();
	if(index.isValid() && index.row()>0)
	{
		int pos = index.row();
		m_StringList.move(pos,pos-1);
		m_ListModel->setStringList(m_StringList);
		m_ListView->setCurrentIndex(m_ListModel->index(pos-1));
	}
}

void AddItem::MoveDown()
{
	QModelIndex index = m_ListView->currentIndex();
	if(index.isValid() && index.row()>=0 && (index.row()< m_ListModel->rowCount()-1))
	{
		int pos = index.row();
		m_StringList.move(pos,pos+1);
		m_ListModel->setStringList(m_StringList);
		m_ListView->setCurrentIndex(m_ListModel->index(pos+1));
	}

}

void AddItem::MoveUpToTop()
{
	QModelIndex index = m_ListView->currentIndex();
	if(index.isValid() && index.row()>0)
	{
		m_StringList.move(index.row(),0);
		m_ListModel->setStringList(m_StringList);
		m_ListView->setCurrentIndex(m_ListModel->index(0));
	}
}

void AddItem::MoveDownToBotton()
{
	QModelIndex index = m_ListView->currentIndex();
	if(index.isValid() && index.row()>=0 && (index.row()<m_ListModel->rowCount()-1))
	{
		int bottomPos = m_ListModel->rowCount()-1;
		m_StringList.move(index.row(),bottomPos);
		m_ListModel->setStringList(m_StringList);
		m_ListView->setCurrentIndex(m_ListModel->index(bottomPos));
	}

}

void AddItem::Synchronous()
{
	m_StringList.clear();
	m_ListModel->setStringList(m_StringList);

	QMapIterator<int, QString> it(m_ItemMap);
	while (it.hasNext())
	{
		it.next();
		m_StringList += it.value();
	}
	m_ListModel->setStringList(m_StringList);
	m_TreeModel->ResetTreeModel(m_StringList);
	this->SetBtnEnableOrDisable();
}

void AddItem::accept()
{
	if(m_StringList.isEmpty()) 
	{
		m_ItemMap.clear();
	}
	QMap<int,QString> itemMap;
	int count = m_StringList.count();
	for(int i=0;i<count;i++)
	{
		itemMap.insert(i,m_StringList[i]);
	}
	if(m_ItemMap!=itemMap)
	{
		m_ItemMap.clear();
		QMapIterator<int,QString> it(itemMap);
		while (it.hasNext())
		{
			it.next();
			m_ItemMap.insert(it.key(),it.value());
		}
	}
	QDialog::accept();
}

void AddItem::SetBtnEnableOrDisable()
{
	if(m_TreeModel->rowCount()==0)
	{
		m_BtnAdd->setEnabled(false);
		m_BtnAddAll->setEnabled(false);
	}
	else
	{
		m_BtnAdd->setEnabled(true);
		m_BtnAddAll->setEnabled(true);
	}

	if(m_ListModel->rowCount()==0)
	{
		m_BtnDelete->setEnabled(false);
		m_BtnDeleteAll->setEnabled(false);
		m_BtnUp->setEnabled(false);
		m_BtnTop->setEnabled(false);
		m_BtnDown->setEnabled(false);
		m_BtnBottom->setEnabled(false);
	}
	else
	{
		m_BtnDelete->setEnabled(true);
		m_BtnDeleteAll->setEnabled(true);
		m_BtnUp->setEnabled(true);
		m_BtnTop->setEnabled(true);
		m_BtnDown->setEnabled(true);
		m_BtnBottom->setEnabled(true);
	}
}

void AddItem::SetSizeAnimation(const QSize& beginSize,const QSize& endSize)
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
	animation->setDuration(500);
	animation->setStartValue(beginSize);
	animation->setEndValue(endSize);
	animation->start();
}
