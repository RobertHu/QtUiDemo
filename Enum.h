#ifndef ENUM_H
#define ENUM_H

//��ת�ؼ�����;
enum GridItemEnum
{  
	GRAP = 2,				//�ؼ����ܼ�϶���ɸ���;
	TRUNOVERRATE = 10,		//��ת�ٶ�,�ɸ���;	
	WIDTH = 270+2*GRAP,		//+2*GRAP���ܸ��ģ�ֻ�ܸ�ǰ�������,�罫400��Ϊ300��500����ͬ;
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