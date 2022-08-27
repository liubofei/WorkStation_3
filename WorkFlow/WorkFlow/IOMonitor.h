#pragma once
#include <QThread>
#include "../../include/Motion.h"

class IOMonitor : public QThread
{
	Q_OBJECT

public:
	IOMonitor(QObject *parent);
	~IOMonitor();

	void	exitThread();

protected:
	void	run();
	void	setWorkPause();
	void	resetWorkPauseFlag();

private:
	QVector<CardInfo>   m_vCardInfo;
};
