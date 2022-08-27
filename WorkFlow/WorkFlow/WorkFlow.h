#pragma once
#include "workflow_global.h"
#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include "../../include/Common.h"
#include "../../include/Motion.h"
#include <mutex>
#include <memory>

#define  WORKFLOW_INSTANCE  WorkFlow::instance()

class GoHome;			
class IOMonitor;				
class LogCtl;
class FeedModule;
class UnLoadModule;
class CarryModule;
class LaserModule;
class MyModule;


class WORKFLOW_EXPORT WorkFlow : public QThread
{
	Q_OBJECT

public:
	static WorkFlow* instance();
	~WorkFlow();
	friend GoHome;
	friend IOMonitor;

public:
	void initIO();
	void exitIO();
	void initThread();
	
	void startHoming();
	void startWorking();
	void stopWorking();

	void printLog(const QString &msg);
	void testFun(const QString & str);
	void continueWorking();
	void setAutoMode(bool mode);
	void setClearMode(bool mode);

	int getFeedStatus();
	int getCarryStatus();
	int getLaserStatus();
	int getUnloadStatus();
	bool unLoadTrayTaked();

	void setSysStatus(SYSTEM_STATUS status);
	SYSTEM_STATUS	getSysStatus();
	int calibLaserAsyn();

public slots :
	void onAppInit();
	void onExitApp();
	void onChanageLanguage(int id);
	void onReceiveReady(MODULE_READY type);

signals:
	void printUILog(QString msg);
	void setUISysStatus(SYSTEM_STATUS status);

	void hintAddFeedTray();     //feed模组提示需要增加料盘
	void hintTakeUnloadTray();	//Unload提示取走下料仓料盘

	//Laser
	void updateLaserResult(int row, int col, bool status);
	void initLaserResult();
	void updateOutput(unsigned int total, unsigned int ngNum);	//产量更新

protected:
	void  changeEvent(QEvent* event);
	void  timerEvent(QTimerEvent *event);
	void  initData();
	void  run();
	void  setSystemLight(int r, int g, int y);
	int   createLogDir();
	int   getModuleStatus(MyModule* module);
	bool  isAllModulehomed() const;

	void startCarry();
	void startFeed();
	void startLaser();
	void startUnload();



private:
	static std::once_flag m_initFlag;
	static std::unique_ptr<WorkFlow> m_pInstance;	
	WorkFlow(QObject *parent = nullptr);

	GoHome*			 m_pGoHome;;
	IOMonitor*		 m_pIOMonitor;
	QTranslator*	 m_pTranslator;
	LaserModule*	 m_laserModule;
	FeedModule*      m_feedModule;
	UnLoadModule*    m_unloadModule;
	CarryModule*     m_carryModule;

	SYSTEM_STATUS	m_sysStatus;
	QMutex			m_mutexStatus;
	QString			m_strCurMtrDir;
	QString			m_strLogDataPath;	

	bool			m_autoMode;	//自动模式
	int				m_timerId;

	QFuture<int> m_movePointFuture;
};
