#include "WorkStation.h"
#include "MainWidget.h"
#include "LoginWidget.h"
#include "ParamWidget.h"
#include "CanConnectWidget.h"
#include "moduledebug.h"
#include "axisMoveWidget.h"
#include "../Motion/Motion_dmc/Motion_dmc.h"
#include "../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../WorkFlow/WorkFlow/WorkFlow.h"
#include "../Utility/SerialPort/SerialPort.h"
#include "../Utility/Utility/Utility.h"
#include "../Utility/XMessageBox/XMessageBox.h"
#include "../Utility/NetWork/NetWork.h"
#include "../Utility/System/Config.h"
#include <QFileDialog>

WorkStation::WorkStation(QWidget *parent)
	: QMainWindow(parent)
{
	initData();
	initUI();
	configUser();
	initConnection();
	m_updateModuleStatus = startTimer(150);
	initStyle(CFGDIR("Config/Skin.qss"));
	SERIALPORT_INSTANCE;
	emit AppInit();
}

WorkStation::~WorkStation()
{
	qDebug() << "WorkStation Destroyed";
}

void	WorkStation::initData()
{
	m_mainWidget = new MainWidget(this);
	m_paramWidget = new ParamWidget;
	m_moduleDebug = new ModuleDebug;
	m_axisMoveWidget = new AxisMoveWidget;
	m_menuBar = new QMenuBar(this);
	m_statusBar = new QStatusBar(this);
	m_canConnectWidget = new CanConnectWidget;
	m_translator = new QTranslator;

	int languageId = CONFIG_INSTANCE->getSysInfo().languageId;
	if (0 == languageId)
		onMenuChinese();
	else if (1 == languageId)
		onMenuEnglish();
	else
		onMenuVietnamese();
	
	m_mainWidget->setObjectName("mainWidget");
	m_paramWidget->setObjectName("paramWidget");
	m_menuBar->setObjectName("menuBar");
	m_statusBar->setObjectName("statusBar");
	m_axisMoveWidget->setObjectName("axisMoveWidget");
	m_paramWidget->setWindowFlags(m_paramWidget->windowFlags() | Qt::WindowStaysOnTopHint);
}

void WorkStation::initUI()
{
	setWindowTitle("ScanBarSystem 14.0");
	initLayout();
	initMenuBar();
	initStatusBar();
	setWindowState(Qt::WindowMaximized);
}

void WorkStation::initLayout()
{
	setMinimumSize(1200, 700);
	setMenuBar(m_menuBar);
	setStatusBar(m_statusBar);
	setCentralWidget(m_mainWidget);
}

