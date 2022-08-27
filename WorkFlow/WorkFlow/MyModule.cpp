#include "MyModule.h"

MyModule::MyModule(QObject *parent)
	: QThread(parent)
{
	m_bReady = false;
	m_bIsHome = false;
}

MyModule::~MyModule()
{

}

void MyModule::setReady(bool ready)
{
	m_bReady = ready;
}

bool MyModule::getReady() const
{
	return m_bReady;
}

bool MyModule::waitReset()
{
	m_homeFuture.waitForFinished();
	return m_homeFuture.result();
}

bool MyModule::getHomeFlag() const
{
	return m_bIsHome;
}
