#include "IOMonitor.h"
#include "WorkFlow.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../../Utility/System/Config.h"
#include <QDebug>

IOMonitor::IOMonitor(QObject *parent)
	: QThread(parent)
{
	CONFIG_INSTANCE->getCardInfo(m_vCardInfo);
}

IOMonitor::~IOMonitor()
{

}

void	IOMonitor::run()
{
	short val   = 0;
	short step  = 0;	
	static bool eStopPressed = false;
	while (!isInterruptionRequested())
	{
		SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
		switch (step)
		{
			case 0:
			{			
				if (MANAGER->getInputStatus(QStringLiteral("��ͣ")) && !eStopPressed)
				{
					eStopPressed = true;
					WORKFLOW_INSTANCE->stopWorking();
					break;
				}
				else if (!MANAGER->getInputStatus(QStringLiteral("��ͣ")) && eStopPressed)
				{
					eStopPressed = false;
				}								
			}
			case 1:
			{
				for (const auto &cardInfo : m_vCardInfo)
				{
					for (const auto &axisInfo : cardInfo.vecAxisParam)
					{
						if (0 == axisInfo.motorType && axisInfo.enable)
						{
							MOTION_INSTANCE->ReadInBit_Alarm(axisInfo.cardIndex, axisInfo.axisIndex, val);
							if (val)
							{
								WORKFLOW_INSTANCE->stopWorking();
								MANAGER->setOutputStatus(QStringLiteral("����Z��ɲ��"), 0);
								MANAGER->setOutputStatus(QStringLiteral("����Z��ɲ��"), 0);
								WORKFLOW_INSTANCE->setSysStatus(SYSTEM_ERROR);
								WORKFLOW_INSTANCE->printLog(tr("[Error] %1Axis servo alarm").arg(axisInfo.axisName));
								return;
							}
						}
					}
				}
			}
			case 2:
			{
				if (MANAGER->getInputStatus(QStringLiteral("��λ")))
				{
					WORKFLOW_INSTANCE->startHoming();
				}
			}
			case 3:
			{
				if (sysInfo.enableSafeDoor)
				{
					if (!MANAGER->getInputStatus(QStringLiteral("�Ž�")))
					{
						WORKFLOW_INSTANCE->printLog(QStringLiteral("[Warn] �Ž�����"));
						WORKFLOW_INSTANCE->setSysStatus(SYSTEM_PAUSE);
						setWorkPause();
					}			
				}
			}
			case 5:
			{
				static bool bPause = false;
				if (MANAGER->getInputStatus(QStringLiteral("��ͣ")))
				{
					if (!bPause)
					{
						WORKFLOW_INSTANCE->printLog(QStringLiteral("[Warn] ��ͣ��ť����"));
						WORKFLOW_INSTANCE->setSysStatus(SYSTEM_PAUSE);
						setWorkPause();
						bPause = true;		
					}
				}
				else
				{
					bPause = false;
				}
			}
			case 6:
			{
				if (MANAGER->getInputStatus(QStringLiteral("����")))
				{
					resetWorkPauseFlag();
					WORKFLOW_INSTANCE->startWorking();
				}
			}
		}

		msleep(50);
	}

	qDebug() << "IOMonitor::run exit";
}

void IOMonitor::setWorkPause()
{
	MANAGER->setPauseFlag(true);
	MANAGER->setContinueFlag(false);
}

void IOMonitor::resetWorkPauseFlag()
{
	MANAGER->setPauseFlag(false);
	MANAGER->setContinueFlag(false);
}

void IOMonitor::exitThread()
{
	requestInterruption();
	wait(100);
}
