#include "Motion_dmc.h"
#include "Card.h"
#include "Axis.h"
#include "IOC0640.h"
#include "Io.h"
#include "../../include/Motion.h"
#include "../../include/Common.h"
#include "../../include/LTDMC.h"
#include "../../Utility/Utility/Utility.h"
#include "../../Utility/System/Config.h"
#include <math.h>
#include <algorithm>  

QMutex Motion_dmc::m_insMutex;
QSharedPointer<Motion_dmc> Motion_dmc::m_pInstance;

Motion_dmc::Motion_dmc()
{
	m_bInit             = false;
	m_realCardCnt       = 0;

	for (int i = 0; i < 8; i++)
	{
		m_pCard[i] = nullptr;
	}

	CONFIG_INSTANCE->getCardInfo(m_vecCardInfo);

	InitAllCard();
	connect(CONFIG_INSTANCE.data(), &Config::cardInfoChanged,      this, &Motion_dmc::onCardInfoChanged);
	connect(CONFIG_INSTANCE.data(), &Config::extIOCardInfoChanged, this, &Motion_dmc::onExtCardInfoChanged);
}

QSharedPointer<Motion_dmc>& Motion_dmc::instance()
{
	if (m_pInstance.isNull())
	{
		QMutexLocker mutexLocker(&m_insMutex);
		if (m_pInstance.isNull())
			m_pInstance = QSharedPointer<Motion_dmc>(new Motion_dmc());
	}
	return m_pInstance;
}

Motion_dmc::~Motion_dmc()
{
	Deinit();
}

int Motion_dmc::Reset()
{
	short ret = dmc_board_reset();
	LOG_INFO("Motion_dmc call dmc_board_reset().");
	if (ret)
	{
		LOG_ERR("dmc_board_reset return error %d", ret);
		return ERR_CARD_RESET;
	}

	ret = dmc_board_close();
	LOG_INFO("Motion_dmc call dmc_board_close().");
	if (ret)
	{
		LOG_ERR("dmc_board_close return error %d", ret);
		return ERR_CARD_RESET;
	}

	sleepMS(5000);    //必须等待5s以上才能初始化

	return RETURN_OK;
}

int Motion_dmc::InitBoard()
{
	short ret = 0;
	WORD cardCnt = 0;

	RETURN_CHK(!m_bInit, RETURN_OK);

	m_realCardCnt = dmc_board_init();
	LOG_INFO("Motion_dmc call dmc_board_init(),Card count:%d", m_realCardCnt);

	if (0 == m_realCardCnt)
	{
		LOG_ERR("Motion_dmc call dmc_board_init(),Card count:%d", m_realCardCnt);
		return ERR_NO_CARD;
	}
	else if (m_realCardCnt < 0)
	{
		return ERR_INIT_MOTOR;
	}

	int extCardNum = ioc_board_init();
	LOG_INFO("Motion_dmc call ioc_board_init(),ExtCard count:%d", extCardNum);

	IO_INSTANCE->setCardNum(m_realCardCnt);
	IO_INSTANCE->setExtCardNum(extCardNum);

	m_pCoord = new Coord[m_realCardCnt * CRD_AXIS_CNT];

	m_bInit = true;

	return RETURN_OK;
}

int Motion_dmc::InitAllCard()
{
	long  readVal = 0;
	int   ret = 0;
	short curExtIndex = 0;  //扩展卡从0开始计算

	ret = InitBoard();

	RETURN_CHK(!ret, ret);

	for (int i = 0; i < m_vecCardInfo.size(); i++)
	{
		Card* pCard = new Card(i, m_vecCardInfo[i].vecAxisParam.size());

		ret = pCard->Init(m_vecCardInfo[i].vecAxisParam);
		if (ret)
		{
			LOG_ERR("init card return error:%d", ret);
			Deinit();
			return ret;
		}

		//初始化坐标系
		m_pCoord[i * 2].cardIndex = i;
		m_pCoord[i * 2].index = 0;
		m_pCoord[i * 2 + 1].cardIndex = i;
		m_pCoord[i * 2 + 1].index = 1;

		m_pCard[i] = pCard;
	}

	return 0;
}

void Motion_dmc::Deinit()
{
	for (int i = 0; i < 8; i++)
	{
		FREE_ANY(m_pCard[i]);
	}
	dmc_board_close();  //关闭卡
	ioc_board_close();  //关闭扩展卡
	LOG_INFO("Motion_dmc call dmc_board_close() ioc_board_close().");
}

Axis *Motion_dmc::GetAxis(quint16 cardIndex, quint16 axisIndex)
{
	CardInfo cardInfo;
	RETURN_CHK(cardIndex < m_realCardCnt, nullptr);
	RETURN_CHK(m_pCard[cardIndex], nullptr);
	return m_pCard[cardIndex]->GetAxis(axisIndex);
}

