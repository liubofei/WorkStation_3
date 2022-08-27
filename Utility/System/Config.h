#pragma once

#include "system_global.h"
#include <QMutex>
#include <QSharedPointer>
#include <QSettings>
#include <vector>
#include <QBuffer>
#include "../../include/Common.h"
#include "../../include/Motion.h"

#define  CONFIG_INSTANCE Config::instance()

class  SYSTEM_EXPORT Config:public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<Config> instance();


	~Config();
	
	bool	getCardInfo(QVector<CardInfo> &cardInfo);
	bool	setCardInfo(const QVector<CardInfo>  &cardInfo);
	int		getCardCfgCnt() { return m_vecCardInfo.size(); }
	int		getAxisCfgCnt(int cardIndex);

	int		getExtIOCardInfoCnt() { return m_vecExtIOCardInfo.size(); }
	bool	getExtIOCardInfo(QVector<ExtIOCard> &extIOInfo);
	bool	setExtIOCfg(const QVector<ExtIOCard> &extIOInfo);

	bool	getInputInfo(QVector<IOInfo> &info);
	bool	setInputInfo(const QVector<IOInfo> &info);
	bool	getOutputInfo(QVector<IOInfo> &info);
	bool	setOutputInfo(const QVector<IOInfo> &info);

	bool	getTcpInfo(QVector<TcpInfo> &info);
	bool	setTcpInfo(const QVector<TcpInfo> &info);

	bool	getCameraInfo(QVector<CameraInfo> &info);
	bool	setCameraInfo(const QVector<CameraInfo> &info);

	bool	getSerPortInfo(QVector<SeriaPortInfo> &info);
	bool	setSerPortInfo(const QVector<SeriaPortInfo> &info);

	bool	getRunPointInfo(QVector<RunPoint> &info);
	bool	setPointInfo(const QVector<RunPoint> &info);

	SystemInfo	getSysInfo();
	bool		setSysInfo(const SystemInfo &info);

	//获取视觉参数
	VisonInfo	getProgInfo(QString fileName,int modelIndex);		
	VisonInfo	getCalibInfo();	

	bool		setProgInfo(VisonInfo &info, int modelIndex);
	bool		setCalibInfo(VisonInfo &info);

	CalibMatrix getCalibMatrix();
	bool		setCalibMatrix(const CalibMatrix& matrix);
	bool		loadSysInfo();

	bool getAnalogInfo(AnalogInfo& info);
	bool setAnalogInfo(const AnalogInfo& info);

signals:			
	void cardInfoChanged(QVector<CardInfo> cardInfo);
	void extIOCardInfoChanged(QVector<ExtIOCard> extCardinfo);
	void IOInfoChanged(QVector<IOInfo> IOInputInfo, QVector<IOInfo> IOOutputInfo);
	void pointsInfoChanged(QVector<RunPoint> pointsInfo);
	void tcpTcpInfoChanged(QVector<TcpInfo> tcpServer);
	void serialPortInfoChanged(QVector<SeriaPortInfo> seriaPortInfo);
	void progInfoChanged(VisonInfo info,int modelIndex);
	void calibInfoChanged(VisonInfo info);
	void matrixChanged(CalibMatrix matrix);
	void updateSystemInfoUI();
	void sysInfoChanage(SystemInfo info);

private:
	void init();

	bool loadCardInfo();
	bool saveCardInfo();
	bool loadIOInfo();
	bool saveIOInfo();
	bool loadTcpInfo();
	bool saveTcpInfo();
	bool loadCameraInfo();
	bool saveCameraInfo();
	bool loadSerPortInfo();
	bool saveSerPortInfo();
	bool loadCalibMatrix();
	bool saveCalibMatrix();
	bool loadRunPointInfo();
	bool saveRunPointInfo();
	bool saveSysInfo();
	bool loadProgInfo();
	bool loadCalibInfo();
	bool saveProgInfo();
	bool saveCalibInfo();
	bool loadAnalogInfo();
	bool saveAnalogInfo();

	bool parseCardInfo(QByteArray &byteArray);
	bool cardInfo2Byte(QByteArray &byteArray);
	bool parseIOInfo(QByteArray &byteArray);
	bool IOInfo2Byte(QByteArray &byteArray);
	bool parseSysInfo(QByteArray &byteArray);
	bool SysInfo2Byte(QByteArray &byteArray);
	bool parseTcpInfo(QByteArray &byteArray);
	bool TcpInfo2Byte(QByteArray &byteArray);
	bool parseCameraInfo(QByteArray &byteArray);
	bool CameraInfo2Byte(QByteArray &byteArray);
	bool pareaSerPortInfo(QByteArray &byteArray);
	bool serPortInfo2Byte(QByteArray &byteArray);
	bool pareaRunPointInfo(QByteArray &byteArray);
	bool runPointfo2Byte(QByteArray &byteArray);

private:
	Config();
	static QMutex					m_insMutex;
	static QSharedPointer<Config>	m_pInstance;
	QMutex							m_rwMutex;

	QVector<CardInfo>				m_vecCardInfo;
	QVector<ExtIOCard>				m_vecExtIOCardInfo;
	QVector<IOInfo>					m_vecInputInfo;
	QVector<IOInfo>					m_vecOutputInfo;
	QVector<TcpInfo>				m_vecTcpInfo;
	QVector<SeriaPortInfo>			m_vecSerPortInfo;
	QVector<RunPoint>				m_vRunPoint;
	QVector<CameraInfo>             m_vCameraInfo;
	QString							m_fileName;
	VisonInfo						m_progInfo[5];
	VisonInfo						m_calibInfo;
	CalibMatrix						m_calibMatrix;
	SystemInfo						m_sysInfo;
	AnalogInfo						m_analogInfo;
};