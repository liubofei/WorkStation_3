#include "SerialPort.h"
#include "_SerialPort.h"
#include <memory>
#include <QThread>
#include <QEventLoop>

QMutex SerialPort::m_instanceMutex;
QSharedPointer<SerialPort> SerialPort::m_pInstance = nullptr;

SerialPort::SerialPort(QObject *parent)
	: QObject(parent)
{
	init();
}

QSharedPointer<SerialPort> SerialPort::instance()
{
	if (m_pInstance.isNull())
	{
		QMutexLocker mutexLocker(&m_instanceMutex);
		if (m_pInstance.isNull())
			m_pInstance = QSharedPointer<SerialPort>(new SerialPort());
	}
	return m_pInstance;	
}

SerialPort::~SerialPort()
{
	
}

void SerialPort::onSerialPortInfoChanged(QVector<SeriaPortInfo> seriaPortInfo)
{
	m_vecSerialPortInfo = seriaPortInfo;
}

bool SerialPort::isOpened(const QString &name)
{
	for (auto item : m_mSerialPort){
		if (item->getName() == name){
			return item->isOpen();
		}
	}
	return false;
}

void  SerialPort::init()
{
	CONFIG_INSTANCE->getSerPortInfo(m_vecSerialPortInfo);
	connect(CONFIG_INSTANCE.data(), &Config::serialPortInfoChanged, this, &SerialPort::onSerialPortInfoChanged);

	for (const auto portInfo : m_vecSerialPortInfo){
		_SerialPort* port = new _SerialPort;
		port->setHexSend(portInfo.isHex);
		port->setName(portInfo.name);
		connect(this, &SerialPort::sigSend, port, &_SerialPort::onSend);
		connect(this, &SerialPort::sigClosePort, port, &_SerialPort::onClosePort);
		connect(this, &SerialPort::sigQuit, port, &_SerialPort::onQuitThread);
		connect(this, &SerialPort::openPort, port, &_SerialPort::onOpenPort);

		emit openPort(portInfo.name, portInfo.comNO, portInfo.baudrate, portInfo.parity, portInfo.databits, portInfo.stopbits);
		m_mSerialPort.insert(portInfo.name, port);
	}
}

void  SerialPort::closePort(const QString &name)
{		
	emit sigClosePort(name);
}

void SerialPort::reOpenPort(const QString &name)
{
	for (auto portInfo : m_vecSerialPortInfo){
		if (name == portInfo.name){
			emit openPort(portInfo.name, portInfo.comNO, portInfo.baudrate, portInfo.parity, portInfo.databits, portInfo.stopbits);
		}
	}
}

void SerialPort::quitThread()
{
	for(const auto item : m_vecSerialPortInfo){		
		emit sigQuit(item.name);
	}
}

bool SerialPort::sendRecive(const QString &name, const  QString &msg, QString& rcv, int timeout)
{
	_SerialPort *port = m_mSerialPort[name];
	if (nullptr != port)
	{
		bool ret = false;
		QTimer timer;
		QEventLoop eventLoop;
		timer.setSingleShot(true);
		
		auto con1 = std::make_shared<QMetaObject::Connection>();
		auto con2 = std::make_shared<QMetaObject::Connection>();

		*con1 = connect(&timer, &QTimer::timeout, [&](){
			ret = false;
			rcv = "";
			disconnect(*con2);
			disconnect(*con1);
			eventLoop.quit();
		});

		*con2 = connect(port, &_SerialPort::received, [&](QString str){
			ret = true;
			rcv = str;
			disconnect(*con1);
			disconnect(*con2);
			eventLoop.quit();
		});

		emit sigSend(name, msg);

		timer.start(timeout);
		eventLoop.exec();
		return ret;
	}

	return false;
}