#include "FeedModule.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Utility/System/Config.h"

FeedModule::FeedModule(QObject *parent)
	: MyModule(parent)
{
	m_bClearMode = false;
}

FeedModule::~FeedModule()
{
}

bool FeedModule::moduleReset()
{
	setReady(false);
	m_bIsHome = false;
	
	if (0 == MANAGER->getInputStatus(QStringLiteral("上料推入到位")))
	{
		emit printUILog(QStringLiteral("[Warn] 上料仓未推入到位，请检查后，再复位上料仓"));
		return false;
	}
	if (1 == MANAGER->getInputStatus(QStringLiteral("上料仓空")))
	{
		emit printUILog(QStringLiteral("[Warn] 上料仓有料盘，请取走料盘后，再复位上料仓"));
		return false;
	}
	if (0 != MANAGER->setCylinder(QStringLiteral("上料锁仓"), QStringLiteral("上料仓锁+"), QStringLiteral("上料仓锁-"), 3000, 1))
	{
		emit printUILog(QStringLiteral("[Warn] 上料锁仓锁失败，请检查后，再复位上料仓"));
		return false;
	}

	QString zName = "Feed_Z";
	int zCard = 0, zAxis = 0, zHomeResult = 0;

	if (!MANAGER->findAxis(zName, zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] 上料模组 Feed_Z轴不存在"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] 上料模组 启动Feed_Z轴回原失败"));
		return false;
	}
	zHomeResult = MOTION_INSTANCE->Axis_WaiteHome(zCard, zAxis);
	if (0 != zHomeResult)
	{
		emit printUILog(QStringLiteral("[Error] 上料模组 Feed_Z回原失败"));
		return false;
	}
	if (0 != MANAGER->pointMoveSync("Feed_Init_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] 上料模组 移动到点 Feed_Init_Pos 失败"));
		return false;
	}
	if (0 != MANAGER->setCylinder(QStringLiteral("上料锁仓"), QStringLiteral("上料仓锁+"), QStringLiteral("上料仓锁-"), 3000, 0))
	{
		emit printUILog(QStringLiteral("[Warn] 上料模组 上料锁仓解锁失败"));
	}

	emit printUILog(QStringLiteral("[OK] 上料模组 复位成功，请添加料盘后，启动工作"));
	m_bIsHome = true;
	return true;
}

bool FeedModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] 上料模组正在复位中...,请等待完成"));
		return false;
	}

	m_homeFuture = QtConcurrent::run(this, &FeedModule::moduleReset);
	return true;
}

void FeedModule::setClearMode(bool mode)
{
	m_bClearMode = mode;
	if (mode == false)
	{
		m_bReady = false;
	}
}

void FeedModule::run()
{
	if (runFun())
	{
		setReady(true);
		emit sendReady(FEED);
	}
	else
	{
		emit printUILog(m_strError);
	}
}

bool FeedModule::runFun()
{
	int ret = 0;
	if (!m_bIsHome)
	{
		m_strError = QStringLiteral("[Error] 上料模组未回原，请回原后继续");
		return false; 
	}
	if (m_bClearMode) return true;
	if (m_bReady) return true;

	//1.保证料仓是关闭状态，才动作
	if (0 == MANAGER->getInputStatus(QStringLiteral("上料推入到位")))
	{
		m_strError = QStringLiteral("[Error] 上料仓未推送到位，请检查,关闭上料仓后，再继续");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("上料仓空")))
	{
		MANAGER->pointMoveSyncInterrupable("Feed_Init_Pos");
		m_strError = QStringLiteral("[Error] 上料仓料盘已空，请添加料盘后继续！");
		MANAGER->setCylinder(QStringLiteral("上料锁仓"), QStringLiteral("上料仓锁+"), QStringLiteral("上料仓锁-"), 3000, 0);
		emit hintAddFeedTray();
		return false;
	}

	MANAGER->setCylinder(QStringLiteral("上料锁仓"), QStringLiteral("上料仓锁+"), QStringLiteral("上料仓锁-"), 3000, 1);

	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	RunPoint runPt, tempPt;

	tempPt.dimension.axisNameZ = "Feed_Z";

	while (true)
	{
		if (MANAGER->getInputStatus(QStringLiteral("上料料盘到位"))) break;  //料盘就绪

		tempPt.pos[2] = MANAGER->getAxisPos("Feed_Z") + abs(info.feed_z_offset);
		MANAGER->pointMoveSyncInterrupable(tempPt);
		msleep(50);
		if (MANAGER->getInputStatus(QStringLiteral("上料料盘到位"))) break;  //料盘就绪

		//计算移动的次数	
		if (MANAGER->findPoint("Feed_Init_Pos", runPt))
		{
			double curZPos = MANAGER->getAxisPos(runPt.dimension.axisNameZ);
			if (curZPos > runPt.pos[2] + (info.feed_max_tray_num - 1) * info.feed_z_offset)
			{
				m_strError = QStringLiteral("[Error] 请检查 上料料盘到位感应 是否正常工作");
				return false;
			}
		}
	}

	setReady(true);
	return true;
}
