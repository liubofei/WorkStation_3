#include "NetWork.h"
#include "../../Utility/System/Config.h"
#include "TcpClient.h"
#include "TcpServer.h"

QMutex NetWork::m_instanceMutex;
QSharedPointer<NetWork> NetWork::m_pInstance = nullptr;


NetWork::NetWork(QObject *parent)
	: QObject(parent)
{
	init();
}

NetWork::~NetWork()
{
}

void NetWork::init()
{	
	CONFIG_INSTANCE->getTcpInfo(m_vecTcpInfo);
	connect(CONFIG_INSTANCE.data(), &Config::tcpTcpInfoChanged, this, &NetWork::onTcpInfoChanged);

	for (int i = 0; i < m_vecTcpInfo.size(); i++)
	{
		if (0==m_vecTcpInfo[i].type)	//创建服务端
		{
			TcpServer* server = new TcpServer(this);
			bool rtn = server->startServer(m_vecTcpInfo[i].name, m_vecTcpInfo[i].ip, m_vecTcpInfo[i].port);
			m_mapSever.insert(m_vecTcpInfo[i].name, server);
			connect(server, &TcpServer::recvMessage, this, &NetWork::recvTcpMessage);
		}
		else   //创建客户端
		{
			TcpClient* client = new TcpClient(this);
			bool rtn = client->conect2Server(m_vecTcpInfo[i].ip, m_vecTcpInfo[i].port, 1);

			client->setTcpName(m_vecTcpInfo[i].name);

			m_mapClient.insert(m_vecTcpInfo[i].name, client);

			if (m_vecTcpInfo[i].isHex == 1)
			{
				client->setHexSend(1);
			}
		}
	}
}

void    NetWork::onTcpInfoChanged(QVector<TcpInfo> tcpInfo)
{
	m_vecTcpInfo = tcpInfo;
}

bool	NetWork::isConnected(QString connName)
{
	if (m_mapClient.contains(connName))
	{
		return m_mapClient[connName]->isConnected();
	}
	else 	if (m_mapSever.contains(connName))
	{
		return m_mapSever[connName]->isConnected();
	}
	else
	{
		return false;
	}
}

bool		NetWork::sendData(QString connName, QString steData)
{
	if (m_mapClient.contains(connName))
	{
		return m_mapClient[connName]->sendData(steData);
	}
	else 	if (m_mapSever.contains(connName))
	{
		return m_mapSever[connName]->sendData(steData);;
	}
	else
	{
		return false;
	}
}

bool	NetWork::recvData(QString connName, QString &strData, int msTimeOut)
{
	if (m_mapClient.contains(connName))
	{
		return m_mapClient[connName]->recvData(strData, msTimeOut);
	}
	else 	if (m_mapSever.contains(connName))
	{
		return m_mapSever[connName]->recvData(strData, msTimeOut);
	}
	else
	{
		return false;
	}
}

bool	NetWork::clientReConnect(quint16 id)
{
	bool rtn = false;
	QString name = m_vecTcpInfo[id].name;
	TcpClient* p = m_mapClient[name];

	if (p!=nullptr)
	{
		rtn = p->conect2Server(m_vecTcpInfo[id].ip, m_vecTcpInfo[id].port, 0);
	}

	return rtn;
}


bool	NetWork::clientDisconnect(quint16 id)
{
	QString name = m_vecTcpInfo[id].name;
	TcpClient* p = m_mapClient[name];

	if (p != nullptr)
	{
		p->disconnect();
	}
	return true;
}
