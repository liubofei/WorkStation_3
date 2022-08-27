#include "TcpServer.h"
#include "../../Utility/System/Log.h"
#include "../../include/Common.h"
#include "../../Utility/Utility/Utility.h"
#include <QDataStream>

TcpServer::TcpServer(QObject *parent)
: QObject(parent), m_recvSem(0)
{
	init();
}

TcpServer::~TcpServer()
{
}

void	TcpServer::init()
{
	m_connected = false;
	m_recvSem.release(0);
	m_pTcpSever = new QTcpServer(this);
}

bool	TcpServer::startServer(QString name,QString serAddress, int serPorts)
{
	m_name = name;

	//若传入地址为空，则监听所有地址
	QHostAddress hostAdd = serAddress.isEmpty() ? QHostAddress::Any : QHostAddress(serAddress);

	if (!m_pTcpSever->listen(hostAdd, serPorts)) 
	{
		LOG_ERR("startServer(%1, %2)", serAddress, serPorts);
		return false;
	}
	else
	{
		connect(m_pTcpSever, &QTcpServer::newConnection, this, &TcpServer::onNewConnected);
		return true;
	}
}

void	TcpServer::onNewConnected()
{
	if (m_connected)	//防止多个客户端连接
	{
		return;
	}

	m_pClient = m_pTcpSever->nextPendingConnection();

	connect(m_pClient, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
	connect(m_pClient, &QTcpSocket::readyRead, this, &TcpServer::onReadData);
	connect(m_pClient, &QTcpSocket::disconnected, m_pClient, &QTcpSocket::deleteLater);

	m_connected = true;

}

void	TcpServer::onDisconnected()
{
	m_connected = false;
}

bool	TcpServer::sendData(QString msg)
{
	if (nullptr==m_pClient)
	{
		return false;
	}
	else if (!m_connected)
	{
		return false;
	}
	else
	{
		m_pClient->write(msg.toUtf8());

		return true;
	}
}

void	TcpServer::onReadData()
{
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	QByteArray rawData = socket->readAll();
	QString strData(rawData);
	m_strBuff.append(strData);

	int pos = m_strBuff.indexOf('\n');

	if (pos != -1)
	{
		m_strRecv = m_strBuff.left(pos);
		m_strBuff = m_strBuff.mid(pos + 1);

		emit recvMessage(m_name, m_strRecv);


		m_recvSem.release(1);
	}
}

bool	TcpServer::recvData(QString &msg, int msTimeOut)
{
	if (m_recvSem.tryAcquire(1, msTimeOut))
	{
		msg = m_strRecv;
		return true;
	}
	else
	{
		msg = "";
		return false;
	}

}