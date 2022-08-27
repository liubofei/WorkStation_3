#include "CardInterfaceManager.h"
#include "../Motion_dmc/Motion_dmc.h"
#include "../../Utility/System/Config.h"
#include "../../include/LTDMC.h"


once_flag  CardInterfaceManager::m_initFlag;
unique_ptr<CardInterfaceManager> CardInterfaceManager::m_pInstance = nullptr;
const double DIF = 0.021;

CardInterfaceManager::CardInterfaceManager(QObject *parent)
	:QThread(parent)
{
	initData();
}

CardInterfaceManager::~CardInterfaceManager()
{
	qDebug() << "~CardInterfaceManager()";
}

CardInterfaceManager* CardInterfaceManager::instance()
{
	std::call_once(m_initFlag, [&](){m_pInstance = unique_ptr<CardInterfaceManager>(new CardInterfaceManager()); });
	return m_pInstance.get();
}

double CardInterfaceManager::getAxisPos(const QString &axisName)
{
	double val = 0;
	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		MOTION_INSTANCE->Get_Current_Pos(cardId, axisId, val);
	}
	return val;
}

int CardInterfaceManager::setAxisPos(const QString &axisName, double pos)
{
	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return MOTION_INSTANCE->Set_Current_Pos(cardId, axisId, pos);
	}
	return 1;
}

bool CardInterfaceManager::findAxis(const QString &name, int &cardIndex, int &axisIndex)
{
	for each (const auto &cardInfo in m_vCardInfo)
	{
		for each (const auto &axisParam in cardInfo.vecAxisParam)
		{
			if (axisParam.axisName == name)
			{
				cardIndex = axisParam.cardIndex;
				axisIndex = axisParam.axisIndex;
				return true;
			}
		}
	}
	return false;
}

int CardInterfaceManager::stopAllAxis()
{
	for each (const auto &cardInfo in m_vCardInfo)
	{
		for each (const auto &axisParam in cardInfo.vecAxisParam)
		{
			MOTION_INSTANCE->Axis_Stop(axisParam.cardIndex, axisParam.axisIndex, 0);
		}
	}
	return 0;
}

int CardInterfaceManager::stopAxis(const QString &axisName)
{
	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return MOTION_INSTANCE->Axis_Stop(cardId, axisId, 0);
	}
	return 1;
}

int CardInterfaceManager::getInputStatus(const QString &IOName)
{
	short val = 0;
	for (const auto &IOInfo : m_vInputInfo)
	{
		if (IOName == IOInfo.name)
		{
			MOTION_INSTANCE->ReadInBit(IOInfo.cardIndex, IOInfo.cardNode, IOInfo.ioIndex, val, IOInfo.cardType);
			if (val == IOInfo.sense)
				return 1;
			else
				return 0;
		}
	}
	emit printUILog(QStringLiteral("[Error] 输入信号[%1]不存在").arg(IOName));
	return 0;
}

int CardInterfaceManager::getOutputStatus(const QString &IOName)
{
	short val = 0;
	for each (const auto &IOInfo in m_vOutputInfo)
	{
		if (IOName == IOInfo.name)
		{
			MOTION_INSTANCE->ReadOutBit(IOInfo.cardIndex, IOInfo.cardNode, IOInfo.ioIndex, val, IOInfo.cardType);
			if (val == IOInfo.sense)
				return 1;
			else
				return 0;
		}
	}
	emit printUILog(QStringLiteral("[Error] 输出信号[%1]不存在").arg(IOName));
	return 0;
}

int CardInterfaceManager::setOutputStatus(const QString &IOName, int val)
{
	for each (const auto &IOInfo in m_vOutputInfo)
	{
		if (IOName == IOInfo.name)
		{
			if (IOInfo.sense == 0)
				val = !val;
			MOTION_INSTANCE->writeOutBit(IOInfo.cardIndex, IOInfo.cardNode, IOInfo.ioIndex, val,IOInfo.cardType);
			return 0;
		}
	}
	emit printUILog(QStringLiteral("[Error] 输出信号[%1]不存在").arg(IOName));
	return 1;
}

