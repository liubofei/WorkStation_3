#pragma once
#include "serialport_global.h"
#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include <mutex>
#include <QThread>
#include "../../Utility/System/Config.h"

class _SerialPort;

#define  SERIALPORT_INSTANCE SerialPort::instance()

class SERIALPORT_EXPORT SerialPort : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<SerialPort> instance();
	~SerialPort();

	bool isOpened(const QString &name);
	void closePort(const QString &name);
	void reOpenPort(const QString &name);
	bool sendRecive(const QString &name, const QString &msg, QString& rcv, int timeout = 2000);
	void quitThread();

protected slots:
	void onSerialPortInfoChanged(QVector<SeriaPortInfo> seriaPortInfo);

signals:
	void sigSend(QString name, QString msg);
	void sigQuit(QString name);
	void sigClosePort(QString name);
	void openPort(QString name, QString COM, QString baudrate, QString parity, QString databits, QString stopbits);

private:
	void init();

private:
	SerialPort(QObject *parent = nullptr);
	static QMutex m_instanceMutex;
	static QSharedPointer<SerialPort> m_pInstance;
	QVector<SeriaPortInfo>		   m_vecSerialPortInfo;
	QMap<QString, _SerialPort*>    m_mSerialPort;
};
