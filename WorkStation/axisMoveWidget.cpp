#include "AxisMoveWidget.h"
#include "../WorkFlow/WorkFlow/WorkFlow.h"
#include "../Utility/System/Config.h"
#include "../Utility/Utility/Utility.h"
#include "../Utility/XMessageBox/XMessageBox.h"
#include "../Motion/Motion_dmc/CardInterfaceManager.h"


AxisMoveWidget::AxisMoveWidget(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);
	initData();
	initUI();
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	SetStyle(this, "Skin.qss");
	m_updatePosID = startTimer(150);
}

AxisMoveWidget::~AxisMoveWidget()
{
}

void AxisMoveWidget::onSpeedRadoiClicked()
{
	if (ui.radioButton_speed_low->isChecked())
		m_speedMode = 0;
	else if (ui.radioButton_speed_normal->isChecked())
		m_speedMode = 1;
	else if (ui.radioButton_speed_fast->isChecked())
		m_speedMode = 2;	
}

void AxisMoveWidget::onLaserXPClicked()
{
	axisMove("Laser_X", 1);
}

void AxisMoveWidget::onLaserXPReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Laser_X");
}

void AxisMoveWidget::onLaserXNClicked()
{
	axisMove("Laser_X", 0);
}

void AxisMoveWidget::onLaserXNReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Laser_X");
}

void AxisMoveWidget::onLaserYPClicked()
{
	axisMove("Laser_Y", 1);
}

void AxisMoveWidget::onLaserYPReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Laser_Y");
}


void AxisMoveWidget::onLaserYNClicked()
{
	axisMove("Laser_Y", 0);
}

void AxisMoveWidget::onLaserYNReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Laser_Y");
}


void AxisMoveWidget::onCarryXPClicked()
{
	axisMove("Carry_X", 1);
}


void AxisMoveWidget::onCarryXPReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Carry_X");
}

void AxisMoveWidget::onCarryXNClicked()
{
	axisMove("Carry_X", 0);
}

void AxisMoveWidget::onCarryXNReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Carry_X");
}

void AxisMoveWidget::onFeedZPClicked()
{
	axisMove("Feed_Z", 1);
}

void AxisMoveWidget::onFeedZPReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Feed_Z");
}

void AxisMoveWidget::onFeedZNClicked()
{
	axisMove("Feed_Z", 0);
}

void AxisMoveWidget::onFeedZNReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Feed_Z");
}

void AxisMoveWidget::onUnLoadZPClicked()
{
	axisMove("Unload_Z", 1);
}

void AxisMoveWidget::onUnLoadZPReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Unload_Z");
}

void AxisMoveWidget::onUnLoadZNClicked()
{
	axisMove("Unload_Z", 0);
}

void AxisMoveWidget::onUnLoadZNReleased()
{
	if (ui.checkBox_pmove->isChecked()) return;
	MANAGER->stopAxis("Unload_Z");
}

void AxisMoveWidget::initData()
{
	m_speedMode = 0;
	ui.comboBox_move_step->addItem("0.1");
	ui.comboBox_move_step->addItem("0.2");
	ui.comboBox_move_step->addItem("0.5");
	ui.comboBox_move_step->addItem("1");
	ui.comboBox_move_step->addItem("2");
	ui.comboBox_move_step->addItem("10");
	ui.comboBox_move_step->setCurrentIndex(0);
	ui.radioButton_speed_low->setChecked(true);
}

