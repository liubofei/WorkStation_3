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
	
	if (0 == MANAGER->getInputStatus(QStringLiteral("�������뵽λ")))
	{
		emit printUILog(QStringLiteral("[Warn] ���ϲ�δ���뵽λ��������ٸ�λ���ϲ�"));
		return false;
	}
	if (1 == MANAGER->getInputStatus(QStringLiteral("���ϲֿ�")))
	{
		emit printUILog(QStringLiteral("[Warn] ���ϲ������̣���ȡ�����̺��ٸ�λ���ϲ�"));
		return false;
	}
	if (0 != MANAGER->setCylinder(QStringLiteral("��������"), QStringLiteral("���ϲ���+"), QStringLiteral("���ϲ���-"), 3000, 1))
	{
		emit printUILog(QStringLiteral("[Warn] ����������ʧ�ܣ�������ٸ�λ���ϲ�"));
		return false;
	}

	QString zName = "Feed_Z";
	int zCard = 0, zAxis = 0, zHomeResult = 0;

	if (!MANAGER->findAxis(zName, zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� Feed_Z�᲻����"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(zCard, zAxis))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� ����Feed_Z���ԭʧ��"));
		return false;
	}
	zHomeResult = MOTION_INSTANCE->Axis_WaiteHome(zCard, zAxis);
	if (0 != zHomeResult)
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� Feed_Z��ԭʧ��"));
		return false;
	}
	if (0 != MANAGER->pointMoveSync("Feed_Init_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �ƶ����� Feed_Init_Pos ʧ��"));
		return false;
	}
	if (0 != MANAGER->setCylinder(QStringLiteral("��������"), QStringLiteral("���ϲ���+"), QStringLiteral("���ϲ���-"), 3000, 0))
	{
		emit printUILog(QStringLiteral("[Warn] ����ģ�� �������ֽ���ʧ��"));
	}

	emit printUILog(QStringLiteral("[OK] ����ģ�� ��λ�ɹ�����������̺���������"));
	m_bIsHome = true;
	return true;
}

bool FeedModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] ����ģ�����ڸ�λ��...,��ȴ����"));
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
		m_strError = QStringLiteral("[Error] ����ģ��δ��ԭ�����ԭ�����");
		return false; 
	}
	if (m_bClearMode) return true;
	if (m_bReady) return true;

	//1.��֤�ϲ��ǹر�״̬���Ŷ���
	if (0 == MANAGER->getInputStatus(QStringLiteral("�������뵽λ")))
	{
		m_strError = QStringLiteral("[Error] ���ϲ�δ���͵�λ������,�ر����ϲֺ��ټ���");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("���ϲֿ�")))
	{
		MANAGER->pointMoveSyncInterrupable("Feed_Init_Pos");
		m_strError = QStringLiteral("[Error] ���ϲ������ѿգ���������̺������");
		MANAGER->setCylinder(QStringLiteral("��������"), QStringLiteral("���ϲ���+"), QStringLiteral("���ϲ���-"), 3000, 0);
		emit hintAddFeedTray();
		return false;
	}

	MANAGER->setCylinder(QStringLiteral("��������"), QStringLiteral("���ϲ���+"), QStringLiteral("���ϲ���-"), 3000, 1);

	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	RunPoint runPt, tempPt;

	tempPt.dimension.axisNameZ = "Feed_Z";

	while (true)
	{
		if (MANAGER->getInputStatus(QStringLiteral("�������̵�λ"))) break;  //���̾���

		tempPt.pos[2] = MANAGER->getAxisPos("Feed_Z") + abs(info.feed_z_offset);
		MANAGER->pointMoveSyncInterrupable(tempPt);
		msleep(50);
		if (MANAGER->getInputStatus(QStringLiteral("�������̵�λ"))) break;  //���̾���

		//�����ƶ��Ĵ���	
		if (MANAGER->findPoint("Feed_Init_Pos", runPt))
		{
			double curZPos = MANAGER->getAxisPos(runPt.dimension.axisNameZ);
			if (curZPos > runPt.pos[2] + (info.feed_max_tray_num - 1) * info.feed_z_offset)
			{
				m_strError = QStringLiteral("[Error] ���� �������̵�λ��Ӧ �Ƿ���������");
				return false;
			}
		}
	}

	setReady(true);
	return true;
}
