#include "WorkFlow.h"
#include "GoHome.h"
#include "IOMonitor.h"
#include "LogCtl.h"
#include "LaserModule.h"
#include "FeedModule.h"
#include "UnLoadModule.h"
#include "CarryModule.h"
#include "../../Utility/System/Log.h"
#include "../../Utility/NetWork/NetWork.h"
#include "../../Utility/System/Config.h"
#include "../../Utility/Utility/Utility.h"
#include "../../Utility/XMessageBox/XMessageBox.h"
#include "../../include/Common.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include <math.h>
#include <QSettings>

const double DIF = 0.021;
std::once_flag  WorkFlow::m_initFlag;
std::unique_ptr<WorkFlow> WorkFlow::m_pInstance = nullptr;

WorkFlow::WorkFlow(QObject *parent)
{
	MOTION_INSTANCE;
	initData();
	setSysStatus(SYSTEM_UNHOME);
	m_timerId = startTimer(1000);
}

WorkFlow* WorkFlow::instance()
{
	std::call_once(m_initFlag, [&](){m_pInstance = std::unique_ptr<WorkFlow>(new WorkFlow()); });
	return m_pInstance.get();
}

WorkFlow::~WorkFlow()
{

}

void WorkFlow::initData()
{
	m_autoMode = false;
	m_pGoHome = new GoHome(this);
	m_pIOMonitor = new IOMonitor(this);
	m_laserModule = new LaserModule(this);
	m_feedModule = new FeedModule(this);
	m_unloadModule = new UnLoadModule(this);
	m_carryModule = new CarryModule(this);

	SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
	m_pTranslator = new QTranslator(this);
	onChanageLanguage(sysInfo.languageId);

	connect(m_feedModule, &FeedModule::sendReady, this, &WorkFlow::onReceiveReady);
	connect(m_laserModule, &LaserModule::sendReady, this, &WorkFlow::onReceiveReady);
	connect(m_unloadModule, &UnLoadModule::sendReady, this, &WorkFlow::onReceiveReady);
	connect(m_carryModule, &CarryModule::sendReady, this, &WorkFlow::onReceiveReady);
	connect(m_feedModule, &FeedModule::printUILog, this, &WorkFlow::printUILog);
	connect(m_laserModule, &LaserModule::printUILog, this, &WorkFlow::printUILog);
	connect(m_unloadModule, &UnLoadModule::printUILog, this, &WorkFlow::printUILog);
	connect(m_carryModule, &CarryModule::printUILog, this, &WorkFlow::printUILog);
	connect(m_laserModule, &LaserModule::updateLaserResult, this, &WorkFlow::updateLaserResult);
	connect(m_laserModule, &LaserModule::initLaserResult, this, &WorkFlow::initLaserResult);
	connect(m_feedModule, &FeedModule::hintAddFeedTray, this, &WorkFlow::hintAddFeedTray);
	connect(m_laserModule, &LaserModule::updateOutput, this, &WorkFlow::updateOutput);
	connect(m_unloadModule, &UnLoadModule::hintTakeUnloadTray, this, &WorkFlow::hintTakeUnloadTray);
}

void WorkFlow::initIO()
{
	MANAGER->setOutputStatus(QStringLiteral("����Z��ɲ��"), 1);
	MANAGER->setOutputStatus(QStringLiteral("����Z��ɲ��"), 1);

	MANAGER->setOutputStatus(QStringLiteral("���"), 0);
	MANAGER->setOutputStatus(QStringLiteral("�Ƶ�"), 0);
	MANAGER->setOutputStatus(QStringLiteral("�̵�"), 0);
	MANAGER->setOutputStatus(QStringLiteral("������"), 0);
}

void WorkFlow::exitIO()
{
	MANAGER->setOutputStatus(QStringLiteral("����Z��ɲ��"), 0);
	MANAGER->setOutputStatus(QStringLiteral("����Z��ɲ��"), 0);
	MANAGER->setOutputStatus(QStringLiteral("���"), 0);
	MANAGER->setOutputStatus(QStringLiteral("�Ƶ�"), 0);
	MANAGER->setOutputStatus(QStringLiteral("�̵�"), 0);
	MANAGER->setOutputStatus(QStringLiteral("������"), 0);
}

void	WorkFlow::initThread()
{
	m_pIOMonitor->start();
}

SYSTEM_STATUS	WorkFlow::getSysStatus()
{
	QMutexLocker locker(&m_mutexStatus);
	return m_sysStatus;
}

int WorkFlow::calibLaserAsyn()
{
	if (m_movePointFuture.isRunning())
	{
		printLog(tr("[Warn] Point movement ..., please wait for completion"));
		return 1;
	}
	qDebug() << QString("main thread:%1").arg((int)QThread::currentThreadId());

	

	m_movePointFuture = QtConcurrent::run(m_laserModule, &LaserModule::calibLaserFun);

	return 0;
}