bool CardInterfaceManager::axisIsMoving(const QString &axisName)
{
	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return MOTION_INSTANCE->Axis_Is_Moving(cardId, axisId);
	}

	emit printUILog(QStringLiteral("[Error] 轴%1不存在").arg(axisName));
	return true;
}

int		CardInterfaceManager::axisJogMove(const QString &axisName, int dir, double vel, double acc, double dec)
{
	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return MOTION_INSTANCE->Move_Jog(cardId, axisId, dir, vel, acc, dec);
	}

	emit printUILog(QStringLiteral("[Error] 轴%1不存在").arg(axisName));
	return 1;
}

int		CardInterfaceManager::axisMovePos(const QString &axisName, double pos, double vel, double acc, double dec)
{
	if (m_bExitFlag)
	{
		emit printUILog(QStringLiteral("[Error] 急停可能按下，不容许轴运动！"));
		return 1;
	}

	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return MOTION_INSTANCE->Move_Pos(cardId, axisId, pos, vel, acc, dec);
	}
	emit printUILog(QStringLiteral("[Error] 轴%1不存在").arg(axisName));
	return 1;
}

int		CardInterfaceManager::axisMoveOffset(const QString &axisName, double pos, double vel, double acc, double dec)
{
	if (m_bExitFlag)
	{
		emit printUILog(QStringLiteral("[Error] 急停可能按下，不容许轴运动！"));
		return 1;
	}

	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return MOTION_INSTANCE->Move_Offset(cardId, axisId, pos, vel, acc, dec);
	}

	emit printUILog(QStringLiteral("[Error] 轴%1不存在").arg(axisName));
	return 1;
}

void CardInterfaceManager::initData()
{
	m_bExitFlag = false;
	m_bPauseFlag = false;
	m_bContinueFlag = false;

	CONFIG_INSTANCE->getCardInfo(m_vCardInfo);
	CONFIG_INSTANCE->getInputInfo(m_vInputInfo);
	CONFIG_INSTANCE->getOutputInfo(m_vOutputInfo);
	CONFIG_INSTANCE->getRunPointInfo(m_vRunPoint);

	connect(CONFIG_INSTANCE.data(), &Config::cardInfoChanged, this, &CardInterfaceManager::onCardInfoChanged);
	connect(CONFIG_INSTANCE.data(), &Config::IOInfoChanged, this, &CardInterfaceManager::onIOInfoChanged);
	connect(CONFIG_INSTANCE.data(), &Config::pointsInfoChanged, this, &CardInterfaceManager::onPointsInfoChanged);
}

int		CardInterfaceManager::axisWaitStop(const QString &axisName, bool interrupt)
{
	int cardId = 0, axisId = 0;
	if (findAxis(axisName, cardId, axisId))
	{
		return axisWaitStop(cardId, axisId, interrupt);
	}

	emit printUILog(QStringLiteral("[Error] 轴%1不存在").arg(axisName));
	return 1;
}

void CardInterfaceManager::showAxisStopReason(const QString &axisName)
{
	long stopReason = 0;
	int axisIndex = 0;
	int cardId = 0;
	int axisId = 0;

	if (findAxis(axisName, cardId, axisId))
	{
		dmc_get_stop_reason(cardId, axisId, &stopReason);
		dmc_clear_stop_reason(cardId, axisId);
		emit printUILog(QStringLiteral("%1轴停止原因是 %2").arg(axisName).arg(mapStopReason[stopReason]));
	}
}

bool CardInterfaceManager::isPointMoving()
{
	return m_movePointFuture.isRunning();
}

void CardInterfaceManager::setExitFlag(bool exit)
{
	m_bExitFlag = exit;
}

void CardInterfaceManager::onCardInfoChanged(QVector<CardInfo> cardInfo)
{
	m_vCardInfo = cardInfo;
}

