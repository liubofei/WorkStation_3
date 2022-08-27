#pragma once
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include "../../include/Common.h"

class MyModule : public QThread
{
	Q_OBJECT

public:
	MyModule(QObject *parent);
	virtual ~MyModule();

	void setReady(bool ready);
	bool getReady() const;
	bool waitReset();
	bool getHomeFlag() const;


	virtual bool moduleReset() = 0;		   //ģ�鸴λ ͬ��
	virtual bool moduleResetAsync() = 0;   //ģ�鸴λ �첽

signals:
	void sendReady(MODULE_READY type);
	void printUILog(QString msg);


protected:
	QFuture<bool> m_homeFuture;
	QString m_strError;
	bool    m_bReady;
	bool    m_bIsHome;
};
