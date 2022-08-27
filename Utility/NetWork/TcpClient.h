#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QSemaphore>
#include "network_global.h"
#include "../../Utility/System/Config.h"
#include "HPSocket.h"

enum EnState
{
	STARTING,
	STARTED,
	CONNECTING,
	CONNECTED,
	STOPPING,
	STOPPED
};

class  TcpClient : public QObject, public CTcpPullClientListener
{
	Q_OBJECT

public:
	TcpClient(QObject *parent);
	~TcpClient();

	int  conect2Server(QString address, quint16 port, int async);

	//设置属性
	void setTcpName(QString name);
	void setHexSend(int isHes){ m_isHex = isHes; }
	void setStatus(EnState state);
	bool isConnected() { return m_enState == CONNECTED; }

	bool sendData(QString smg);
	bool recvData(QString &msg, int msTimeOut = 3000);

	void disconnect();

	
	protected slots:
	

signals:
	void recvMessage(QString name, QString &msg);

private:
	virtual EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);
	virtual EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength);
	virtual EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);

	int     sendData(unsigned char* pBuff, int len);
	void	parseData(BYTE* pData, int len);

private:
	QString					m_name;

	QString					m_strRecv;
	QSemaphore				m_recvSem;
	quint16					m_isHex;		//16进制发送

	CTcpPullClientPtr       m_Client;
	EnState                 m_enState;
	QMutex                  m_mutStatus;

	ulong					m_connId;
	void			        init();
};
