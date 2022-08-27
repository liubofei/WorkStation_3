#include "UnLoadModule.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Utility/System/Config.h"

UnLoadModule::UnLoadModule(QObject *parent)
	: MyModule(parent)
{
	m_mutex = new QMutex();
	m_isNeedTakeTray = false;
}

UnLoadModule::~UnLoadModule()
{

}

bool UnLoadModule::moduleReset()
{
	setReady(false);
	m_bIsHome = false;
	
	QString zName = "Unload_Z";
	int zCard = 0, zAxis = 0, zHomeResult = 0;

	if (1 == MANAGER->getInputStatus(QStringLiteral("下料料盘感应")))
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 下料料盘感应感应到有料盘，不能复位"));
		return false;
	}
	if (1 == MANAGER->getInputStatus(QStringLiteral("下料满料感应")))
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 下料满料感应感应到料盘，不能复位"));
		return false;
	}

	if (!MANAGER->findAxis(zName, zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 Unload_Z轴不存在"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 启动Unload_Z轴回原失败"));
		return false;
	}
	zHomeResult = MOTION_INSTANCE->Axis_WaiteHome(zCard, zAxis);
	if (zHomeResult != 0)
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 Unload_Z回原失败"));
		return false;
	}

	if (0 != MANAGER->pointMoveSync("UnLoad_Init_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 移动到点位 UnLoad_Init_Pos 失败"));
		return false;
	}

	emit printUILog(QStringLiteral("[OK] 下料模组复位成功"));
	setReady(true);
	m_bIsHome = true;
	return true;
}

bool UnLoadModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] 下料模组正在复位中...,请等待完成"));
		return false;
	}

	m_homeFuture = QtConcurrent::run(this, &UnLoadModule::moduleReset);
	return true;
}

bool UnLoadModule::unLoadTrayTaked()
{
	if (m_isNeedTakeTray)
	{
		if (0 == MANAGER->getInputStatus(QStringLiteral("下料满料感应")))
		{
			m_mutex->lock();
			m_wait.wakeAll();
			m_mutex->unlock();
			m_isNeedTakeTray = false;
			return true;
		}
		else
		{
			emit printUILog(QStringLiteral("[Error] 下料模组 下料满料感应感应到物料，请检查"));
			return false;
		}
	}
	else
	{
		emit printUILog(QStringLiteral("[Error] 下料模组 当前状态不需要取走料盘"));
	}

	return true;
}

void UnLoadModule::run()
{
	setReady(false);
	if (runFun())
	{
		setReady(true);
		emit sendReady(UNLOAD);
	}
	else
	{	
		emit printUILog(m_strError);
	}
}

bool UnLoadModule::runFun()
{
	if (!m_bIsHome)
	{
		m_strError = QStringLiteral("[Error] 下料仓未回原，请回原后继续");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("下料料盘感应")))
	{
		m_strError = QStringLiteral("[OK] 下料料盘感应 未感应到料盘，已返回");
		return true;
	}

	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	double offset = -info.feed_z_offset;
	MANAGER->axisMoveOffset("Unload_Z", offset);
	MANAGER->axisWaitStop("Unload_Z");

	if (1 == MANAGER->getInputStatus(QStringLiteral("下料满料感应")))
	{
		m_isNeedTakeTray = true;
		emit hintTakeUnloadTray();

		m_mutex->lock();
		m_wait.wait(m_mutex);
		m_mutex->unlock();

		if (0 != MANAGER->pointMoveSync("UnLoad_Init_Pos"))
		{
			emit printUILog(QStringLiteral("[Error] 下料模组 移动到点位 UnLoad_Init_Pos 失败"));
			return false;
		}
	}

	return true;
}
