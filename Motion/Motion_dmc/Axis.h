#pragma once
#include <QThread>

struct AxisParam;

class Axis:public QThread
{
	Q_OBJECT

public:
	Axis();
	~Axis();

	short	Init(AxisParam *paxis);
    bool	Reset();
    int		Home();
	int		HomeFinished() const;
	int		WaiteHome();
	int		WaiteHome(int waitTime);
	int     WaitHome(double pos, double len);
    int		MovePos(double pos, double vel = 0, double acc = 0, double dec = 0);
    int		MoveOffset(double offset, double vel = 0, double acc = 0, double dec = 0);
    int		MoveJog(int dir, double vel = 0, double acc = 0, double dec = 0);
	bool    SetPosMM(double pos = 0);
	bool	SetPosPulse(long pos = 0);
	void	GetCurPos(double &pos);
	void	GetPlanPos(double &pos);
	bool	IsMoving();
    bool	Stop(int type = 0);
    bool	StopAndWait(int type = 0); 
	bool	eStop();
	bool	smoothStop();
    int		GearMove(Axis* pAxis, int iGearType, double ratio, long masterSlope = 0);
	const	AxisParam* GetParam();

protected:
    int		SetSpeed(double vel = 0, double acc = 0, double dec = 0);
    bool	WaitStopFlag(int iWait);
    bool	MoveToLimitN(double vel = 0,double acc = 0,double dec =0);
	bool	MoveToLimitP(double vel = 0,double acc = 0,double dec = 0); 
    int		HomeAsCapture();        //捕获回原
    int		HomeAsNormal();         //正常回原
    int		HomeAsSelf();           //自定义回原
    int		HomeFun();
    int		DDHome();
	bool	isHomeP();
	bool	isLimitP();	
	bool	isLimitN();
	bool	isDrvAlarm();
	bool	isReady();
	bool	isMoveOK();
	void	run();

private:
    bool	   m_bInit;
	bool	   m_bExitFlag;
    int		   m_iHomeResult;
    AxisParam* m_pParam;
};
