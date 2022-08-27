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

	int		Axis_WaiteHome(quint16 cardIndex, quint16 axisIndex,int waitTime); //�ȴ���ԭ�������ȴ�ʱ�䵽�ֹͣ���˶�
	int     Axis_WaitHome(quint16 cardIndex, quint16 axisIndex, double curPos, double len); //�ȴ���ԭ���������ƶ�����len���룬ֹͣ��
	int		Axis_Home_Finished(quint16 cardIndex, quint16 axisIndex);
	int		Axis_Is_Moving(quint16 cardIndex, quint16 axisIndex);		    //1�˶��� 0����

	int		Move_Pos(quint16 cardIndex, quint16 axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0);
	int		Move_Offset(quint16 cardIndex, quint16 axisIndex, double pos, double vel = 0, double acc = 0, double dec = 0);
	int		Move_Jog(quint16 cardIndex, quint16 axisIndex, int dir, double vel = 0, double acc = 0, double dec = 0);  //dir 0 ������ 1 ������
	int		Axis_Stop(quint16 cardIndex, quint16 axisIndex, int stopType);

	int     ReadInBit_Alarm(quint16 cardIndex, quint16 axisInx, short &val);					   
	int     ReadInBit_LimitN(quint16 cardIndex, quint16 axisInx, short &val);					
	int     ReadInBit_LimitP(quint16 cardIndex, quint16 axisInx, short &val);					
	int     ReadInBit_Origin(quint16 cardIndex, quint16 axisInx, short &val);					 
	int     ReadInBit_Ready(quint16 cardIndex, quint16 axisInx, short &val);					 
	int     ReadInBit_Inplace(quint16 cardIndex, quint16 axisInx, short &val);		//��ȡ����λ�ź�
	int     ReadInBit_Enable(quint16 cardIndex, quint16 axisInx, short &val);		
	int     writeOutBit_Enable(quint16 cardIndex, quint16 axisInx,short val);	

	int     ReadInBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType);
	int     ReadOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType);
	int     writeOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex,  short val, int cardType);

	int     Set_Current_Pos(quint16 cardIndex, quint16 axisIndex, double pos);	//���ø���λ��
	int		Get_Current_Pos(quint16 cardIndex, quint16 axisIndex, double &val);	//��ȡ��ǰλ��
	int		Get_Panning_Pos(quint16 cardIndex, quint16 axisIndex, double &val);	//��ȡ�滮λ��

	int		CreateCrd(quint16 *pCardIndex, quint16 *pAxisIndex, quint16 axisCnt);
	int		AddLinePos(int crdID, double *ppos, TSpeed* pspeed);
	int		AddArcPos(int crdID, double *ppos1, double *ppos2, double *ppos3, TSpeed* pspeed);
	int		CrdStartMove(int crdID);
	int		CrdStatus(int crdID, short *pRun, long *pSegment);
	int		ClearCrdData(int crdID);
	int		GetAxisType(quint16 cardIndex, quint16 axisIndex);	//��ȡ������

protected:
	Axis*	GetAxis(quint16 cardIndex, quint16 axisIndex);
	const	AxisParam* GetAxisParam(quint16 cardIndex, quint16 axisIndex);
	Coord*	FindCrd(int crdID);     //ͨ��ID��������ϵ
	Coord*	GetCrd(quint16 cardIndex, int crdID); //ͨ��card+ID��ȡ����ϵ,���ޣ����½�

public slots :
	void onCardInfoChanged(QVector<CardInfo> cardInfo);
	void onExtCardInfoChanged(QVector<ExtIOCard> extCardInfo);
	void onAppExit();

private:
	Motion_dmc();
	static QMutex m_insMutex;
	static QSharedPointer<Motion_dmc>  m_pInstance;
	QVector<CardInfo> m_vecCardInfo;

	Coord*	m_pCoord; //�Ѿ������ɹ�������ϵ
	Card*	m_pCard[8];
	int		m_realCardCnt;
	int		m_errorCode;
	bool	m_bInit;	//�Ƿ��Ѿ���ʼ���˶����ƿ�
};
