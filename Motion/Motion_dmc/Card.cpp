#include "Card.h"
#include "../../include/Motion.h"
#include "../../Utility/Utility/Utility.h"

typedef Axis*  PAxis;

Card::Card(quint16 cardID, quint16 axisCnt)
{
	m_cardID = cardID;
	m_axisCnt = axisCnt;
    m_pAxis = new PAxis[axisCnt];    //一个卡最多可以8个轴

    for(quint16 i = 0; i < m_axisCnt; i++)
    {
        m_pAxis[i] = new Axis();
    }

    for(quint16 i = 0; i < COOL_CNT; i++)
    {
		m_stCool[i].samStop.release(0);
		m_stCool[i].samExit.release(0);
        CloseCrd(i);
    }
}

Card::~Card()
{
    for(quint16 i = 0; i < COOL_CNT; i++)
    {
        CloseCrd(i);
	 }
    for (int i = 0; i < m_axisCnt; i++)
    {
        FREE_ANY(m_pAxis[i]);
    }
    FREE_ANY(m_pAxis);
    m_axisCnt = 0;
}

short Card::Init(const std::vector<AxisParam> &vecAxisParam)
{
    int ret = 0;

	QString strName = QString("Config/card_%1.ini").arg(m_cardID);
	QString strPath = CFGDIR(strName);

	strPath.replace("/", "\\");	//老铁，这句话很重要，就得是反斜杠

	ret = dmc_download_configfile(m_cardID, strPath.toStdString().c_str());
	LOG_INFO("Card call dmc_download_configfile(%d, '%s')=%d.", m_cardID, strPath.toStdString().c_str(), ret);
    if (ret)
    {
        LOG_ERR("Card:%d Load config error.%d", m_cardID, ret);
        return ERR_LOAD_CFG;
    }

    for(quint16 i = 0; i < m_axisCnt; i++)
    {
		AxisParam para = vecAxisParam[i];
		ret = m_pAxis[i]->Init(&para);
        RETURN_CHK(!ret, ret);

		ret = m_pAxis[i]->SetPosPulse();
		RETURN_CHK(ret, ret);
    }

	return RETURN_OK;
}

Axis *Card::GetAxis(quint16 index)
{
    RETURN_CHK(index < m_axisCnt, NULL);
	return m_pAxis[index];
}

int Card::AxisReset(quint16 axisIndex)
{
    Axis *pAxis = GetAxis(axisIndex);
    RETURN_CHK(pAxis, ERR_INVALID_AXIS);
    if (AxisIsMoving(axisIndex))
    {
        AxisStop(axisIndex, 0);
    }
    return pAxis->Reset();
}

int Card::AxisHome(quint16 axisIndex)
{
    Axis *pAxis = GetAxis(axisIndex);
    RETURN_CHK(pAxis, ERR_INVALID_AXIS);
    if (AxisIsMoving(axisIndex))
    {
        AxisStop(axisIndex, 0);
    }
    return pAxis->Home();
}

int Card::AxisIsMoving(quint16 axisIndex)
{
    short crd = 0;
    Axis *pAxis = GetAxis(axisIndex);
    RETURN_CHK(pAxis, ERR_INVALID_AXIS);
    crd = GetAxisInCrd(axisIndex);
    if (crd >= 0 && IsCrdMoving(crd))
    {
        return 1;   //运动中
    }
    return pAxis->IsMoving() ? 1 : 0;
}