void	WorkFlow::setSysStatus(SYSTEM_STATUS status)
{
	QMutexLocker locker(&m_mutexStatus);
	m_sysStatus = status;
	emit setUISysStatus(status);

	switch (status)
	{
		case  	SYSTEM_ERROR:
		{
			setSystemLight(1, 0, 0);
		}break;
		case  	SYSTEM_UNHOME:
		{
			setSystemLight(0, 0, 1);
		}break;
		case  	SYSTEM_HOMING:
		{
			setSystemLight(0, 0, 1);
		}break;
		case  	SYSTEM_STANDBY:
		{
			setSystemLight(0, 0, 1);
		}break;
		case  	SYSTEM_PAUSE:
		{
			setSystemLight(0, 0, 1);
		}break;
		case  	SYSTEM_WORKING:
		{
			setSystemLight(0, 1, 0);
		}break;
	}
}

void WorkFlow::onAppInit()
{
	initIO();
	initThread();
}

void WorkFlow::onExitApp()
{
	MANAGER->stopAllAxis();
	m_pIOMonitor->exitThread();
	m_pGoHome->exitThread();
	exitIO();
	wait(100);
}

void WorkFlow::onChanageLanguage(int id)
{
	if (id == 0)
		m_pTranslator->load(BINDIF("workflow_zh.qm"));	
	else if (id == 1)
		m_pTranslator->load(BINDIF("workflow_en.qm"));	
	else if (id == 2)
		m_pTranslator->load(BINDIF("workflow_vi.qm"));	

	QCoreApplication::installTranslator(m_pTranslator);
}

void WorkFlow::onReceiveReady(MODULE_READY type)
{
	if (type == FEED)		//���Ͼ���
	{
		startCarry();
	}
	else if (type == CARRY) //���˾���
	{
		if (m_autoMode)
		{
			startFeed();
			startLaser();
			startUnload();
		}
	}
	else if (type == LASER)  //�������
	{
		startCarry();
	}
	else if (type == UNLOAD)  //���Ͼ���
	{
		startCarry();
	}
}

void WorkFlow::setAutoMode(bool mode)
{
	m_autoMode = mode;
}

void WorkFlow::setClearMode(bool mode)
{
	m_feedModule->setClearMode(mode);
}

int WorkFlow::getFeedStatus()
{
	return getModuleStatus(m_feedModule);
}

int WorkFlow::getCarryStatus()
{
	return getModuleStatus(m_carryModule);
}

int WorkFlow::getLaserStatus()
{
	return getModuleStatus(m_laserModule);
}

int WorkFlow::getUnloadStatus()
{
	return getModuleStatus(m_unloadModule);
}

bool WorkFlow::unLoadTrayTaked()
{
	return m_unloadModule->unLoadTrayTaked();
}

void WorkFlow::startFeed()
{
	m_feedModule->setReady(false);
	m_feedModule->start();
}

void WorkFlow::startLaser()
{
	m_laserModule->setReady(false);
	m_laserModule->start();
}

void WorkFlow::startUnload()
{
	m_unloadModule->setReady(false);
	m_unloadModule->start();
}

void  WorkFlow::testFun(const QString &str)
{
	if ("Feed_home" == str){
		if (!m_feedModule->isRunning()){
			m_feedModule->moduleResetAsync();
		}
		else{
			printLog(QStringLiteral("[Error] ����ģ�������У��޷���λ"));
		}	
	}
	else if ("Carry_home" == str){
		if (!m_carryModule->isRunning()){
			m_carryModule->moduleResetAsync();
		}
		else{
			printLog(QStringLiteral("[Error] ����ģ�������У��޷���λ"));
		}
	}
	else if ("Scan_home" == str){
		if (!m_laserModule->isRunning()){
			m_laserModule->moduleResetAsync();
		}
		else{
			printLog(QStringLiteral("[Error] ɨ��ģ�������У��޷���λ"));
		}
	}
	else if ("UnLoad_home" == str){
		if (!m_unloadModule->isRunning()){
			m_unloadModule->moduleResetAsync();
		}
		else{
			printLog(QStringLiteral("[Error] ����ģ�������У��޷���λ"));
		}
	}
	else if ("Feed_start" == str)
	{
		if (!m_feedModule->isRunning() && 
			!m_carryModule->isRunning())
		{
			m_feedModule->start();
		}
		else
		{
			printLog(QStringLiteral("[Error] ����ģ������ģ�������У��޷���������ģ��"));
		}
	}
	else if ("Carry_start" == str)
	{
		if (!m_carryModule->isRunning() &&
			!m_feedModule->isRunning()  &&
			!m_laserModule->isRunning()  &&
			!m_unloadModule->isRunning())
		{
			m_carryModule->start();
		}
		else
		{
			printLog(QStringLiteral("[Error] ��ģ���������У��޷���������ģ��"));
		}	
	}
	else if ("Scan_start" == str)
	{
		if (!m_laserModule->isRunning() && 
			!m_carryModule->isRunning())
		{
			m_laserModule->start();
		}
		else
		{
			printLog(QStringLiteral("[Error] ɨ��ģ������ģ�������У��޷�����ɨ��ģ��"));
		}
	}
	else if ("UnLoad_start" == str)
	{
		if (!m_unloadModule->isRunning() &&
			!m_carryModule->isRunning())
		{
			m_unloadModule->start();
		}
		else
		{
			printLog(QStringLiteral("[Error] ����ģ������ģ������ģ�������У��޷���������ģ��"));
		}
	}
}

