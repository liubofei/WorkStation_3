#include "CarryModule.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"

CarryModule::CarryModule(QObject *parent)
	: MyModule(parent)
{
}

CarryModule::~CarryModule()
{
}

bool CarryModule::moduleReset()
{
	setReady(false);
	m_bIsHome = false;

	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"),  QStringLiteral("搬运升降-"), 1, 3000))
	{
		emit printUILog(QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败"));
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运左夹爪紧"), QStringLiteral("搬运左夹爪松"), QStringLiteral("搬运左夹爪+"), QStringLiteral("搬运左夹爪-"), 0, 3000))
	{
		emit printUILog(QStringLiteral("[Error] 搬运模组 搬运左夹爪 松开失败"));
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运右夹爪紧"), QStringLiteral("搬运右夹爪松"), QStringLiteral("搬运右夹爪+"), QStringLiteral("搬运右夹爪-"), 0, 3000))
	{
		emit printUILog(QStringLiteral("[Error] 搬运模组 搬运右夹爪 松开失败"));
		return false;
	}

	QString xName = "Carry_X";
	int xCard = 0, xAxis = 0, xHomeResult = 0;
	if (!MANAGER->findAxis(xName, xCard, xAxis))
	{
		emit printUILog(QStringLiteral("[Error] 搬运模组Carry_X轴不存在"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(xCard, xAxis))
	{
		emit printUILog(QStringLiteral("[Error] 搬运模组启动Carry_X轴回原失败"));
		return false;
	}

	xHomeResult = MOTION_INSTANCE->Axis_WaiteHome(xCard, xAxis);
	if (0 != xHomeResult)
	{
		emit printUILog(QStringLiteral("[Error] 搬运Carry_X回原失败"));
		return false;
	}
	if (0 != MANAGER->pointMoveSync("Carry_Get_Tray_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] 搬运模组 移动到点位 Carry_Get_Tray_Pos 失败"));
		return false;
	}

	emit printUILog(QStringLiteral("[OK] 搬运模块复位成功"));
	setReady(true);
	m_bIsHome = true;
	return true;
}

bool CarryModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] 搬运模组正在复位中...,请等待完成"));
		return false;
	}

	m_homeFuture = QtConcurrent::run(this, &CarryModule::moduleReset);
	return true;
}

void CarryModule::run()
{
	setReady(false);

	if (runFun())
	{
		setReady(true);
		emit sendReady(CARRY);
	}
	else
	{
		emit printUILog(m_strError);
	}
}

bool CarryModule::runFun()
{
	if (!m_bIsHome)
	{
		m_strError = QStringLiteral("[Error] 搬运模组未回原，请回原后继续");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Get_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 移动到点位 Carry_Get_Tray_Pos 失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运左夹爪紧"), QStringLiteral("搬运左夹爪松"), QStringLiteral("搬运左夹爪+"), QStringLiteral("搬运左夹爪-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 松开失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运右夹爪紧"), QStringLiteral("搬运右夹爪松"), QStringLiteral("搬运右夹爪+"), QStringLiteral("搬运右夹爪-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 松开失败");
		return false;
	}

	bool rtn = false;
	if (1 == MANAGER->getInputStatus(QStringLiteral("上料料盘到位")) &&
		1 == MANAGER->getInputStatus(QStringLiteral("镭码料盘到位")))
	{
		if (0 == MANAGER->getInputStatus(QStringLiteral("下料料盘到位")))
		{
			rtn = feedHaveLaserHave();
		}	
	}
	else if (1 == MANAGER->getInputStatus(QStringLiteral("上料料盘到位")) &&
		     0 == MANAGER->getInputStatus(QStringLiteral("镭码料盘到位")))
	{
		rtn = feedHaveLaserNone();
	}
	else if (0 == MANAGER->getInputStatus(QStringLiteral("上料料盘到位")) && 
		     1 == MANAGER->getInputStatus(QStringLiteral("镭码料盘到位")))
	{
		if (0 == MANAGER->getInputStatus(QStringLiteral("下料料盘到位")))
		{
			rtn = feedNoneLaserHave();
		}
	}
	else if (0 == MANAGER->getInputStatus(QStringLiteral("上料料盘到位")) &&
		     0 == MANAGER->getInputStatus(QStringLiteral("镭码料盘到位")))
	{
		rtn = feedNoneLaserNone();
	}
	if (!rtn)
	{
		return false;
	}
	if (0 != MANAGER->pointMoveSync("Carry_Get_Tray_Pos") != 0)
	{
		m_strError = QStringLiteral("[Error] 搬运模组 移动到点位 Carry_Get_Tray_Pos 失败");
		return false;
	}
	return true;
}


bool CarryModule::feedHaveLaserHave()
{
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 下降失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运左夹爪紧"), QStringLiteral("搬运左夹爪松"), QStringLiteral("搬运左夹爪+"), QStringLiteral("搬运左夹爪-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 夹紧失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运右夹爪紧"), QStringLiteral("搬运右夹爪松"), QStringLiteral("搬运右夹爪+"), QStringLiteral("搬运右夹爪-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 夹紧失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败");
		return false;
	}
	if ( 0 == MANAGER->getInputStatus(QStringLiteral("搬运左夹爪料盘感应")))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 未检测到料盘");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("搬运右夹爪料盘感应")))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 未检测到料盘");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Put_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 移动到点位 Carry_Put_Tray_Pos 失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 下降失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运左夹爪紧"), QStringLiteral("搬运左夹爪松"), QStringLiteral("搬运左夹爪+"), QStringLiteral("搬运左夹爪-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 松开失败");
		return false;
	}	
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运右夹爪紧"), QStringLiteral("搬运右夹爪松"), QStringLiteral("搬运右夹爪+"), QStringLiteral("搬运右夹爪-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 夹紧失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败");
		return false;
	}

	return true;
}

bool CarryModule::feedHaveLaserNone()
{
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 下降失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运左夹爪紧"), QStringLiteral("搬运左夹爪松"), QStringLiteral("搬运左夹爪+"), QStringLiteral("搬运左夹爪-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 夹紧失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("搬运左夹爪料盘感应")))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 未检测到料盘");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Put_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 移动到点位 Carry_Put_Tray_Pos 失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 下降失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运左夹爪紧"), QStringLiteral("搬运左夹爪松"), QStringLiteral("搬运左夹爪+"), QStringLiteral("搬运左夹爪-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运左夹爪 松开失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败");
		return false;
	}
	return true;
}

bool CarryModule::feedNoneLaserHave()
{
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 下降失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运右夹爪紧"), QStringLiteral("搬运右夹爪松"), QStringLiteral("搬运右夹爪+"), QStringLiteral("搬运右夹爪-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 夹紧失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("搬运右夹爪料盘感应")))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 未检测到料盘");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Put_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 移动到点位 Carry_Put_Tray_Pos 失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 下降失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运右夹爪紧"), QStringLiteral("搬运右夹爪松"), QStringLiteral("搬运右夹爪+"), QStringLiteral("搬运右夹爪-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运右夹爪 夹紧失败");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("搬运升降升"), QStringLiteral("搬运升降降"), QStringLiteral("搬运升降+"), QStringLiteral("搬运升降-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] 搬运模组 搬运升降气缸 升起失败");
		return false;
	}
	return true;
}

bool CarryModule::feedNoneLaserNone()
{
	return true;
}