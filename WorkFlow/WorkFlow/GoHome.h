#pragma once
#include <QThread>

class GoHome : public QThread
{
	Q_OBJECT

public:
	GoHome(QObject *parent);
	~GoHome();
	void exitThread();

protected:
	void run();
};