void CardInterfaceManager::onIOInfoChanged(QVector<IOInfo> IOInputInfo, QVector<IOInfo> IOOutputInfo)
{
	m_vInputInfo = IOInputInfo;
	m_vOutputInfo = IOOutputInfo;
}

void CardInterfaceManager::onPointsInfoChanged(QVector<RunPoint> pointsInfo)
{
	m_vRunPoint = pointsInfo;
}

bool CardInterfaceManager::isInPos(const RunPoint& pt)
{
	double pos = 0.0;
	if (!pt.dimension.axisNameX.isEmpty())
	{
		pos = getAxisPos(pt.dimension.axisNameX);
		if (abs(pos - pt.pos[0]) > DIF)
			return false;
	}

	if (!pt.dimension.axisNameY.isEmpty())
	{
		pos = getAxisPos(pt.dimension.axisNameY);
		if (abs(pos - pt.pos[1]) > DIF)
			return false;
	}

	return true;
}

void CardInterfaceManager::createStopReason()
{
	mapStopReason[0] = QStringLiteral("正常停止");
	mapStopReason[1] = QStringLiteral("ALM立即停止");
	mapStopReason[2] = QStringLiteral("ALM减速停止");
	mapStopReason[3] = QStringLiteral("LTC外部触发立即停止");
	mapStopReason[4] = QStringLiteral("EMG立即停止");
	mapStopReason[5] = QStringLiteral("正硬限位立即停止");
	mapStopReason[6] = QStringLiteral("负硬限位立即停止");
	mapStopReason[7] = QStringLiteral("正硬限位减速停止");
	mapStopReason[8] = QStringLiteral("负硬限位减速停止");
	mapStopReason[9] = QStringLiteral("正软限位立即停止");
	mapStopReason[10] = QStringLiteral("负软限位立即停止");
	mapStopReason[11] = QStringLiteral("正软限位减速停止");
	mapStopReason[12] = QStringLiteral("负软限位减速停止");
	mapStopReason[13] = QStringLiteral("命令立即停止");
	mapStopReason[14] = QStringLiteral("命令减速停止");
	mapStopReason[15] = QStringLiteral("其它原因立即停止");
	mapStopReason[16] = QStringLiteral("其它原因减速停止");
	mapStopReason[17] = QStringLiteral("未知原因立刻停止");
}

bool CardInterfaceManager::findPoint(const QString& ptName, RunPoint& ptInfo)
{
	for each (const auto &pointInfo in m_vRunPoint)
	{
		if (pointInfo.name == ptName)
		{
			ptInfo = pointInfo;
			return true;
		}
	}
	return false;
}

int		CardInterfaceManager::pointMoveSync(const QString &ptName, double vel, double acc, double dec)
{
	RunPoint pt;
	if (findPoint(ptName,pt))
	{
		return pointMoveSync(pt, vel, acc, dec);
	}

	emit printUILog(QStringLiteral("[Error] 点位名称%1不存在").arg(ptName));
	return 1;
}