int	Card::AxisWaitHome(quint16 axisIndex)
{
	Axis *pAxis = GetAxis(axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	return pAxis->WaiteHome();
}


int	Card::AxisWaitHome(quint16 axisIndex,int waitTime)
{
	Axis *pAxis = GetAxis(axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	return pAxis->WaiteHome(waitTime);
}

int Card::AxisWaitHome(quint16 axisIndex, double curPos, double len)
{
	Axis *pAxis = GetAxis(axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	return pAxis->WaitHome(curPos, len);
}

int	Card::AxisSetPos(quint16 axisIndex, double pos)
{
	Axis *pAxis = GetAxis(axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	return pAxis->SetPosMM(pos);
}

int Card::MovePos(quint16 axisIndex, double pos, double vel, double acc, double dec)
{
    Axis *pAxis = GetAxis(axisIndex);
    RETURN_CHK(pAxis, ERR_INVALID_AXIS);
    RETURN_CHK(!AxisIsMoving(axisIndex), ERR_AXIS_MOVING);
    return pAxis->MovePos(pos, vel, acc, dec);
}


int Card::MoveOffset(quint16 axisIndex, double pos, double vel, double acc, double dec)
{
	Axis *pAxis = GetAxis(axisIndex);
	RETURN_CHK(pAxis, ERR_INVALID_AXIS);
	RETURN_CHK(!AxisIsMoving(axisIndex), ERR_AXIS_MOVING);
	return pAxis->MoveOffset(pos, vel, acc, dec);
}

int Card::MoveJog(quint16 axisIndex, int dir, double vel, double acc, double dec)
{
    Axis *pAxis = GetAxis(axisIndex);
    RETURN_CHK(pAxis, ERR_INVALID_AXIS);
    RETURN_CHK(!AxisIsMoving(axisIndex), ERR_AXIS_MOVING);
    return pAxis->MoveJog(dir, vel, acc, dec);
}

int Card::AxisStop(quint16 axisIndex, int stopType)
{
    short crd = 0;
    RETURN_CHK(axisIndex < m_axisCnt, ERR_INVALID_AXIS);
    crd = GetAxisInCrd(axisIndex);
    if (crd >= 0)
    {
        StopCp(crd);
    }
	return m_pAxis[axisIndex]->Stop(stopType) ? RETURN_OK : ERR_MOTOR_API;
}

short Card::GetAxisInCrd(quint16 axisIndex)
{
    for(short i = 0; i < COOL_CNT; i++)
    {//判断该轴是否参与坐标系
        if (!m_stCool[i].isMoving)
        {
            continue;
        }
        for(short k = 0; k < m_stCool[i].axisCnt; k++)
        {
            if (axisIndex == m_stCool[i].axis[k])
            {//坐标轴属于这个坐标系
                return i;
            }
        }
    }
    return -1;
}

int Card::IsCrdMoving(quint16 crdID)
{
    RETURN_CHK(0 == crdID || 1 == crdID, 0);
    return m_stCool[crdID].isMoving;
}

int Card::CreateCrd(quint16 *pAxisIndex, quint16 axisCnt)
{
    bool bFind = false;
    unsigned crdID = 0;
    vector<TMovept*>::iterator it;

    for(crdID = 0; crdID < COOL_CNT; crdID++)
    {
        if (!m_stCool[crdID].isMoving && !m_stCool[crdID].bLock)
        {
            bFind = true;
            break;
        }
    }

    if (!bFind)
    {
		m_errorCode = ERR_CRD_OVERLIMIT ;
        return -1;
    }

	QMutexLocker locker(&m_mutex);

    for(quint16 i = 0; i < axisCnt; i++)
    {
        m_stCool[crdID].axis[i] = pAxisIndex[i];
    }

    m_stCool[crdID].cardID = m_cardID;
    m_stCool[crdID].crdID = crdID;
    m_stCool[crdID].curMoveIndex = 0;
    m_stCool[crdID].axisCnt = axisCnt;
    m_stCool[crdID].samStop.release(0);
	m_stCool[crdID].samExit.release(0);

    for(it = m_stCool[crdID].vecpt.begin(); it != m_stCool[crdID].vecpt.end(); it++)
    {
        FREE_ANY(*it);
    }
    m_stCool[crdID].vecpt.clear();

    return crdID;
}

int Card::ClearCrdData(unsigned int crdID)
{
    vector<TMovept*>::iterator it;

    StopCp(crdID);

	QMutexLocker locker(&m_mutex);

    for(it = m_stCool[crdID].vecpt.begin(); it != m_stCool[crdID].vecpt.end(); it++)
    {
        FREE_ANY(*it);
    }
    m_stCool[crdID].vecpt.clear();
    m_stCool[crdID].bLock = 0;

    return 0;
}

int Card::CloseCrd(quint16 crdID)
{
    vector<TMovept*>::iterator it;

    RETURN_CHK(0 == crdID || 1 == crdID, ERR_INPUT_PARAM);

    StopCp(crdID);  //先让坐标系停止

	QMutexLocker locker(&m_mutex);

    memset(m_stCool[crdID].axis, 0, sizeof(quint16)*CRD_AXIS_CNT);
    m_stCool[crdID].bLock = 0;
    m_stCool[crdID].axisCnt = 0;
    m_stCool[crdID].isMoving = 0;
    m_stCool[crdID].curMoveIndex = 0;
    for(it = m_stCool[crdID].vecpt.begin(); it != m_stCool[crdID].vecpt.end(); it++)
    {
        FREE_ANY(*it);
    }
    m_stCool[crdID].vecpt.clear();

    return RETURN_OK;
}

int Card::AddPos(quint16 crdID, TMovept& pt)
{
    RETURN_CHK(0 == crdID || 1 == crdID, ERR_INPUT_PARAM);
    RETURN_CHK(!m_stCool[crdID].isMoving, ERR_AXIS_MOVING);

    TMovept* pt1 = new TMovept;
    memcpy(pt1, &pt, sizeof(TMovept));
	QMutexLocker locker(&m_mutex);
    m_stCool[crdID].bLock = 1;
    m_stCool[crdID].vecpt.push_back(pt1);
    return 0;
}

int Card::StartCP(quint16 crdID)
{
    RETURN_CHK(0 == crdID || 1 == crdID, ERR_INPUT_PARAM);
    RETURN_CHK(!m_stCool[crdID].isMoving, ERR_AXIS_MOVING);
    RETURN_CHK(m_stCool[crdID].vecpt.size(), ERR_INPUT_PARAM);

	QMutexLocker locker(&m_mutex);
    m_stCool[crdID].isMoving	 = TRUE;   //正在运动中
	m_stCool[crdID].threadHandle = QtConcurrent::run(this,&Card::ThreadMoveCP ,this,&m_stCool[crdID]);
    return 0;
}

void Card::StopCp(quint16 crdID)
{
    ZERO_CHK(m_stCool[crdID].isMoving);
	m_stCool[crdID].samExit.release(1);
	m_stCool[crdID].samExit.acquire(1);
}


int Card::CrdStatus(quint16 crdID, short *pRun, long *pSegment)
{
    RETURN_CHK(0 == crdID || 1 == crdID, 0);
    *pRun = m_stCool[crdID].isMoving;
    *pSegment = m_stCool[crdID].curMoveIndex;
    return 0;
}

bool Card::IsSamePos(long* pos1, long* pos2, int axisCnt)
{
    for(int i = 0; i < axisCnt; i++)
    {
        if (abs(pos1[i] - pos2[i]) >= SAME_PULSE_OFFSET)
        {//差距在可允许范围内
            return false;
        }
    }
    return true;
}

int Card::CalcArcPos(long* pos1, long* pos2, long* pos3, int axisCnt, long& axisX, long& axisY)
{
    int i = 0;

    //3个点不能重合
    RETURN_CHK(!IsSamePos(pos1, pos2, axisCnt), ERR_ARC_MOVE);
    RETURN_CHK(!IsSamePos(pos2, pos3, axisCnt), ERR_ARC_MOVE);
    RETURN_CHK(!IsSamePos(pos1, pos3, axisCnt), ERR_ARC_MOVE);

    for(i = 0; i < axisCnt; i++)
    {
        if (abs(pos1[i] - pos2[i]) < SAME_PULSE_OFFSET &&
            abs(pos1[i] - pos3[i]) < SAME_PULSE_OFFSET &&
            abs(pos2[i] - pos3[i]) < SAME_PULSE_OFFSET)
        {//差距在可允许范围内
            break;
        }
    }

    RETURN_CHK(i <= 2, ERR_ARC_MOVE);    //圆弧插补只能前面3个轴之间任意两轴

    switch (i)
    {
    case 0: //0号轴值相等
        axisX = 1;
        axisY = 2;
        pos1[0] = pos1[1];
        pos1[1] = pos1[2];
        pos2[0] = pos2[1];
        pos2[1] = pos2[2];
        pos3[0] = pos3[1];
        pos3[1] = pos3[2];
        break;
    case 1:
        axisX = 2;
        axisY = 0;
        pos1[1] = pos1[0];
        pos1[0] = pos1[2];
        pos2[1] = pos2[0];
        pos2[0] = pos2[2];
        pos3[1] = pos3[0];
        pos3[0] = pos3[2];
        break;
    case 2:
        axisX = 0;
        axisY = 1;
        break;
    default:
        return ERR_ARC_MOVE;
        break;
    }
    return 0;
}

void Card::CalcCenter(long* pos1, long* pos2, long* pos3, long &x, long &y, double&r)
{
    double a,b,c,d,e,f;
    double x1,x2,x3,y1,y2,y3;

    x1 = pos1[0];
    x2 = pos2[0];
    x3 = pos3[0];
    y1 = pos1[1];
    y2 = pos2[1];
    y3 = pos3[1];

    a = 2 * (x2 - x1);
    b = 2 * (y2 - y1);
    c = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
    d = 2 * (x3 - x2);
    e = 2 * (y3 - y2);
    f = x3 * x3 + y3 * y3 - x2 * x2 - y2 * y2;
    x = doubleToInt((b * f - e * c) / (b * d - e * a));
    y = doubleToInt((d * c - a * f) / (b * d - e * a));
    r = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
}

int Card::CalcDir(long *pos1, long* pos2, long* pos3)
{
    //a b c 顺序3个点，网上参考答案
    //(b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x)
    long rtn = (pos2[0] - pos1[0]) * (pos3[1] - pos2[1]) - (pos2[1] - pos1[1]) * (pos3[0] - pos2[0]);

    //大于0 顺时针, 小于0 逆时针
    return rtn > 0 ? 1 : -1;
}

int Card::AddLinePos(quint16 crdID, double *ppos, TSpeed* pspeed)
{
    TMovept pt;
    double curPos = 0;
    double maxVel = 500000;
    double prevMaxVel = 500000;
    Axis* pAxis = NULL;
    const AxisParam* pAxisParam = NULL;
    vector<TMovept*>::iterator it;

    memset(&pt, 0, sizeof(pt));
    for(int i = 0; i < m_stCool[crdID].axisCnt; i++)
    {
        pAxis = GetAxis(m_stCool[crdID].axis[i]);
        pAxisParam = pAxis->GetParam();
        pAxis->GetCurPos(curPos);
        for(it = m_stCool[crdID].vecpt.begin(); it != m_stCool[crdID].vecpt.end(); it++)
        {
            curPos += (double)(*it)->pos[i] / pAxisParam->stepvalue;
        }
        pt.pos[i] = doubleToInt((ppos[i] - curPos) * pAxisParam->stepvalue);
		prevMaxVel = MIN(prevMaxVel, pAxisParam->vel);
        if (0 == pt.pos[i])
        {//不参与运动的除外
            continue;
        }
        maxVel = MIN(maxVel, pAxisParam->vel);
    }

    pt.dir = 0; //直线插补
    pt.vel = pspeed->vel * maxVel / prevMaxVel;
    pt.acc = pspeed->acc;
    return AddPos(crdID, pt);
}

int Card::AddArcPos(quint16 crdID, double *ppos1, double *ppos2, double *ppos3, TSpeed* pspeed)
{
    int ret = 0;
    TMovept pt;
    long realPos1[4];
    long realPos2[4];
    long realPos3[4];
    long axisX, axisY;
    long x, y;
    double r;
    double maxVel = 500000;
    double prevMaxVel = 500000;
    Axis* pAxis = NULL;
    const AxisParam* pAxisParam = NULL;

    memset(&pt, 0, sizeof(pt));
    memset(realPos1, 0, sizeof(realPos1));  //1为起始点
    for(int i = 0; i < m_stCool[crdID].axisCnt; i++)
    {
        pAxis = GetAxis(m_stCool[crdID].axis[i]);
        pAxisParam = pAxis->GetParam();
        realPos2[i] = doubleToInt(ppos2[i] - ppos1[i] * pAxisParam->stepvalue);
        realPos3[i] = doubleToInt(ppos3[i] - ppos1[i] * pAxisParam->stepvalue);
		prevMaxVel = MIN(prevMaxVel, pAxisParam->vel);
        if (0 == realPos2[i])
        {//不参与运动的除外
            continue;
        }
		maxVel = MIN(maxVel, pAxisParam->vel);
    }

    //计算圆弧运动类型，并按类型处理位置数据
    ret = CalcArcPos(realPos1, realPos2, realPos3, m_stCool[crdID].axisCnt, axisX, axisY);

    RETURN_CHK(!ret, ret);

    //计算圆心坐标
    CalcCenter(realPos1, realPos2, realPos3, x, y, r);

    //计算圆弧运动方向 0 顺时针 1逆时针
    pt.dir = CalcDir(realPos1, realPos2, realPos3);
    pt.pos[0] = realPos3[0];
    pt.pos[1] = realPos3[1];
    pt.pos[2] = x;
    pt.pos[3] = y;
    pt.pos[4] = m_stCool[crdID].axis[axisX];
    pt.pos[5] = m_stCool[crdID].axis[axisY];
    pt.vel = pspeed->vel * maxVel / prevMaxVel;
    pt.acc = pspeed->acc;

    return AddPos(crdID, pt);
}

int  Card::ThreadMoveCP(Card *card, TCool *pCool)
{
    short ret = 0;
    bool bRun = true;
    double tvel = 0.0;
    long pos[4] = {0};
    long center[2] = {0};
    quint16 axisCnt = 0;
    quint16 axis[4] = {0};

    while(pCool->curMoveIndex < pCool->vecpt.size() && bRun)
    {
        if (pCool->curMoveIndex < pCool->vecpt.size() - 1)
        {//后面还有点位，则结束速度等于下一个点的起始速度
            tvel = pCool->vecpt[pCool->curMoveIndex+1]->vel;
        }
        else
        {//后面没点位了，速度设置为0
            tvel = 0.0;
        }
        ret = dmc_set_vector_profile_multicoor(pCool->cardID, pCool->crdID, 0, pCool->vecpt[pCool->curMoveIndex]->vel, 
            pCool->vecpt[pCool->curMoveIndex]->acc, 0.0, tvel);

        LOG_INFO("Card call dmc_set_vector_profile_multicoor(%d,%d,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf)=%d.", pCool->cardID, pCool->crdID, 0.0f, pCool->vecpt[pCool->curMoveIndex]->vel,  pCool->vecpt[pCool->curMoveIndex]->acc, 0.0, tvel, ret);

        if (ret)
        {
            LOG_ERR("card:%d crd:%d ThreadMoveCP dmc_set_vector_profile_multicoor return error.",pCool->cardID, pCool->crdID, ret);
			card->m_errorCode = ERR_CRD_MOVE;
            break;
        }

        if (!pCool->vecpt[pCool->curMoveIndex]->dir)
        {//直线插补
            axisCnt = 0;
            for(int i = 0; i < pCool->axisCnt; i++)
            {
                if (0 == pCool->vecpt[pCool->curMoveIndex]->pos[i])
                {
                    continue;
                }
                pos[axisCnt] = pCool->vecpt[pCool->curMoveIndex]->pos[i];
                axis[axisCnt++] = pCool->axis[i];
            }
            if (axisCnt > 1)
            {
                ret = dmc_line_multicoor(pCool->cardID, pCool->crdID, axisCnt, axis, pos, 0);   //相对位置
            }
            else if (1 == axisCnt)
            {
                double vel = pCool->vecpt[pCool->curMoveIndex]->vel;
                double acc = pCool->vecpt[pCool->curMoveIndex]->acc;
                dmc_set_profile(pCool->cardID, axis[0], vel / 10, vel, acc, acc, vel / 10);
                ret = dmc_pmove(pCool->cardID, axis[0], pos[0], 0);
            }
            else
            {
                LOG_WARN("Card dmc_line_multicoor this position not need move...");
                ret = 0;
            }
            LOG_INFO("Card call dmc_line_multicoor(%d,%d,%d,%d,%d,%d)=%d.", pCool->cardID, 
                pCool->crdID, pCool->axisCnt, pCool->axis[0], pCool->vecpt[pCool->curMoveIndex]->pos[0], 0, ret);
        }
        else
        {//圆弧插补
            pos[0] = pCool->vecpt[pCool->curMoveIndex]->pos[0];
            pos[1] = pCool->vecpt[pCool->curMoveIndex]->pos[1];
            center[0] = pCool->vecpt[pCool->curMoveIndex]->pos[2];
            center[1] = pCool->vecpt[pCool->curMoveIndex]->pos[3];
            axis[0] = (quint16)(pCool->vecpt[pCool->curMoveIndex]->pos[4]);
            axis[1] = (quint16)(pCool->vecpt[pCool->curMoveIndex]->pos[5]);
            ret = dmc_arc_move_multicoor(pCool->cardID, pCool->crdID, axis, pos, center,
                pCool->vecpt[pCool->curMoveIndex]->dir, 0);
            LOG_INFO("Card call dmc_arc_move_multicoor(%d,%d,%d,%d,%d,%d,%d)=%d.", pCool->cardID, 
                pCool->crdID, axis[0], pos[0], center[0], pCool->vecpt[pCool->curMoveIndex]->dir, 0, ret);
        }

        if (ret)
        {
            LOG_ERR("card:%d crd:%d ThreadMoveCP dmc_multicoor move return error.",pCool->cardID, pCool->crdID, ret);
			card->m_errorCode = ERR_CRD_MOVE;
            break;
        }

        while(0 == dmc_check_done_multicoor(pCool->cardID, pCool->crdID))
        {
			if (true == pCool->samStop.tryAcquire(1, 50))
            {//有信号，则退出
                bRun = false;
                break;
            }
        }
        LOG_INFO("Card call dmc_check_done_multicoor(%d,%d)=0.", pCool->cardID, pCool->crdID);
        pCool->curMoveIndex++;  //运行下一个点
    }

    ret = dmc_stop_multicoor(pCool->cardID, pCool->crdID, 0);
    LOG_INFO("Card call dmc_stop_multicoor(%d,%d,0)=%d.", pCool->cardID, pCool->crdID, ret);

    while(0 == dmc_check_done_multicoor(pCool->cardID, pCool->crdID))
    {//等待停稳
		sleepMS(10);
    }
    
    pCool->isMoving = 0;			//不在运动中
    pCool->bLock = 0;				//解除锁定
	pCool->samExit.release(1);
    return 0;
}