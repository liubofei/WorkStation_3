#pragma once
#include <QThread>
#include <vector>
#include <mutex>
#include <memory>
#include "../../include/Common.h"
#include "../../include/Motion.h"
#include "motion_dmc_global.h"

using namespace std;

#define MANAGER CardInterfaceManager::instance()

class MOTION_DMC_EXPORT CardInterfaceManager : public QThread
{
	Q_OBJECT

public:
	CardInterfaceManager(QObject *parent = nullptr);
	~CardInterfaceManager();
	static CardInterfaceManager* instance();

public:
	double	getAxisPos(const QString &axisName);
	int		setAxisPos(const QString &axisName, double pos);
	bool	findAxis(const QString &name, int &cardIndex, int &axisIndex);
	int		stopAllAxis();
	int		stopAxis(const QString &axisName);
	int		getInputStatus(const QString &IOName);
	int		getOutputStatus(const QString &IOName);
	int		setOutputStatus(const QString &IOName, int val);
	bool    axisIsMoving(const QString &axisName);
	int		axisJogMove(const QString &axisName, int dir, double vel = 0, double acc = 0, double dec = 0);				//dir 0 负方向 1 正方向
	int		axisMovePos(const QString &axisName, double pos, double vel = 0, double acc = 0, double dec = 0);
	int		axisMoveOffset(const QString &axisName, double pos, double vel = 0, double acc = 0, double dec = 0);
	int		axisWaitStop(const QString &axisName, bool interrupt = true);

	int		pointMoveSync(const QString &ptName, double vel = 0, double acc = 0, double dec = 0);
	int		pointMoveSync(const RunPoint& point, double vel = 0, double acc = 0, double dec = 0);
	int		pointSafeMoveSync(const RunPoint& point, double vel = 0, double acc = 0, double dec = 0);
	int		pointSafeMoveSync(const QString &ptName, double vel = 0, double acc = 0, double dec = 0);
	int		pointjogMoveSync(const RunPoint& point, double up);

	int		pointMoveAsync(const QString &ptName, double vel = 0, double acc = 0, double dec = 0);
	int		pointSafeMoveAsync(const RunPoint& point, double vel = 0, double acc = 0, double dec = 0);

	int		pointMoveSyncInterrupable(const QString &ptName, double vel = 0, double acc = 0, double dec = 0);
	int		pointMoveSyncInterrupable(const RunPoint &ptName, double vel = 0, double acc = 0, double dec = 0);
	int		pointjogMoveSyncInterrupable(const RunPoint& point, double up);
	int		pointsafeMoveSyncInterrupable(const RunPoint &ptName, double vel = 0, double acc = 0, double dec = 0);

	int     getCylinderStatus(const QString &strInP, const QString &strInN);
	int		setCylinder(const QString &strOut, const QString &strInP, const QString &strInN, int msTimeout, int on);

	int doubleCylinder(const QString& outP, const QString& outN, const QString &inP, const QString &inN, int value, int msTimeout);

	bool	isNearPoint(const QString &pointName, double precision = 0.05);
	bool    findPoint(const QString &pointName, RunPoint &point);
	void	setPauseFlag(bool flag);
	void	setContinueFlag(bool flag);
	bool	getPauseFlag() const;
	bool	getContinueFlag() const;
	void    showAxisStopReason(const QString &axisName);
	bool    isPointMoving();                                //正在异步点位运动？
	void    setExitFlag(bool exit);

signals:
	void printUILog(QString msg);

public slots:
	void onCardInfoChanged(QVector<CardInfo> cardInfo);
	void onIOInfoChanged(QVector<IOInfo> IOInputInfo, QVector<IOInfo> IOOutputInfo);
	void onPointsInfoChanged(QVector<RunPoint> pointsInfo);

private:
	void initData();
	int	 axisWaitStop(int cardIndex, int axisIndex, bool interrupt);
	bool isInPos(const RunPoint& pt);
	void createStopReason();


private:
	static once_flag m_initFlag;
	static unique_ptr<CardInterfaceManager> m_pInstance;
	
	bool				    m_bExitFlag;
	bool					m_bPauseFlag;
	bool					m_bContinueFlag;
	QFuture<int>			m_movePointFuture;

	QVector<CardInfo>		m_vCardInfo;
	QVector<IOInfo>			m_vInputInfo;
	QVector<IOInfo>			m_vOutputInfo;
	QVector<RunPoint>		m_vRunPoint;
	QMap<int, QString>      mapStopReason;
};
