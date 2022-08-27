#pragma once

#include "network_global.h"
#include "../../Utility/System/Config.h"
#include <QMap>
#include <QObject>
#include <QSharedPointer>

class TcpClient;
class TcpServer;

#define  NETWORK_INSTANCE NetWork::instance()

class NETWORK_EXPORT NetWork : public QObject
{
	Q_OBJECT

public:

	static QSharedPointer<NetWork> instance()
	{

		if (m_pInstance.isNull())
		{
			QMutexLocker mutexLocker(&m_instanceMutex);
			if (m_pInstance.isNull())
				m_pInstance = QSharedPointer<NetWork>(new NetWork());
		}
		return m_pInstance;
	}

	~NetWork();

	bool	isConnected(QString connName);
	bool	sendData(QString connName, QString steData);
	bool	recvData(QString connName, QString &strData, int msTimeOut = 3000);


	bool	clientReConnect(quint16 id);
	bool	clientDisconnect(quint16 id);

protected slots:
	void    onTcpInfoChanged(QVector<TcpInfo> tcpInfo);


signals:
	void    recvTcpMessage(QString name, QString msg);

private:
	static	QMutex m_instanceMutex;
	static	QSharedPointer<NetWork> m_pInstance;
	NetWork(QObject *parent = nullptr);

	QMap<QString, TcpServer*>	m_mapSever;
	QMap<QString, TcpClient*>	m_mapClient;

	QVector<TcpInfo>		m_vecTcpInfo;

	void init();
};
