#pragma once
#include "MyModule.h"

//����ģ��
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
	void hintAddFeedTray();	//��ʾ����Tray��


protected:
	void run();
	bool runFun();

private:
	bool m_bClearMode;	//����ģʽ����������
};
