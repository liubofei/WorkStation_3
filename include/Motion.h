#pragma once
#include <QSemaphore>
#include <vector>
#include <QtConcurrent/QtConcurrent>
#include <bitset>

//电机及运动相关

#define INVALID_AXIS		-1		//无效轴
#define MOTOR_MAX_NAME		36		//名称
#define MOTOR_MAX_AXIS		6       //最大多少轴？
#define COOL_CNT			2		//每张卡只能有2个坐标系
#define CRD_AXIS_CNT		4		//每个坐标系最多4个轴
#define SAME_PULSE_OFFSET	5		//差距多少个脉冲认为位置没有变化
#define MAX_AXISCNT			8


//以下自由配置信号是否取反
#define DMC_CFG			"dmc_cfg"
#define POSITIVE_SENCE	"positive_sence"        //正限位
#define NEGATIVE_SENCE	"negative_sence"        //负限位
#define ALARM_SENCE		"alarm_sence"           //报警信号
#define HOME_SENCE		"home_sence"            //原点信号
#define GPI_SENCE		"gpi_sence"             //通用输入
#define GPIEXT_SENCE	"gpiext_sence"          //扩展卡通用输入
#define ENABLE_SENCE	"enable_sence"          //伺服使能
#define CLEAR_SENCE		"clear_sence"           //清除报警
#define GPO_SENCE		"gpo_sence"             //通用输出
#define GPOEXT_SENCE	"gpoext_sence"          //扩展卡通用输出

enum EM_IO_TYPE
{//io类型
	EM_IO_START = 0,		//开始io
	EM_IO_RESET,			//复位io
	EM_IO_ESTOP,			//急停
	EM_IO_PAUSE,			//暂停
	EM_IO_STOP,				//停止操作IO
	EM_IO_USUALLY,			//常用IO
	EM_IO_BRAKE,			//刹车IO
	EM_IO_OTHER,			//其它
};


struct STM_CARD  //卡信息
{
	unsigned short cardIndex;   //卡索引
	unsigned short axisCnt;     //轴个数
	unsigned short ioCnt;       //主io位数
	unsigned short extCnt;      //扩展模块个数
	unsigned short cntType;     //连接卡连接方式
	STM_CARD()
	{
		cardIndex	= 0;
		axisCnt		= 0;
		ioCnt		= 0;
		extCnt		= 0;
		cntType		= 0;
	}
};

enum EM_AXIS_STATUS_TYPE
{
	EM_AXIS_ALARM	= 1,		//驱动报警
	EM_AXIS_LIMIT_P = 5,		//限位触发
	EM_AXIS_LIMIT_L = 6,		//
	EM_AXIS_ESTOP	= 8,		//急停io
	EM_AXIS_ENABLE	= 9,		//使能标志
	EM_AXIS_MOVING	= 10,		//规划器运动标志

};

enum EM_CRDID
{//坐标ID，每个卡只能有2个
	EM_CRD_FST = 1,
	EM_CRD_SEC,
};


enum EM_AXIS_TYPE
{//轴类型
	EM_AXIS_SERVO = 0,      //伺服
	EM_AXIS_STEPPER,        //步进电机
	EM_AXIS_DDMOTOR,        //DD马达
	EM_AXIS_FLOW,           //流水线皮带，不需要回原
};

enum EM_GPIO_TYPE
{//IO信号类型
	EM_GPO = 0,     //通用输出  输出
	EM_GPI,         //通用输入
	EM_LIMIT_POS,   //正限位
	EM_LIMIT_NEG,   //负限位
	EM_ALARM,       //报警信号
	EM_HOME,        //原点信号
	EM_ENABLE,      //伺服使能  输出
	EM_CLEAR,       //清除报警  输出
	EM_ADC,         //模拟量
	EM_RDY,		    //read信号
	EM_INP		    //inp 轴到位信号
};

enum EM_LIMIT_TYPE
{//回限位方式
	EM_AXIS_LIMITN = 0,     //回负限位
	EM_AXIS_LIMITP,         //回正限位
	EM_AXIS_NOLIMIT,        //无限位
};


enum EM_HOME_TYPE
{//回原方式
	EM_HOME_NORMAL = 0,     //正常回原
	EM_HOME_SPECIAL1,       //硬件捕获 特殊方式1
	EM_HOME_SPECIAL2,       //index+home 特殊方式2
	EM_HOME_SELF,           //自定义回原
};


typedef struct _TSpeed
{//速度结构
	double vel;
	double acc;
	double dec;
} TSpeed;

/*******************************插补***************************************/

struct TMovept
{//插补参数
	int     dir;			//1 顺时针方向 -1 逆时针方向 0直线插补
	long    pos[6];			//1轴位置 圆弧插补终点X
	//long    pos2;			//2轴位置 圆弧插补中点Y
	//long    pos3;			//3轴位置 圆弧插补圆心X
	//long    pos4;			//4轴位置 圆弧插补圆心Y
	//long    pos5;			//5轴位置 圆弧插补 轴1索引
	//long    pos6;			//6轴位置 圆弧插补 轴2索引
	double  vel;			//速度
	double  acc;			//加减速度
};


struct TCool
{//坐标系数据
	QSemaphore				samStop;				//停止信号量
	QSemaphore				samExit;				//退出信号量
	QFuture<int>			threadHandle;			//
	unsigned short			cardID;					//卡号
	unsigned short			crdID;					//坐标系id
	unsigned short			bLock;					//是否已经锁定坐标系
	unsigned short			axisCnt;				//轴数量
	unsigned short			axis[CRD_AXIS_CNT];		//轴索引数组
	unsigned short			isMoving;				//是否在运动中，1运动中 0不在运动中
	unsigned short			curMoveIndex;			//当前已完成插补段
	std::vector<TMovept*>	vecpt;					//插补段缓冲区
};

