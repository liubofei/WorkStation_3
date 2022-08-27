#pragma once
#include "MyModule.h"

struct RunPoint;

struct LaserInfo
{
	QString QrStr;
	int		Seq;		 //��ˮ��
	double laserXY[2];	 //0 X����  1 Y���� 
	double angle;	     //�Ƕ�
	double radius;

	LaserInfo()
		:Seq(0), angle(0.0), radius(0.0)
	{
		laserXY[0] = 0.0;
		laserXY[1] = 0.0;
	}
	
	void reset()
	{
		QrStr = "";
		Seq = -1;
		laserXY[0] = 0.0;
		laserXY[1] = 0.0;
	}
};



//ɨ��ģ��
class LaserModule : public MyModule
{
	Q_OBJECT

public:
	LaserModule(QObject *parent);
	~LaserModule();

	bool moduleReset();
	bool moduleResetAsync();
	void pause();		//��ͣ
	void resume();		//��������

	void test();
	int  calibLaserFun();

signals:
	void updateLaserResult(int row, int col, bool status);
	void initLaserResult();
	void updateOutput(unsigned int total, unsigned int ngNum);

protected:
	void run();
	bool runFun();

private:
	void initData();
	bool setLaserPts();
	bool setLaserResult(int row, int col, bool isOk);
	void getRowCol(int id, int rowNum, int colNum, int &row, int &col);
	bool laserCommuni(const QString &send, QString &recv);
	bool visionCommuni(const QString &send, QString &recv, int msTimeOut = 6000);
	bool laserModel(int row, int col);
	bool ccdLocation(int row, int col);
	bool checkVisionResult(const QString &recv, int size);
	bool laserMarking();


private:
	RunPoint  **m_laserPt;		//�����λ
	LaserInfo **m_laserInfo;
	bool      **m_bLaserResult;	//�����Ƿ�ɹ����
	int      m_row;	//������
	int      m_col; //������
	int      m_breakPos;
	QMutex   m_mutex;
	unsigned int m_total;	//�ܲ���
	unsigned int m_ngNum;	//Ng����
};
