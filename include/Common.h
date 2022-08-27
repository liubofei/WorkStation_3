#pragma once

//此宏判断条件不成立，则返回指定值，代码中可考虑使用，简化代码
#define RETURN_CHK(p, v) if (!(p)) \
{\
	return v; \
}

#define ZERO_CHK(p) if (!(p)) \
{	\
	return; \
}

//安全释放,并置空
#define FREE_ANY(p) if (0 != (p)) \
{\
	delete (p); \
	(p) = NULL; \
}

#define COMM_0F 0.00001  //小于这个数认为等于0

//判断浮点数是否相等
#define EQUALF(x,y) abs((x) - (y)) < COMM_0F ? true : false

//判断浮点数是否为0
#define ZEROF(x) ((x) < COMM_0F && (x) > -COMM_0F) ? true : false

#ifndef MAX
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define  AXIS_PAUSE 100


#define CFGDIR(subDir) (QString("D:/app/LuenFung/TrimLaserMarking/Config/%1").arg(subDir))
#define DATADIR(subDir) (QString("D:/app/LuenFung/TrimLaserMarking/data/%1").arg(subDir))

#ifdef NDEBUG
#define BINDIF(subFile) (QString("D:/app/LuenFung/TrimLaserMarking/release/%1").arg(subFile))
#else
#define BINDIF(subFile) (QString("D:/app/LuenFung/TrimLaserMarking/bin/%1").arg(subFile))
#endif

typedef enum
{
	USER_OPTR,		//作业员
	USER_CONFIG,	//维护员
	USER_ADMIN		//管理员
}USERMODE;

enum MODULE_STATUS
{
	MODULE_STATUS_READY = 0,  //就绪
	MODULE_STATUS_UN_READY,   //未就绪，执行一些动作后到达就绪状态
	MODULE_STATUS_RUNING,     //运行中
	MODULE_STATUS_HOMING,     //复位中
	MODULE_STATUS_ERROR       //出错
};

enum MODULE_READY
{
	FEED = 0,  //上料仓
	CARRY,    //搬运
	LASER,     //扫码
	UNLOAD    //下料仓
};

Q_DECLARE_METATYPE(MODULE_READY);


struct CameraInfo
{
	QString serialNumber;
	QString type;
	unsigned short workId;

	CameraInfo()
		:workId(0)
	{

	}
};

struct AnalogInfo
{
	unsigned short cardNo;
	unsigned short nodeId;
	unsigned short channel;
	unsigned short mode;	//0 电压 1电流

	AnalogInfo()
		:cardNo(0), nodeId(0), channel(0), mode(0)
	{

	}
};


typedef struct _SystemInfo
{
	QString titile;
	QString passwordAdmin;
	QString password;
	QString cameraName;
	QString machineName;
	QString lastMaintainDate;		//上次保养日期

	int     languageId;				//0,中文，1,英文，2越南语
	int     calibType;				//0,相机移动 1.喷嘴移动

	int     maintainSpan;			//保养间隔
	int     maintainAlarmTime;      //保养报警时间

	int     usermode;
	int     coorOrg;			  //顺时针：0左上角，1右上角，2右下角，3左下角
	double	manualSpeed[3];		  //手动速度
	double	safeHeightZ;		  //Z轴安全高度
	int		lightValue;			  //光源亮度
	int		canBaudrate;		  //can总线波特率

	int		autoRun;			  //开机自动启动
	int     captureAftGlue;		  //点胶后牌照
	int     XYAngleAffine;		  //XY角度纠偏
	int     enableWipeNozzle;	  //使能擦胶模组
	int		enableUploading;	  //容许数据上传
	int		enableVisionProtect;  //使能视觉防呆

	int     enableLaser;	  //使能打标

	int     enableSafeBar;		  //使能安全光栅
	int		enableSafeDoor;		  //使能安全门
	int     enableBuzzer;		  //蜂鸣器
	int     enableShowTrack;	  //显示轨迹
	int		enableDryRun;		  //空跑模式
	int     enableUAxis;		  //使用U轴插补
	QString curFileName;		  //当前文件名

	//扫码机参数
	//上料模块参数
	double feed_z_offset;			//上料偏移量
	int feed_max_tray_num;       //上料模块最大料盘数量


	//料盘参数
	double tray_row_space;		//料盘行间距
	double tray_col_space;		//料盘列间距
	int tray_row_num;			//行数量
	int tray_col_num;			//列数量

	//打标参数
	int enableV0Command;
	int enableRCommand;


	int visionVersion;	//视觉程序编号
	int laserVersion;	//镭码程序编号

	_SystemInfo()
	{
		calibType = 0;
		languageId = 0;
		maintainSpan = 0;
		maintainAlarmTime = 0;
		usermode = 0;
		coorOrg = 0;
		manualSpeed[0] = 0;
		manualSpeed[1] = 0;
		manualSpeed[2] = 0;
		safeHeightZ = 0;
		lightValue = 0;
		canBaudrate = 0;
		autoRun = 0;
		captureAftGlue = 0;
		XYAngleAffine = 0;
		enableWipeNozzle = 0;
		enableUploading = 0;
		enableVisionProtect = 0;
		enableSafeBar = 0;
		enableSafeDoor = 0;
		enableBuzzer = 0;
		enableShowTrack = 0;
		enableDryRun = 0;
		enableLaser = 1;
		enableUAxis = 0;

		feed_z_offset = 0.0;
		feed_max_tray_num = 0;

		tray_row_space = 0.0;
		tray_col_space = 0.0;
		tray_row_num = 0;
		tray_col_num = 0;

		enableV0Command = 0;
		enableRCommand = 0;

		visionVersion = 0;
		laserVersion = 0;
	}


}SystemInfo;

