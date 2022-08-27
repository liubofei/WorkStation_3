#include "axis.h"
#include "../../include/LTDMC.h"
#include "../../include/Motion.h"
#include "../../include/Error.h"
#include "../../include/Common.h"
#include "../../include/Motion.h"
#include "../../Utility/System/Log.h"
#include "../../Utility/Utility/Utility.h"
#include "Io.h"

//设置默认值
#define CHK_DEFUALT_VAL(x, y) if ((x) < 0.000001) \
{ \
	(x) = (y); \
}

Axis::Axis()
{
	m_bInit = false;
	m_iHomeResult = ERR_AXIS_HOME;
	m_pParam = new AxisParam;
	memset(m_pParam, 0, sizeof(AxisParam));
}

Axis::~Axis()
{
	Reset();
	FREE_ANY(m_pParam);
}

short Axis::Init(AxisParam *paxis)
{
	short ret = 0;
	RETURN_CHK(paxis, 1);
	memcpy(m_pParam, paxis, sizeof(AxisParam));
	
	ret = dmc_set_equiv(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->stepvalue);
	LOG_INFO("Axis call dmc_set_equiv(%d,%d,%f)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->stepvalue, ret);
	if (ret)
	{
		LOG_ERR("dmc_set_equiv return error:%d", ret);
		return ERR_MOTOR_API;
	}

	ret = dmc_set_home_pin_logic(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->homeSense, 0);
	LOG_INFO("Axis call dmc_set_home_pin_logic(%d,%d,%d,0)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->homeSense, ret);
	if (ret)
	{
		LOG_ERR("dmc_set_home_pin_logic return error:%d", ret);
		return ERR_MOTOR_API;
	}

	ret = dmc_set_el_mode(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->limitMode, m_pParam->limitSense, m_pParam->stopMode);
	LOG_INFO("Axis call dmc_set_el_mode(%d,%d,%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->limitMode, m_pParam->limitSense, 0, ret);
	if (ret)
	{
		LOG_ERR("dmc_set_el_mode return error:%d", ret);
		return ERR_MOTOR_API;
	}

	ret = dmc_set_dec_stop_time(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->stopTime);
	LOG_INFO("Axis call dmc_set_dec_stop_time(%d,%d,%f)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->stopTime, ret);
	if (ret)
	{
		LOG_ERR("dmc_set_dec_stop_time return error:%d", ret);
		return ERR_MOTOR_API;
	}

	if (EM_AXIS_STEPPER == m_pParam->motorType || EM_AXIS_FLOW == m_pParam->motorType)
	{
		ret = dmc_set_softlimit(m_pParam->cardIndex, m_pParam->axisIndex, 1, 0, 0, m_pParam->limitN*m_pParam->stepvalue, m_pParam->limitP*m_pParam->stepvalue);
	}
	else
	{
		ret = dmc_set_softlimit(m_pParam->cardIndex, m_pParam->axisIndex, 1, 1, 0, m_pParam->limitN*m_pParam->stepvalue, m_pParam->limitP*m_pParam->stepvalue);   //设置限位开关
	}
	LOG_INFO("Axis call dmc_set_softlimit(%d,%d,%d,%d,%d,%f,%f)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, 1, 1, 0, m_pParam->limitN, m_pParam->limitP, ret);
	if (ret)
	{
		LOG_ERR("dmc_set_softlimit return error:%d", ret);
		return ERR_MOTOR_API;
	}


	if(EM_AXIS_STEPPER == m_pParam->motorType || EM_AXIS_FLOW == m_pParam->motorType)
	{
		//步进没有报警 报警 1：允许ALM信号 1：高电平有效 0：立即停止
		ret = dmc_set_alm_mode(m_pParam->cardIndex, m_pParam->axisIndex, 0, 1, 0);  //禁止ALM信号
	}
	else
	{
		//是伺服 报警信号低电平有效
		ret = dmc_set_alm_mode(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->almMode, m_pParam->almSense, 0);	
	}
	LOG_INFO("Axis call dmc_set_alm_mode(%d,%d,%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, 1, 1, 0, ret);

	if (ret)
	{
		LOG_ERR("dmc_set_alm_mode return error:%d", ret);
		return ERR_MOTOR_API;
	}


	if (EM_AXIS_STEPPER != m_pParam->motorType && EM_AXIS_FLOW != m_pParam->motorType)
	{
		ret = dmc_write_sevon_pin(m_pParam->cardIndex, m_pParam->axisIndex, 0);  //打开使能
		LOG_INFO("Axis call dmc_write_sevon_pin(%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, 0, ret);
		if (ret)
		{
			LOG_ERR("card:%d axis%d dmc_write_sevon_pin return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return ERR_MOTOR_API;
		}
	}

	m_bInit = true;
	return RETURN_OK;
}

bool Axis::Reset()
{
	LOG_INFO("card:%d axis%d reset()", m_pParam->cardIndex, m_pParam->axisIndex);
	Stop(0);
	while (ERR_AXIS_MOVING == m_iHomeResult)
	{
		msleep (10);
	}
	return true;
}

int Axis::SetSpeed(double vel, double acc, double dec)
{
	short ret = 0;
	CHK_DEFUALT_VAL(vel, m_pParam->vel);
	CHK_DEFUALT_VAL(acc, m_pParam->accTime);
	CHK_DEFUALT_VAL(dec, m_pParam->decTime);

	ret = dmc_set_profile_unit(m_pParam->cardIndex, m_pParam->axisIndex, vel / 5.0, vel, acc, dec, vel / 10.0);
	LOG_INFO("Axis call dmc_set_profile_unit(%d,%d,0,%.3f,%.3f,%.3f,0)=%d", m_pParam->cardIndex, m_pParam->axisIndex, vel, acc, dec, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_set_profile_unit return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ERR_MOTOR_API;
	}

	ret = dmc_set_s_profile(m_pParam->cardIndex, m_pParam->axisIndex, 0, acc / 4.0);		//S段参数设置为加速度的四分之一
	LOG_INFO("Axis call dmc_set_s_profile(%d,%d,0,%.3f)=%d", m_pParam->cardIndex, m_pParam->axisIndex, acc / 4.0, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_set_s_profile return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ERR_MOTOR_API;
	}

	return RETURN_OK;
}

bool Axis::WaitStopFlag(int iWait)
{
	if (m_bExitFlag)
	{
		//eStop();
		return true;
	}
	msleep(iWait);
	return false;	
}

int Axis::MoveOffset(double offset, double vel, double acc, double dec)
{
	short ret = 0;
	RETURN_CHK(m_bInit, ERR_NOINIT_MOTOR);

	ret = SetSpeed(vel, acc, dec);
	RETURN_CHK(!ret, ret);

	//走绝对坐标
	double curPos = 0.0;
	GetCurPos(curPos);
	double dstPos = curPos + offset;
	ret = dmc_pmove_unit(m_pParam->cardIndex, m_pParam->axisIndex, dstPos, 1);		//0 相对坐标  1绝对坐标
	LOG_INFO("Axis call dmc_pmove_unit(%d,%d,%f,1)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, dstPos, ret);
	if (ret)
	{
		LOG_ERR("Axis call dmc_pmove_unit() return error: %d", ret);
		return ERR_AXIS_TRAP;
	}

	//相对运动实现方式
	//ret = dmc_pmove_unit(m_pParam->cardIndex, m_pParam->axisIndex, offset, 0);		//0 相对坐标  1绝对坐标
	//LOG_INFO("Axis call dmc_pmove_unit(%d,%d,%f,0)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, offset, ret);

	//if (ret)
	//{
	//	LOG_ERR("Axis call dmc_pmove_unit() return error: %d", ret);
	//	return ERR_AXIS_TRAP;
	//}

	return RETURN_OK;
}

int Axis::MovePos(double pos, double vel, double acc, double dec)
{
	if (EM_AXIS_FLOW == m_pParam->motorType)
	{
		return MoveJog(pos > 0 ? 1 : 0, vel, acc, dec);
	}

	int ret = SetSpeed(vel, acc, dec);
	RETURN_CHK(!ret, ret);

	ret = dmc_pmove_unit(m_pParam->cardIndex, m_pParam->axisIndex, pos, 1);	//0 相对  1坐标
	LOG_INFO("Axis call dmc_pmove_unit(%d,%d,%f,1)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, pos, ret);
	if (ret)
	{
		LOG_ERR("Axis call dmc_pmove_unit() return error: %d", ret);
		return ERR_AXIS_TRAP;
	}
	return RETURN_OK;


	//GetCurPos(realPos);
	//offset = pos - realPos;
	//RETURN_CHK(offset > 0.01 || offset < -0.01, 0);
	//return MoveOffset(offset, vel, acc, dec);
}

int Axis::MoveJog(int dir, double vel, double acc, double dec)
{
	short ret = 0;
	RETURN_CHK(m_bInit, ERR_NOINIT_MOTOR);
	ret = SetSpeed(vel, acc, dec);
	RETURN_CHK(!ret, ret);

	ret = dmc_vmove(m_pParam->cardIndex, m_pParam->axisIndex, dir);
	LOG_INFO("Axis call dmc_vmove(%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, dir, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d MoveJog dmc_vmove return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ERR_AXIS_TRAP;
	}
	return RETURN_OK;
}

void Axis::GetCurPos(double &pos)
{
	if (EM_AXIS_STEPPER == m_pParam->motorType || EM_AXIS_FLOW == m_pParam->motorType)
	{
		dmc_get_position_unit(m_pParam->cardIndex, m_pParam->axisIndex, &pos);
	}
	else
	{
		dmc_get_encoder_unit(m_pParam->cardIndex, m_pParam->axisIndex, &pos);
	}
}

void Axis::GetPlanPos(double &pos)
{
	dmc_get_encoder_unit(m_pParam->cardIndex, m_pParam->axisIndex, &pos);
}

bool Axis::IsMoving()
{
	short ret = dmc_check_done(m_pParam->cardIndex, m_pParam->axisIndex);
	return 0 == ret ? true : false;
}

bool Axis::Stop(int type)
{
	m_bExitFlag = true;

	return type ? eStop() : smoothStop();
}

bool Axis::StopAndWait(int type)
{
	RETURN_CHK((type ? eStop() : smoothStop()), false);
	while(IsMoving())
	{
		msleep(10);
	}

	return true;
}

bool Axis::smoothStop()
{
	short ret = dmc_stop(m_pParam->cardIndex, m_pParam->axisIndex, 0);		//0减速停止 1紧急停止
	LOG_INFO("Axis call dmc_stop(%d,%d,0)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_stop return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return false;
	}
	return true;
}

const AxisParam* Axis::GetParam()
{
	return m_pParam;
}

bool Axis::eStop()
{
	short ret = dmc_stop(m_pParam->cardIndex, m_pParam->axisIndex, 1);
	LOG_INFO("Axis call dmc_stop(%d,%d,1)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_stop return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return false;
	}
	return true;
}

bool Axis::SetPosMM(double pos)
{
	short ret = 0;
	RETURN_CHK(!IsMoving(), false);

	ret = dmc_set_position_unit(m_pParam->cardIndex, m_pParam->axisIndex, pos);
	LOG_INFO("Axis call dmc_set_position_unit(%d,%d,%f)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, pos, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_set_position_unit return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return false;
	}

	if ((EM_AXIS_SERVO == m_pParam->motorType) || (EM_AXIS_DDMOTOR == m_pParam->motorType))
	{
		ret = dmc_set_encoder_unit(m_pParam->cardIndex, m_pParam->axisIndex, pos);
		LOG_INFO("Axis call dmc_set_encoder_unit(%d,%d,%f)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, pos, ret);
		if (ret)
		{
			LOG_ERR("card:%d axis%d dmc_set_encoder_unit return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return false;
		}
	}

	return true;
}

bool Axis::SetPosPulse(long pos)
{
	short ret = 0;
	RETURN_CHK(!IsMoving(), false);

	ret = dmc_set_position(m_pParam->cardIndex, m_pParam->axisIndex, pos);
	LOG_INFO("Axis call dmc_set_position(%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, pos, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_set_position return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return false;
	}

	if ((EM_AXIS_SERVO == m_pParam->motorType) || (EM_AXIS_DDMOTOR == m_pParam->motorType))
	{
		ret = dmc_set_encoder(m_pParam->cardIndex, m_pParam->axisIndex, pos);
		LOG_INFO("Axis call dmc_set_encoder(%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, pos, ret);
		if (ret)
		{
			LOG_ERR("card:%d axis%d dmc_set_encoder return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return false;
		}
	}

	return true;
}

bool Axis::isHomeP()
{
	short val;
	IO_INSTANCE->readInBit_Origin(m_pParam->cardIndex, m_pParam->axisIndex, val);
	return val;
}

bool Axis::isLimitP()
{
	short val;
	IO_INSTANCE->readInBit_LimitP(m_pParam->cardIndex, m_pParam->axisIndex, val);
	return val;
}

bool Axis::isLimitN()
{
	short val;
	IO_INSTANCE->readInBit_LimitN(m_pParam->cardIndex, m_pParam->axisIndex, val);
	return val;
}

bool Axis::isDrvAlarm()
{
	short val;
	if (EM_AXIS_FLOW == m_pParam->motorType || EM_AXIS_STEPPER == m_pParam->motorType)
		return false;
	
	IO_INSTANCE->readInBit_Alarm(m_pParam->cardIndex, m_pParam->axisIndex, val);
	return val;
}

bool Axis::isReady()
{
	short val;
	IO_INSTANCE->readInBit_Ready(m_pParam->cardIndex, m_pParam->axisIndex, val);
	return val;
}

bool Axis::isMoveOK()
{
	short val;
	IO_INSTANCE->readInBit_Inplace(m_pParam->cardIndex, m_pParam->axisIndex, val);
	return val;
}

bool Axis::MoveToLimitN(double vel, double acc, double dec)
{
	if (isLimitN() || (m_pParam->limitMode == 0 || m_pParam->limitMode == 3))	//在限位上, 也直接查找复位信号
	{
		LOG_INFO("card:%d, axis:%d need't move to limitN ", m_pParam->cardIndex, m_pParam->axisIndex);
		return true;
	}

	//最大距离
	if (MoveOffset(m_pParam->limitN - m_pParam->limitP, vel, acc, dec))
	{
		return false;
	}

	LOG_INFO("Card:%d,Axis:%d Start move to limitN.", m_pParam->cardIndex, m_pParam->axisIndex);
	while (IsMoving())
	{
		RETURN_CHK(!WaitStopFlag(20), false);
	}

	return isLimitN();
}

bool Axis::MoveToLimitP(double vel, double acc, double dec)
{
	if (isLimitP() || (m_pParam->limitMode == 0 || m_pParam->limitMode == 2))	//在限位上
	{
		LOG_INFO("card:%d, axis:%d need't move to limitP ", m_pParam->cardIndex, m_pParam->axisIndex + 1);
		return true;
	}

	//最大距离
	if (MoveOffset(m_pParam->limitP - m_pParam->limitN,vel,acc,dec))
	{
		return false;
	}

	LOG_INFO("Card:%d,Axis:%d Start move to limitP.", m_pParam->cardIndex, m_pParam->axisIndex);
	while (IsMoving()) 
	{
		RETURN_CHK(!WaitStopFlag(20), false);
	}

	return isLimitP();
}

int Axis::DDHome()
{
	unsigned short card_index = (m_pParam->homeType)>>16 & 0xff;
	unsigned short out_index = (m_pParam->homeType)>>8 & 0xff;

	IO_INSTANCE->writeOutBit_Self(card_index, out_index, 1);
	msleep(200);
	IO_INSTANCE->writeOutBit_Self(card_index, out_index, 0);

	while(!isHomeP())
	{
		RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
	}

	msleep(200);     //延时等待停稳
	return RETURN_OK;
}

int Axis::HomeAsCapture()
{
	long pos = 0;
	short ret = 0;
	ret = dmc_set_homelatch_mode(m_pParam->cardIndex, m_pParam->axisIndex, 1, 1, 0);    //设置原点锁存
	LOG_INFO("Axis call dmc_set_homelatch_mode(%d,%d,%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, 1, 1, 0, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_set_homelatch_mode return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ERR_AXIS_CAPTURE;
	}

	ret = dmc_reset_homelatch_flag(m_pParam->cardIndex, m_pParam->axisIndex);   //清除原点锁存标识
	LOG_INFO("Axis call dmc_reset_homelatch_flag(%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, ret);
	if (ret)
	{
		LOG_ERR("card:%d axis%d dmc_reset_homelatch_flag return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ERR_AXIS_CAPTURE;
	}

	if (ret = MoveOffset(m_pParam->sreachhomePos, m_pParam->homeVel))
	{//运动
		LOG_ERR("card:%d axis%d MoveOffset return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ret;
	}

	LOG_INFO("Card:%d,Axis:%d start home as capture.", m_pParam->cardIndex, m_pParam->axisIndex);
	while(0 == dmc_get_homelatch_flag(m_pParam->cardIndex, m_pParam->axisIndex))
	{//检测原点位置
		RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
	}

	LOG_INFO("Axis call dmc_get_homelatch_flag(%d,%d)=1.", m_pParam->cardIndex, m_pParam->axisIndex);
	StopAndWait();   //先停止，再走到目标位置
	if (abs(m_pParam->inHomeOffset)>0)
	{//二次回原
		//第一次碰到原点后回退
		if (ret = MoveOffset(m_pParam->inHomeOffset, m_pParam->homeVel*0.6))
		{//运动
			LOG_ERR("card:%d axis%d MoveOffset return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return ret;
		}
		while (IsMoving())
		{//等待移动结束
			RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
		}
		//再找一次原点
		ret = dmc_reset_homelatch_flag(m_pParam->cardIndex, m_pParam->axisIndex);   //清除原点锁存标识
		LOG_INFO("Axis call dmc_reset_homelatch_flag(%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		if (ret)
		{
			LOG_ERR("card:%d axis%d dmc_reset_homelatch_flag return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return ERR_AXIS_CAPTURE;
		}
		if (ret = MoveOffset(-2*m_pParam->afterhomeOffset, m_pParam->homeVel*0.1))
		{//运动
			LOG_ERR("card:%d axis%d MoveOffset return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return ret;
		}

		LOG_INFO("Card:%d,Axis:%d start home as capture.", m_pParam->cardIndex, m_pParam->axisIndex);
		while(0 == dmc_get_homelatch_flag(m_pParam->cardIndex, m_pParam->axisIndex))
		{//检测原点位置
			RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
		}

		LOG_INFO("Axis call dmc_get_homelatch_flag(%d,%d)=1.", m_pParam->cardIndex, m_pParam->axisIndex);
		StopAndWait();   //先停止，再走到目标位置
	}

	pos = dmc_get_homelatch_value(m_pParam->cardIndex, m_pParam->axisIndex);
	LOG_INFO("Axis call dmc_get_homelatch_value(%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, pos);
	if (ret = MovePos(pos + m_pParam->afterhomeOffset, m_pParam->homeVel*0.1))
	{
		LOG_ERR("card:%d axis%d HomeAsCapture MovePos return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		return ret;
	}

	while (IsMoving())
	{//等待移动结束
		RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
	}

	return RETURN_OK;
}

int Axis::HomeAsNormal()
{
	short ret = 0;

	//ret = SetSpeed(m_pParam->homeVel);

	ret = dmc_set_home_profile_unit(m_pParam->cardIndex, m_pParam->axisIndex, 0, m_pParam->homeVel, m_pParam->homeAccTime, m_pParam->homeDecTime);

	RETURN_CHK(!ret, ret);

	//默认低速回零,一次回零加回找
	ret = dmc_set_homemode(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->homeDir > 0 ? 1 : 0, 1, 0, 1);
	LOG_INFO("Axis call dmc_set_homemode(%d,%d,%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->homeDir > 0 ? 1 : 0, 0, 1, ret);
	RETURN_CHK(!ret, ret);

	ret = dmc_home_move(m_pParam->cardIndex, m_pParam->axisIndex);
	LOG_INFO("Axis call dmc_home_move(%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, ret);
	RETURN_CHK(!ret, ret);

	while(IsMoving())
	{
		RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
	}

	if (abs(m_pParam->inHomeOffset)>0)
	{//二次回原
		//第一次碰到原点后回退
		if (MoveOffset(m_pParam->inHomeOffset, m_pParam->homeVel / 2))
		{
			LOG_ERR("card:%d axis%d MoveOffset return error:%d", m_pParam->cardIndex, m_pParam->axisIndex, ret);
			return ret;
		}

		while (IsMoving())
		{
			RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
		}

		ret = dmc_set_home_profile_unit(m_pParam->cardIndex, m_pParam->axisIndex, 0, m_pParam->homeVel / 4.0, m_pParam->homeAccTime, m_pParam->homeDecTime);
		RETURN_CHK(!ret, ret);

		//再找一次原点
		ret = dmc_set_homemode(m_pParam->cardIndex, m_pParam->axisIndex, m_pParam->homeDir > 0 ? 1 : 0, 1, 0, 1);
		LOG_INFO("Axis call dmc_set_homemode(%d,%d,%d,%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, 
			m_pParam->homeDir > 0 ? 1 : 0, 0, 1, ret);
		RETURN_CHK(!ret, ret);

		ret = dmc_home_move(m_pParam->cardIndex, m_pParam->axisIndex);
		LOG_INFO("Axis call dmc_home_move(%d,%d)=%d.", m_pParam->cardIndex, m_pParam->axisIndex, ret);
		RETURN_CHK(!ret, ret);

		while(IsMoving())
		{
			RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
		}
	}

	RETURN_CHK(m_pParam->afterhomeOffset, RETURN_OK);

	MoveOffset(m_pParam->afterhomeOffset);
	while(IsMoving())
	{
		RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
	}

	return RETURN_OK;
}

int Axis::HomeAsSelf()
{
	int cnt = 0;
	int error_num = 0;
	double dpos1 = 0.0;
	double dpos2 = 0.0;
	long offset = 200;
	double vel = m_pParam->homeVel;
	long pos = m_pParam->sreachhomePos;
	bool bInHome = true;    //目标位置是否有原点信号

	LOG_INFO("start move Home AsSelf. card%d axis%d", m_pParam->cardIndex, m_pParam->axisIndex);
	while (true)
	{
		error_num = MovePos(pos, vel);
		if (error_num)
		{
			LOG_ERR("HomeAsSelf MovePos return error:%d", error_num);
			return ERR_AXIS_TRAP;
		}

		while(IsMoving() && isHomeP() == bInHome)
		{
			RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
		}

		GetCurPos(dpos1);
		StopAndWait();
		GetCurPos(dpos2);
		offset = (dpos2 < dpos1 ? 1 : -1) * abs(offset) / 2;
		pos = dpos1 + offset;
		bInHome = !bInHome;
		vel /= 2;
		if (3 == ++cnt)
		{//第三次，直接回到原点了
			MovePos(dpos1 + m_pParam->afterhomeOffset, m_pParam->homeVel);
			break;
		}
	}

	//等待运动结束
	while (IsMoving())
	{
		RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
	}
	return RETURN_OK;
}

int Axis::HomeFun()
{
	int ret = 0;
	if (EM_AXIS_DDMOTOR == m_pParam->motorType)
	{
		return DDHome();
	}
	else if (EM_AXIS_FLOW == m_pParam->motorType)
	{
		SetPosPulse();
		return RETURN_OK;
	}

	if (EM_AXIS_LIMITN == m_pParam->homeDir)
	{
		RETURN_CHK(MoveToLimitN(m_pParam->homeVelToLimit), ERR_AXIS_TRAP);
	}
	else if (EM_AXIS_LIMITP == m_pParam->homeDir)
	{
		RETURN_CHK(MoveToLimitP(m_pParam->homeVelToLimit), ERR_AXIS_TRAP);
	}

	if (isHomeP() && m_pParam->inHomeOffset)
	{
		MoveOffset(m_pParam->inHomeOffset);
		while(IsMoving())
		{
			RETURN_CHK(!WaitStopFlag(20), ERR_AXIS_HOME);
		}
	}

	if (EM_HOME_SPECIAL1 == m_pParam->homeType)
	{
		ret = HomeAsCapture();
	}
	else if (EM_HOME_SPECIAL2 == m_pParam->homeType || EM_HOME_NORMAL == m_pParam->homeType)
	{
		ret = HomeAsNormal();
	}
	else if (EM_HOME_SELF == m_pParam->homeType)
	{
		ret = HomeAsSelf();
	}

	RETURN_CHK(!ret, ret);

	msleep(100);
	if (!SetPosPulse())
	{
		return ERR_SET_HOMEPOS;
	}

	return RETURN_OK;
}

int Axis::Home()
{
	m_iHomeResult = ERR_AXIS_MOVING;  //回原中
	LOG_INFO("card:%d axis%d Home()", m_pParam->cardIndex, m_pParam->axisIndex);
	m_bExitFlag = false;
	start();
	return RETURN_OK;
}

int Axis::HomeFinished() const
{
	return m_iHomeResult;
}

int	Axis::WaiteHome()
{
	while (isRunning())
	{
		msleep(10);
	}
	return m_iHomeResult;
}

int	Axis::WaiteHome(int waitTime)
{
	int time = 0;
	while (isRunning())
	{
		msleep(10);
		time += 10;
		if (time > waitTime)
		{
			Stop();
			return 1;
		}
	}

	return m_iHomeResult;
}

int Axis::WaitHome(double pos, double len)
{
	double curPos = 0;
	double limitPos = 0;
	int time = 0;

	if (0 == m_pParam->homeDir)
	{
		limitPos = pos + abs(len);
	}
	else if (1 == m_pParam->homeDir)
	{
		limitPos = pos - abs(len);
	}

	while (isRunning())
	{
		GetCurPos(curPos);
		msleep(10);
		time += 10;
		if (0 == m_pParam->homeDir)
		{
			if (curPos >= limitPos)
			{
				Stop();
				return 1;
			}
		}
		else if (1 == m_pParam->homeDir)
		{
			if (curPos <= limitPos)
			{
				Stop();
				return 1;
			}
		}
	}

	return m_iHomeResult;
}

void Axis::run()
{
	m_iHomeResult = HomeFun();
	LOG_INFO("Card:%d Axis:%d home return %d", m_pParam->cardIndex, m_pParam->axisIndex, m_iHomeResult);
}