int		CardInterfaceManager::pointMoveSync(const RunPoint& point, double vel, double acc, double dec)
{
	//1.运动  Z轴最后运动
	int ret = 0;
	if (!point.dimension.axisNameX.isEmpty())
	{
		ret = axisMovePos(point.dimension.axisNameX, point.pos[0], vel, acc, dec);
		RETURN_CHK(!ret, ret);
	}
	if (!point.dimension.axisNameY.isEmpty())
	{
		ret = axisMovePos(point.dimension.axisNameY, point.pos[1], vel, acc, dec);
		RETURN_CHK(!ret, ret);
	}
	if (!point.dimension.axisNameU.isEmpty())
	{
		ret = axisMovePos(point.dimension.axisNameU, point.pos[3], vel, acc, dec);
		RETURN_CHK(!ret, ret);
	}
	if (!point.dimension.axisNameV.isEmpty())
	{
		ret = axisMovePos(point.dimension.axisNameV, point.pos[4], vel, acc, dec);
		RETURN_CHK(!ret, ret);
	}

	//2.等待运动完成
	if (!point.dimension.axisNameX.isEmpty())
	{
		ret = axisWaitStop(point.dimension.axisNameX);
		RETURN_CHK(!ret, ret);
	}
	if (!point.dimension.axisNameY.isEmpty())
	{
		ret = axisWaitStop(point.dimension.axisNameY);
		RETURN_CHK(!ret, ret);
	}
	if (!point.dimension.axisNameU.isEmpty())
	{
		ret = axisWaitStop(point.dimension.axisNameU);
		RETURN_CHK(!ret, ret);
	}
	if (!point.dimension.axisNameV.isEmpty())
	{
		ret = axisWaitStop(point.dimension.axisNameV);
		RETURN_CHK(!ret, ret);
	}

	//等待Z轴运动到位
	if (!point.dimension.axisNameZ.isEmpty())
	{
		ret = axisMovePos(point.dimension.axisNameZ, point.pos[2], vel, acc, dec);
		RETURN_CHK(!ret, ret);
		ret = axisWaitStop(point.dimension.axisNameZ);
		RETURN_CHK(!ret, ret);
	}
	msleep(500);

	short error = 0;

	//3.精度检查
	if (!point.dimension.axisNameX.isEmpty())
	{
		double curXPos = getAxisPos(point.dimension.axisNameX);
		if (abs(curXPos - point.pos[0]) > DIF)
		{
			++error;
			showAxisStopReason(point.dimension.axisNameX);
		}
	}
	if (!point.dimension.axisNameY.isEmpty())
	{
		double curYPos = getAxisPos(point.dimension.axisNameY);
		if (abs(curYPos - point.pos[1]) > DIF)
		{
			++error;
			showAxisStopReason(point.dimension.axisNameY);
		}
	}
	if (!point.dimension.axisNameZ.isEmpty())
	{
		double curZPos = getAxisPos(point.dimension.axisNameZ);
		if (abs(curZPos - point.pos[2]) > DIF)
		{
			++error;
			showAxisStopReason(point.dimension.axisNameZ);
		}
	}
	if (!point.dimension.axisNameU.isEmpty())
	{
		double curUPos = getAxisPos(point.dimension.axisNameU);
		if (abs(curUPos - point.pos[3]) > DIF)
		{
			++error;
			showAxisStopReason(point.dimension.axisNameZ);
		}
	}
	if (!point.dimension.axisNameV.isEmpty())
	{
		double curVPos = getAxisPos(point.dimension.axisNameV);
		if (abs(curVPos - point.pos[4]) > DIF)
		{
			++error;
			showAxisStopReason(point.dimension.axisNameV);
		}
	}


	if (error != 0)
	{
		emit printUILog(tr("Unable to move to point:%1(%2, %3, %4)").arg(point.name).arg(point.pos[0]).arg(point.pos[1]).arg(point.pos[2]));
		return 1;
	}
	return 0;
}

int		CardInterfaceManager::pointSafeMoveSync(const RunPoint& point, double vel, double acc, double dec)
{
	if (!isInPos(point))
	{
		QString axisName = point.dimension.axisNameZ;
		RETURN_CHK(!axisMovePos(axisName, CONFIG_INSTANCE->getSysInfo().safeHeightZ), 1);
		RETURN_CHK(!axisWaitStop(axisName), 1);
	}
	return pointMoveSync(point);
}

int		CardInterfaceManager::pointSafeMoveSync(const QString &ptName, double vel, double acc, double dec)
{
	RunPoint pt;
	if (findPoint(ptName,pt))
	{
		return pointSafeMoveSync(pt, vel, acc, dec);
	}
	emit printUILog(tr("Point %1 does not exist").arg(ptName));
	return 1;
}

