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

	if (1 == MANAGER->getInputStatus(QStringLiteral("�������̸�Ӧ")))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �������̸�Ӧ��Ӧ�������̣����ܸ�λ"));
		return false;
	}
	if (1 == MANAGER->getInputStatus(QStringLiteral("�������ϸ�Ӧ")))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �������ϸ�Ӧ��Ӧ�����̣����ܸ�λ"));
		return false;
	}

	if (!MANAGER->findAxis(zName, zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� Unload_Z�᲻����"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� ����Unload_Z���ԭʧ��"));
		return false;
	}
	zHomeResult = MOTION_INSTANCE->Axis_WaiteHome(zCard, zAxis);
	if (zHomeResult != 0)
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� Unload_Z��ԭʧ��"));
		return false;
	}

	if (0 != MANAGER->pointMoveSync("UnLoad_Init_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �ƶ�����λ UnLoad_Init_Pos ʧ��"));
		return false;
	}

	emit printUILog(QStringLiteral("[OK] ����ģ�鸴λ�ɹ�"));
	setReady(true);
	m_bIsHome = true;
	return true;
}

bool UnLoadModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] ����ģ�����ڸ�λ��...,��ȴ����"));
		return false;
	}

	m_homeFuture = QtConcurrent::run(this, &UnLoadModule::moduleReset);
	return true;
}

bool UnLoadModule::unLoadTrayTaked()
{
	if (m_isNeedTakeTray)
	{
		if (0 == MANAGER->getInputStatus(QStringLiteral("�������ϸ�Ӧ")))
		{
			m_mutex->lock();
			m_wait.wakeAll();
			m_mutex->unlock();
			m_isNeedTakeTray = false;
			return true;
		}
		else
		{
			emit printUILog(QStringLiteral("[Error] ����ģ�� �������ϸ�Ӧ��Ӧ�����ϣ�����"));
			return false;
		}
	}
	else
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� ��ǰ״̬����Ҫȡ������"));
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
		m_strError = QStringLiteral("[Error] ���ϲ�δ��ԭ�����ԭ�����");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("�������̸�Ӧ")))
	{
		m_strError = QStringLiteral("[OK] �������̸�Ӧ δ��Ӧ�����̣��ѷ���");
		return true;
	}

	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	double offset = -info.feed_z_offset;
	MANAGER->axisMoveOffset("Unload_Z", offset);
	MANAGER->axisWaitStop("Unload_Z");

	if (1 == MANAGER->getInputStatus(QStringLiteral("�������ϸ�Ӧ")))
	{
		m_isNeedTakeTray = true;
		emit hintTakeUnloadTray();

		m_mutex->lock();
		m_wait.wait(m_mutex);
		m_mutex->unlock();

		if (0 != MANAGER->pointMoveSync("UnLoad_Init_Pos"))
		{
			emit printUILog(QStringLiteral("[Error] ����ģ�� �ƶ�����λ UnLoad_Init_Pos ʧ��"));
			return false;
		}
	}

	return true;
}
