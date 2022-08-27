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

	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"),  QStringLiteral("��������-"), 1, 3000))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��"));
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�������צ��"), QStringLiteral("�������צ��"), QStringLiteral("�������צ+"), QStringLiteral("�������צ-"), 0, 3000))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �������צ �ɿ�ʧ��"));
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ+"), QStringLiteral("�����Ҽ�צ-"), 0, 3000))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �����Ҽ�צ �ɿ�ʧ��"));
		return false;
	}

	QString xName = "Carry_X";
	int xCard = 0, xAxis = 0, xHomeResult = 0;
	if (!MANAGER->findAxis(xName, xCard, xAxis))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ��Carry_X�᲻����"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(xCard, xAxis))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ������Carry_X���ԭʧ��"));
		return false;
	}

	xHomeResult = MOTION_INSTANCE->Axis_WaiteHome(xCard, xAxis);
	if (0 != xHomeResult)
	{
		emit printUILog(QStringLiteral("[Error] ����Carry_X��ԭʧ��"));
		return false;
	}
	if (0 != MANAGER->pointMoveSync("Carry_Get_Tray_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] ����ģ�� �ƶ�����λ Carry_Get_Tray_Pos ʧ��"));
		return false;
	}

	emit printUILog(QStringLiteral("[OK] ����ģ�鸴λ�ɹ�"));
	setReady(true);
	m_bIsHome = true;
	return true;
}

bool CarryModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] ����ģ�����ڸ�λ��...,��ȴ����"));
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
		m_strError = QStringLiteral("[Error] ����ģ��δ��ԭ�����ԭ�����");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Get_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �ƶ�����λ Carry_Get_Tray_Pos ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�������צ��"), QStringLiteral("�������צ��"), QStringLiteral("�������צ+"), QStringLiteral("�������צ-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ �ɿ�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ+"), QStringLiteral("�����Ҽ�צ-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ �ɿ�ʧ��");
		return false;
	}

	bool rtn = false;
	if (1 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")) &&
		1 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")))
	{
		if (0 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")))
		{
			rtn = feedHaveLaserHave();
		}	
	}
	else if (1 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")) &&
		     0 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")))
	{
		rtn = feedHaveLaserNone();
	}
	else if (0 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")) && 
		     1 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")))
	{
		if (0 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")))
		{
			rtn = feedNoneLaserHave();
		}
	}
	else if (0 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")) &&
		     0 == MANAGER->getInputStatus(QStringLiteral("�������̵�λ")))
	{
		rtn = feedNoneLaserNone();
	}
	if (!rtn)
	{
		return false;
	}
	if (0 != MANAGER->pointMoveSync("Carry_Get_Tray_Pos") != 0)
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �ƶ�����λ Carry_Get_Tray_Pos ʧ��");
		return false;
	}
	return true;
}


bool CarryModule::feedHaveLaserHave()
{
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ �½�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�������צ��"), QStringLiteral("�������צ��"), QStringLiteral("�������צ+"), QStringLiteral("�������צ-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ �н�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ+"), QStringLiteral("�����Ҽ�צ-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ �н�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��");
		return false;
	}
	if ( 0 == MANAGER->getInputStatus(QStringLiteral("�������צ���̸�Ӧ")))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ δ��⵽����");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("�����Ҽ�צ���̸�Ӧ")))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ δ��⵽����");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Put_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �ƶ�����λ Carry_Put_Tray_Pos ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ �½�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�������צ��"), QStringLiteral("�������צ��"), QStringLiteral("�������צ+"), QStringLiteral("�������צ-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ �ɿ�ʧ��");
		return false;
	}	
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ+"), QStringLiteral("�����Ҽ�צ-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ �н�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��");
		return false;
	}

	return true;
}

bool CarryModule::feedHaveLaserNone()
{
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ �½�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�������צ��"), QStringLiteral("�������צ��"), QStringLiteral("�������צ+"), QStringLiteral("�������צ-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ �н�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("�������צ���̸�Ӧ")))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ δ��⵽����");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Put_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �ƶ�����λ Carry_Put_Tray_Pos ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ �½�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�������צ��"), QStringLiteral("�������צ��"), QStringLiteral("�������צ+"), QStringLiteral("�������צ-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �������צ �ɿ�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��");
		return false;
	}
	return true;
}

bool CarryModule::feedNoneLaserHave()
{
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ �½�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ+"), QStringLiteral("�����Ҽ�צ-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ �н�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("�����Ҽ�צ���̸�Ӧ")))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ δ��⵽����");
		return false;
	}
	if (0 != MANAGER->pointMoveSyncInterrupable("Carry_Put_Tray_Pos"))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �ƶ�����λ Carry_Put_Tray_Pos ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ �½�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ��"), QStringLiteral("�����Ҽ�צ+"), QStringLiteral("�����Ҽ�צ-"), 0, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� �����Ҽ�צ �н�ʧ��");
		return false;
	}
	if (0 != MANAGER->doubleCylinder(QStringLiteral("����������"), QStringLiteral("����������"), QStringLiteral("��������+"), QStringLiteral("��������-"), 1, 3000))
	{
		m_strError = QStringLiteral("[Error] ����ģ�� ������������ ����ʧ��");
		return false;
	}
	return true;
}

bool CarryModule::feedNoneLaserNone()
{
	return true;
}