int		CardInterfaceManager::pointjogMoveSync(const RunPoint& point, double up)
{
	int ret = 0;
	QString axisName = point.dimension.axisNameZ;
	if (abs(CONFIG_INSTANCE->getSysInfo().safeHeightZ - getAxisPos(axisName)) > 3)
	{
		ret = axisMoveOffset(axisName, abs(up));
		RETURN_CHK(!ret, ret);
		ret = axisWaitStop(axisName);
		RETURN_CHK(!ret, ret);
	}
	return pointMoveSync(point);
}

int		CardInterfaceManager::pointSafeMoveAsync(const RunPoint& point, double vel, double acc, double dec)
{
	if (m_movePointFuture.isRunning())
	{
		emit printUILog(tr("Point movement ..., please wait for completion"));
		return 1;
	}

	m_movePointFuture = QtConcurrent::run(this, static_cast<int(CardInterfaceManager::*)(const RunPoint&, double, double, double)>(&CardInterfaceManager::pointSafeMoveSync), point, vel, acc, dec);
	return 0;
}

int		CardInterfaceManager::pointjogMoveSyncInterrupable(const RunPoint& point, double up)
{
	int rtn = 0;
	while (true)
	{
		rtn = pointjogMoveSync(point, abs(up));
		if (AXIS_PAUSE != rtn)
			return rtn;
		else
		{
			while (true)
			{
				if (!m_bPauseFlag && m_bContinueFlag) //继续		
					break;

				if (m_bExitFlag)
					return 1;

				msleep(10);
			}
		}

		if (m_bExitFlag)
			return 1;
	}
}

int		CardInterfaceManager::pointMoveSyncInterrupable(const QString &ptName, double vel, double acc, double dec)
{
	RunPoint pt;
	if (findPoint(ptName,pt))
	{
		return pointMoveSyncInterrupable(pt, vel, acc, dec);
	}

	emit printUILog(tr("Point %1 does not exist").arg(ptName));
	return 1;
}

int		CardInterfaceManager::pointMoveSyncInterrupable(const RunPoint &ptName, double vel, double acc, double dec)
{
	int rtn = 0;
	while (true)
	{
		rtn = pointMoveSync(ptName);
		if (AXIS_PAUSE != rtn)
			return rtn;
		else
		{
			while (true)
			{
				if (!m_bPauseFlag && m_bContinueFlag) //继续				
					break;

				if (m_bExitFlag)
					return 1;

				msleep(10);
			}
		}

		if (m_bExitFlag)
			return 1;
	}
}

int		CardInterfaceManager::pointsafeMoveSyncInterrupable(const RunPoint &ptName, double vel, double acc, double dec)
{
	int rtn = 0;
	while (true)
	{
		rtn = pointSafeMoveSync(ptName);

		if (AXIS_PAUSE != rtn)
			return rtn;
		else{
			while (true)
			{
				if (!m_bPauseFlag && m_bContinueFlag) //继续			
					break;

				if (m_bExitFlag)
					return 1;
				msleep(10);
			}
		}

		if (m_bExitFlag)
			return 1;
	}
}

int		CardInterfaceManager::pointMoveAsync(const QString &ptName, double vel, double acc, double dec)
{
	if (m_movePointFuture.isRunning())
	{
		emit printUILog(tr("Point movement ..., please wait for completion"));
		return 1;
	}
	m_movePointFuture = QtConcurrent::run(this, static_cast<int(CardInterfaceManager::*)(const QString &, double, double, double)>(&CardInterfaceManager::pointMoveSync), ptName, vel, acc, dec);
	return 0;
}

int     CardInterfaceManager::getCylinderStatus(const QString &strInP, const QString &strInN)
{
	int inPStatus = 0, inNStatus = 0;
	inPStatus = getInputStatus(strInP);
	inNStatus = getInputStatus(strInN);

	if (inPStatus && 0 == inNStatus)
		return 1;
	else if (0 == inPStatus && inNStatus)
		return 0;

	return -1;
}