typedef struct _SnData
{
	QString sn;
	int stationId;

	_SnData()
		:sn(""), stationId(0)
	{

	}

	void reset()
	{
		sn = "";
		stationId = 0;
	}

}SnData;


typedef struct _SeriaPortInfo
{
	QString		name;
	QString		desc;
	QString		comNO;
	QString     baudrate;
	QString		parity;
	QString		databits;
	QString		stopbits;
	int         isHex;		//16进制数据
}SeriaPortInfo;

typedef struct _TcpInfo
{
	QString name;
	QString desc;
	QString ip;
	int     port;
	int		type;
	int		isHex;
}TcpInfo;


typedef enum
{
	SYSTEM_ERROR = 0,		//系统错误
	SYSTEM_UNHOME,			//未回原
	SYSTEM_HOMING,			//回原中
	SYSTEM_STANDBY,			//待机中，也就是回原后的状态
	SYSTEM_PAUSE,			//暂停中
	SYSTEM_WORKING			//工作中


}SYSTEM_STATUS;

Q_DECLARE_METATYPE(SYSTEM_STATUS);





typedef struct _VisonInfo
{
	double exposeTime;				//曝光	
	double minAngle;				//模板最小角度
	double maxAngle;				//模板最大角度
	double smooth;					//边缘平滑度
	double minContrast;				//最小对比度
	double maxContrast;				//最大对比度
	double minScore;				//匹配分数

	double xImage[2];				//模板创建时图像中模板在的位置
	double yImage[2];				//模板创建时图像中模板在的位置
	double aImage[2];				//模板创建时图像中模板在的位置

	double xMotor[2];				//模板创建时X轴位置
	double yMotor[2];				//模板创建时Y轴位置
	double zMotor[2];				//模板创建时Z轴位置

	_VisonInfo()
	{
		exposeTime				= 30000;
		minAngle				= -15;
		maxAngle				= 15;
		smooth					= 1;
		minContrast				= 20;
		maxContrast				= 30;
		minScore				= 0.5;

		memset(xImage, 0, sizeof(double) * 2);
		memset(yImage, 0, sizeof(double) * 2);
		memset(aImage, 0, sizeof(double) * 2);
		memset(xMotor, 0, sizeof(double) * 2);
		memset(yMotor, 0, sizeof(double) * 2);
		memset(zMotor, 0, sizeof(double) * 2);
	}
}VisonInfo;


typedef struct _CalibMatrix
{
	double value[6];

	_CalibMatrix()
	{
		memset(value, 0, sizeof(double) * 6);
	}

}CalibMatrix;


//******************************手柄********************************

#define  RMKEY_NUM 28
#define  RMLIGHT_NUM 6

//手柄按键上点的定义
typedef enum RMKEY
{
	RMKEY_NULL = 0,	//没有按键按下
	RMKEY_RUN = 1,
	RMKEY_STOP,
	RMKEY_GOHOME,
	RMKEY_LOCK,
	RMKEY_SIMULATE,
	RMKEY_GLUE,
	RMKEY_UP,
	RMKEY_LOCATE,
	RMKEY_TEACH,
	RMKEY_DOWN,
	RMKEY_RP,
	RMKEY_YP,
	RMKEY_ZP,
	RMKEY_XN,
	RMKEY_SPEED,
	RMKEY_XP,
	RMKEY_RN,
	RMKEY_YN,
	RMKEY_ZN,
	RMKEY_PSTART,
	RMKEY_PARC,
	RMKEY_PLINE,
	RMKEY_PEND,
	RMKEY_INSERT,
	RMKEY_SINGLE,
	RMKEY_F1,
	RMKEY_F2,
	RMKEY_F3
};

//手柄灯的定义
typedef enum RMLIGHT
{
	RMLIGHT_LOCK = (0x01 << 0),
	RMLIGHT_RUN  = (0x01 << 1),
	RMLIGHT_STOP = (0x01 << 2),
	RMLIGHT_LOW  = (0x01 << 4),
	RMLIGHT_MID  = (0x01 << 5),
	RMLIGHT_HIGH = (0x01 << 7),
	RMLIGHT_GLUE = (0x01 << 12),
};

//**************************************************************


