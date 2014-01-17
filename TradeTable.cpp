#include "TradeTable.h"

#include <QMouseEvent>
#include <QMenu>
#include <QScrollBar>
#include <QJsonObject>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>

#include <QFile>
#include <QDir>

#include "TradeHeaderView.h"


TradeTable::TradeTable(QList<TradeItem>& itemList,const QString& columnJsonFile,QWidget* parent):m_ItemList(itemList),QTableView(parent)
{
	m_ColumnJsonFile = columnJsonFile;
	this->LoadColumnJson();
		
	m_Delegate = new TableItemDelegate(m_ColumnMap);
	m_TableModel = new TableModel(itemList,m_ColumnMap,this);

	this->setModel(m_TableModel);
	this->setItemDelegate(m_Delegate); //在单元格中显示图片;
	this->setHorizontalHeader(new TradeHeaderView(m_ColumnMap,Qt::Horizontal,this));//设置列标题;

	this->setSelectionBehavior(QAbstractItemView::SelectItems);//选择一项;

	this->verticalHeader()->hide();	  //隐藏垂直方向上的标头; //this->verticalHeader()->setVisible(false);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	this->resizeColumnsToContents(); //列宽随列标题内容而缩放,下类同;
	this->resizeRowsToContents();

	this->setAlternatingRowColors(true);  //交替行颜色; 
	QString tableBgStyle = "QHeaderView::section{height:28px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 #555555);color: black;padding-left: 4px;border: 1px solid #6c6c6c;}"
						   "QTableView{font-size:18px; color:black; background-color:white;alternate-background-color:rgb(192,192,192);}";
	this->setStyleSheet(tableBgStyle);

	this->setMouseTracking(true);	//鼠标经过时高亮显示;

	QString vScrollBarStyle = "QScrollBar:vertical{ width:20px; background:rgba(0,0,0,0%); margin:0px,0px,0px,0px; padding-top:21px; padding-bottom:21px; }"
							  "QScrollBar::handle:vertical{width:20px;background:rgba(0,0,0,20%);border-radius:4px;min-height:20;}"
							  "QScrollBar::handle:vertical:hover{width:20px;background:qlineargradient(x1:0, y1:0, x2:1, y2:0, stop: 0 #eeeeee, stop: 1 #555555);border-radius:4px;min-height:20;}"
							  "QScrollBar::add-line:vertical{height:21px;width:20px;border-image:url(images/ListTab/3.png);subcontrol-position:bottom;}"
							  "QScrollBar::sub-line:vertical{height:21px;width:20px;border-image:url(images/ListTab/1.png);subcontrol-position:top;}"
							  "QScrollBar::add-line:vertical:hover{height:21px;width:20px;border-image:url(images/ListTab/4.png);subcontrol-position:bottom;}"
							  "QScrollBar::sub-line:vertical:hover{height:21px;width:20px;border-image:url(images/ListTab/2.png);subcontrol-position:top;}"
							  "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(0,0,0,10%);border-radius:4px;}";

 	QString hScrollBarStyle = "QScrollBar:horizontal{ height:20px; background:rgba(0,0,0,0%); margin:0px,0px,0px,0px; padding-left:21px; padding-right:21px; }"
							  "QScrollBar::handle:horizontal{height:20px;background:rgba(0,0,0,20%);border-radius:4px;min-width:20;}"
							  "QScrollBar::handle:horizontal:hover{width:20px;background:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #eeeeee, stop: 1 #555555);border-radius:4px;min-width:20;}"
							  "QScrollBar::add-line:horizontal{width:21px;height:20px;border-image:url(images/ListTab/30.png);subcontrol-position:right;}"
							  "QScrollBar::sub-line:horizontal{width:21px;height:20px;border-image:url(images/ListTab/10.png);subcontrol-position:left;}"
							  "QScrollBar::add-line:horizontal:hover{width:21px;height:20px;border-image:url(images/ListTab/40.png);subcontrol-position:right;}"
							  "QScrollBar::sub-line:horizontal:hover{width:21px;height:20px;border-image:url(images/ListTab/20.png);subcontrol-position:left;}"
							  "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal{background:rgba(0,0,0,10%);border-radius:4px;}";

	this->horizontalScrollBar()->setStyleSheet(hScrollBarStyle);
	this->verticalScrollBar()->setStyleSheet(vScrollBarStyle);

	this->setContextMenuPolicy(Qt::ActionsContextMenu);	//菜单;

	for(int i=0;i<m_ColumnMap.count();i++)
	{
		if(!m_ColumnMap[i].IsShow())
			setColumnHidden(i,true);
	}
}
TradeTable::~TradeTable()
{
	this->SaveColumnJson();
}
void TradeTable::mousePressEvent(QMouseEvent * event)
{  
	QModelIndex modelIndex = indexAt(event->pos());
	if (event->button() == Qt::RightButton)
	{
		QMenu * popupMenu = new QMenu(this);
		QString menuStyle = "QMenu { font-size:18px; color:blue; background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop: 0 #cccccc, stop: 1 #555555);}" ;
		popupMenu->setStyleSheet(menuStyle);
		m_SelectedIndex = modelIndex.row();
		if(modelIndex.isValid() && modelIndex.row()>=0)
		{
			this->setSelection(this->visualRect(modelIndex),QItemSelectionModel::SelectCurrent);
			popupMenu->addAction(tr("&Order"), this, SLOT(Order()),QKeySequence(Qt::CTRL + Qt::Key_O));
			popupMenu->addAction(tr("&Chart"),this,SLOT(Chart()),QKeySequence(Qt::CTRL + Qt::Key_C));
			popupMenu->addSeparator();
			popupMenu->addAction(tr("&Delete"),this,SLOT(Delete()),QKeySequence(Qt::CTRL + Qt::Key_D));
			popupMenu->addAction(tr("&Add"),this,SLOT(Add()),QKeySequence(Qt::CTRL + Qt::Key_A));
			popupMenu->addAction(tr("&Move&Up"),this,SLOT(MoveUp()),QKeySequence(Qt::CTRL + Qt::Key_M,Qt::CTRL + Qt::Key_U));
			popupMenu->addAction(tr("&UpTo&Top"),this,SLOT(UpToTop()),QKeySequence(Qt::CTRL + Qt::Key_U,Qt::CTRL + Qt::Key_T));
			popupMenu->addAction(tr("&Move&Down"),this,SLOT(MoveDown()),QKeySequence(Qt::CTRL + Qt::Key_M,Qt::CTRL + Qt::Key_D));
			popupMenu->addAction(tr("&DownTo&Bottom"),this,SLOT(DownToBottom()),QKeySequence(Qt::CTRL + Qt::Key_D,Qt::CTRL + Qt::Key_B));
		}
		else
		{
			popupMenu->addAction(tr("&Add"),this,SLOT(Add()),QKeySequence(Qt::CTRL + Qt::Key_A));
		}
		popupMenu->exec(event->globalPos());  
	}
	QTableView::mousePressEvent(event);
}
void TradeTable::mouseMoveEvent(QMouseEvent * event)
{
	QModelIndex index = indexAt(event->pos());
	if(index.isValid() && index.row()>=0)
		this->setSelection(this->visualRect(index),QItemSelectionModel::SelectCurrent);
}
void TradeTable::SetHeaderColumnHideOrShow(int column,bool bShow)
{
	this->setColumnHidden(column,!bShow);
}
void TradeTable::SetBold(int index,bool bBold)
{
	m_TableModel->SetFontBold(index,bBold);
}
void TradeTable::SetItalic(int index,bool bItalic)
{
	m_TableModel->SetFontItalic(index,bItalic);
}
void TradeTable::SetFontSize(int index,int fontSize)
{
	m_TableModel->SetFontSize(index,fontSize);
}
void TradeTable::SetFontColor(int index,const QColor& fontColor)
{
	m_TableModel->SetFontColor(index,fontColor);
}

