#pragma once

//�˺��ж��������������򷵻�ָ��ֵ�������пɿ���ʹ�ã��򻯴���
#define RETURN_CHK(p, v) if (!(p)) \
{\
	return v; \
}

#define ZERO_CHK(p) if (!(p)) \
{	\
	return; \
}

//��ȫ�ͷ�,���ÿ�
#define FREE_ANY(p) if (0 != (p)) \
{\
	delete (p); \
	(p) = NULL; \
}

#define COMM_0F 0.00001  //С���������Ϊ����0

//�жϸ������Ƿ����
#define EQUALF(x,y) abs((x) - (y)) < COMM_0F ? true : false

//�жϸ������Ƿ�Ϊ0
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
	USER_OPTR,		//��ҵԱ
	USER_CONFIG,	//ά��Ա
	USER_ADMIN		//����Ա
}USERMODE;

enum MODULE_STATUS
{
	MODULE_STATUS_READY = 0,  //����
	MODULE_STATUS_UN_READY,   //δ������ִ��һЩ�����󵽴����״̬
	MODULE_STATUS_RUNING,     //������
	MODULE_STATUS_HOMING,     //��λ��
	MODULE_STATUS_ERROR       //����
};

enum MODULE_READY
{
	FEED = 0,  //���ϲ�
	CARRY,    //����
	LASER,     //ɨ��
	UNLOAD    //���ϲ�
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
	unsigned short mode;	//0 ��ѹ 1����

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
	QString lastMaintainDate;		//�ϴα�������

	int     languageId;				//0,���ģ�1,Ӣ�ģ�2Խ����
	int     calibType;				//0,����ƶ� 1.�����ƶ�

	int     maintainSpan;			//�������
	int     maintainAlarmTime;      //��������ʱ��

	int     usermode;
	int     coorOrg;			  //˳ʱ�룺0���Ͻǣ�1���Ͻǣ�2���½ǣ�3���½�
	double	manualSpeed[3];		  //�ֶ��ٶ�
	double	safeHeightZ;		  //Z�ᰲȫ�߶�
	int		lightValue;			  //��Դ����
	int		canBaudrate;		  //can���߲�����

	int		autoRun;			  //�����Զ�����
	int     captureAftGlue;		  //�㽺������
	int     XYAngleAffine;		  //XY�ǶȾ�ƫ
	int     enableWipeNozzle;	  //ʹ�ܲ���ģ��
	int		enableUploading;	  //���������ϴ�
	int		enableVisionProtect;  //ʹ���Ӿ�����

	int     enableLaser;	  //ʹ�ܴ��

	int     enableSafeBar;		  //ʹ�ܰ�ȫ��դ
	int		enableSafeDoor;		  //ʹ�ܰ�ȫ��
	int     enableBuzzer;		  //������
	int     enableShowTrack;	  //��ʾ�켣
	int		enableDryRun;		  //����ģʽ
	int     enableUAxis;		  //ʹ��U��岹
	QString curFileName;		  //��ǰ�ļ���

	//ɨ�������
	//����ģ�����
	double feed_z_offset;			//����ƫ����
	int feed_max_tray_num;       //����ģ�������������


	//���̲���
	double tray_row_space;		//�����м��
	double tray_col_space;		//�����м��
	int tray_row_num;			//������
	int tray_col_num;			//������

	//������
	int enableV0Command;
	int enableRCommand;


	int visionVersion;	//�Ӿ�������
	int laserVersion;	//���������

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
	int         isHex;		//16��������
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
	SYSTEM_ERROR = 0,		//ϵͳ����
	SYSTEM_UNHOME,			//δ��ԭ
	SYSTEM_HOMING,			//��ԭ��
	SYSTEM_STANDBY,			//�����У�Ҳ���ǻ�ԭ���״̬
	SYSTEM_PAUSE,			//��ͣ��
	SYSTEM_WORKING			//������


}SYSTEM_STATUS;

Q_DECLARE_METATYPE(SYSTEM_STATUS);





typedef struct _VisonInfo
{
	double exposeTime;				//�ع�	
	double minAngle;				//ģ����С�Ƕ�
	double maxAngle;				//ģ�����Ƕ�
	double smooth;					//��Եƽ����
	double minContrast;				//��С�Աȶ�
	double maxContrast;				//���Աȶ�
	double minScore;				//ƥ�����

	double xImage[2];				//ģ�崴��ʱͼ����ģ���ڵ�λ��
	double yImage[2];				//ģ�崴��ʱͼ����ģ���ڵ�λ��
	double aImage[2];				//ģ�崴��ʱͼ����ģ���ڵ�λ��

	double xMotor[2];				//ģ�崴��ʱX��λ��
	double yMotor[2];				//ģ�崴��ʱY��λ��
	double zMotor[2];				//ģ�崴��ʱZ��λ��

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


//******************************�ֱ�********************************

#define  RMKEY_NUM 28
#define  RMLIGHT_NUM 6

//�ֱ������ϵ�Ķ���
typedef enum RMKEY
{
	RMKEY_NULL = 0,	//û�а�������
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

//�ֱ��ƵĶ���
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


