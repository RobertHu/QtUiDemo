#ifndef ENUM_H
#define ENUM_H

//翻转控件参数;
enum GridItemEnum
{  
	GRAP = 2,				//控件四周间隙，可更改;
	TRUNOVERRATE = 10,		//翻转速度,可更改;	
	WIDTH = 270+2*GRAP,		//+2*GRAP不能更改，只能改前面的数字,如将400改为300或500，下同;
	HEIGHT = 80+2*GRAP,
};
enum MarkInfo
{
	HIGHTLOW,PRECLOSE,INTERESTCLOSE
};
enum OrderEnum
{
	CONTROLSGRAP = 5,
	MARGINSIZE = 5,
	BIDASKWIDTH = 150,
	BIDASKHEIGHT = 60,
	ORDERLISTMINIWIDTH = 2*BIDASKWIDTH+CONTROLSGRAP,
	
};
enum TrendStatusEnum
{
	KEEP = 0,
	UP = 1,
	DOWN = 2
};

#endif