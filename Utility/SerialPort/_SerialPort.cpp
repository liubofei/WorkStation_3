#include "_SerialPort.h"
#include <QTimer>
#include <QThread>

_SerialPort::_SerialPort(QObject *parent)
	: QSerialPort(parent)
{
	init();
}

_SerialPort::~_SerialPort()
{
}

void _SerialPort::setName(const QString &name)
{
	m_name = name;
}

QString _SerialPort::getName() const
{
	return m_name;
}

void _SerialPort::init()
{
	m_isHex = false;
	m_workThread = new QThread;
	m_timer = new QTimer;

	this->moveToThread(m_workThread);
	m_timer->moveToThread(m_workThread);
	m_timer->setSingleShot(true);

	connect(this, &QSerialPort::readyRead, this, &_SerialPort::onReceive);
	connect(m_timer, &QTimer::timeout, this, &_SerialPort::onTimeOut);
}

QByteArray _SerialPort::hexToByte(const QString &msg)
{
	QStringList strList = msg.split(" ");
	int len = strList.size();
	QByteArray buff;
	bool isOK = false;
	for (int i = 0; i < len; ++i){
		buff.append(strList.at(i).toInt(&isOK, 16));
	}
	return buff;
}

void _SerialPort::setHexSend(bool isHex)
{
	m_isHex = isHex;
}

void  _SerialPort::onSend(QString name, QString msg)
{
	if (m_name == name){	
		if (isOpen()){
			readAll();				//发送之前，清空接收缓冲
			m_buffer.clear();
			if (m_isHex){
				QByteArray data = hexToByte(msg);
				write(data);
			}
			else{
				write(msg.toLatin1());
			}
			waitForBytesWritten(300);
		}
	}	
}

void _SerialPort::onOpenPort(QString name, QString COM, QString baudrate, QString parity, QString databits, QString stopbits)
{	
	if (m_name == name)
	{
		QSerialPort::BaudRate _baudrate;
		QSerialPort::Parity _Parity;
		QSerialPort::DataBits _databits;
		QSerialPort::StopBits _stopbits;

		if (QStringLiteral("无") == parity){
			_Parity = QSerialPort::NoParity;
		}
		else if (QStringLiteral("偶") == parity){
			_Parity = QSerialPort::EvenParity;
		}
		else if (QStringLiteral("奇") == parity){
			_Parity = QSerialPort::OddParity;
		}

		if ("1" == stopbits){
			_stopbits = QSerialPort::OneStop;
		}
		else if ("1.5" == stopbits){
			_stopbits = QSerialPort::OneAndHalfStop;
		}
		else if ("2" == stopbits){
			_stopbits = QSerialPort::TwoStop;
		}

		_baudrate = (QSerialPort::BaudRate)baudrate.toInt();
		_databits = (QSerialPort::DataBits)databits.toInt();

		setPortName(COM);
		if (!setBaudRate(_baudrate))return;
		if (!setParity(_Parity))return;
		if (!setDataBits(_databits))return;
		if (!setStopBits(_stopbits))return;
		if (!setFlowControl(QSerialPort::NoFlowControl))return;
		bool isOpen = open(QIODevice::ReadWrite);
	}
}

void _SerialPort::onClosePort(QString name)
{
	if (m_name == name){
		if (isOpen()){
			close();
		}	
	}
}

void _SerialPort::onQuitThread(QString name)
{
	if (m_name == name){
		m_workThread->quit();
	}
}

void _SerialPort::onReceive()
{
	if (m_timer->isActive()){
		m_timer->stop();
	}
	m_timer->start(200);
}

void _SerialPort::onTimeOut()
{
	m_buffer.append(QString(readAll()));
	if (!m_buffer.isEmpty()){
		emit received(m_buffer);
	}
}