int		CardInterfaceManager::setCylinder(const QString &strOut, const QString &strInP, const QString &strInN, int msTimeout, int on)
{
	int times = 5;

	int rtn = 0;
	int inPStatus = 0, inNStatus = 0;

	setOutputStatus(strOut, on);
	msleep(5);
	rtn = setOutputStatus(strOut, on);

	RETURN_CHK(rtn == 0, 1);

	msleep(100);
	while (msTimeout > 0)
	{
		inPStatus = getInputStatus(strInP);
		inNStatus = getInputStatus(strInN);

		if (1 == on && 1 == inPStatus && 0 == inNStatus)
			return 0;
		else if (0 == on && 0 == inPStatus && 1 == inNStatus)
			return 0;

		msleep(30);
		msTimeout -= 30;
	}

	if (0 == on)
		emit printUILog(QStringLiteral("[Error] 气缸 %1 关闭失败").arg(strOut));
	else
		emit printUILog(QStringLiteral("[Error] 气缸 %1 打开失败").arg(strOut));
	return 1;
}

int CardInterfaceManager::doubleCylinder(const QString& outP, const QString& outN, const QString &inP, const QString &inN, int value, int msTimeout)
{
	int ret = 0;
	setOutputStatus(outP, value);
	msleep(5);
	ret = setOutputStatus(outP, value);
	RETURN_CHK(ret == 0, 1);

	setOutputStatus(outN, !value);
	msleep(5);
	ret = setOutputStatus(outN, !value);
	RETURN_CHK(ret == 0, 1);

	int status1 = 0, status2 = 0;

	msleep(100);
	while (msTimeout > 0)
	{
		status1 = getInputStatus(inP);
		status2 = getInputStatus(inN);

		if (1 == value && 1 == status1 && 0 == status2)
			return 0;
		else if (0 == value && 0 == status1 && 1 == status2)
			return 0;

		msleep(30);
		msTimeout -= 30;
	}

	return 1;
}

bool	CardInterfaceManager::isNearPoint(const QString &pointName, double precision)
{
	double x = 0.0, y = 0.0, z = 0.0;
	for each (const auto &pointInfo in m_vRunPoint)
	{
		if (pointInfo.name == pointName)
		{
			if (!pointInfo.dimension.axisNameX.isEmpty())
			{
				x = getAxisPos(pointInfo.dimension.axisNameX);
				RETURN_CHK(abs(x - pointInfo.pos[0]) < precision, false);
			}
			if (!pointInfo.dimension.axisNameY.isEmpty())
			{
				y = getAxisPos(pointInfo.dimension.axisNameY);
				RETURN_CHK(abs(y - pointInfo.pos[1]) < precision, false);
			}
			if (!pointInfo.dimension.axisNameZ.isEmpty())
			{
				z = getAxisPos(pointInfo.dimension.axisNameZ);
				RETURN_CHK(abs(z - pointInfo.pos[2]) < precision, false);
			}
			return true;
		}
	}
	emit printUILog(tr("Point %1 does not exist").arg(pointName));
	return false;
}

void	CardInterfaceManager::setPauseFlag(bool flag)
{
	m_bPauseFlag = flag;
}

void	CardInterfaceManager::setContinueFlag(bool flag)
{
	m_bContinueFlag = flag;
}

bool	CardInterfaceManager::getPauseFlag() const
{
	return m_bPauseFlag;
}

bool	CardInterfaceManager::getContinueFlag() const
{
	return m_bContinueFlag;
}

int CardInterfaceManager::axisWaitStop(int cardIndex, int axisIndex, bool interrupt)
{
	while (true)
	{
		int status = MOTION_INSTANCE->Axis_Is_Moving(cardIndex, axisIndex);
		if (0 == status) return 0;
		if (m_bExitFlag)
		{
			return MOTION_INSTANCE->Axis_Stop(cardIndex, axisIndex, 0);
		}
		else if (m_bPauseFlag && !m_bContinueFlag && interrupt)
		{
			stopAllAxis();
			return AXIS_PAUSE;
		}

		msleep(30);
	}
}