const AxisParam *Motion_dmc::GetAxisParam(quint16 cardIndex, quint16 axisIndex)
{
	Axis* pAxis = GetAxis(cardIndex, axisIndex);
	RETURN_CHK(pAxis, NULL);
	return pAxis->GetParam();
}

int Motion_dmc::Axis_Reset(quint16 cardIndex, quint16 axisIndex)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisReset(axisIndex) ? RETURN_OK : ERR_AXIS_RESET;
}

int Motion_dmc::Axis_Home(quint16 cardIndex, quint16 axisIndex)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisHome(axisIndex);
}

int Motion_dmc::Axis_WaiteHome(quint16 cardIndex, quint16 axisIndex)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisWaitHome(axisIndex);
}

int	Motion_dmc::Axis_WaiteHome(quint16 cardIndex, quint16 axisIndex, int waitTime)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisWaitHome(axisIndex, waitTime);
}

int Motion_dmc::Axis_WaitHome(quint16 cardIndex, quint16 axisIndex, double curPos, double len)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisWaitHome(axisIndex, curPos,len);
}

int Motion_dmc::Axis_Is_Moving(quint16 cardIndex, quint16 axisIndex)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisIsMoving(axisIndex);
}

int Motion_dmc::Set_Current_Pos(quint16 cardIndex, quint16 axisIndex, double pos)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisSetPos(axisIndex, pos);
}

int Motion_dmc::Axis_Home_Finished(quint16 cardIndex, quint16 axisIndex)
{
	Axis* pAxis = GetAxis(cardIndex, axisIndex);
	RETURN_CHK(pAxis, NULL);
	return pAxis->HomeFinished();
}

int Motion_dmc::Move_Pos(quint16 cardIndex, quint16 axisIndex, double pos, double vel, double acc, double dec)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->MovePos(axisIndex, pos, vel, acc, dec);
}

int Motion_dmc::Move_Offset(quint16 cardIndex, quint16 axisIndex, double pos, double vel, double acc, double dec)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->MoveOffset(axisIndex, pos, vel, acc, dec);
}

int Motion_dmc::Move_Jog(quint16 cardIndex, quint16 axisIndex, int dir, double vel, double acc, double dec)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->MoveJog(axisIndex, dir, vel, acc, dec);
}

int Motion_dmc::Axis_Stop(quint16 cardIndex, quint16 axisIndex, int stopType)
{
	Card *pCard = m_pCard[cardIndex];
	RETURN_CHK(pCard, ERR_INVALID_AXIS);
	return pCard->AxisStop(axisIndex, stopType);
}

