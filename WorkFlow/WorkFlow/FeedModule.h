#pragma once
#include "MyModule.h"

//上料模组
class FeedModule : public MyModule
{
	Q_OBJECT

public:
	FeedModule(QObject *parent);
	~FeedModule();

	bool moduleReset();
	bool moduleResetAsync();
	void setClearMode(bool mode);

signals:
	void hintAddFeedTray();	//提示增加Tray盘


protected:
	void run();
	bool runFun();

private:
	bool m_bClearMode;	//清料模式，不再上料
};
