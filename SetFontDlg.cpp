#include "SetFontDlg.h"

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QLayout>

SetFontDlg::SetFontDlg(int logicalIndex,QWidget* parent):m_LogicalIndex(logicalIndex),QDialog(parent)
{	
//	this->setFixedSize(300,400);

	QCheckBox* bold = new QCheckBox("Bold",this);
	QCheckBox* italic = new QCheckBox("Italic",this);	
	QLabel*	   fontSizeLabel = new QLabel("Font Size:",this);
	QSpinBox*  fontSize = new QSpinBox(this);
	QLabel*	   fontColorLabel = new QLabel("Font Color:",this);
	QComboBox* fontColor = new QComboBox(this);

	QHBoxLayout* layout1 = new QHBoxLayout;	QHBoxLayout* layout2 = new QHBoxLayout;
	QHBoxLayout* layout3 = new QHBoxLayout;
	QGridLayout* layout = new QGridLayout;	  
	layout1->addWidget(bold);
	layout1->addWidget(italic);
	layout2->addWidget(fontSizeLabel);
	layout2->addWidget(fontSize);
	layout3->addWidget(fontColorLabel);
	layout3->addWidget(fontColor);
	layout->addLayout(layout1,0,0,Qt::AlignHCenter);
	layout->addLayout(layout2,1,0,Qt::AlignHCenter);
	layout->addLayout(layout3,2,0,Qt::AlignHCenter);
	this->setLayout(layout);
	this->setWindowTitle("Set Font");

	fontSize->setValue(12);
	fontSize->setMinimum(12);
	fontSize->setMaximum(18); 
	fontColor->addItem("Black");
	fontColor->addItem("Red");
	fontColor->addItem("Green");
	fontColor->addItem("Blue");
	fontColor->addItem("Gray");	
	fontColor->setCurrentIndex(0);
	if(logicalIndex==2 || logicalIndex==3 || logicalIndex==4)
		fontColor->setEnabled(false);

	connect(bold,SIGNAL(stateChanged(int)),this,SLOT(SetBold(int)));
	connect(italic,SIGNAL(stateChanged(int)),this,SLOT(SetItalic(int)));
	connect(fontSize,SIGNAL(valueChanged(int)),this,SLOT(SetFontSize(int)));
	connect(fontColor,SIGNAL(currentIndexChanged(int)),this,SLOT(SetFontColor(int)));

	connect(this,SIGNAL(SetBoldSignal(int,bool)),parent->parent(),SLOT(SetBold(int,bool)));
	connect(this,SIGNAL(SetItalicSignal(int,bool)),parent->parent(),SLOT(SetItalic(int,bool)));
	connect(this,SIGNAL(SetFontSizeSignal(int,int)),parent->parent(),SLOT(SetFontSize(int,int)));
	connect(this,SIGNAL(SetFontColorSignal(int,const QColor&)),parent->parent(),SLOT(SetFontColor(int,const QColor&)));
}
void SetFontDlg::SetBold(int status)
{
	bool bBold = false;
	if(status==Qt::Checked)
		bBold = true;
	emit SetBoldSignal(m_LogicalIndex,bBold);
}
void SetFontDlg::SetItalic(int status)
{
	bool bBold = false;
	if(status==Qt::Checked)
		bBold = true;
	emit SetItalicSignal(m_LogicalIndex,bBold);
}
void SetFontDlg::SetFontSize(int fontSize)
{
	emit SetFontSizeSignal(m_LogicalIndex,fontSize);
}
void SetFontDlg::SetFontColor(int fontColor)
{
	QColor color = QColor(Qt::black);
	switch (fontColor)
	{ 
	case 0:
		color = QColor(Qt::black);
		break;
	case 1:
		color = QColor(Qt::red);
		break;
	case 2:
		color = QColor(Qt::green);
		break;
	case 3:
		color = QColor(Qt::blue);
		break;
	case 4:
		color = QColor(Qt::gray);
		break;
	default:
		break;
	}
	emit SetFontColorSignal(m_LogicalIndex,color);
}