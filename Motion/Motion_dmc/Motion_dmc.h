#pragma once

#include "motion_dmc_global.h"
#include <QObject>
#include <QMutex>
#include <QSharedPointer>
#include "../../include/Motion.h"


class Axis;

#define  MOTION_INSTANCE Motion_dmc::instance()

class MOTION_DMC_EXPORT Motion_dmc :public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<Motion_dmc>& instance();
	~Motion_dmc();

	int		InitBoard();
	int		InitAllCard();	

	void	Deinit();
	int		Reset();

	int		Axis_Reset(quint16 cardIndex, quint16 axisIndex);
	int		Axis_Home(quint16 cardIndex, quint16 axisIndex);
	int		Axis_WaiteHome(quint16 cardIndex, quint16 axisIndex);

	int		Axis_WaiteHome(quint16 cardIndex, quint16 axisIndex,int waitTime); //等待回原结束，等待时间到达，停止轴运动
	int     Axis_WaitHome(quint16 cardIndex, quint16 axisIndex, double curPos, double len); //等待回原结束，轴移动超过len距离，停止轴
	int		Axis_Home_Finished(quint16 cardIndex, quint16 axisIndex);
	int		Axis_Is_Moving(quint16 cardIndex, quint16 axisIndex);		    //1运动中 0就绪

	int		Move_Pos(quint16 cardIndex, quint16 axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0);
	int		Move_Offset(quint16 cardIndex, quint16 axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0);
	int		Move_Jog(quint16 cardIndex, quint16 axisIndex, int dir, double vel = 0, double acc = 0, double dec = 0);  //dir 0 负方向 1 正方向
	int		Axis_Stop(quint16 cardIndex, quint16 axisIndex, int stopType);

	int     ReadInBit_Alarm(quint16 cardIndex, quint16 axisInx, short &val);					   
	int     ReadInBit_LimitN(quint16 cardIndex, quint16 axisInx, short &val);					
	int     ReadInBit_LimitP(quint16 cardIndex, quint16 axisInx, short &val);					
	int     ReadInBit_Origin(quint16 cardIndex, quint16 axisInx, short &val);					 
	int     ReadInBit_Ready(quint16 cardIndex, quint16 axisInx, short &val);					 
	int     ReadInBit_Inplace(quint16 cardIndex, quint16 axisInx, short &val);		//读取卡到位信号
	int     ReadInBit_Enable(quint16 cardIndex, quint16 axisInx, short &val);		
	int     writeOutBit_Enable(quint16 cardIndex, quint16 axisInx,short val);	

	int     ReadInBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType);
	int     ReadOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType);
	int     writeOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex,  short val, int cardType);

	int     Set_Current_Pos(quint16 cardIndex, quint16 axisIndex, double pos);	//设置该轴位置
	int		Get_Current_Pos(quint16 cardIndex, quint16 axisIndex, double &val);	//获取当前位置
	int		Get_Panning_Pos(quint16 cardIndex, quint16 axisIndex, double &val);	//获取规划位置

	int		CreateCrd(quint16 *pCardIndex, quint16 *pAxisIndex, quint16 axisCnt);
	int		AddLinePos(int crdID, double *ppos, TSpeed* pspeed);
	int		AddArcPos(int crdID, double *ppos1, double *ppos2, double *ppos3, TSpeed* pspeed);
	int		CrdStartMove(int crdID);
	int		CrdStatus(int crdID, short *pRun, long *pSegment);
	int		ClearCrdData(int crdID);
	int		GetAxisType(quint16 cardIndex, quint16 axisIndex);	//获取轴类型

protected:
	Axis*	GetAxis(quint16 cardIndex, quint16 axisIndex);
	const	AxisParam* GetAxisParam(quint16 cardIndex, quint16 axisIndex);
	Coord*	FindCrd(int crdID);     //通过ID查找坐标系
	Coord*	GetCrd(quint16 cardIndex, int crdID); //通过card+ID获取坐标系,若无，则新建

public slots :
	void onCardInfoChanged(QVector<CardInfo> cardInfo);
	void onExtCardInfoChanged(QVector<ExtIOCard> extCardInfo);
	void onAppExit();

private:
	Motion_dmc();
	static QMutex m_insMutex;
	static QSharedPointer<Motion_dmc>  m_pInstance;
	QVector<CardInfo> m_vecCardInfo;

	Coord*	m_pCoord; //已经创建成功的坐标系
	Card*	m_pCard[8];
	int		m_realCardCnt;
	int		m_errorCode;
	bool	m_bInit;	//是否已经初始化运动控制卡
};
