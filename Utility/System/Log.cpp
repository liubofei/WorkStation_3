#include "Log.h"
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include "../../include/Common.h"
#include "../../Utility/Utility/Utility.h"

QMutex Log::m_insMutex;
QSharedPointer<Log> Log::m_pInstance;

QString strHead[] = { "", " <INFO> ", " <WARN> ", " <ERRO> ", " <CRIT> " };

Log::Log()
{
}

Log::~Log()
{
}


void Log::writeLog(QString strMsg, int level)
{
	QMutexLocker mutexLocker(&m_writeMutex);

	QDateTime curTime = QDateTime::currentDateTime();
	QString   strTime = curTime.toString("[hh:mm:ss:zzz] ");
	QString   strDate = curTime.toString("yyyy-MM-dd");

	createDir(DATADIR("Log/"));

	QString  strName = DATADIR("Log/" + strDate + ".txt");

	QFile file(strName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.seek(file.size());
		stream << strTime + strHead[level] +  strMsg + "\n\r";
	}
}

void Log::writeErrorLog(QString strMsg)
{
	QMutexLocker mutexLocker(&m_writeMutex);

	QDateTime curTime = QDateTime::currentDateTime();
	QString   strTime = curTime.toString("[hh:mm:ss:zzz] ");
	QString   strDate = curTime.toString("yyyy-MM-dd");

	createDir(DATADIR("ErrorLog/"));

	QString  strName = DATADIR("ErrorLog/" + strDate + ".txt");

	QFile	 file(strName);
	if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.seek(file.size());
		stream << strTime + strMsg + "\n\r";
	}
	else
	{
		qDebug() << "Create logfile failed ";
	}
}


void Log::writeTrackLog(QString strMsg)
{
	QMutexLocker mutexLocker(&m_writeMutex);

	QDateTime curTime = QDateTime::currentDateTime();
	QString   strTime = curTime.toString("[hh:mm:ss] ");
	QString   strDate = curTime.toString("yyyy-MM-dd");

	createDir(DATADIR("TrackLog/"));

	QString  strName = DATADIR("TrackLog/" + strDate + ".txt");

	QFile	 file(strName);
	if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.seek(file.size());
		stream << strTime + strMsg + "\n\r";
	}
	else
	{
		qDebug() << "Create logfile failed ";
	}
}


void Log::writePointMove(QString strMsg)
{
	QMutexLocker mutexLocker(&m_writeMutex);

	QDateTime curTime = QDateTime::currentDateTime();
	QString   strTime = curTime.toString("[hh:mm:ss] ");
	QString   strDate = curTime.toString("yyyy-MM-dd");

	createDir(DATADIR("PointMoveLog/"));

	QString  strName = DATADIR("PointMoveLog/" + strDate + ".txt");

	QFile	 file(strName);
	if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.seek(file.size());
		stream << strTime + strMsg + "\n\r";
	}
	else
	{
		qDebug() << "Create logfile failed ";
	}
}