void TradeTable::RealTimeDisplay(const TradeItem& item)
{
	for(int i=0;i<m_ItemList.count();i++)
	{
		if(item.m_TradingCode==m_ItemList[i].m_TradingCode)
		{
			int count = this->model()->rowCount();
			for(int j=0;j<count;j++)
			{
				if(this->model()->index(j,0).data().toString()==item.m_TradingCode)
				{
					m_TableModel->SetUpdatingItem(item);
					
					m_TableModel->SetPerPrice(item.m_TradingCode,m_TableModel->GetItemList()[j].m_CurrentBidPrice);
					this->update();
					QVariant variant;
					m_TableModel->setData(m_TableModel->index(j,1),variant);
					m_TableModel->setData(m_TableModel->index(j,3),variant);
					m_TableModel->setData(m_TableModel->index(j,4),variant);
					return ;
				}
			}
		}
	}

}

void TradeTable::AddSlot()
{
	m_TableModel->ReLoadItemList(m_ItemList);
}
void TradeTable::OrderSlot()
{
	//need not do anything...;
}
void TradeTable::ChartSlot()
{
    //need not do anything...;
}
void TradeTable::DeleteSlot(int index)
{
	m_TableModel->removeRow(index);
}
void TradeTable::MoveUpSlot(int index)
{
	m_TableModel->moveRow(QModelIndex(),index,QModelIndex(),index-1);
}
void TradeTable::UpToTopSlot(int index)
{
	m_TableModel->moveRow(QModelIndex(),index,QModelIndex(),0);
}
void TradeTable::MoveDownSlot(int index)
{
	m_TableModel->moveRow(QModelIndex(),index,QModelIndex(),index+1);
}
void TradeTable::DownToBottomSlot(int index)
{
	m_TableModel->moveRow(QModelIndex(),index,QModelIndex(),m_ItemList.count()-1);
}

