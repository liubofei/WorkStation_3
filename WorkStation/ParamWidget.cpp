#include "ParamWidget.h"

ParamWidget::ParamWidget()
{
	ui.setupUi(this);

	init();
	initTable();
}

ParamWidget::~ParamWidget()
{
}

void ParamWidget::init()
{
	m_systemWidget	 = new SystemWidget(this);
	m_motorWidget	 = new MotorWidget(this);
	m_IOConfigWidget = new IOWidget(this);
	m_pointsWidget	 = new PointsWidget(this);
	m_communiWidget	 = new CommuniWidget(this);
}

void ParamWidget::initTable()
{
	ui.tabWidget->clear();
	ui.tabWidget->addTab(m_systemWidget, tr("System setting"));
	ui.tabWidget->addTab(m_motorWidget, tr("Motor setting"));
	ui.tabWidget->addTab(m_communiWidget, tr("Network/serial port"));
	ui.tabWidget->addTab(m_pointsWidget, tr("Point list"));
	ui.tabWidget->addTab(m_IOConfigWidget, tr(" IO setting"));
	this->setWindowTitle(tr("Parameter setting"));
}


void ParamWidget::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		initTable();
		break;
	default:
		break;
	}
}

void  ParamWidget::setCurTab(int index)
{
	if (index<0 && index >=6)
	{
		return;
	}

	ui.tabWidget->setCurrentIndex(index);
}


void  ParamWidget::setUserConfig(USERMODE userMode)
{
	if (USER_OPTR == userMode)
	{
		ui.tabWidget->setTabEnabled(0, false);
		ui.tabWidget->setTabEnabled(1, false);
		ui.tabWidget->setTabEnabled(2, false);
		ui.tabWidget->setTabEnabled(3, false);
		ui.tabWidget->setTabEnabled(4, false);
		ui.tabWidget->setTabEnabled(5, false);

	}
	else if (USER_CONFIG == userMode)
	{
		ui.tabWidget->setTabEnabled(0, false);
		ui.tabWidget->setTabEnabled(1, false);
		ui.tabWidget->setTabEnabled(2, false);
		ui.tabWidget->setTabEnabled(3, false);
		ui.tabWidget->setTabEnabled(4, true);
		ui.tabWidget->setTabEnabled(5, true);
	}
	else if (USER_ADMIN == userMode)
	{
		ui.tabWidget->setTabEnabled(0, true);
		ui.tabWidget->setTabEnabled(1, true);
		ui.tabWidget->setTabEnabled(2, true);
		ui.tabWidget->setTabEnabled(3, true);
		ui.tabWidget->setTabEnabled(4, true);
		ui.tabWidget->setTabEnabled(5, true);
	}

}

void  ParamWidget::onSysChanged(SYSTEM_STATUS status)
{
	
}

void  ParamWidget::onExitApp()
{
	
}

void  ParamWidget::keyPressEvent(QKeyEvent *e)
{
	if (e->key() >= Qt::Key_F1 && e->key() <= Qt::Key_F6)
	{
		ui.tabWidget->setCurrentIndex(e->key() - Qt::Key_F1);
	}

	QWidget::keyPressEvent(e);
}