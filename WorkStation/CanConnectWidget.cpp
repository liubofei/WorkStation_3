#include "CanConnectWidget.h"
#include "../../Utility/System/Config.h"
#include "../../Utility/XMessageBox/XMessageBox.h"
#include "../include/LTDMC.h"

CanConnectWidget::CanConnectWidget(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);
	initData();
	initUI();	
}

CanConnectWidget::~CanConnectWidget()
{
}

void CanConnectWidget::initUI()
{
	ui.comboBox_CANState->addItem(QStringLiteral("断开"));
	ui.comboBox_CANState->addItem(QStringLiteral("连接"));
	ui.comboBox_CANBaud->addItem("1000Kbps");
	ui.comboBox_CANBaud->addItem("800Kbps");
	ui.comboBox_CANBaud->addItem("500Kbps");
	ui.comboBox_CANBaud->addItem("250Kbps");
	ui.comboBox_CANBaud->addItem("125Kbps");
	ui.comboBox_CANBaud->addItem("100Kbps");

	ui.spinBox_CANCardNo->setValue(0);
	ui.comboBox_CANBaud->setCurrentIndex(0);
	ui.comboBox_CANState->setCurrentIndex(1);

	unsigned short status = 2;
	unsigned short nodeNum = 0;
	nmc_get_connect_state(0, &nodeNum, &status);
	setStatusUI(status);
	ui.spinBox_CANNodeNum->setValue(nodeNum);

	connect(ui.pushButton_CAN_OK, &QPushButton::clicked, this, &CanConnectWidget::onSave);
	connect(ui.pushButton_CAN_Cancel, &QPushButton::clicked, this, &CanConnectWidget::onCancel);
}

void CanConnectWidget::initData()
{
	m_mapCANState[0] = QStringLiteral("断开");
	m_mapCANState[1] = QStringLiteral("连接");
	m_mapCANBaud[0] = QStringLiteral("1000Kbps");
	m_mapCANBaud[1] = QStringLiteral("800Kbps");
	m_mapCANBaud[2] = QStringLiteral("500Kbps");
	m_mapCANBaud[3] = QStringLiteral("250Kbps");
	m_mapCANBaud[4] = QStringLiteral("125Kbps");
	m_mapCANBaud[5] = QStringLiteral("100Kbps");
}

void CanConnectWidget::onSave()
{
	unsigned short cardNo = ui.spinBox_CANCardNo->value();
	unsigned short nodeId = ui.spinBox_CANNodeNum->value();
	unsigned short baud = ui.comboBox_CANBaud->currentIndex();	
	unsigned short operation = ui.comboBox_CANState->currentIndex();
	unsigned short status = 2;

	int rtn = nmc_set_connect_state(cardNo, nodeId, operation, baud);
	if (0 == rtn)
	{
		nmc_get_connect_state(cardNo, &nodeId, &status);
		showConnectResults(status);
	}
	else
	{
		setStatusUI(status);
		XMessageBox::error(QStringLiteral("错误代码: %1\n控制卡卡号: %2\nCAN节点: %3\n通讯状态: %4\n波特率: %5").arg(rtn).arg(cardNo).arg(nodeId).arg(m_mapCANState[operation]).arg(m_mapCANBaud[baud]));
	}
}

void CanConnectWidget::onCancel()
{
	close();
}

void CanConnectWidget::setStatusUI(unsigned short status)
{
	if (0 == status)
	{
		ui.lineEdit_CANState->setStyleSheet("color:rgb(255,128,0)");
		ui.lineEdit_CANState->setText(QStringLiteral("断开"));
	}
	else if (1 == status)
	{
		ui.lineEdit_CANState->setStyleSheet("color:rgb(0,255,0)");
		ui.lineEdit_CANState->setText(QStringLiteral("连接"));
	}
	else
	{
		ui.lineEdit_CANState->setStyleSheet("color:rgb(255,0,0)");
		ui.lineEdit_CANState->setText(QStringLiteral("异常"));
	}
}

void CanConnectWidget::showConnectResults(unsigned short status)
{
	if (0 == status)
	{
		setStatusUI(status);
		XMessageBox::show(QStringLiteral("扩展卡已断开！"));
	}
	else if (1 == status)
	{
		setStatusUI(status);
		//XMessageBox::show(QStringLiteral("扩展卡已连接！"));
	}
	else
	{
		setStatusUI(status);
		XMessageBox::error(QStringLiteral("扩展卡异常，请检查小电！"));
	}
}