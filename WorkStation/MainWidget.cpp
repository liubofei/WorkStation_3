#include "MainWidget.h"
#include "TrimArray.h"
#include "../Utility/System/Config.h"
#include "../Utility/XMessageBox/XMessageBox.h"
#include "../Utility/Utility/Utility.h"
#include "../Utility/System/Log.h"
#include "../Motion/Motion_dmc/Motion_dmc.h"
#include "../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../WorkFlow/WorkFlow/WorkFlow.h"
#include <QTranslator>
#include <QDateTime>
#include <QDebug>
#include <QKeyEvent>
#include <QMenu>
#include <QtWidgets/QApplication>


MainWidget::MainWidget(QWidget *parent)
: QWidget(parent)
{
	//QString str = QString("123\r");

	//QString temp = QString("123");
	//temp.append('\r');

	//if (str == temp)
	//{
	//	int g = 0;
	//}


	ui.setupUi(this);
	initData();
	initUI();
	m_updateTimerID = startTimer(1000);
}

MainWidget::~MainWidget()
{
}

void MainWidget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_updateTimerID)
	{
		QDateTime dataTime = QDateTime::currentDateTime();
		QString   strTime  = dataTime.toString("MM/dd hh:mm:ss");
		ui.label_time->setText(strTime);
		//测试用
		WORKFLOW_INSTANCE->continueWorking();
	}
}

void MainWidget::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:	
		ui.retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWidget::initData()
{
	m_userMode = USER_OPTR;
	m_laserArryWidget = new TrimArray(this);
	m_laserArryWidget->setObjectName(QString("laserArryWidget"));
	ui.tabWidget_tray_status->addTab(m_laserArryWidget, QStringLiteral("镭码盘"));
}

void MainWidget::initUI()
{
	connect(ui.pushButton_reset, &QPushButton::clicked, this, &MainWidget::onSysCtrlReset);
	connect(ui.pushButton_start_up, &QPushButton::clicked, this, &MainWidget::onSysCtrlStart);
	connect(ui.pushButton_stop, &QPushButton::clicked, this, &MainWidget::onSysCtrlStop);
	connect(ui.pushButton_continue, &QPushButton::clicked, this, &MainWidget::onSysCtrlConti);
	connect(ui.pushButton_unload_tray_taked, &QPushButton::clicked, this, &MainWidget::onUnloadTrayTaked);	

	connect(ui.pushButton_laserCalib, &QPushButton::clicked, this, &MainWidget::onLaserCalib);

	
	connect(ui.textEdit_log, &QTextEdit::customContextMenuRequested, this, &MainWidget::onTextEditMenuRequested);
	connect(WORKFLOW_INSTANCE, &WorkFlow::hintAddFeedTray, this, &MainWidget::onHintAddFeedTray);
	connect(WORKFLOW_INSTANCE, &WorkFlow::hintTakeUnloadTray, this, &MainWidget::onHintTakeUnloadTray);
	connect(WORKFLOW_INSTANCE, &WorkFlow::updateLaserResult, m_laserArryWidget, &TrimArray::onUpdateScanResult);
	connect(WORKFLOW_INSTANCE, &WorkFlow::initLaserResult, m_laserArryWidget, &TrimArray::onClearScanResult);
}

void MainWidget::onUserModeChanged(USERMODE mode)
{
	m_userMode = mode;
}

void MainWidget::printLog(QString msg)
{
	if (msg.isEmpty())
	{
		return;
	}
	else if (ui.textEdit_log->document()->lineCount()>50)
	{
		ui.textEdit_log->setText("");
		return;
	}
	else if (msg.contains("[Clear]"))
	{
		ui.textEdit_log->setText("");
		return;
	}
	else if (msg.contains("[Warn]"))
	{
		ui.textEdit_log->setTextColor(QColor(255,128,0));
		LOG_SYSTEM_ERROR(msg);
	}
	else if (msg.contains("[Error]"))
	{
		ui.textEdit_log->setTextColor(QColor(255, 0, 0));
		LOG_SYSTEM_ERROR(msg);
	}
	else if (msg.contains("[OK]"))
	{
		ui.textEdit_log->setTextColor(QColor(0 , 255, 0));
	}
	else
	{
		ui.textEdit_log->setTextColor(QColor(0, 0, 0));
	}

	QDateTime curTime = QDateTime::currentDateTime();
	QString   strTime = curTime.toString("[hh:mm:ss] ");
	ui.textEdit_log->append(strTime + msg);
}

