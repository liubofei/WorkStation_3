#include "Config.h"
#include <QJsonObject>
#include "../Utility/Utility.h"
#include "../../Utility/XMessageBox/XMessageBox.h"

QMutex Config::m_insMutex;
QSharedPointer<Config> Config::m_pInstance;

Config::Config()
{
	init();
}

QSharedPointer<Config> Config::instance()
{
	if (nullptr == m_pInstance)
	{
		QMutexLocker mutexLocker(&m_insMutex);
		if (nullptr == m_pInstance)
			m_pInstance = QSharedPointer<Config>(new Config());
	}
	return m_pInstance;
}

Config::~Config()
{
}

void  Config::init()
{
	loadSysInfo();
	loadCardInfo();
	loadIOInfo();
	loadTcpInfo();
	loadSerPortInfo();
	loadCardInfo();
	loadCalibInfo();
	loadRunPointInfo();
	loadCalibMatrix();
	loadCameraInfo();
	loadAnalogInfo();
}

bool Config::parseCardInfo(QByteArray &byteArray)
{
	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
	m_vecCardInfo.clear();
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) 
	{  
		if (document.isObject())
		{
			QJsonObject jsonObj = document.object();
			QJsonArray cardArray = jsonObj.value("Card").toArray();
			int ncardnum = cardArray.size();
			for (int i = 0; i < ncardnum; i++)
			{
				CardInfo cardInfo;
				QJsonObject cardObj = cardArray.at(i).toObject();
				QJsonArray axisArray = cardObj.value("Axis").toArray();
				for (int j = 0; j < axisArray.size(); j++)
				{
					AxisParam axisParam;

					QJsonObject axisValue		= axisArray.at(j).toObject();
					
					axisParam.cardIndex			= axisValue.value("cardIndex").toInt();
					axisParam.axisIndex			= axisValue.value("axisIndex").toInt();
					axisParam.axisName			= axisValue.value("axisName").toString();
					axisParam.motorType			= axisValue.value("motorType").toInt();
					axisParam.homeSense			= axisValue.value("homeSense").toInt();
					axisParam.limitMode			= axisValue.value("limitMode").toInt();
					axisParam.limitSense		= axisValue.value("limitSense").toInt();
					axisParam.almMode			= axisValue.value("almMode").toInt();
					axisParam.almSense			= axisValue.value("almSense").toInt();
					axisParam.almSense			= axisValue.value("almSense").toInt();
					
					axisParam.stepvalue			= axisValue.value("stepvalue").toDouble();
					axisParam.limitN			= axisValue.value("limitN").toDouble();
					axisParam.limitP			= axisValue.value("limitP").toDouble();
					axisParam.homeVel			= axisValue.value("homeVel").toDouble();
					axisParam.vel				= axisValue.value("vel").toDouble();
					axisParam.accTime			= axisValue.value("accTime").toDouble();
					axisParam.decTime			= axisValue.value("decTime").toDouble();
					
					axisParam.homeDir			= axisValue.value("homeDir").toInt();
					axisParam.homeType			= axisValue.value("homeType").toInt();
					axisParam.homeVel			= axisValue.value("homeVel").toDouble();
					axisParam.homeAccTime		= axisValue.value("homeAccTime").toDouble();
					axisParam.homeDecTime		= axisValue.value("homeDecTime").toDouble();
					axisParam.sreachhomePos		= axisValue.value("sreachhomePos").toDouble();
					axisParam.inHomeOffset		= axisValue.value("inHomeOffset").toDouble();
					axisParam.afterhomeOffset	= axisValue.value("afterhomeOffset").toDouble();
					axisParam.homeVelToLimit    = axisValue.value("homeVelToLimit").toDouble(20);
					axisParam.homeAccToLimit    = axisValue.value("homeAccToLimit").toDouble(0.1);
					axisParam.homeDecToLimit    = axisValue.value("homeDecToLimit").toDouble(0.1);
					axisParam.enable            = axisValue.value("enable").toBool();
					axisParam.stopTime          = axisValue.value("stopTime").toDouble(0.005);
					axisParam.stopMode          = axisValue.value("stopMode").toInt(1);

					cardInfo.vecAxisParam.push_back(axisParam);
				}

				//“‘œ¬≤ªƒ‹¥”≈‰÷√Œƒº˛º”‘ÿ
				cardInfo.bInit = false;
				m_vecCardInfo.push_back(cardInfo);
			}

			QJsonArray extArray = jsonObj.value("ExtCard").toArray();
			int extCardNum = cardArray.size();
			for (int i = 0; i < extCardNum; i++)
			{
				ExtIOCard extCard;
				QJsonObject extValue = extArray.at(i).toObject();
				extCard.extID	= extValue.value("extID").toInt();
				extCard.address = extValue.value("address").toInt();
				extCard.bInit	= false;
				m_vecExtIOCardInfo.push_back(extCard);
			}

			return true;
		}
	}

	// Ω‚ŒˆŒ¥∑¢…˙¥ÌŒÛ
	XMessageBox::error(QStringLiteral("CardInfoΩ‚Œˆ ß∞‹"));
	return false;
}

