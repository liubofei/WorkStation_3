#pragma once
#include <QSemaphore>
#include <vector>
#include <QtConcurrent/QtConcurrent>
#include <bitset>

//������˶����

#define INVALID_AXIS		-1		//��Ч��
#define MOTOR_MAX_NAME		36		//����
#define MOTOR_MAX_AXIS		6       //�������᣿
#define COOL_CNT			2		//ÿ�ſ�ֻ����2������ϵ
#define CRD_AXIS_CNT		4		//ÿ������ϵ���4����
#define SAME_PULSE_OFFSET	5		//�����ٸ�������Ϊλ��û�б仯
#define MAX_AXISCNT			8


//�������������ź��Ƿ�ȡ��
#define DMC_CFG			"dmc_cfg"
#define POSITIVE_SENCE	"positive_sence"        //����λ
#define NEGATIVE_SENCE	"negative_sence"        //����λ
#define ALARM_SENCE		"alarm_sence"           //�����ź�
#define HOME_SENCE		"home_sence"            //ԭ���ź�
#define GPI_SENCE		"gpi_sence"             //ͨ������
#define GPIEXT_SENCE	"gpiext_sence"          //��չ��ͨ������
#define ENABLE_SENCE	"enable_sence"          //�ŷ�ʹ��
#define CLEAR_SENCE		"clear_sence"           //�������
#define GPO_SENCE		"gpo_sence"             //ͨ�����
#define GPOEXT_SENCE	"gpoext_sence"          //��չ��ͨ�����

enum EM_IO_TYPE
{//io����
	EM_IO_START = 0,		//��ʼio
	EM_IO_RESET,			//��λio
	EM_IO_ESTOP,			//��ͣ
	EM_IO_PAUSE,			//��ͣ
	EM_IO_STOP,				//ֹͣ����IO
	EM_IO_USUALLY,			//����IO
	EM_IO_BRAKE,			//ɲ��IO
	EM_IO_OTHER,			//����
};


struct STM_CARD  //����Ϣ
{
	unsigned short cardIndex;   //������
	unsigned short axisCnt;     //�����
	unsigned short ioCnt;       //��ioλ��
	unsigned short extCnt;      //��չģ�����
	unsigned short cntType;     //���ӿ����ӷ�ʽ
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
	EM_AXIS_ALARM	= 1,		//��������
	EM_AXIS_LIMIT_P = 5,		//��λ����
	EM_AXIS_LIMIT_L = 6,		//
	EM_AXIS_ESTOP	= 8,		//��ͣio
	EM_AXIS_ENABLE	= 9,		//ʹ�ܱ�־
	EM_AXIS_MOVING	= 10,		//�滮���˶���־

};

enum EM_CRDID
{//����ID��ÿ����ֻ����2��
	EM_CRD_FST = 1,
	EM_CRD_SEC,
};


enum EM_AXIS_TYPE
{//������
	EM_AXIS_SERVO = 0,      //�ŷ�
	EM_AXIS_STEPPER,        //�������
	EM_AXIS_DDMOTOR,        //DD���
	EM_AXIS_FLOW,           //��ˮ��Ƥ��������Ҫ��ԭ
};

enum EM_GPIO_TYPE
{//IO�ź�����
	EM_GPO = 0,     //ͨ�����  ���
	EM_GPI,         //ͨ������
	EM_LIMIT_POS,   //����λ
	EM_LIMIT_NEG,   //����λ
	EM_ALARM,       //�����ź�
	EM_HOME,        //ԭ���ź�
	EM_ENABLE,      //�ŷ�ʹ��  ���
	EM_CLEAR,       //�������  ���
	EM_ADC,         //ģ����
	EM_RDY,		    //read�ź�
	EM_INP		    //inp �ᵽλ�ź�
};

enum EM_LIMIT_TYPE
{//����λ��ʽ
	EM_AXIS_LIMITN = 0,     //�ظ���λ
	EM_AXIS_LIMITP,         //������λ
	EM_AXIS_NOLIMIT,        //����λ
};


enum EM_HOME_TYPE
{//��ԭ��ʽ
	EM_HOME_NORMAL = 0,     //������ԭ
	EM_HOME_SPECIAL1,       //Ӳ������ ���ⷽʽ1
	EM_HOME_SPECIAL2,       //index+home ���ⷽʽ2
	EM_HOME_SELF,           //�Զ����ԭ
};


