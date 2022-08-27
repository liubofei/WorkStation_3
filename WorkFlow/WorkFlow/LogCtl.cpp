#include "logctl.h"
#include <QTextStream>
#include <QDateTime>
#include "../../Utility/Utility/Utility.h"


LogCtl::LogCtl(QObject *parent)
	:QObject(parent)
{
	m_path = "D:/GlueSystem_Data/SN_Log/";
	createDir(m_path);
	createCsv();

}

LogCtl::~LogCtl()
{

}


bool LogCtl::writeSnLog(const SnData &snData)
{
	QDateTime dataTime = QDateTime::currentDateTime();
	QString   strDate = dataTime.toString("yyyy-MM");
	QString   strw = dataTime.toString("yyyy-MM-dd");

	QString  curTime = dataTime.toString("hh:mm:ss");

	QString filename = m_path + strDate + ".csv";
	m_snLogFile.setFileName(filename);

	if (!m_snLogFile.exists())
	{
		createCsv();
	}

	if (!m_snLogFile.open(QFile::WriteOnly | QFile::Append | QFile::Text))
		return false;
	
	QString sn = snData.sn == "" ? "None" : snData.sn;

	
	QTextStream textStream;
	textStream.setDevice(&m_snLogFile);

	textStream <<    strw + "," +
					curTime + "," +
					sn + "," +
					QString("%1").arg(snData.stationId == 0 ? "L" : "R") + "\n";

	m_snLogFile.close();

	return true;
}


void LogCtl::createCsv()
{
	QDateTime dataTime = QDateTime::currentDateTime();
	QString   strDate = dataTime.toString("yyyy-MM");
	QString filename = m_path + strDate + ".csv";
	m_snLogFile.setFileName(filename);

	if (!m_snLogFile.exists())
	{
		if (!m_snLogFile.open(QFile::WriteOnly | QFile::Append | QFile::Text))
			return;

		QTextStream textStream;
		textStream.setDevice(&m_snLogFile);
		textStream.setCodec("GB2312");

		textStream << QStringLiteral("����") + "," +
					  QStringLiteral("ʱ��") + "," +
					  QStringLiteral("Sn") + "," +
					  QStringLiteral("��վ") + "\n";

		m_snLogFile.close();
	}
}