#pragma once

#include <QThread>
#include <QSemaphore>
#include <vector>
#include <QtConcurrent/QtConcurrent>
#include "../../include/Common.h"
#include "../../include/LTDMC.h"
#include "../../include/Error.h"
#include "../../include/Motion.h"
#include "../../Utility/System/Log.h"
#include "Axis.h"

using std::vector;


class Card
{
public:

	Card(quint16 cardID, quint16 axisCnt);
	virtual ~Card();

	short	Init(const std::vector<AxisParam> &vecAxisParam);
	Axis*	GetAxis(quint16 index);
	int		AxisReset(quint16 axisIndex);
	int		AxisHome(quint16 axisIndex);
	int		AxisIsMoving(quint16 axisIndex);
	int		AxisWaitHome(quint16 axisIndex);
	int		AxisWaitHome(quint16 axisIndex, int waitTime);
	int     AxisWaitHome(quint16 axisIndex, double curPos, double len);
	int		AxisSetPos(quint16 axisIndex, double pos);
	int		MovePos(quint16 axisIndex, double pos, double vel, double acc, double dec);
	int		MoveOffset(quint16 axisIndex, double pos, double vel, double acc, double dec);
	int		MoveJog(quint16 axisIndex, int dir, double vel, double acc, double dec);
	int		AxisStop(quint16 axisIndex, int stopType);   //停止一个轴运动
	int		CreateCrd(quint16 *pAxisIndex, quint16 axisCnt);  //创建坐标系, 成功返回坐标系ID
	int		ClearCrdData(unsigned int crdID);   //清空坐标系缓冲区
	int		StartCP(quint16 crdID);		//启动连续插补
	int		CrdStatus(quint16 crdID, short *pRun, long *pSegment);  //获取坐标系状态
	int		AddArcPos(quint16 crdID, double *ppos1, double *ppos2, double *ppos3, TSpeed* pspeed);
	int		AddLinePos(quint16 crdID, double *ppos, TSpeed* pspeed);
	int		getErrorCode() { return m_errorCode; }

protected:
	int		IsCrdMoving(quint16 crdID);			 //坐标系是否在运动中
	int		AddPos(quint16 crdID, TMovept& pt);   //增加一个插补段
	void	StopCp(quint16 crdID);	//停止插补运动
	int		CloseCrd(quint16 crdID); //关闭坐标系
    bool	IsSamePos(long* pos1, long* pos2, int axisCnt); //判断两个位置是否一样
    int		CalcArcPos(long* pos1, long* pos2, long* pos3, int axisCnt, long& axisX, long& axisY);  //通过位置调整圆弧插补数据
    void	CalcCenter(long* pos1, long* pos2, long* pos3, long &x, long &y, double&r); //3个点计算圆心，数组只取前两个
    int		CalcDir(long *pos1, long* pos2, long* pos3);   //判断一段圆弧方向，1 顺时针 -1 逆时针
	short	GetAxisInCrd(quint16 axisIndex);
	int		ThreadMoveCP(Card *card,TCool *pCool);

private:
	EM_ERR_CODE		m_errorCode;
	quint16	m_cardID;			//卡ID
	quint16	m_axisCnt;			//轴数量

    QMutex			m_mutex;			//临界区
    TCool			m_stCool[COOL_CNT];	//坐标系
	Axis**			m_pAxis;			//轴数组类指针
};

