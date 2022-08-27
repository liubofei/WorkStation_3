#pragma once
#include "MyModule.h"

//°áÔËÄ£×é
class CarryModule : public MyModule
{
	Q_OBJECT

public:
	CarryModule(QObject *parent);
	~CarryModule();

	bool moduleReset();
	bool moduleResetAsync();

protected:
	void run();
	bool runFun();

private:
	bool feedHaveLaserHave();
	bool feedHaveLaserNone();
	bool feedNoneLaserHave();
	bool feedNoneLaserNone();
};
