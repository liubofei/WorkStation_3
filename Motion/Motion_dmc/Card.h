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
	int		AxisStop(quint16 axisIndex, int stopType);   //ֹͣһ�����˶�
	int		CreateCrd(quint16 *pAxisIndex, quint16 axisCnt);  //��������ϵ, �ɹ���������ϵID
	int		ClearCrdData(unsigned int crdID);   //�������ϵ������
	int		StartCP(quint16 crdID);		//���������岹
	int		CrdStatus(quint16 crdID, short *pRun, long *pSegment);  //��ȡ����ϵ״̬
	int		AddArcPos(quint16 crdID, double *ppos1, double *ppos2, double *ppos3, TSpeed* pspeed);
	int		AddLinePos(quint16 crdID, double *ppos, TSpeed* pspeed);
	int		getErrorCode() { return m_errorCode; }

protected:
	int		IsCrdMoving(quint16 crdID);			 //����ϵ�Ƿ����˶���
	int		AddPos(quint16 crdID, TMovept& pt);   //����һ���岹��
	void	StopCp(quint16 crdID);	//ֹͣ�岹�˶�
	int		CloseCrd(quint16 crdID); //�ر�����ϵ
    bool	IsSamePos(long* pos1, long* pos2, int axisCnt); //�ж�����λ���Ƿ�һ��
    int		CalcArcPos(long* pos1, long* pos2, long* pos3, int axisCnt, long& axisX, long& axisY);  //ͨ��λ�õ���Բ���岹����
    void	CalcCenter(long* pos1, long* pos2, long* pos3, long &x, long &y, double&r); //3�������Բ�ģ�����ֻȡǰ����
    int		CalcDir(long *pos1, long* pos2, long* pos3);   //�ж�һ��Բ������1 ˳ʱ�� -1 ��ʱ��
	short	GetAxisInCrd(quint16 axisIndex);
	int		ThreadMoveCP(Card *card,TCool *pCool);

private:
	EM_ERR_CODE		m_errorCode;
	quint16	m_cardID;			//��ID
	quint16	m_axisCnt;			//������

    QMutex			m_mutex;			//�ٽ���
    TCool			m_stCool[COOL_CNT];	//����ϵ
	Axis**			m_pAxis;			//��������ָ��
};

