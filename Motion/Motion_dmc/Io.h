#pragma once

#include <QObject>
#include <QSharedPointer>

#define IO_INSTANCE Io::instance()

class Io : public QObject
{
	Q_OBJECT

public:
	static QSharedPointer<Io>& instance();
	~Io();

	void setCardNum(int num);
	void setExtCardNum(int num);

	int readInBit_Alarm(quint16 cardIndex, quint16 axisInx, short &val);
	int readInBit_LimitN(quint16 cardIndex, quint16 axisInx, short &val);
	int readInBit_LimitP(quint16 cardIndex, quint16 axisInx, short &val);
	int readInBit_Origin(quint16 cardIndex, quint16 axisInx, short &val);
	int readInBit_Ready(quint16 cardIndex, quint16 axisInx, short &val);				//��ȡ�������ź�
	int readInBit_Inplace(quint16 cardIndex, quint16 axisInx, short &val);				//��ȡ����λ�ź�
	int readInBit_Enable(quint16 cardIndex, quint16 axisInx, short &val);				//��ȡ��ʹ���ź�
	int writeOutBit_Enable(quint16 cardIndex, quint16 axisInx, short val);			    //�����ǿ����ź�

	int	readInBit_Self(quint16 cardIndex, quint16 IOIndex, short &val);					//��IO
	int	readOutBit_Self(quint16 cardIndex, quint16 IOIndex, short &val);
	int	writeOutBit_Self(quint16 cardIndex, quint16 IOIndex, short val);

	int	readInBit_Ext(quint16 extIndex, quint16 IOIndex, short &val);	//0640
	int	readOutBit_Ext(quint16 extIndex, quint16 IOIndex, short &val);
	int	writeOutBit_Ext(quint16 extIndex, quint16 IOIndex, short val);

	int	readIn_Ext(quint16 extIndex, long long &val);				    //0640
	int	readOut_Ext(quint16 extIndex, long long &val);
	int	writeOut_Ext(quint16 extIndex, long long val);

	int	readInBit_Can(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val);		   //��ȡCan��չ����λ
	int	readOutBit_Can(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val);		   //��ȡCan��չ���λ
	int	writeOutBit_Can(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short val);		   //����Can��չ���λ
	   
	int readInBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType);
	int readOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short &val, int cardType);
	int writeOutBit(quint16 cardIndex, quint16 cardNode, quint16 IOIndex, short val, int cardType);


private:
	Io(QObject *parent);

private:
	static QMutex m_insMutex;
	static QSharedPointer<Io>  m_pInstance;


	QMutex m_mutexIO;	//IO�ٽ���

	int	m_cardNum;		//������
	int	m_extCardNum;   //��չ������
};
