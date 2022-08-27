#include "Io.h"
#include "../../include/LTDMC.h"
#include "../../include/Error.h"
#include "../../include/Common.h"
#include "IOC0640.h"

QMutex Io::m_insMutex;
QSharedPointer<Io> Io::m_pInstance;

Io::Io(QObject *parent)
	: QObject(parent)
{
	m_cardNum = 0;
	m_extCardNum = 0;
}

Io::~Io()
{
}

QSharedPointer<Io>& Io::instance()
{
	if (m_pInstance.isNull())
	{
		QMutexLocker mutexLocker(&m_insMutex);
		if (m_pInstance.isNull())
			m_pInstance = QSharedPointer<Io>(new Io(nullptr));
	}
	return m_pInstance;
}

void Io::setCardNum(int num)
{
	m_cardNum = num;
}

void Io::setExtCardNum(int num)
{
	m_extCardNum = num;
}

int Io::readInBit_Alarm(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	quint16 status = dmc_axis_io_status(cardIndex, axisInx);
	val = (status >> 0) & 0x01;
	return RETURN_OK;
}

int Io::readInBit_LimitN(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	quint16 status = dmc_axis_io_status(cardIndex, axisInx);
	val = (status >> 2) & 0x01;
	return RETURN_OK;
}

int Io::readInBit_LimitP(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	quint16 status = dmc_axis_io_status(cardIndex, axisInx);
	val = (status >> 1) & 0x01;
	return RETURN_OK;
}

int Io::readInBit_Origin(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	quint16 status = dmc_axis_io_status(cardIndex, axisInx);
	val = (status >> 4) & 0x01;
	return RETURN_OK;
}

int Io::readInBit_Ready(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	quint16 status = dmc_axis_io_status(cardIndex, axisInx);
	val = (status >> 10) & 0x01;
	return RETURN_OK;
}

int Io::readInBit_Inplace(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	quint16 status = dmc_axis_io_status(cardIndex, axisInx);
	val = (status >> 8) & 0x01;
	return RETURN_OK;
}

int Io::readInBit_Enable(quint16 cardIndex, quint16 axisInx, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	val = dmc_read_sevon_pin(cardIndex, axisInx);
	return RETURN_OK;
}

int Io::writeOutBit_Enable(quint16 cardIndex, quint16 axisInx, short val)
{
	QMutexLocker lock(&m_mutexIO);
	dmc_write_sevon_pin(cardIndex, axisInx, val);
	return RETURN_OK;
}

int Io::readInBit_Self(quint16 cardIndex, quint16 IOIndex, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(cardIndex < m_cardNum, ERR_INPUT_PARAM);
	RETURN_CHK(IOIndex < 16, ERR_INPUT_PARAM);
	val = dmc_read_inbit(cardIndex, IOIndex);
	return RETURN_OK;
}

int Io::readOutBit_Self(quint16 cardIndex, quint16 IOIndex, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(cardIndex < m_cardNum, ERR_INPUT_PARAM);
	RETURN_CHK(IOIndex < 16, ERR_INPUT_PARAM);
	val = dmc_read_outbit(cardIndex, IOIndex);
	return RETURN_OK;
}

int Io::writeOutBit_Self(quint16 cardIndex, quint16 IOIndex, short val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(cardIndex < m_cardNum, ERR_INPUT_PARAM);
	int rtn = dmc_write_outbit(cardIndex, IOIndex, val);
	RETURN_CHK(!rtn, ERR_WRITE_IO);
	return RETURN_OK;
}

int Io::readInBit_Ext(quint16 extIndex, quint16 IOIndex, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(extIndex < m_extCardNum, ERR_INPUT_PARAM);
	RETURN_CHK(IOIndex < 48, ERR_INPUT_PARAM);
	val = ioc_read_inbit(extIndex, IOIndex);
	return RETURN_OK;
}

int Io::readOutBit_Ext(quint16 extIndex, quint16 IOIndex, short &val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(extIndex < m_extCardNum, ERR_INPUT_PARAM);
	RETURN_CHK(IOIndex < 48, ERR_INPUT_PARAM);
	val = ioc_read_outbit(extIndex, IOIndex);
	return RETURN_OK;
}

int Io::writeOutBit_Ext(quint16 extIndex, quint16 IOIndex, short val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(extIndex < m_extCardNum, ERR_INPUT_PARAM);
	RETURN_CHK(IOIndex < 48, ERR_INPUT_PARAM);
	short rtn = ioc_write_outbit(extIndex, IOIndex, val);
	RETURN_CHK(!rtn, ERR_WRITE_IO);
	return RETURN_OK;
}

int Io::readIn_Ext(quint16 extIndex, long long &val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(extIndex < m_extCardNum, ERR_INPUT_PARAM);
	long readVal = 0;
	val = 0;
	val = ioc_read_inport(extIndex, 1);   //[32,47]
	val = val << 32;
	readVal = ioc_read_inport(extIndex, 0);   //[0,31]
	val &= readVal;
	return RETURN_OK;
}

int Io::readOut_Ext(quint16 extIndex, long long &val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(extIndex < m_extCardNum, ERR_INPUT_PARAM);
	long readVal = 0;
	val = 0;
	val = ioc_read_outport(extIndex, 1);   //[32,47]
	val = val << 32;
	readVal = ioc_read_outport(extIndex, 0);   //[0,31]
	val &= readVal;
	return RETURN_OK;
}

