#pragma once
#include <QtSerialPort/QSerialPort>

class QTimer;
class QThread;

class _SerialPort : public QSerialPort
{
	Q_OBJECT

public:
	_SerialPort(QObject *parent = 0);
	~_SerialPort();

	void setName(const QString &name);
	QString getName() const;
	void setHexSend(bool isHex);

public slots:
	void onSend(QString name, QString msg);
	void onOpenPort(QString name, QString COM, QString baudrate, QString parity, QString databits, QString stopbits);
	void onClosePort(QString name);
	void onQuitThread(QString name);
	void onReceive();
	void onTimeOut();

signals:
	void received(QString msg);

private:
	void init();
	QByteArray hexToByte(const QString &msg);

private:	
	bool    m_isHex;
	QString m_name;
	QString m_buffer;
	QThread* m_workThread;
	QTimer*  m_timer;
};