void MainWidget::clearLog()
{
	ui.textEdit_log->clear();
}

void MainWidget::onPrintLog(QString msg)
{
	printLog(msg);
}

void MainWidget::onSetUISysStatus(SYSTEM_STATUS status)
{
	if (SYSTEM_ERROR==status)
	{
		ui.label_sysStatus->setText(tr("System Error"));
		ui.label_sysStatus->setStyleSheet("color: rgb(255, 0, 0);");
	}
	else if (SYSTEM_UNHOME == status)
	{
		ui.label_sysStatus->setText(tr("Please Reset"));
		ui.label_sysStatus->setStyleSheet("color: rgb(255, 85, 0);");
	}
	else if (SYSTEM_HOMING == status)
	{
		ui.label_sysStatus->setText(tr("Homing.."));
		ui.label_sysStatus->setStyleSheet("color: rgb(255, 85, 0);");
	}
	else if (SYSTEM_STANDBY == status)
	{
		ui.label_sysStatus->setText(tr("Ready"));
		ui.label_sysStatus->setStyleSheet("color: rgb(255, 85, 0);");
	}
	else if (SYSTEM_PAUSE == status)
	{
		ui.label_sysStatus->setText(tr("Pausing.."));
		ui.label_sysStatus->setStyleSheet("color: rgb(255, 0, 0);");
	}
	else if (SYSTEM_WORKING  == status)
	{
		ui.label_sysStatus->setText(tr("Working.."));
		ui.label_sysStatus->setStyleSheet("color: rgb(0, 255, 0);");
	}
}

void MainWidget::onSysCtrlReset()
{
	WORKFLOW_INSTANCE->startHoming();
}

void MainWidget::onSysCtrlStart()
{
	WORKFLOW_INSTANCE->startWorking();
}

void MainWidget::onSysCtrlStop()
{
	WORKFLOW_INSTANCE->stopWorking();
}

void MainWidget::onSysCtrlConti()
{
	WORKFLOW_INSTANCE->continueWorking();
}

void MainWidget::onTextEditMenuRequested(const QPoint& pos)
{
	QMenu *menu = new QMenu(ui.textEdit_log);
	menu->addAction(tr("Clear"), this, &MainWidget::onTextEidtLogMenu);
	menu->exec(QCursor::pos());
}

void MainWidget::onTextEidtLogMenu()
{
	ui.textEdit_log->clear();
}

void MainWidget::onAppInit()
{
}

void MainWidget::onExitApp()
{
}

void MainWidget::onHintTakeUnloadTray()
{
	MANAGER->setOutputStatus(QStringLiteral("蜂鸣器"), 1);
	XMessageBox::show(QStringLiteral("下料模组已满，需要取走料盘，请处理！"));
	MANAGER->setOutputStatus(QStringLiteral("蜂鸣器"), 0);
}

void MainWidget::onLaserCalib()
{
	if (0 == XMessageBox::ask(QStringLiteral("将进行激光系统与视觉系统之间的标定，请确定是否继续？"))) return;

	if (SYSTEM_STANDBY == WORKFLOW_INSTANCE->getSysStatus())
	{
		WORKFLOW_INSTANCE->calibLaserAsyn();
	}
}

void MainWidget::onHintAddFeedTray()
{
	MANAGER->setOutputStatus(QStringLiteral("蜂鸣器"), 1);
	XMessageBox::show(QStringLiteral("上料模组已空，需要增加Tray盘，请处理！"));
	MANAGER->setOutputStatus(QStringLiteral("蜂鸣器"), 0);
}

void MainWidget::onUnloadTrayTaked()
{
	WORKFLOW_INSTANCE->unLoadTrayTaked();
}