void  WorkStation::initMenuBar()
{
	QString menuTitile = CONFIG_INSTANCE->getSysInfo().usermode == USER_ADMIN ? tr("Quit Register") : tr("Register");
	m_menuSet = m_menuBar->addMenu(tr("Setting"));
	m_menuDebug = m_menuBar->addMenu(tr("Debug"));
	m_menuRun = m_menuBar->addMenu(tr("Run"));
	m_menuLogin = m_menuBar->addMenu(tr("Permission"));
	m_menuLanguage = m_menuBar->addMenu(tr("Language"));
	actSet = m_menuSet->addAction(tr("System Para"));
	actMotor = m_menuSet->addAction(tr("Motor"));
	actCommu = m_menuSet->addAction(tr("Communication"));
	actPoints = m_menuSet->addAction(tr("Point"));
	actIO = m_menuSet->addAction(tr("IO"));
	actModuleDebugWidget = m_menuDebug->addAction(tr("Module Debug"));
	actAxisDebugWidget = m_menuDebug->addAction(tr("Axis Debug"));
	actCanConnectWidget = m_menuDebug->addAction(tr("CanConnect"));

	actAutoMode = m_menuRun->addAction(tr("Auto Mode"));
	actClearMode = m_menuRun->addAction(tr("Clear Mode"));
	actLog = m_menuRun->addAction(tr("Clear Message"));
	actLogin = m_menuLogin->addAction(menuTitile);
	actZw = m_menuLanguage->addAction(tr("chinese"));
	actEnglish = m_menuLanguage->addAction(tr("english"));
	actVietnamese = m_menuLanguage->addAction(tr("vietnamese"));
	
	actAutoMode->setCheckable(true);
	actAutoMode->setChecked(false);
	actClearMode->setCheckable(true);
	actClearMode->setChecked(false);

	actSet->setShortcut(QKeySequence("F1"));
	actMotor->setShortcut(QKeySequence("F2"));
	actCommu->setShortcut(QKeySequence("F3"));
	actPoints->setShortcut(QKeySequence("F4"));
	actIO->setShortcut(QKeySequence("F5"));
	actLogin->setShortcut(QKeySequence("Alt+Z"));

	connect(actLog, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actSet, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actMotor, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actIO, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actPoints, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actAutoMode, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actClearMode, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actCommu, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actLogin, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actZw, &QAction::triggered, this, &WorkStation::onMenuChinese);
	connect(actVietnamese, &QAction::triggered, this, &WorkStation::onMenuVietnamese);
	connect(actEnglish, &QAction::triggered, this, &WorkStation::onMenuEnglish);
	connect(actModuleDebugWidget, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actAxisDebugWidget, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
	connect(actCanConnectWidget, &QAction::triggered, this, &WorkStation::onMenuBtnClicked);
}

void WorkStation::initStatusBar()
{
	m_statusLabel   = new QLabel(this);
	m_logStatus     = new QLabel(this);
	m_productLabel  = new QLabel(this);
	m_ngNumLabel = new QLabel(this);
	m_feedStatusLabel = new QLabel(this);
	m_carryStatusLabel = new QLabel(this);
	m_laserStatusLabel = new QLabel(this);
	m_unloadStatusLabel = new QLabel(this);

	m_statusLabel  ->setMinimumSize(m_statusLabel->sizeHint());
	m_logStatus    ->setFixedWidth(110);
	m_productLabel ->setFixedWidth(110);
	m_ngNumLabel->setFixedWidth(110);
	m_feedStatusLabel->setFixedWidth(110);
	m_carryStatusLabel->setFixedWidth(110);
	m_laserStatusLabel->setFixedWidth(110);
	m_unloadStatusLabel->setFixedWidth(110);

	m_logStatus->setText(tr("Operator"));
	m_productLabel->setText(tr("Work count:0"));
	m_ngNumLabel->setText(QStringLiteral("Ng数量:"));

	m_feedStatusLabel->setText(QStringLiteral("上料模组:"));
	m_carryStatusLabel->setText(QStringLiteral("搬运模组:"));
	m_laserStatusLabel->setText(QStringLiteral("扫码模组:"));
	m_unloadStatusLabel->setText(QStringLiteral("下料模组:"));

	m_logStatus->setAlignment(Qt::AlignCenter);
	m_statusLabel->setAlignment(Qt::AlignCenter);
	m_productLabel->setAlignment(Qt::AlignCenter);
	m_ngNumLabel->setAlignment(Qt::AlignCenter);
	m_feedStatusLabel->setAlignment(Qt::AlignCenter);
	m_carryStatusLabel->setAlignment(Qt::AlignCenter);
	m_laserStatusLabel->setAlignment(Qt::AlignCenter);
	m_unloadStatusLabel->setAlignment(Qt::AlignCenter);

	m_logStatus    ->setObjectName("statusLabel");
	m_statusLabel  ->setObjectName("statusLabel");
	m_productLabel ->setObjectName("productLabel");
	m_ngNumLabel->setObjectName("ngNumLabel");
	m_feedStatusLabel->setObjectName("feedStatusLabel");
	m_carryStatusLabel->setObjectName("carryStatusLabel");
	m_laserStatusLabel->setObjectName("laserStatusLabel");
	m_unloadStatusLabel->setObjectName("unloadStatusLabel");

	m_statusBar->addWidget(m_statusLabel);
	m_statusBar->addPermanentWidget(m_logStatus);
	m_statusBar->addPermanentWidget(m_productLabel);
	m_statusBar->addPermanentWidget(m_ngNumLabel);
	m_statusBar->addPermanentWidget(m_feedStatusLabel);
	m_statusBar->addPermanentWidget(m_carryStatusLabel);
	m_statusBar->addPermanentWidget(m_laserStatusLabel);
	m_statusBar->addPermanentWidget(m_unloadStatusLabel);
	m_statusLabel ->setText("Ready");
}

void WorkStation::initConnection()
{
	connect(this, &WorkStation::userModeChanged, m_mainWidget, &MainWidget::onUserModeChanged);
	connect(this, &WorkStation::userModeChanged, m_paramWidget, &ParamWidget::setUserConfig);
	connect(this, &WorkStation::AppInit, m_mainWidget, &MainWidget::onAppInit, Qt::DirectConnection);
	connect(this, &WorkStation::AppInit, WORKFLOW_INSTANCE, &WorkFlow::onAppInit);
	connect(this, &WorkStation::AppExit, WORKFLOW_INSTANCE, &WorkFlow::onExitApp);
	connect(this, &WorkStation::AppExit, MOTION_INSTANCE.data(), &Motion_dmc::onAppExit);
	connect(this, &WorkStation::AppExit, m_paramWidget, &ParamWidget::onExitApp);
	connect(this, &WorkStation::chanageLanguage, WORKFLOW_INSTANCE, &WorkFlow::onChanageLanguage);
	connect(MANAGER, &CardInterfaceManager::printUILog, m_mainWidget, &MainWidget::onPrintLog);
	connect(WORKFLOW_INSTANCE, &WorkFlow::printUILog, m_mainWidget, &MainWidget::onPrintLog);
	connect(WORKFLOW_INSTANCE, &WorkFlow::setUISysStatus, m_mainWidget, &MainWidget::onSetUISysStatus);
	connect(WORKFLOW_INSTANCE, &WorkFlow::setUISysStatus, m_paramWidget, &ParamWidget::onSysChanged);
	connect(WORKFLOW_INSTANCE, &WorkFlow::updateOutput, this, &WorkStation::onUpdateOutput);	
}

void WorkStation::onMenuBtnClicked()
{
	QAction* action = qobject_cast<QAction*>(sender());
	QString objText = action->text();
	qDebug() << objText;

	if (objText == tr("System Para"))
	{
		if (USER_ADMIN != CONFIG_INSTANCE->getSysInfo().usermode) return;
		m_paramWidget->setCurTab(0);
		m_paramWidget->showNormal();
	}
	else if (objText == tr("Motor"))
	{
		if (USER_ADMIN != CONFIG_INSTANCE->getSysInfo().usermode) return;
		m_paramWidget->setCurTab(1);
		m_paramWidget->showNormal();
	}
	else if (objText == tr("Communication"))
	{
		if (USER_ADMIN != CONFIG_INSTANCE->getSysInfo().usermode) return;
		m_paramWidget->setCurTab(2);
		m_paramWidget->showNormal();
	}
	else if (objText == tr("Point"))
	{
		if (USER_ADMIN != CONFIG_INSTANCE->getSysInfo().usermode) return;
		m_paramWidget->setCurTab(3);
		m_paramWidget->showNormal();
	}
	else if (objText == tr("IO"))
	{
		if (USER_OPTR == CONFIG_INSTANCE->getSysInfo().usermode) return;
		m_paramWidget->setCurTab(4);
		m_paramWidget->showNormal();
	}
	else if (objText == tr("Auto Mode"))
	{
		WORKFLOW_INSTANCE->setAutoMode(action->isChecked());	
	}
	else if (objText == tr("Clear Mode"))
	{
		WORKFLOW_INSTANCE->setClearMode(action->isChecked());
	}
	else if (objText == tr("Register"))
	{
		menuClickedLogin(objText);
	}
	else if (objText == tr("Quit Register"))
	{
		menuClickedLogin(objText);
	}
	else if (objText.contains(tr("Enable glue")))
	{
	}
	else if (objText.contains(tr("Clear Message")))
	{
		m_mainWidget->clearLog();
	}
	else if (objText == tr("Module Debug"))
	{
		m_moduleDebug->show();
	}
	else if (objText == tr("Axis Debug"))
	{
		m_axisMoveWidget->show();
	}
	else if (objText == tr("CanConnect"))
	{
		m_canConnectWidget->show();
	}
}

void WorkStation::onMenuChinese()
{
	m_translator->load(BINDIF("workstation_zh.qm"));
	qApp->installTranslator(m_translator);

	emit chanageLanguage(0);
	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	if (info.languageId != 0)
	{
		info.languageId = 0;
		CONFIG_INSTANCE->setSysInfo(info);
	}
}

void WorkStation::onMenuVietnamese()
{
	m_translator->load(BINDIF("workstation_vi.qm"));
	qApp->installTranslator(m_translator);

	emit chanageLanguage(2);
	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	if (info.languageId != 2)
	{
		info.languageId = 2;
		CONFIG_INSTANCE->setSysInfo(info);
	}
}

void WorkStation::onMenuEnglish()
{
	m_translator->load(BINDIF("workstation_en.qm"));
	qApp->installTranslator(m_translator);

	emit chanageLanguage(1);
	SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	if (info.languageId != 1)
	{
		info.languageId = 1;
		CONFIG_INSTANCE->setSysInfo(info);
	}
}

void  WorkStation::menuClickedLogin(QString &menuText)
{
	if (menuText == tr("Register"))
	{
		LoginWidget login;
		int rtn = login.exec();

		if (rtn != QDialog::Rejected)
		{
			SystemInfo info = CONFIG_INSTANCE->getSysInfo();
			info.usermode = (USERMODE)rtn;
			CONFIG_INSTANCE->setSysInfo(info);

			this->configUser();
			emit userModeChanged((USERMODE)info.usermode);
	
			this->m_logStatus->setText(info.usermode == USER_ADMIN ? tr("Administrator") : tr("After sale"));
			getMenuBarAction(m_menuLogin, tr("Register"))->setText(tr("Quit Register"));
		}
	}
	else if (menuText == tr("Quit Register"))
	{
		SystemInfo info = CONFIG_INSTANCE->getSysInfo();
		info.usermode = USER_OPTR;
		CONFIG_INSTANCE->setSysInfo(info);

		this->configUser();
		emit userModeChanged((USERMODE)info.usermode);
	
		this->m_logStatus->setText(tr("Operator"));
		getMenuBarAction(m_menuLogin, tr("Quit Register"))->setText(tr("Register"));
	}
}

void WorkStation::closeEvent(QCloseEvent *event)
{
	int rtn = XMessageBox::ask(tr("Sure close the software?"));

	if (rtn)
	{
		emit AppExit();
		m_paramWidget	->accept();
		SERIALPORT_INSTANCE->quitThread();
		event->accept();
	}
	else
		event->ignore();
}

QAction*  WorkStation::getMenuBarAction(QMenu *menu, QString name)
{
	QList<QAction*> actions = menu->actions();
	for each (auto action in actions)
	{
		QString strTest = action->text();
		if (strTest == name)	
			return action;	
	}
	return nullptr;
}


void WorkStation::configUser()
{
	if (USER_OPTR == CONFIG_INSTANCE->getSysInfo().usermode)
	{
		m_menuSet    ->setEnabled(false);
		m_menuDebug  ->setEnabled(false);
	}
	else if (USER_CONFIG == CONFIG_INSTANCE->getSysInfo().usermode)
	{
		m_menuSet	 ->setEnabled(true);
		m_menuDebug	 ->setEnabled(true);
	}
	else if (USER_ADMIN == CONFIG_INSTANCE->getSysInfo().usermode)
	{
		m_menuSet	->setEnabled(true);
		m_menuDebug	->setEnabled(true);
	}
}

void   WorkStation::retranslateUi()
{
	QString menuTitile = CONFIG_INSTANCE->getSysInfo().usermode == USER_ADMIN ? tr("Quit Register") : tr("Register");
	m_menuSet->setTitle(tr("Setting"));
	m_menuDebug->setTitle(tr("Debug"));
	m_menuRun->setTitle(tr("Run"));
	m_menuLogin->setTitle(tr("Permission"));
	m_menuLanguage->setTitle(tr("Language"));
	actSet->setText(tr("System Para"));
	actMotor->setText(tr("Motor"));
	actCommu->setText(tr("Communication"));
	actPoints->setText(tr("Point"));
	actIO->setText(tr("IO"));
	actAutoMode->setText(tr("Auto Mode"));
	actClearMode->setText(tr("Clear Mode"));
	actLog->setText(tr("Clear Message"));
	actModuleDebugWidget->setText(tr("Module Debug"));
	actAxisDebugWidget->setText(tr("Axis Debug"));
	actLogin->setText(menuTitile);
	actZw->setText(tr("chinese"));
	actVietnamese->setText(tr("vietnamese"));
	actEnglish->setText(tr("english"));
	m_logStatus->setText(tr("Operator"));
	m_productLabel->setText(tr("Work count:0"));
}

void WorkStation::initStyle(QString filePath)
{
	QFile file(filePath);
	if (file.open(QFile::ReadOnly))
	{
		QString qss = QLatin1String(file.readAll());
		QString paletteColor = qss.mid(20, 7);
		qApp->setStyleSheet(qss);
		file.close();
	}
}

void WorkStation::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_updateModuleStatus)
	{
		int ret = WORKFLOW_INSTANCE->getFeedStatus();

		QString str = ret == 0 ? QStringLiteral("上料模组:运行中") : 
					 (ret == 1 ? QStringLiteral("上料模组:就绪") : QStringLiteral("上料模组:未就绪"));

		m_feedStatusLabel->setText(str);
		
		ret = WORKFLOW_INSTANCE->getCarryStatus();
		str = ret == 0 ? QStringLiteral("搬运模组:运行中") :
			 (ret == 1 ? QStringLiteral("搬运模组:就绪") : QStringLiteral("搬运模组:未就绪"));
		m_carryStatusLabel->setText(str);

		ret = WORKFLOW_INSTANCE->getLaserStatus();
		str = ret == 0 ? QStringLiteral("镭码模组:运行中") :
			(ret == 1 ? QStringLiteral("镭码模组:就绪") : QStringLiteral("镭码模组:未就绪"));
		m_laserStatusLabel->setText(str);

		ret = WORKFLOW_INSTANCE->getUnloadStatus();
		str = ret == 0 ? QStringLiteral("下料模组:运行中") :
			(ret == 1 ? QStringLiteral("下料模组:就绪") : QStringLiteral("下料模组:未就绪"));
		m_unloadStatusLabel->setText(str);
	}
}

void WorkStation::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		retranslateUi();
		break;
	default:
		break;
	}
}


void WorkStation::onUpdateOutput(unsigned int total, unsigned int ngNum)
{
	QString str = QStringLiteral("工作计数:%1").arg(total);
	QString str1 = QStringLiteral("Ng数量:%1").arg(ngNum);
	m_productLabel->setText(str);
	m_ngNumLabel->setText(str1);
}