void AxisMoveWidget::initUI()
{
	connect(ui.pushButton_laserXP, &QPushButton::clicked, this, &AxisMoveWidget::onLaserXPClicked);
	connect(ui.pushButton_laserXP, &QPushButton::released, this, &AxisMoveWidget::onLaserXPReleased);
	connect(ui.pushButton_laserXN, &QPushButton::clicked, this, &AxisMoveWidget::onLaserXNClicked);
	connect(ui.pushButton_laserXN, &QPushButton::released, this, &AxisMoveWidget::onLaserYNReleased);
	connect(ui.pushButton_laserYP, &QPushButton::clicked, this, &AxisMoveWidget::onLaserYPClicked);
	connect(ui.pushButton_laserYP, &QPushButton::released, this, &AxisMoveWidget::onLaserYPReleased);
	connect(ui.pushButton_laserYN, &QPushButton::clicked, this, &AxisMoveWidget::onLaserYNClicked);
	connect(ui.pushButton_laserYN, &QPushButton::released, this, &AxisMoveWidget::onLaserYNReleased);

	connect(ui.pushButton_carryXP, &QPushButton::clicked, this, &AxisMoveWidget::onCarryXPClicked);
	connect(ui.pushButton_carryXP, &QPushButton::released, this, &AxisMoveWidget::onCarryXPReleased);
	connect(ui.pushButton_carryXN, &QPushButton::clicked, this, &AxisMoveWidget::onCarryXNClicked);
	connect(ui.pushButton_carryXN, &QPushButton::released, this, &AxisMoveWidget::onCarryXNReleased);

	connect(ui.pushButton_feedZP, &QPushButton::clicked, this, &AxisMoveWidget::onFeedZPClicked);
	connect(ui.pushButton_feedZP, &QPushButton::released, this, &AxisMoveWidget::onFeedZPReleased);
	connect(ui.pushButton_feedZN, &QPushButton::clicked, this, &AxisMoveWidget::onFeedZNClicked);
	connect(ui.pushButton_feedZN, &QPushButton::released, this, &AxisMoveWidget::onFeedZNReleased);

	connect(ui.pushButton_unloadZP, &QPushButton::clicked, this, &AxisMoveWidget::onUnLoadZPClicked);
	connect(ui.pushButton_unloadZP, &QPushButton::released, this, &AxisMoveWidget::onUnLoadZPReleased);
	connect(ui.pushButton_unloadZN, &QPushButton::clicked, this, &AxisMoveWidget::onUnLoadZNClicked);
	connect(ui.pushButton_unloadZN, &QPushButton::released, this, &AxisMoveWidget::onUnLoadZNReleased);
}

void AxisMoveWidget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_updatePosID)
	{
		if (isVisible())
		{
			updateAxisPos();
		}	
	}
}

void AxisMoveWidget::updateAxisPos()
{
	//int station = m_trail->getCurStation();
	//QString xName, yName, zName, uName, vName;
	//SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
	//axisAllocation axisAlloc = CONFIG_INSTANCE->getAxisAlloc(sysInfo.workMode == 3 ? m_trail->m_frontBack : sysInfo.workMode);

	//xName = 0 == station ? axisAlloc.axisName_L[0] : axisAlloc.axisName_R[0];
	//yName = 0 == station ? axisAlloc.axisName_L[1] : axisAlloc.axisName_R[1];
	//zName = 0 == station ? axisAlloc.axisName_L[2] : axisAlloc.axisName_R[2];
	//uName = 0 == station ? axisAlloc.axisName_L[3] : axisAlloc.axisName_R[3];
	//vName = 0 == station ? "V0" : "V1";

	//double	pos[5] = { 0, 0, 0, 0, 0 };
	//pos[0] = MANAGER->getAxisPos(xName);
	//pos[1] = MANAGER->getAxisPos(yName);
	//pos[2] = MANAGER->getAxisPos(zName);
	//pos[3] = MANAGER->getAxisPos(uName);
	//pos[4] = MANAGER->getAxisPos(vName);

	//ui.label_x->setText("X:"+QString::number(pos[0], 10, 3));
	//ui.label_y->setText("Y:"+QString::number(pos[1], 10, 3));
	//ui.label_z->setText("Z:"+QString::number(pos[2], 10, 3));
	//ui.label_u->setText("U:"+QString::number(pos[3], 10, 3));
	//ui.label_v->setText("V:"+QString::number(pos[4], 10, 3));
}
	
void AxisMoveWidget::axisMove(const QString& axisName, int dir)
{
	double speed = CONFIG_INSTANCE->getSysInfo().manualSpeed[m_speedMode];
	if (ui.checkBox_pmove->isChecked())
	{
		double offset = ui.comboBox_move_step->currentText().toDouble();
		if (dir == 0) 
			offset = -offset;
		MANAGER->axisMoveOffset(axisName, offset, speed);
	}
	else
	{
		MANAGER->axisJogMove(axisName, dir, speed);
	}
}

