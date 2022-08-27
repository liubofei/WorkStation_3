#pragma once

#include <QObject>
#include <QFile>
#include "../../include/Common.h"

class LogCtl : public QObject
{
	Q_OBJECT

public:
	LogCtl(QObject *parent);
	~LogCtl();

	bool writeSnLog(const SnData &milingData);

private:
	void createCsv();

private:
	QFile m_snLogFile;
	QString m_path;
};