int Io::writeOut_Ext(quint16 extIndex, long long val)
{
	QMutexLocker lock(&m_mutexIO);
	RETURN_CHK(extIndex < m_extCardNum, ERR_INPUT_PARAM);
	short rtn = 0;
	long writeVal = (val & 0xffffffff);
	rtn = ioc_write_outbit(extIndex, 0, writeVal);   //[0,31]
	RETURN_CHK(rtn == 0, ERR_WRITE_IO);
	writeVal = val >> 32;
	rtn = ioc_write_outbit(extIndex, 1, writeVal);   //[32,47]
	RETURN_CHK(!rtn, ERR_WRITE_IO);
	return RETURN_OK;
}

int Io::readInBit_Can(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val)
{
	val = 0;

	quint16 readVal = 0;
	quint16 nodeNum = 0;
	quint16 status = 0;
	quint16 baudrate = 0;
	quint16 rtn = nmc_get_connect_state(cardIndex, &nodeNum, &status);
	RETURN_CHK(rtn == 0, ERR_ERROR);

	if (1 != status || nodeNum <= cardNode)
	{
		rtn = nmc_set_connect_state(cardIndex, cardNode + 1, 1, baudrate);
		RETURN_CHK(rtn == 0, ERR_ERROR);
		rtn = nmc_get_connect_state(cardIndex, &nodeNum, &status);
		RETURN_CHK(rtn == 0, ERR_ERROR);
	}

	if (1 == status && nodeNum > cardNode)
	{
		nmc_read_inbit(cardIndex, cardNode + 1, IOIndex, &readVal);
		RETURN_CHK(rtn == 0, ERR_ERROR);
		val = readVal == 1 ? 1 : 0;
		return RETURN_OK;
	}
	
	return ERR_ERROR;	
}

int Io::readOutBit_Can(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val)
{
	val = 0;

	quint16 readVal = 0;
	quint16 nodeNum = 0;
	quint16 status = 0;
	quint16 baudrate = 0;
	quint16 rtn = nmc_get_connect_state(cardIndex, &nodeNum, &status);
	RETURN_CHK(rtn == 0, ERR_ERROR);

	if (1 != status || nodeNum <= cardNode)
	{
		rtn = nmc_set_connect_state(cardIndex, cardNode + 1, 1, baudrate);
		RETURN_CHK(rtn == 0, ERR_ERROR);
		rtn = nmc_get_connect_state(cardIndex, &nodeNum, &status);
		RETURN_CHK(rtn == 0, ERR_ERROR);
	}

	if (1 == status && nodeNum > cardNode)
	{
		nmc_read_outbit(cardIndex, cardNode + 1, IOIndex, &readVal);
		RETURN_CHK(rtn == 0, ERR_ERROR);
		val = readVal == 1 ? 1 : 0;
		return RETURN_OK;
	}
	
	return ERR_ERROR;
}

int Io::writeOutBit_Can(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short val)
{
	quint16 writeVal = 0;
	quint16 nodeNum = 0;
	quint16 status = 0;
	quint16 baudrate = 0;
	quint16 rtn = nmc_get_connect_state(cardIndex, &nodeNum, &status);
	RETURN_CHK(rtn == 0, ERR_ERROR);

	if (1 != status || nodeNum <= cardNode)
	{
		rtn = nmc_set_connect_state(cardIndex, cardNode + 1, 1, baudrate);
		RETURN_CHK(rtn == 0, ERR_ERROR);
		rtn = nmc_get_connect_state(cardIndex, &nodeNum, &status);
		RETURN_CHK(rtn == 0, ERR_ERROR);
	}

	if (1 == status && nodeNum > cardNode)
	{
		writeVal = val > 0 ? 1 : 0;
		rtn = nmc_write_outbit(cardIndex, cardNode + 1, IOIndex, writeVal);
		RETURN_CHK(rtn == 0, ERR_ERROR);
		return RETURN_OK;
	}

	return ERR_ERROR;
}

int Io::readInBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType)
{
	val = 0;

	if (0 == cardType)
	{
		return readInBit_Self(cardIndex, IOIndex, val);
	}
	else if (1 == cardType)
	{
		return readInBit_Ext(cardIndex, IOIndex, val);
	}
	else if (2 == cardType)
	{
		return readInBit_Can(cardIndex, cardNode, IOIndex, val);
	}

	return ERR_INPUT_PARAM;
}

int Io::readOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType)
{
	val = 0;

	if (0 == cardType)
	{
		return readOutBit_Self(cardIndex, IOIndex, val);
	}
	else if (1 == cardType)
	{
		return readOutBit_Ext(cardIndex, IOIndex, val);
	}
	else if (2 == cardType)
	{
		return readOutBit_Can(cardIndex, cardNode, IOIndex, val);
	}

	return ERR_INPUT_PARAM;	
}

int Io::writeOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short val, int cardType)
{
	if (0 == cardType)
	{
		return writeOutBit_Self(cardIndex, IOIndex, val);
	}
	else if (1 == cardType)
	{
		return writeOutBit_Ext(cardIndex, IOIndex, val);
	}
	else if (2 == cardType)
	{
		return writeOutBit_Can(cardIndex, cardNode, IOIndex, val);

	}

	return ERR_INPUT_PARAM;
}
