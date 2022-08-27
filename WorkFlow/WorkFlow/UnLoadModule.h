#pragma once
#include "MyModule.h"
#include<QWaitCondition>
#include <QMutex>

//下料模组
class UnLoadModule : public MyModule
{
	Q_OBJECT

public:
	UnLoadModule(QObject *parent);
	~UnLoadModule();

	bool moduleReset();
	bool moduleResetAsync();
	bool unLoadTrayTaked();	//已取走下料模组所有料盘

signals:
	void hintTakeUnloadTray();	//提示取走下料仓料盘

protected:
	void run();
	bool runFun();

private:
	QWaitCondition m_wait;
	QMutex*  m_mutex;
	bool m_isNeedTakeTray;
};