struct Coord
{
	unsigned short  cardIndex;      //卡索引
	unsigned short  index;          //坐标系[0,1]
};

/************************************************************************/
typedef struct _AxisPos
{
	QString	axisName;
	double	axisPos;
	_AxisPos& operator=(const _AxisPos & other)
	{
		axisName = other.axisName;
		axisPos  = other.axisPos;
		return *this;
	}
}AxisPos;

typedef struct _Dimension
{
	QString axisNameX;
	QString axisNameY;
	QString axisNameZ;
	QString axisNameU;
	QString axisNameV;
	QString axisNameW;
}Dimension;


struct RunPoint
{
	QString		name;			//点位名称
	QString		desc;			//点位描述
	Dimension	dimension;		//维度信息
	double		pos[6];			//位置

	RunPoint()
	{
		memset(pos, 0, sizeof(double) * 6);
	}
};




typedef struct _IOInfo
{
	QString name;
	int		cardType;		//0=运动控制卡本身，1=IOC0640,3=Can总线
	int		cardIndex;		//卡号
	int		cardNode;		//Can节点，运动控制卡下面的节点号
	int		ioIndex;		//io索引
	int		sense;			//1=高电平有效，0-低电平有效
	int		group;			//分组

	_IOInfo()
	{
		name		= "";
		cardType	= 0;
		cardIndex	= 0;
		cardNode	= 0;
		ioIndex		= 0;
		sense		= 1;
		group		= 0;
	}

	_IOInfo& operator=(const _IOInfo& other)
	{
		name		= other.name;
		cardType	= other.cardType;
		cardIndex	= other.cardIndex;
		cardNode	= other.cardNode;
		ioIndex		= other.ioIndex;
		sense		= other.sense;
		group		= other.group;
		return *this;
	}

}IOInfo, *IOInfoPtr;


typedef struct AxisParam
{//轴参数
	int			cardIndex;				    //卡索引
	int			axisIndex;				    //轴索引
	QString		axisName;				    //轴名称
	int			motorType;				    //参考 EM_AXIS_TYPE 0-伺服, 1步进, 2 dd马达
	int			homeSense;					//原点限位有效电平
	int			limitMode;					//限位方式
	int			limitSense;					//正限位有效电平
	int			almMode;					//报警启用/禁止模式
	int			almSense;					//报警有效电平
	
	double		stepvalue;					//1mm对应多少脉冲
	double		limitN;						//负软限位脉冲
	double		limitP;						//正软限位脉冲
	double		vel;						//默认工作速度  这里所有速度都是 脉冲/毫秒
	double		accTime;					//加速时间
	double		decTime;					//减速时间

	int			homeDir;					//回限位方式，EM_LIMIT_TYPE 0 负限位 1 回正限位 2 无限位
	int			homeType;				    //回原方式 参考 EM_HOME_TYPE 0 正常 1 硬件捕获 2 index 3 自定义 dd马达类型时表示 回原操作IO 8:null,8:card,8:ioindex,8:extmodle
	double		homeVel;					//回原速度 速度加速度 都需要 / 1000
	double		homeAccTime;				//加速时间
	double		homeDecTime;				//减速时间
	double		sreachhomePos;				//回原搜索的距离 脉冲
	double		inHomeOffset;				//原点偏移量 回原前，若处于原点位置，则偏移
	double		afterhomeOffset;			//回原后偏移量

	//回零时，轴向限位移动的速度
	double      homeVelToLimit;
	double      homeAccToLimit;
	double      homeDecToLimit;
	double		stopTime;				//减速停止时间，包括回原
	int			stopMode;				//限位停止模式

	bool		enable;



	AxisParam()
	{
		cardIndex	    = 0;
		axisIndex	    = 0;
		axisName	    = "";
		motorType	    = 0;				
		homeSense	    = 0 ;
		limitMode	    = 0;	
		limitSense	    = 0;
		almMode		    = 0;				
		almSense	    = 0;	

		stepvalue	    = 0;
		limitN		    = 0;
		limitP		    = 0;
		vel			    = 0;
		accTime		    = 0;
		decTime		    = 0;

		homeDir		    = 0;						
		homeType	    = 0;				    
		homeVel		    = 0;						
		homeAccTime	    = 0;					
		homeDecTime	    = 0;					
		sreachhomePos	= 0;
		inHomeOffset	= 0;
		afterhomeOffset	= 0;		
		homeVelToLimit  = 0;
		homeAccToLimit  = 0;
		homeDecToLimit  = 0;
		enable			= true;
		stopTime        = 0.005;
		stopMode        = 0;
	}

}*AxisParamPtr;


typedef struct _ExtIOCard
{
	int		extID;		//扩展卡号
	int		address;	//地址
	bool		bInit;

	_ExtIOCard()
	{
		extID	= 0;
		address	= 0x00000;
		bInit	= false;
	}

	_ExtIOCard& operator = (const _ExtIOCard& other)
	{
		extID	= other.extID;
		address	= other.address;
		bInit	= other.bInit;

		return *this;
	}
}ExtIOCard, *ExtIOCardPtr;

class Card;

typedef struct _CardInfo
{
	std::vector<AxisParam>	vecAxisParam;
	bool                    bInit;

	_CardInfo()
	{
		bInit = false;
	}

	_CardInfo& operator = (const _CardInfo& other)
	{
		vecAxisParam	= other.vecAxisParam;
		bInit		= other.bInit;
		return *this;
	}

}CardInfo, *CardInfoPtr;



