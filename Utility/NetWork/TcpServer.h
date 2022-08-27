#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSemaphore>

class  TcpServer : public QObject
{
	Q_OBJECT

public:
	TcpServer(QObject *parent);
	~TcpServer();

	bool	startServer(QString name,QString serAddress, int serPorts);
	bool	isConnected() { return m_connected; }
	bool	sendData(QString msg);
	bool	recvData(QString &msg, int msTimeOut = 3000);

	protected slots:
	void	onNewConnected();
	void	onDisconnected();
	void	onReadData();

signals:
	void recvMessage(QString name, QString &msg);

private:
	QString					m_name;
	QTcpServer*				m_pTcpSever;
	QTcpSocket*				m_pClient;
	QString					m_serAddress;
	QString					m_strBuff;
	QString					m_strRecv;
	QSemaphore				m_recvSem;
	int						m_serPort;
	bool					m_connected;

	void				init();
};