void WorkFlow::startHoming()
{
	if (m_feedModule->isRunning()||
		m_carryModule->isRunning()||
		m_laserModule->isRunning()||
		m_unloadModule->isRunning())
	{
		printLog(QStringLiteral("[Warm] ��ģ�鴦������״̬����ֹ��λ"));
		return;
	}

	MANAGER->setExitFlag(false);
	WORKFLOW_INSTANCE->setSysStatus(SYSTEM_HOMING);
	m_pGoHome->start();
}

void	WorkFlow::setSystemLight(int r, int g, int y)
{
	MANAGER->setOutputStatus(QStringLiteral("���"), r);
	MANAGER->setOutputStatus(QStringLiteral("�Ƶ�"), y);
	MANAGER->setOutputStatus(QStringLiteral("�̵�"), g);
}

void WorkFlow::startWorking()
{
	if (!isRunning())
	{
		start();
	}
}

void WorkFlow::stopWorking()
{
	MANAGER->setExitFlag(true);
	MANAGER->stopAllAxis();
	m_pGoHome->exitThread();
	WORKFLOW_INSTANCE->setSysStatus(SYSTEM_UNHOME);
}

void WorkFlow::printLog(const QString &msg)
{
	emit printUILog(msg);
}

void WorkFlow::run()
{
	if (m_autoMode){
		if (!m_feedModule->isRunning() && !m_carryModule->isRunning()){
			m_feedModule->start();
		}
	}
	else{
		printLog(QStringLiteral("[Warn] ���Զ�ģʽ���޷�����"));
	}
}

void WorkFlow::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		break;
	default:
		break;
	}
}

void WorkFlow::timerEvent(QTimerEvent *event)
{
	if (m_timerId == event->timerId())
	{
		if (m_feedModule->isRunning() ||
			m_carryModule->isRunning()||
			m_laserModule->isRunning() ||
			m_unloadModule->isRunning())
		{
			if (getSysStatus() != SYSTEM_WORKING &&
				getSysStatus() != SYSTEM_PAUSE)
			{
				setSysStatus(SYSTEM_WORKING);
			}
		}

		//
		if (!m_feedModule->isRunning()  &&
			!m_carryModule->isRunning() &&
			!m_laserModule->isRunning()  && 
			!m_unloadModule->isRunning())
		{
			if (isAllModulehomed())
			{
				if (getSysStatus() != SYSTEM_STANDBY)
				{
					setSysStatus(SYSTEM_STANDBY);
				}		
			}
		}
	}
}

int	WorkFlow::createLogDir()
{
	//QDateTime dataTime = QDateTime::currentDateTime();
	//QString   strDate = dataTime.toString("yyyy-MM-dd/hhmmss/");
	//QString   temp = m_vMesInfo.sn + "/";
	//QString   imageDir = m_vMesInfo.sn.isEmpty() ? strDate  : temp;

	//m_strLogDataPath   = DATADIR("Data/") + dataTime.toString("yyyy-MM-dd") + ".csv";
	//m_strCurImgDir     = DATADIR("Image/") + imageDir;
	//m_strCurMtrDir     = DATADIR("Motor/") + strDate;

	//createDir(DATADIR("Data/"));
	//createDir(m_strCurImgDir);
	//createDir(m_strCurMtrDir);
	return 0;
}

void WorkFlow::startCarry()
{
	if (m_autoMode)
	{
		if (m_feedModule->getReady()  &&
			m_carryModule->getReady() &&
			m_laserModule->getReady()  &&
			m_unloadModule->getReady())
		{
			m_carryModule->start();
		}
	}
}

int WorkFlow::getModuleStatus(MyModule* module)
{
	if (module->isRunning())	//������
	{	
		return 0;
	}
	else if (module->getReady()) //����
	{
		return 1;
	}
	else  //δ����
	{
		return 2;
	}
}

bool WorkFlow::isAllModulehomed() const
{
	if (m_feedModule->getHomeFlag() &&
		m_carryModule->getHomeFlag() &&
		m_laserModule->getHomeFlag() &&
		m_unloadModule->getHomeFlag())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void    WorkFlow::continueWorking()
{
	m_laserModule->test();

	return;
	if (SYSTEM_PAUSE == getSysStatus())
	{
		printLog(QStringLiteral("[OK] �����ͣ��������վ"));
		setSysStatus(SYSTEM_WORKING);
		MANAGER->setPauseFlag(false);
		MANAGER->setContinueFlag(true);
	}
}