void TradeTable::Add()
{
	emit AddSignal();
}
void TradeTable::Order()
{
	emit OrderSignal(m_SelectedIndex);
}
void TradeTable::Chart()
{
	emit ChartSignal(m_SelectedIndex);
}
void TradeTable::Delete()
{
	emit DeleteSignal(m_SelectedIndex);	
}
void TradeTable::MoveUp()
{
	emit MoveUpSignal(m_SelectedIndex);	
}
void TradeTable::UpToTop()
{
	emit UpToTopSignal(m_SelectedIndex);	
}
void TradeTable::MoveDown()
{
	emit MoveDownSignal(m_SelectedIndex);	
}
void TradeTable::DownToBottom()
{
	emit DownToBottomSignal(m_SelectedIndex);	
}

bool TradeTable::SaveColumnJson()
{
	int count = m_ColumnMap.count();
	QJsonArray jsonArray;
	for(int i=0;i<count;i++)
	{
		QJsonObject jsonObject;
		jsonObject.insert("columnText",m_ColumnMap[i].GetColumnText());
		jsonObject.insert("isShow",m_ColumnMap[i].IsShow());
		jsonObject.insert("isForbidHide",m_ColumnMap[i].IsForbidHide());
		jsonObject.insert("isPicture",m_ColumnMap[i].IsPicture());
		jsonArray.append(jsonObject);
	}
	QJsonObject root;
	root.insert("columnSetting",jsonArray);
	QFile file(m_ColumnJsonFile);
	if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
		return false;
	QTextStream stream(&file);
	QJsonDocument jsonDoc;
	jsonDoc.setObject(root);
	stream << jsonDoc.toJson();
	file.close();

	return true;
}

bool TradeTable::LoadColumnJson()
{
	QFile file(m_ColumnJsonFile);
	if(!file.exists())
		return false;
	if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
		return false;
	QTextStream stream(&file);
	QString json = stream.readAll();
	if(json.isEmpty())
		return false;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8());

	QJsonObject jsonObject = jsonDoc.object();
	QJsonArray jsonArray = jsonObject.value("columnSetting").toArray();

	int count = jsonArray.count();
	for(int i=0;i<count;i++)
	{
		QJsonObject columnObject = jsonArray[i].toObject();
		QString columnText = columnObject.value("columnText").toString();
		bool isShow = columnObject.value("isShow").toBool();
		bool isForbidHide = columnObject.value("isForbidHide").toBool();
		bool isPicture = columnObject.value("isPicture").toBool();
		m_ColumnMap.insert(i,ColumnObject(columnText,isShow,isForbidHide,isPicture));		
	}

	return true;
}