int Motion_dmc::ReadInBit_Alarm(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_Alarm(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit_LimitN(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_LimitN(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit_LimitP(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_LimitP(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit_Origin(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_Origin(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit_Ready(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_Ready(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit_Inplace(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_Inplace(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit_Enable(quint16 cardIndex, quint16 axisInx, short &val)
{
	return IO_INSTANCE->readInBit_Enable(cardIndex, axisInx, val);
}

int Motion_dmc::writeOutBit_Enable(quint16 cardIndex, quint16 axisInx,  short val)
{
	return IO_INSTANCE->writeOutBit_Enable(cardIndex, axisInx, val);
}

int Motion_dmc::ReadInBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType)
{
	return IO_INSTANCE->readInBit(cardIndex, cardNode, IOIndex, val, cardType);
}

int Motion_dmc::ReadOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType)
{
	return IO_INSTANCE->readOutBit(cardIndex, cardNode, IOIndex, val, cardType);
}

int Motion_dmc::writeOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short val, int cardType)
{
	return IO_INSTANCE->writeOutBit(cardIndex, cardNode, IOIndex, val, cardType);
}

int Motion_dmc::Get_Current_Pos(quint16 cardIndex, quint16 axisIndex, double &val)
{
	val = 0.0;
	Axis *pAxis = GetAxis(cardIndex, axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	pAxis->GetCurPos(val);
	return RETURN_OK;
}

int Motion_dmc::Get_Panning_Pos(quint16 cardIndex, quint16 axisIndex, double &val)
{
	val = 0.0;
	Axis *pAxis = GetAxis(cardIndex, axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	pAxis->GetPlanPos(val);
	return RETURN_OK;
}

Coord* Motion_dmc::FindCrd(int crdID)
{
	bool bFind = false;
	Coord* pCrd = (Coord*)crdID;
	for (short i = 0; i < m_realCardCnt * 2; i++)
	{
		if (pCrd->cardIndex == m_pCoord[i].cardIndex
			&& pCrd->index == m_pCoord[i].index)
		{
			bFind = true;
			break;
		}
	}

	return bFind ? pCrd : NULL;
}

Coord* Motion_dmc::GetCrd(quint16 cardIndex, int crdID)
{
	Coord* pCrd = NULL;
	for (short i = 0; i < m_realCardCnt * 2; i++)
	{
		if (cardIndex == m_pCoord[i].cardIndex && crdID == m_pCoord[i].index)
		{
			pCrd = &m_pCoord[i];
			break;
		}
	}

	return pCrd;
}

int Motion_dmc::CreateCrd(quint16 *pCardIndex, quint16 *pAxisIndex, quint16 axisCnt)
{
	Coord* pCrd = NULL;
	int ires = 0;
	quint16 cardIndex = 0;

	if (axisCnt <= 1 || axisCnt > 4 || !pCardIndex || !pAxisIndex)
	{
		m_errorCode = ERR_INPUT_PARAM;
		return -1;
	}

	cardIndex = pCardIndex[0];
	if (cardIndex >= m_realCardCnt)
	{//卡索引必须合法
		LOG_ERR("CreateCrd cardIndex=%d but card Count is %d", cardIndex, m_realCardCnt);
		m_errorCode = ERR_INPUT_PARAM;
		return -1;
	}
	for (int i = 1; i < axisCnt; i++)
	{//必须在同一张卡
		if (cardIndex != pCardIndex[i])
		{
			m_errorCode = ERR_INPUT_PARAM;
			return -1;
		}
	}

	RETURN_CHK(m_pCard[pCrd->cardIndex], ERR_INVALID_CARD);

	ires = m_pCard[pCrd->cardIndex]->CreateCrd(pAxisIndex, axisCnt);

	RETURN_CHK(-1 != ires, -1);

	pCrd = GetCrd(cardIndex, ires);

	return pCrd ? (int)pCrd : -1;
}

int Motion_dmc::AddLinePos(int crdID, double *ppos, TSpeed* pspeed)
{
	Coord* pCrd = FindCrd(crdID);

	RETURN_CHK(pCrd, ERR_GET_CRD);

	RETURN_CHK(m_pCard[pCrd->cardIndex], ERR_INVALID_CARD);

	return m_pCard[pCrd->cardIndex]->AddLinePos(pCrd->index, ppos, pspeed);
}

int Motion_dmc::AddArcPos(int crdID, double *ppos1, double *ppos2, double *ppos3, TSpeed* pspeed)
{
	Coord* pCrd = FindCrd(crdID);

	RETURN_CHK(pCrd, ERR_GET_CRD);

	RETURN_CHK(m_pCard[pCrd->cardIndex], ERR_INVALID_CARD);

	return m_pCard[pCrd->cardIndex]->AddArcPos(pCrd->index, ppos1, ppos2, ppos3, pspeed);
}

int Motion_dmc::CrdStartMove(int crdID)
{
	Coord* pCrd = FindCrd(crdID);

	RETURN_CHK(pCrd, ERR_GET_CRD);

	RETURN_CHK(m_pCard[pCrd->cardIndex], ERR_INVALID_CARD);

	return m_pCard[pCrd->cardIndex]->StartCP(pCrd->index);
}

int Motion_dmc::CrdStatus(int crdID, short *pRun, long *pSegment)
{
	Coord* pCrd = FindCrd(crdID);

	RETURN_CHK(pCrd, ERR_GET_CRD);

	RETURN_CHK(m_pCard[pCrd->cardIndex], ERR_INVALID_CARD);

	return m_pCard[pCrd->cardIndex]->CrdStatus(pCrd->index, pRun, pSegment);
}

int Motion_dmc::ClearCrdData(int crdID)
{
	Coord* pCrd = FindCrd(crdID);

	RETURN_CHK(pCrd, ERR_GET_CRD);

	RETURN_CHK(m_pCard[pCrd->cardIndex], ERR_INVALID_CARD);

	return m_pCard[pCrd->cardIndex]->ClearCrdData(pCrd->index);
}

int Motion_dmc::GetAxisType(quint16 cardIndex, quint16 axisIndex)
{
	const AxisParam * axisParam = NULL;
	axisParam = GetAxisParam(cardIndex, axisIndex);
	if (NULL == axisParam)
	{
		return 1;//默认步进
	}
	return axisParam->motorType;
}

void Motion_dmc::onCardInfoChanged(QVector<CardInfo> cardInfo)
{
	m_vecCardInfo = cardInfo;

	for (int i = 0; i < m_vecCardInfo.size();i++)
	{
		if (m_pCard[i] == nullptr) continue;

		for (int j = 0; j< m_vecCardInfo[i].vecAxisParam.size();j++)
		{
			if (m_pCard[i]->GetAxis(j) == nullptr) continue;

			AxisParam para = m_vecCardInfo[i].vecAxisParam[j];
			m_pCard[i]->GetAxis(j)->Reset();		//停止轴运动
			m_pCard[i]->GetAxis(j)->Init(&para);
		}
	}
}

void Motion_dmc::onExtCardInfoChanged(QVector<ExtIOCard> extCardInfo)
{
	//m_vecExtIOCardInfo = extCardInfo;
}

void Motion_dmc::onAppExit()
{
	//Deinit();
}
