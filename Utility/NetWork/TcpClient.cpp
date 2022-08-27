#include "TcpClient.h"
#include "../../Utility/System/Log.h"
#include "../../include/Common.h"
#include "../../Utility/Utility/Utility.h"
#include "GeneralHelper.h"


TcpClient::TcpClient(QObject *parent)
	: QObject(parent), m_Client(this), m_recvSem(0)
{
	m_Client->SetSocketBufferSize(10240000);
	m_Client->SetFreeBufferPoolSize(10240000);
	
	init();
}

TcpClient::~TcpClient()
{
}

int TcpClient::conect2Server(QString address, quint16 port, int async)
{	
	if (m_Client->Start(address.toStdWString().c_str(), port, async))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void TcpClient::setTcpName(QString name)
{
	m_name = name;
}

bool TcpClient::sendData(QString smg)
{
	if (!isConnected()) return 1;

	//释放上次未接收数据
	int cur = m_recvSem.available();
	if (cur > 0)
	{
		m_recvSem.acquire(cur);
	}

	QByteArray arr = m_isHex ? hexToByte(smg) : smg.toLatin1();

	int size       = arr.length();
	BYTE* buff     = new BYTE[size];

	for (int i = 0; i < size; ++i)
	{
		buff[i] = arr[i];
	}

	int ret = sendData(buff, size);
	delete[] buff;

	return ret == 0;
}


int TcpClient::sendData(unsigned char* pBuff, int len)
{
	if (!isConnected()) return 1;

	//释放上次未接收数据
	int cur = m_recvSem.available();
	if (cur > 0)
	{
		m_recvSem.acquire(cur);
	}

	int ret = TRUE == m_Client->Send(pBuff, len) ? 0 : 1;

	return  ret;
}

void TcpClient::setStatus(EnState state)
{
	m_enState = state;
}


EnHandleResult TcpClient::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
	setStatus(CONNECTED);

	m_connId = dwConnID;
	return HR_OK;
}

EnHandleResult TcpClient::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{

	return HR_OK;
}

EnHandleResult TcpClient::OnReceive(ITcpClient* pSender, CONNID dwConnID, int iLength)
{
	ITcpPullClient* pClient = ITcpPullClient::FromS(pSender);

	CBufferPtr buffer(iLength + 1, true);
	EnFetchResult result = pClient->Fetch(buffer, (int)buffer.Size() - 1);

	if (m_name == "Vision_L" || m_name == "Vision_R")
	{
		if (result == FR_OK)
		{
			char* pData = (char*)buffer.Ptr();
			m_strRecv = QString("%1").arg(pData);
			m_recvSem.release(1);
		}
	}
	else if (m_name == "Macmini")
	{
		if (result == FR_OK)
		{
			char* pData = (char*)buffer.Ptr();
			QString temp;
			temp = QString("%1").arg(pData);

			if (temp == '{')
			{
				m_strRecv = temp;
			}
			else
			{
				m_strRecv += temp;
				m_recvSem.release(1);
			}		
		}
	}
	else if (m_name == "Measure Height")
	{
		if (result == FR_OK)
		{
			char* pData = (char*)buffer.Ptr();
			QString temp;
			temp = QString("%1").arg(pData);
			m_strRecv = temp;
			m_recvSem.release(1);		
		}
	}

	return HR_OK;
}

EnHandleResult TcpClient::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	setStatus(STOPPED);
	return HR_OK;
}



void	TcpClient::init()
{
	m_connId = 0;
	m_isHex = 0;
}



//西科点激光
void	TcpClient::parseData(BYTE* pData, int len)
{	
	QString s;
	int nm = 0;
	if (pData[0] == 176 && pData[1] == 4)
	{
		for (int i = 2; i <= len - 1; i++)
		{
			if (pData[i] <= 15)
			{
				s = s + "0" + QString("%1").arg(pData[i]);
			}
			else
			{
				s = s + QByteArray::number(pData[i], 16);
			}
		}

		QByteArray arr = s.toLatin1();
		bool isOk = false;
		int data = arr.toInt(&isOk, 16);

		std::vector<int> v;
		v.reserve(33);
		if (isOk == false)
		{
			int fu = 0;
			for (int i = 0; i < arr.size(); ++i)
			{
				//压入补码
				if (arr[i] == '0')
				{
					v.push_back(1);
					v.push_back(1);
					v.push_back(1);
					v.push_back(1);
				}
				if (arr[i] == '1')
				{
					v.push_back(1);
					v.push_back(1);
					v.push_back(1);
					v.push_back(0);
				}
				if (arr[i] == '2')
				{
					v.push_back(1);
					v.push_back(1);
					v.push_back(0);
					v.push_back(1);
				}
				if (arr[i] == '3')
				{
					v.push_back(1);
					v.push_back(1);
					v.push_back(0);
					v.push_back(0);
				}
				if (arr[i] == '4')
				{
					v.push_back(1);
					v.push_back(0);
					v.push_back(1);
					v.push_back(1);
				}
				if (arr[i] == '5')
				{
					v.push_back(1);
					v.push_back(0);
					v.push_back(1);
					v.push_back(0);
				}
				if (arr[i] == '6')
				{
					v.push_back(1);
					v.push_back(0);
					v.push_back(0);
					v.push_back(1);
				}
				if (arr[i] == '7')
				{
					v.push_back(1);
					v.push_back(0);
					v.push_back(0);
					v.push_back(0);
				}
				if (arr[i] == '8')
				{
					v.push_back(0);
					v.push_back(1);
					v.push_back(1);
					v.push_back(1);
				}
				if (arr[i] == '9')
				{
					v.push_back(0);
					v.push_back(1);
					v.push_back(1);
					v.push_back(0);
				}
				if (arr[i] == 'a')
				{
					v.push_back(0);
					v.push_back(1);
					v.push_back(0);
					v.push_back(1);
				}
				if (arr[i] == 'b')
				{
					v.push_back(0);
					v.push_back(1);
					v.push_back(0);
					v.push_back(0);
				}
				if (arr[i] == 'c')
				{
					v.push_back(0);
					v.push_back(0);
					v.push_back(1);
					v.push_back(1);
				}
				if (arr[i] == 'd')
				{
					v.push_back(0);
					v.push_back(0);
					v.push_back(1);
					v.push_back(0);
				}
				if (arr[i] == 'e')
				{
					v.push_back(0);
					v.push_back(0);
					v.push_back(0);
					v.push_back(1);
				}
				if (arr[i] == 'f')
				{
					v.push_back(0);
					v.push_back(0);
					v.push_back(0);
					v.push_back(0);
				}
			}

			for (int i = 0; i < 32; ++i)
			{
				fu = fu + v[i] * pow(2, 31 - i);
			}


			double dData = -(fu + 1) / 1000000.0;
			m_strRecv = QString("%1").arg(dData);
		}
		else
		{
			double dData = data / 1000000.0;
			m_strRecv = QString("%1").arg(dData);
		}

		emit recvMessage(m_name, m_strRecv);
		m_recvSem.release(1);
	}
}


bool	TcpClient::recvData(QString &msg, int msTimeOut)
{
	if (m_recvSem.tryAcquire(1, msTimeOut))
	{
		msg = m_strRecv;
		return true;
	}
	else
	{
		msg = "";
		return false;
	}


	

}

void TcpClient::disconnect()
{
	m_Client->Stop();
}