bool Config::cardInfo2Byte(QByteArray &byteArray)
{

	QJsonDocument	document;
	QJsonObject		jsonObj;

	QJsonArray		cardArrayJObj;
	for (int i = 0; i < m_vecCardInfo.size(); i++)
	{
		QJsonObject cardObj;
		QJsonArray axisArrayObj;

		for (int j = 0; j < m_vecCardInfo[i].vecAxisParam.size(); j++)
		{
			QJsonObject axisObj;

			axisObj.insert("cardIndex",			m_vecCardInfo[i].vecAxisParam[j].cardIndex);
			axisObj.insert("axisIndex",			m_vecCardInfo[i].vecAxisParam[j].axisIndex);
			axisObj.insert("axisName",			m_vecCardInfo[i].vecAxisParam[j].axisName);
			axisObj.insert("motorType",			m_vecCardInfo[i].vecAxisParam[j].motorType);
			
			axisObj.insert("homeSense",			m_vecCardInfo[i].vecAxisParam[j].homeSense);
			axisObj.insert("limitMode",			m_vecCardInfo[i].vecAxisParam[j].limitMode);
			axisObj.insert("limitSense",		m_vecCardInfo[i].vecAxisParam[j].limitSense);
			axisObj.insert("almMode",			m_vecCardInfo[i].vecAxisParam[j].almMode);
			axisObj.insert("almSense",			m_vecCardInfo[i].vecAxisParam[j].almSense);
			
			axisObj.insert("stepvalue",			m_vecCardInfo[i].vecAxisParam[j].stepvalue);
			axisObj.insert("limitN",			m_vecCardInfo[i].vecAxisParam[j].limitN);
			axisObj.insert("limitP",			m_vecCardInfo[i].vecAxisParam[j].limitP);
			axisObj.insert("vel",				m_vecCardInfo[i].vecAxisParam[j].vel);
			axisObj.insert("accTime",			m_vecCardInfo[i].vecAxisParam[j].accTime);
			axisObj.insert("decTime",			m_vecCardInfo[i].vecAxisParam[j].decTime);
			
			axisObj.insert("homeDir",			m_vecCardInfo[i].vecAxisParam[j].homeDir);
			axisObj.insert("homeType",			m_vecCardInfo[i].vecAxisParam[j].homeType);
			axisObj.insert("homeVel",			m_vecCardInfo[i].vecAxisParam[j].homeVel);

			axisObj.insert("homeAccTime",		m_vecCardInfo[i].vecAxisParam[j].homeAccTime);
			axisObj.insert("homeDecTime",		m_vecCardInfo[i].vecAxisParam[j].homeDecTime);
			axisObj.insert("sreachhomePos",		m_vecCardInfo[i].vecAxisParam[j].sreachhomePos);
			axisObj.insert("inHomeOffset",		m_vecCardInfo[i].vecAxisParam[j].inHomeOffset);
			axisObj.insert("afterhomeOffset",	m_vecCardInfo[i].vecAxisParam[j].afterhomeOffset);

			axisObj.insert("homeVelToLimit",    m_vecCardInfo[i].vecAxisParam[j].homeVelToLimit);
			axisObj.insert("homeAccToLimit",    m_vecCardInfo[i].vecAxisParam[j].homeAccToLimit);
			axisObj.insert("homeDecToLimit",    m_vecCardInfo[i].vecAxisParam[j].homeDecToLimit);
			axisObj.insert("stopTime",          m_vecCardInfo[i].vecAxisParam[j].stopTime);
			axisObj.insert("stopMode",          m_vecCardInfo[i].vecAxisParam[j].stopMode);
			axisObj.insert("enable",			m_vecCardInfo[i].vecAxisParam[j].enable);

			axisArrayObj.append(axisObj);
		}

		cardObj.insert("Axis", axisArrayObj);
		cardArrayJObj.append(cardObj);
	}

	jsonObj.insert("Card", cardArrayJObj);


	QJsonArray extIOArrayObj;
	for (int i = 0; i < m_vecExtIOCardInfo.size(); i++)
	{
		QJsonObject extObj;
		extObj.insert("extID", m_vecExtIOCardInfo[i].extID);
		extObj.insert("address", m_vecExtIOCardInfo[i].address);
		extIOArrayObj.append(extObj);
	}
	jsonObj.insert("ExtCard", extIOArrayObj);

	document.setObject(jsonObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}

bool Config::loadCardInfo()
{
	QMutexLocker locker(&m_rwMutex);

	QString filePath = CFGDIR("Config/Config_Card.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		parseCardInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}

}

bool Config::saveCardInfo()
{

	QString filePath = CFGDIR("Config/Config_Card.json");

	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		cardInfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::getExtIOCardInfo(QVector<ExtIOCard> &extIOInfo)
{
	QMutexLocker locker(&m_rwMutex);
	extIOInfo = m_vecExtIOCardInfo;
	return true;
}

bool Config::setExtIOCfg(const QVector<ExtIOCard> &extIOInfo)
{
	QMutexLocker locker(&m_rwMutex);
	m_vecExtIOCardInfo = extIOInfo ;
	emit extIOCardInfoChanged(m_vecExtIOCardInfo);
	saveCardInfo();
	return true;
}

bool  Config::getCardInfo(QVector<CardInfo> &cardInfo)
{
	QMutexLocker locker(&m_rwMutex);
	cardInfo = m_vecCardInfo;
	return true;
}

bool  Config::setCardInfo(const QVector<CardInfo> &cardInfo)
{
	QMutexLocker locker(&m_rwMutex);
	m_vecCardInfo = cardInfo;
	emit cardInfoChanged(m_vecCardInfo);
	saveCardInfo();
	return true;
}

bool Config::parseIOInfo(QByteArray &byteArray)
{

	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
	m_vecInputInfo.clear();
	m_vecOutputInfo.clear();
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isObject())
		{
			QJsonObject jsonObj = document.object();

			QJsonArray inputArray = jsonObj.value("Input").toArray();
			for (int i = 0; i < inputArray.size();i++)
			{
				IOInfo ioInfo;
				QJsonObject ioObj	= inputArray.at(i).toObject();
				ioInfo.name			= ioObj.value("name").toString();
				ioInfo.cardType		= ioObj.value("cardType").toInt();
				ioInfo.cardIndex	= ioObj.value("cardIndex").toInt();
				ioInfo.cardNode		= ioObj.value("cardNode").toInt();
				ioInfo.ioIndex		= ioObj.value("ioIndex").toInt();
				ioInfo.sense		= ioObj.value("sense").toInt();
				ioInfo.group	    = ioObj.value("group").toInt();

				m_vecInputInfo.push_back(ioInfo);
			}

			QJsonArray outputArray = jsonObj.value("Output").toArray();
			for (int i = 0; i < outputArray.size(); i++)
			{
				IOInfo ioInfo;
				QJsonObject ioObj	= outputArray.at(i).toObject();
				ioInfo.name			= ioObj.value("name").toString();
				ioInfo.cardType		= ioObj.value("cardType").toInt();
				ioInfo.cardIndex	= ioObj.value("cardIndex").toInt();
				ioInfo.cardNode		= ioObj.value("cardNode").toInt();
				ioInfo.ioIndex		= ioObj.value("ioIndex").toInt();
				ioInfo.sense		= ioObj.value("sense").toInt();
				ioInfo.group        = ioObj.value("group").toInt();

				m_vecOutputInfo.push_back(ioInfo);
			}

			return true;
		}
	}

	// Ω‚ŒˆŒ¥∑¢…˙¥ÌŒÛ
	XMessageBox::error(QStringLiteral("IOInfoΩ‚Œˆ ß∞‹"));
	return false;
}

bool Config::IOInfo2Byte(QByteArray &byteArray)
{

	QJsonDocument document;
	QJsonObject IOObj;

	QJsonArray inputObj;
	for (int i = 0; i < m_vecInputInfo.size(); i++)
	{
		QJsonObject IOObj;
		IOObj.insert("name",		m_vecInputInfo[i].name);
		IOObj.insert("cardType",	m_vecInputInfo[i].cardType);
		IOObj.insert("cardIndex",	m_vecInputInfo[i].cardIndex);
		IOObj.insert("cardNode",	m_vecInputInfo[i].cardNode);
		IOObj.insert("ioIndex",		m_vecInputInfo[i].ioIndex);
		IOObj.insert("sense",		m_vecInputInfo[i].sense);
		IOObj.insert("group",	    m_vecInputInfo[i].group);

		inputObj.append(IOObj);
	}
	IOObj.insert("Input", inputObj);

	QJsonArray outputObj;
	for (int i = 0; i < m_vecOutputInfo.size(); i++)
	{
		QJsonObject IOObj;
		IOObj.insert("name",      m_vecOutputInfo[i].name);
		IOObj.insert("cardType",  m_vecOutputInfo[i].cardType);
		IOObj.insert("cardIndex", m_vecOutputInfo[i].cardIndex);
		IOObj.insert("cardNode",  m_vecOutputInfo[i].cardNode);
		IOObj.insert("ioIndex",   m_vecOutputInfo[i].ioIndex);
		IOObj.insert("sense",     m_vecOutputInfo[i].sense);
		IOObj.insert("group",     m_vecOutputInfo[i].group);

		outputObj.append(IOObj);
	}

	IOObj.insert("Output", outputObj);


	document.setObject(IOObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}

bool Config::loadIOInfo()
{
	QMutexLocker locker(&m_rwMutex);

	QString filePath = CFGDIR("Config/Config_IO.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		parseIOInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}
}

bool Config::saveIOInfo()
{
	QString filePath = CFGDIR("Config/Config_IO.json");
	
	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		IOInfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::getInputInfo(QVector<IOInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_vecInputInfo;
	return true;
}

bool Config::setInputInfo(const QVector<IOInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	m_vecInputInfo = info;
	emit IOInfoChanged(m_vecInputInfo,m_vecOutputInfo);
	saveIOInfo();
	return true;
}

bool Config::getOutputInfo(QVector<IOInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_vecOutputInfo;
	return true;
}

bool Config::setOutputInfo(const QVector<IOInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);	
	m_vecOutputInfo = info;
	emit IOInfoChanged(m_vecInputInfo,m_vecOutputInfo);
	saveIOInfo();
	return true;
}

bool Config::loadTcpInfo()
{
	QMutexLocker locker(&m_rwMutex);

	QString filePath = CFGDIR("Config/Config_Tcp.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		parseTcpInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}
}

bool Config::saveTcpInfo()
{
	QString filePath = CFGDIR("Config/Config_Tcp.json");

	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		TcpInfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::loadCameraInfo()
{
	QMutexLocker locker(&m_rwMutex);

	QString filePath = CFGDIR("Config/Config_Camera.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		parseCameraInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}
}

bool Config::saveCameraInfo()
{
	QString filePath = CFGDIR("Config/Config_Camera.json");

	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		CameraInfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::getTcpInfo(QVector<TcpInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_vecTcpInfo;
	return true;
}

bool Config::setTcpInfo(const QVector<TcpInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	m_vecTcpInfo = info;
	emit tcpTcpInfoChanged(m_vecTcpInfo);
	saveTcpInfo();
	return true;
}

bool Config::getCameraInfo(QVector<CameraInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_vCameraInfo;
	return true;
}

bool Config::setCameraInfo(const QVector<CameraInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	m_vCameraInfo = info;
	saveCameraInfo();
	return true;
}

bool  Config::parseTcpInfo(QByteArray &byteArray)
{

	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
	m_vecTcpInfo.clear();
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isArray())
		{
			QJsonArray jsonArray = document.array();
			int tcpNum = jsonArray.size();
			for (int i = 0; i < tcpNum; i++)
			{
				TcpInfo tcpInf;
				QJsonObject serObj = jsonArray.at(i).toObject();
				tcpInf.name		= serObj.value("name").toString();
				tcpInf.desc		= serObj.value("desc").toString();
				tcpInf.ip		= serObj.value("ip").toString();
				tcpInf.port		= serObj.value("port").toInt();
				tcpInf.type		= serObj.value("type").toInt();
				tcpInf.isHex = serObj.value("isHex").toInt();
				m_vecTcpInfo.push_back(tcpInf);
			}

			return true;
		}
	}

	// Ω‚ŒˆŒ¥∑¢…˙¥ÌŒÛ
	XMessageBox::error(QStringLiteral("TcpInfoΩ‚Œˆ ß∞‹"));
	return false;
}

bool  Config::TcpInfo2Byte(QByteArray &byteArray)
{
	QJsonDocument	document;

	QJsonArray tcpArrayObj;
	for (int i = 0; i < m_vecTcpInfo.size(); i++)
	{
		QJsonObject tcpObj;
		tcpObj.insert("name",	m_vecTcpInfo[i].name);
		tcpObj.insert("desc",	m_vecTcpInfo[i].desc);
		tcpObj.insert("ip",	m_vecTcpInfo[i].ip);
		tcpObj.insert("port",	m_vecTcpInfo[i].port);
		tcpObj.insert("type",	m_vecTcpInfo[i].type);
		tcpObj.insert("isHex", m_vecTcpInfo[i].isHex);
		tcpArrayObj.append(tcpObj);
	}

	document.setArray(tcpArrayObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}

bool Config::parseCameraInfo(QByteArray &byteArray)
{
	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
	m_vCameraInfo.clear();
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isArray())
		{
			QJsonArray jsonArray = document.array();
			int cameraNum = jsonArray.size();
			for (int i = 0; i < cameraNum; i++)
			{
				CameraInfo cameraInfo;
				QJsonObject serObj = jsonArray.at(i).toObject();
				cameraInfo.serialNumber = serObj.value("serialNumber").toString();
				cameraInfo.type = serObj.value("type").toString();
				cameraInfo.workId = serObj.value("workId").toString().toInt();
				m_vCameraInfo.push_back(cameraInfo);
			}
			return true;
		}
	}

	// Ω‚ŒˆŒ¥∑¢…˙¥ÌŒÛ
	XMessageBox::error(QStringLiteral("TcpInfoΩ‚Œˆ ß∞‹"));
	return false;
}

bool Config::CameraInfo2Byte(QByteArray &byteArray)
{
	QJsonDocument	document;
	QJsonArray cameraArrayObj;
	for (int i = 0; i < m_vCameraInfo.size(); i++)
	{
		QJsonObject tcpObj;
		tcpObj.insert("serialNumber", m_vCameraInfo[i].serialNumber);
		tcpObj.insert("type", m_vCameraInfo[i].type);
		tcpObj.insert("workId", m_vCameraInfo[i].workId);
		cameraArrayObj.append(tcpObj);
	}

	document.setArray(cameraArrayObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}

bool Config::pareaSerPortInfo(QByteArray &byteArray)
{
	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
	m_vecSerPortInfo.clear();
	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isArray())
		{
			QJsonArray jsonArray = document.array();
			int serNum = jsonArray.size();
			for (int i = 0; i < serNum; i++)
			{
				SeriaPortInfo serInfo;
				QJsonObject serObj	= jsonArray.at(i).toObject();
				serInfo.name		= serObj.value("name").toString();
				serInfo.desc		= serObj.value("desc").toString();
				serInfo.comNO		= serObj.value("comNO").toString();
				serInfo.baudrate	= serObj.value("baudrate").toString();
				serInfo.parity		= serObj.value("parity").toString();
				serInfo.databits	= serObj.value("databits").toString();
				serInfo.stopbits	= serObj.value("stopbit").toString();
				serInfo.isHex       = serObj.value("isHex").toInt(0);
				m_vecSerPortInfo.push_back(serInfo);
			}

			return true;
		}
	}

	// Ω‚ŒˆŒ¥∑¢…˙¥ÌŒÛ
	XMessageBox::error(QStringLiteral("SeriaPortΩ‚Œˆ ß∞‹"));
	return false;
}

bool Config::serPortInfo2Byte(QByteArray &byteArray)
{
	QJsonDocument	document;

	QJsonArray serArrayObj;
	for (int i = 0; i < m_vecSerPortInfo.size(); i++)
	{
		QJsonObject serObj;
		serObj.insert("name",		m_vecSerPortInfo[i].name);
		serObj.insert("desc",		m_vecSerPortInfo[i].desc);
		serObj.insert("comNO",		m_vecSerPortInfo[i].comNO);
		serObj.insert("baudrate",	m_vecSerPortInfo[i].baudrate);
		serObj.insert("parity",		m_vecSerPortInfo[i].parity);
		serObj.insert("databits",	m_vecSerPortInfo[i].databits);
		serObj.insert("stopbits",	m_vecSerPortInfo[i].stopbits);
		serObj.insert("isHex", m_vecSerPortInfo[i].isHex);
		serArrayObj.append(serObj);
	}

	document.setArray(serArrayObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}

bool Config::loadSerPortInfo()
{
	QMutexLocker locker(&m_rwMutex);

	QString filePath = CFGDIR("Config/Config_SeriaPort.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		pareaSerPortInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}
}

bool Config::saveSerPortInfo()
{
	QString filePath = CFGDIR("Config/Config_SeriaPort.json");

	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		serPortInfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::getSerPortInfo(QVector<SeriaPortInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_vecSerPortInfo;
	return true;
}

bool Config::setSerPortInfo(const QVector<SeriaPortInfo> &info)
{
	QMutexLocker locker(&m_rwMutex);
	m_vecSerPortInfo = info;
	emit serialPortInfoChanged(m_vecSerPortInfo);
	return true;

}

bool Config::loadRunPointInfo()
{
	QMutexLocker locker(&m_rwMutex);
	QString filePath = CFGDIR("Config/Config_RunPoint.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		pareaRunPointInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}
}

bool Config::saveRunPointInfo()
{
	QString filePath = CFGDIR("Config/Config_RunPoint.json");

	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		runPointfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::getRunPointInfo(QVector<RunPoint> &info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_vRunPoint;
	return true;
}

bool Config::setPointInfo(const QVector<RunPoint> &info)
{
	QMutexLocker locker(&m_rwMutex);
	m_vRunPoint = info;
	saveRunPointInfo();
	emit pointsInfoChanged(m_vRunPoint);
	return true;
}

bool Config::parseSysInfo(QByteArray &byteArray)
{
	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);

	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError))
	{
		if (document.isObject())
		{
			QJsonObject jsonObj = document.object();
			m_sysInfo.titile                = jsonObj.value("titile").toString();
			m_sysInfo.passwordAdmin         = jsonObj.value("passwordAdmin").toString("1");
			m_sysInfo.password			    = jsonObj.value("password").toString("1");
			m_sysInfo.cameraName            = jsonObj.value("cameraName").toString();
			m_sysInfo.machineName           = jsonObj.value("machineName").toString("310");
			m_sysInfo.languageId			= jsonObj.value("languageId").toInt(0);
			m_sysInfo.calibType             = jsonObj.value("calibType").toInt(0);
			m_sysInfo.usermode              = jsonObj.value("usermode").toInt();
			m_sysInfo.coorOrg               = jsonObj.value("coordOrg").toInt();
			m_sysInfo.manualSpeed[0]        = jsonObj.value("lowSpeed").toDouble();
			m_sysInfo.manualSpeed[1]        = jsonObj.value("midSpeed").toDouble();
			m_sysInfo.manualSpeed[2]        = jsonObj.value("hightSpeed").toDouble();
			m_sysInfo.safeHeightZ           = jsonObj.value("safeHeightZ").toDouble();
			m_sysInfo.lightValue            = jsonObj.value("lightValue").toInt();
			m_sysInfo.canBaudrate           = jsonObj.value("canBaudrate").toInt();
			m_sysInfo.autoRun               = jsonObj.value("autoRun").toInt();
			m_sysInfo.captureAftGlue        = jsonObj.value("captureAftGlue").toInt(1);
			m_sysInfo.XYAngleAffine         = jsonObj.value("XYAngleAffine").toInt(1);
			m_sysInfo.enableVisionProtect = jsonObj.value("enableVisionProtect").toInt(0);
			m_sysInfo.enableWipeNozzle      = jsonObj.value("enableWipeNozzle").toInt();
			m_sysInfo.enableUploading       = jsonObj.value("enableUploading").toInt();
			m_sysInfo.enableSafeBar         = jsonObj.value("enableSafeBar").toInt();
			m_sysInfo.enableSafeDoor        = jsonObj.value("enableSafeDoor").toInt();
			m_sysInfo.enableBuzzer			= jsonObj.value("enableBuzzer").toInt();
			m_sysInfo.enableShowTrack       = jsonObj.value("enableShowTrack").toInt();
			m_sysInfo.enableDryRun			= jsonObj.value("enableDryRun").toInt(0);
			m_sysInfo.enableLaser = jsonObj.value("enableLaser").toInt(1);
			m_sysInfo.enableUAxis = jsonObj.value("enableUAxis").toInt(1);
			m_sysInfo.curFileName		    = jsonObj.value("curFileName").toString();
			m_sysInfo.lastMaintainDate      = jsonObj.value("lastMaintainDate").toString("20190907");
			m_sysInfo.maintainSpan		    = jsonObj.value("maintainSpan").toInt(7);
			//
			m_sysInfo.feed_z_offset = jsonObj.value("feed_z_offset").toDouble(0.0);
			m_sysInfo.feed_max_tray_num = jsonObj.value("feed_max_tray_num").toInt(0);

			m_sysInfo.tray_row_space = jsonObj.value("tray_row_space").toDouble(0.0);
			m_sysInfo.tray_col_space = jsonObj.value("tray_col_space").toDouble(0.0);
			m_sysInfo.tray_row_num = jsonObj.value("tray_row_num").toInt(0);
			m_sysInfo.tray_col_num = jsonObj.value("tray_col_num").toInt(0);

			m_sysInfo.enableV0Command = jsonObj.value("enableV0Command").toInt(0);
			m_sysInfo.enableRCommand = jsonObj.value("enableRCommand").toInt(0);

			m_sysInfo.laserVersion = jsonObj.value("laserVersion").toInt(0);
			m_sysInfo.visionVersion = jsonObj.value("visionVersion").toInt(0);

			return true;
		}
	}
	// Ω‚ŒˆŒ¥∑¢…˙¥ÌŒÛ
	XMessageBox::error(QStringLiteral("SysInfoΩ‚Œˆ ß∞‹"));
	return false;
}

bool Config::SysInfo2Byte(QByteArray &byteArray)
{
	QJsonDocument document;
	QJsonObject JsonObj;
	JsonObj.insert("titile",              m_sysInfo.titile);
	JsonObj.insert("passwordAdmin",       m_sysInfo.passwordAdmin);
	JsonObj.insert("password",            m_sysInfo.password);
	JsonObj.insert("cameraName",          m_sysInfo.cameraName);
	JsonObj.insert("machineName",         m_sysInfo.machineName);

	JsonObj.insert("languageId",          m_sysInfo.languageId);
	JsonObj.insert("calibType",           m_sysInfo.calibType);
	JsonObj.insert("coordOrg",            m_sysInfo.coorOrg);
	JsonObj.insert("lowSpeed",            m_sysInfo.manualSpeed[0]);
	JsonObj.insert("midSpeed",            m_sysInfo.manualSpeed[1]);
	JsonObj.insert("hightSpeed",          m_sysInfo.manualSpeed[2]);
	JsonObj.insert("safeHeightZ",         m_sysInfo.safeHeightZ);
	JsonObj.insert("lightValue",          m_sysInfo.lightValue);
	JsonObj.insert("canBaudrate",         m_sysInfo.canBaudrate);
	JsonObj.insert("autoRun",             m_sysInfo.autoRun);
	JsonObj.insert("captureAftGlue",      m_sysInfo.captureAftGlue);
	JsonObj.insert("XYAngleAffine",		  m_sysInfo.XYAngleAffine);
	JsonObj.insert("enableVisionProtect", m_sysInfo.enableVisionProtect);
	JsonObj.insert("enableWipeNozzle",    m_sysInfo.enableWipeNozzle);
	JsonObj.insert("enableUploading",     m_sysInfo.enableUploading);
	JsonObj.insert("enableSafeBar",       m_sysInfo.enableSafeBar);
	JsonObj.insert("enableSafeDoor",      m_sysInfo.enableSafeDoor);
	JsonObj.insert("enableBuzzer",        m_sysInfo.enableBuzzer);
	JsonObj.insert("enableShowTrack",     m_sysInfo.enableShowTrack);
	JsonObj.insert("enableDryRun",		  m_sysInfo.enableDryRun);
	JsonObj.insert("enableLaser", m_sysInfo.enableLaser);
	JsonObj.insert("enableUAxis", m_sysInfo.enableUAxis);

	JsonObj.insert("curFileName",		  m_sysInfo.curFileName);

	JsonObj.insert("lastMaintainDate",	  m_sysInfo.lastMaintainDate);
	JsonObj.insert("maintainSpan",		  m_sysInfo.maintainSpan);
	JsonObj.insert("maintainAlarmTime",   m_sysInfo.maintainAlarmTime);

	//
	JsonObj.insert("feed_z_offset", m_sysInfo.feed_z_offset);
	JsonObj.insert("feed_max_tray_num", m_sysInfo.feed_max_tray_num);

	JsonObj.insert("tray_row_space", m_sysInfo.tray_row_space);
	JsonObj.insert("tray_col_space", m_sysInfo.tray_col_space);
	JsonObj.insert("tray_row_num", m_sysInfo.tray_row_num);
	JsonObj.insert("tray_col_num", m_sysInfo.tray_col_num);

	JsonObj.insert("enableV0Command", m_sysInfo.enableV0Command);
	JsonObj.insert("enableRCommand", m_sysInfo.enableRCommand);
	JsonObj.insert("laserVersion", m_sysInfo.laserVersion);
	JsonObj.insert("visionVersion", m_sysInfo.visionVersion);
	document.setObject(JsonObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}

bool Config::loadSysInfo()
{
	QMutexLocker locker(&m_rwMutex);

	QString filePath = CFGDIR("Config/Config_System.json");

	QJsonDocument document;
	QFile		  file(filePath);
	QByteArray	  byteArray;
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		byteArray = file.readAll();
		file.close();
		parseSysInfo(byteArray);
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
		return false;
	}
}

bool Config::getAnalogInfo(AnalogInfo& info)
{
	QMutexLocker locker(&m_rwMutex);
	info = m_analogInfo;
	return true;
}

bool Config::setAnalogInfo(const AnalogInfo& info)
{
	QMutexLocker locker(&m_rwMutex);
	m_analogInfo = info;
	saveAnalogInfo();
	return true;
}

bool Config::saveSysInfo()
{
	QString filePath = CFGDIR("Config/Config_System.json");

	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QByteArray byteArray;
		SysInfo2Byte(byteArray);
		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

SystemInfo 	Config::getSysInfo()
{
	QMutexLocker locker(&m_rwMutex);

	return m_sysInfo;
}

bool Config::setSysInfo(const SystemInfo &info)
{
	QMutexLocker locker(&m_rwMutex);

	m_sysInfo = info;

	saveSysInfo();

	emit 	sysInfoChanage(info);
	return true;
}


VisonInfo Config::getProgInfo(QString fileName, int modelIndex)
{
	QMutexLocker locker(&m_rwMutex);

	if (m_fileName!=fileName)
	{
		m_fileName = fileName;
		loadProgInfo();
	}

	return m_progInfo[modelIndex];
}

VisonInfo Config::getCalibInfo()
{
	QMutexLocker locker(&m_rwMutex);

	return m_calibInfo;
}

bool Config::setProgInfo(VisonInfo &info, int modelIndex)
{
	QMutexLocker locker(&m_rwMutex);

	m_progInfo[modelIndex] = info;

	emit progInfoChanged(m_progInfo[modelIndex], modelIndex);

	saveProgInfo();

	return true;
}

bool Config::setCalibInfo(VisonInfo &info)
{
	QMutexLocker locker(&m_rwMutex);

	m_calibInfo = info;

	emit calibInfoChanged(m_calibInfo);

	saveCalibInfo();

	return true;
}

CalibMatrix Config::getCalibMatrix()
{
	QMutexLocker locker(&m_rwMutex);
	return m_calibMatrix;
}

bool Config::setCalibMatrix(const CalibMatrix& matrix)
{
	QMutexLocker locker(&m_rwMutex);

	m_calibMatrix = matrix;

	emit matrixChanged(m_calibMatrix);

	saveCalibMatrix();

	return true;
}

bool Config::saveProgInfo()
{
	for (int i = 0; i < 5;i++)
	{
		QString   iniName = QString("/Param_%1.ini").arg(i);
		QString   iniPath = CFGDIR("Program/" + m_fileName + iniName);
		QSettings file(iniPath, QSettings::IniFormat);

		file.setValue("Model/exposeTime",	m_progInfo[i].exposeTime);
		file.setValue("Model/minAngle",		m_progInfo[i].minAngle);
		file.setValue("Model/maxAngle",		m_progInfo[i].maxAngle);
		file.setValue("Model/smooth",		m_progInfo[i].smooth);
		file.setValue("Model/minContrast",	m_progInfo[i].minContrast);
		file.setValue("Model/maxContrast",	m_progInfo[i].maxContrast);
		file.setValue("Model/minScore",		m_progInfo[i].minScore);
		file.setValue("MotorLeft/xMotor",	m_progInfo[i].xMotor[0]);
		file.setValue("MotorLeft/yMotor",	m_progInfo[i].yMotor[0]);
		file.setValue("MotorLeft/zMotor",	m_progInfo[i].zMotor[0]);
		file.setValue("MotorRight/xMotor",	m_progInfo[i].xMotor[1]);
		file.setValue("MotorRight/yMotor",	m_progInfo[i].yMotor[1]);
		file.setValue("MotorRight/zMotor",	m_progInfo[i].zMotor[1]);
		file.setValue("ImageLeft/xImage",	m_progInfo[i].xImage[0]);
		file.setValue("ImageLeft/yImage",	m_progInfo[i].yImage[0]);
		file.setValue("ImageLeft/aImage",	m_progInfo[i].aImage[0]);
		file.setValue("ImageRight/xImage",	m_progInfo[i].xImage[1]);
		file.setValue("ImageRight/yImage",	m_progInfo[i].yImage[1]);
		file.setValue("ImageRight/aImage",	m_progInfo[i].aImage[1]);
	}
	return true;
}

bool Config::saveCalibInfo()
{
	QString   iniPath = CFGDIR("Vision/Program/CalibMatrix.ini");
	QSettings file(iniPath, QSettings::IniFormat);

	file.setValue("Model/exposeTime", m_calibInfo.exposeTime);
	file.setValue("Model/minAngle", m_calibInfo.minAngle);
	file.setValue("Model/maxAngle", m_calibInfo.maxAngle);
	file.setValue("Model/smooth", m_calibInfo.smooth);
	file.setValue("Model/minContrast", m_calibInfo.minContrast);
	file.setValue("Model/maxContrast", m_calibInfo.maxContrast);
	file.setValue("Model/minScore", m_calibInfo.minScore);
	return true;
}

bool Config::loadAnalogInfo()
{
	QMutexLocker locker(&m_rwMutex);
	bool bRtn = false;
	QString filePath = CFGDIR("Config/Config_Analog.json");
	QFile file(filePath);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QByteArray byteArray = file.readAll();
		QJsonParseError jsonError;
		QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);
		if (!document.isNull() && jsonError.error == QJsonParseError::NoError)
		{
			if (document.isObject())
			{
				QJsonObject jsonObj = document.object();
				m_analogInfo.cardNo = jsonObj.value("cardNo").toInt(0);
				m_analogInfo.nodeId = jsonObj.value("nodeId").toInt(0);
				m_analogInfo.channel = jsonObj.value("channel").toInt(0);
				m_analogInfo.mode = jsonObj.value("mode").toInt(0);
				bRtn = true;
			}
		}
		file.close();
	}

	if (!bRtn)
	{
		XMessageBox::error(filePath + QStringLiteral("º”‘ÿ ß∞‹"));
	}
		
	return bRtn;	
}

bool Config::saveAnalogInfo()
{
	QString filePath = CFGDIR("Config/Config_Analog.json");
	QFile file(filePath);
	if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
	{
		QJsonDocument document;
		QJsonObject JsonObj;
		JsonObj.insert("titile", m_analogInfo.cardNo);
		JsonObj.insert("passwordAdmin", m_analogInfo.nodeId);
		JsonObj.insert("password", m_analogInfo.channel);
		JsonObj.insert("cardType", m_analogInfo.mode);

		document.setObject(JsonObj);
		QByteArray byteArray = document.toJson(QJsonDocument::Indented);

		file.write(byteArray);
		file.close();
		return true;
	}
	else
	{
		XMessageBox::error(filePath + QStringLiteral("±£¥Ê ß∞‹"));
		return false;
	}
}

bool Config::loadProgInfo()
{
	if (m_fileName.isEmpty())
	{
		return false;
	}

	for (int i = 0; i < 5; i++)
	{
		QString   iniName = QString("/Param_%1.ini").arg(i);
		QString   iniPath = CFGDIR("Program/" + m_fileName + iniName);
		QSettings file(iniPath, QSettings::IniFormat);

		memset(&m_progInfo[i], 0, sizeof(m_progInfo[i]));

		m_progInfo[i].exposeTime  = file.value("Model/exposeTime", 35000).toDouble();
		m_progInfo[i].minAngle    = file.value("Model/minAngle", -15).toDouble();
		m_progInfo[i].maxAngle    = file.value("Model/maxAngle", 15).toDouble();
		m_progInfo[i].smooth      = file.value("Model/smooth", 1).toDouble();
		m_progInfo[i].minContrast = file.value("Model/minContrast", 5).toDouble();
		m_progInfo[i].maxContrast = file.value("Model/maxContrast", 10).toDouble();
		m_progInfo[i].minScore    = file.value("Model/minScore", 0.5).toDouble();

		m_progInfo[i].xMotor[0] = file.value("MotorLeft/xMotor", 0).toDouble();
		m_progInfo[i].yMotor[0] = file.value("MotorLeft/yMotor", 0).toDouble();
		m_progInfo[i].zMotor[0] = file.value("MotorLeft/zMotor", 0).toDouble();
		m_progInfo[i].xMotor[1] = file.value("MotorRight/xMotor", 0).toDouble();
		m_progInfo[i].yMotor[1] = file.value("MotorRight/yMotor", 0).toDouble();
		m_progInfo[i].zMotor[1] = file.value("MotorRight/zMotor", 0).toDouble();
		m_progInfo[i].xImage[0] = file.value("ImageLeft/xImage", 0).toDouble();
		m_progInfo[i].yImage[0] = file.value("ImageLeft/yImage", 0).toDouble();
		m_progInfo[i].aImage[0] = file.value("ImageLeft/aImage", 0).toDouble();
		m_progInfo[i].xImage[1] = file.value("ImageRight/xImage", 0).toDouble();
		m_progInfo[i].yImage[1] = file.value("ImageRight/yImage", 0).toDouble();
		m_progInfo[i].aImage[1] = file.value("ImageRight/aImage", 0).toDouble();
	}

	return true;
}

bool Config::loadCalibInfo()
{
	QString   iniPath = CFGDIR("Vision/Program/CalibMatrix.ini");	
	QSettings file(iniPath, QSettings::IniFormat);

	memset(&m_calibInfo,0, sizeof(m_calibInfo));

	m_calibInfo.exposeTime		     = file.value("Model/exposeTime", 35000).toDouble();
	m_calibInfo.minAngle		     = file.value("Model/minAngle", -15).toDouble();
	m_calibInfo.maxAngle		     = file.value("Model/maxAngle", 15).toDouble();
	m_calibInfo.smooth		         = file.value("Model/smooth", 1).toDouble();
	m_calibInfo.minContrast	         = file.value("Model/minContrast", 5).toDouble();
	m_calibInfo.maxContrast	         = file.value("Model/maxContrast", 10).toDouble();
	m_calibInfo.minScore		     = file.value("Model/minScore", 0.5).toDouble();
	return true;
}

bool Config::loadCalibMatrix()
{
	QString   iniPath = CFGDIR("Vision/Program/CalibMatrix.ini");
	QSettings file(iniPath, QSettings::IniFormat);

	m_calibMatrix.value[0] = file.value("Calib/val1", 0).toDouble();
	m_calibMatrix.value[1] = file.value("Calib/val2", 0).toDouble();
	m_calibMatrix.value[2] = file.value("Calib/val3", 0).toDouble();
	m_calibMatrix.value[3] = file.value("Calib/val4", 0).toDouble();
	m_calibMatrix.value[4] = file.value("Calib/val5", 0).toDouble();
	m_calibMatrix.value[5] = file.value("Calib/val6", 0).toDouble();

	return true;
}

bool Config::saveCalibMatrix()
{
	QString   iniPath = CFGDIR("Vision/Program/CalibMatrix.ini");
	QSettings file(iniPath, QSettings::IniFormat);

	file.setValue("Calib/val1", m_calibMatrix.value[0]);
	file.setValue("Calib/val2", m_calibMatrix.value[1]);
	file.setValue("Calib/val3", m_calibMatrix.value[2]);
	file.setValue("Calib/val4", m_calibMatrix.value[3]);
	file.setValue("Calib/val5", m_calibMatrix.value[4]);
	file.setValue("Calib/val6", m_calibMatrix.value[5]);

	return true;
}

bool Config::pareaRunPointInfo(QByteArray &byteArray)
{
	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);

	if (document.isArray())
	{
		QJsonArray jsonArray = document.array();
		int pointNum = jsonArray.size();
		for (int i = 0; i < pointNum; i++)
		{
			RunPoint pointInfo;
			QJsonObject pointObj = jsonArray.at(i).toObject();
			
			pointInfo.name = pointObj.value("name").toString();
			pointInfo.desc = pointObj.value("desc").toString();

			QJsonObject objDim = pointObj.value("axisName").toObject();
			pointInfo.dimension.axisNameX = objDim.value("X").toString();
			pointInfo.dimension.axisNameY = objDim.value("Y").toString();
			pointInfo.dimension.axisNameZ = objDim.value("Z").toString();
			pointInfo.dimension.axisNameU = objDim.value("U").toString();
			pointInfo.dimension.axisNameV = objDim.value("V").toString();
			pointInfo.dimension.axisNameW = objDim.value("W").toString();

			QJsonObject objPos = pointObj.value("axisPos").toObject();
			pointInfo.pos[0] = objPos.value("X").toDouble();
			pointInfo.pos[1] = objPos.value("Y").toDouble();
			pointInfo.pos[2] = objPos.value("Z").toDouble();
			pointInfo.pos[3] = objPos.value("U").toDouble();
			pointInfo.pos[4] = objPos.value("V").toDouble();
			pointInfo.pos[5] = objPos.value("W").toDouble();

			m_vRunPoint.push_back(pointInfo);
		}
	}

	return true;
}

bool Config::runPointfo2Byte(QByteArray &byteArray)
{	
	QJsonDocument	document;

	QJsonArray pointArrayObj;
	for (int i = 0; i < m_vRunPoint.size(); i++)
	{
		QJsonObject pointObj;
		pointObj.insert("name", m_vRunPoint[i].name);
		pointObj.insert("desc", m_vRunPoint[i].desc);

		QJsonObject axisName, axisPos;
		for (int j = 0; j < 6; ++j)
		{
			if (!m_vRunPoint[i].dimension.axisNameX.isEmpty())
			{
				axisName.insert("X", m_vRunPoint[i].dimension.axisNameX);
				axisPos.insert("X", m_vRunPoint[i].pos[0]);
			}
			if (!m_vRunPoint[i].dimension.axisNameY.isEmpty())
			{
				axisName.insert("Y", m_vRunPoint[i].dimension.axisNameY);
				axisPos.insert("Y", m_vRunPoint[i].pos[1]);
			}
			if (!m_vRunPoint[i].dimension.axisNameZ.isEmpty())
			{
				axisName.insert("Z", m_vRunPoint[i].dimension.axisNameZ);
				axisPos.insert("Z", m_vRunPoint[i].pos[2]);
			}
			if (!m_vRunPoint[i].dimension.axisNameU.isEmpty())
			{
				axisName.insert("U", m_vRunPoint[i].dimension.axisNameU);
				axisPos.insert("U", m_vRunPoint[i].pos[3]);
			}
			if (!m_vRunPoint[i].dimension.axisNameV.isEmpty())
			{
				axisName.insert("V", m_vRunPoint[i].dimension.axisNameV);
				axisPos.insert("V", m_vRunPoint[i].pos[4]);
			}
			if (!m_vRunPoint[i].dimension.axisNameW.isEmpty())
			{
				axisName.insert("W", m_vRunPoint[i].dimension.axisNameW);
				axisPos.insert("W", m_vRunPoint[i].pos[5]);
			}
		}	
		pointObj.insert("axisName", axisName);
		pointObj.insert("axisPos", axisPos);	
		pointArrayObj.append(pointObj);
	}

	document.setArray(pointArrayObj);
	byteArray = document.toJson(QJsonDocument::Indented);
	return true;
}