#pragma once
#include "MyModule.h"
#include<QWaitCondition>
#include <QMutex>

//����ģ��
class UnLoadModule : public MyModule
{
	Q_OBJECT

public:
	UnLoadModule(QObject *parent);
	~UnLoadModule();

	bool moduleReset();
	bool moduleResetAsync();
	bool unLoadTrayTaked();	//��ȡ������ģ����������

signals:
	void hintTakeUnloadTray();	//��ʾȡ�����ϲ�����

protected:
	void run();
	bool runFun();

private:
	QWaitCondition m_wait;
	QMutex*  m_mutex;
	bool m_isNeedTakeTray;
};