typedef struct _TSpeed
{//�ٶȽṹ
	double vel;
	double acc;
	double dec;
} TSpeed;

/*******************************�岹***************************************/

struct TMovept
{//�岹����
	int     dir;			//1 ˳ʱ�뷽�� -1 ��ʱ�뷽�� 0ֱ�߲岹
	long    pos[6];			//1��λ�� Բ���岹�յ�X
	//long    pos2;			//2��λ�� Բ���岹�е�Y
	//long    pos3;			//3��λ�� Բ���岹Բ��X
	//long    pos4;			//4��λ�� Բ���岹Բ��Y
	//long    pos5;			//5��λ�� Բ���岹 ��1����
	//long    pos6;			//6��λ�� Բ���岹 ��2����
	double  vel;			//�ٶ�
	double  acc;			//�Ӽ��ٶ�
};


struct TCool
{//����ϵ����
	QSemaphore				samStop;				//ֹͣ�ź���
	QSemaphore				samExit;				//�˳��ź���
	QFuture<int>			threadHandle;			//
	unsigned short			cardID;					//����
	unsigned short			crdID;					//����ϵid
	unsigned short			bLock;					//�Ƿ��Ѿ���������ϵ
	unsigned short			axisCnt;				//������
	unsigned short			axis[CRD_AXIS_CNT];		//����������
	unsigned short			isMoving;				//�Ƿ����˶��У�1�˶��� 0�����˶���
	unsigned short			curMoveIndex;			//��ǰ����ɲ岹��
	std::vector<TMovept*>	vecpt;					//�岹�λ�����
};

struct Coord
{
	unsigned short  cardIndex;      //������
	unsigned short  index;          //����ϵ[0,1]
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
	QString		name;			//��λ����
	QString		desc;			//��λ����
	Dimension	dimension;		//ά����Ϣ
	double		pos[6];			//λ��

	RunPoint()
	{
		memset(pos, 0, sizeof(double) * 6);
	}
};




typedef struct _IOInfo
{
	QString name;
	int		cardType;		//0=�˶����ƿ�����1=IOC0640,3=Can����
	int		cardIndex;		//����
	int		cardNode;		//Can�ڵ㣬�˶����ƿ�����Ľڵ��
	int		ioIndex;		//io����
	int		sense;			//1=�ߵ�ƽ��Ч��0-�͵�ƽ��Ч
	int		group;			//����

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
{//�����
	int			cardIndex;				    //������
	int			axisIndex;				    //������
	QString		axisName;				    //������
	int			motorType;				    //�ο� EM_AXIS_TYPE 0-�ŷ�, 1����, 2 dd���
	int			homeSense;					//ԭ����λ��Ч��ƽ
	int			limitMode;					//��λ��ʽ
	int			limitSense;					//����λ��Ч��ƽ
	int			almMode;					//��������/��ֹģʽ
	int			almSense;					//������Ч��ƽ
	
	double		stepvalue;					//1mm��Ӧ��������
	double		limitN;						//������λ����
	double		limitP;						//������λ����
	double		vel;						//Ĭ�Ϲ����ٶ�  ���������ٶȶ��� ����/����
	double		accTime;					//����ʱ��
	double		decTime;					//����ʱ��

	int			homeDir;					//����λ��ʽ��EM_LIMIT_TYPE 0 ����λ 1 ������λ 2 ����λ
	int			homeType;				    //��ԭ��ʽ �ο� EM_HOME_TYPE 0 ���� 1 Ӳ������ 2 index 3 �Զ��� dd�������ʱ��ʾ ��ԭ����IO 8:null,8:card,8:ioindex,8:extmodle
	double		homeVel;					//��ԭ�ٶ� �ٶȼ��ٶ� ����Ҫ / 1000
	double		homeAccTime;				//����ʱ��
	double		homeDecTime;				//����ʱ��
	double		sreachhomePos;				//��ԭ�����ľ��� ����
	double		inHomeOffset;				//ԭ��ƫ���� ��ԭǰ��������ԭ��λ�ã���ƫ��
	double		afterhomeOffset;			//��ԭ��ƫ����

	//����ʱ��������λ�ƶ����ٶ�
	double      homeVelToLimit;
	double      homeAccToLimit;
	double      homeDecToLimit;
	double		stopTime;				//����ֹͣʱ�䣬������ԭ
	int			stopMode;				//��λֹͣģʽ

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
	int		extID;		//��չ����
	int		address;	//��ַ
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



