#include "GoHome.h"
#include "WorkFlow.h"
#include "LaserModule.h"
#include "FeedModule.h"
#include "UnLoadModule.h"
#include "CarryModule.h"

#include "../../Utility/System/Config.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include <QDebug>

GoHome::GoHome(QObject *parent)
	: QThread(parent)
{
}

GoHome::~GoHome()
{
}

void GoHome::exitThread()
{
	wait(3000);
}

void GoHome::run()
{
	WORKFLOW_INSTANCE->printLog("[Clear]");

	WORKFLOW_INSTANCE->m_feedModule->moduleResetAsync();
	WORKFLOW_INSTANCE->m_carryModule->moduleResetAsync();
	WORKFLOW_INSTANCE->m_laserModule->moduleResetAsync();

	WORKFLOW_INSTANCE->m_unloadModule->moduleResetAsync();

	bool feed = WORKFLOW_INSTANCE->m_feedModule->waitReset();
	bool carry = WORKFLOW_INSTANCE->m_carryModule->waitReset();
	bool scan = WORKFLOW_INSTANCE->m_laserModule->waitReset();
	bool unload = WORKFLOW_INSTANCE->m_unloadModule->waitReset();

	if (feed && carry && scan && unload)
	{
		WORKFLOW_INSTANCE->setSysStatus(SYSTEM_STANDBY);
	}
	else
	{
		WORKFLOW_INSTANCE->setUISysStatus(SYSTEM_UNHOME);
	}
}
