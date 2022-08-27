#pragma once

#include "system_global.h"
#include <QMutex>
#include <QSharedPointer>


class SYSTEM_EXPORT Log
{

public:
	static QSharedPointer<Log>& instance()
	{

		if (m_pInstance.isNull())
		{
			QMutexLocker mutexLocker(&m_insMutex);
			if (m_pInstance.isNull())
				m_pInstance = QSharedPointer<Log>(new Log());
		}
		return m_pInstance;
	}

	~Log();

	void writeLog(QString strMsg, int level);

	void writeErrorLog(QString strMsg);

	void writeTrackLog(QString strMsg);

	void writePointMove(QString strMsg);

private:
	Log();
	static QMutex m_insMutex;
	static QSharedPointer<Log>  m_pInstance;

	QMutex m_writeMutex;
};

#define  LOG_INSTANCE Log::instance()


//打印级别
#define LEVEL_CRIT  4
#define LEVEL_ERR   3
#define LEVEL_WARN  2
#define LEVEL_INFO  1

//此处定义打印log接口
#ifndef LOG_INFO
#define LOG_INFO(msg, ...)  Log::instance()->writeLog( QString().sprintf(msg, __VA_ARGS__),LEVEL_INFO)
#endif

#ifndef LOG_WARN
#define LOG_WARN(msg, ...)   Log::instance()->writeLog( QString().sprintf(msg, __VA_ARGS__),LEVEL_WARN)
#endif

#ifndef LOG_ERR
#define LOG_ERR(msg, ...)    Log::instance()->writeLog( QString().sprintf(msg, __VA_ARGS__),LEVEL_ERR)
#endif

#ifndef LOG_CRIT
#define LOG_CRIT(msg, ...)   Log::instance()->writeLog( QString().sprintf(msg, __VA_ARGS__),LOG_CRIT)
#endif

#ifndef LOG_SYSTEM_ERROR
#define LOG_SYSTEM_ERROR(msg)  Log::instance()->writeErrorLog(msg)
#endif


#ifndef LOG_TRACK
#define LOG_TRACK(msg)   Log::instance()->writeTrackLog(msg)
#endif


#ifndef LOG_POINT_MOVE
#define LOG_POINT_MOVE(msg)   Log::instance()->writePointMove(msg)
#endif