#include "SystemWidget.h"
#include "../../Utility/System/Config.h"
#include "../../include/Common.h"
#include "../../Utility/XMessageBox/XMessageBox.h"
#include "../../Utility/SerialPort/SerialPort.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"

SystemWidget::SystemWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

SystemWidget::~SystemWidget()
{
}

void SystemWidget::init()
{
	ui.comboBox_laser_version->addItem("0");
	ui.comboBox_laser_version->addItem("1");
	ui.comboBox_laser_version->addItem("2");
	ui.comboBox_vision_version->addItem("0");
	ui.comboBox_vision_version->addItem("1");
	ui.comboBox_vision_version->addItem("2");



	sysInfo2Widget();
	ui.pushButton_edit->setVisible(true);
	ui.pushButton_save->setVisible(false);
	ui.pushButton_cancel->setVisible(false);
	enableAllCtrls(false);
}

void SystemWidget::sysInfo2Widget()
{
	const SystemInfo info = CONFIG_INSTANCE->getSysInfo();
	ui.checkBox_safeBar->setChecked(info.enableSafeBar);
	ui.checkBox_safeDoor->setChecked(info.enableSafeDoor);
	ui.checkBox_visionProtect->setChecked(info.enableVisionProtect);
	ui.checkBox_wipeNozzleModule->setChecked(info.enableWipeNozzle);
	ui.checkBox_XYAngleAffine->setChecked(info.XYAngleAffine);
	ui.checkBox_enbleBuzzing->setChecked(info.enableBuzzer);
	ui.checkBox_showTrack->setChecked(info.enableShowTrack);
	ui.checkBox_dryrun->setChecked(info.enableDryRun);
	ui.checkBox_enableMakeBar->setChecked(info.enableLaser);
	ui.checkBox_enableV0Command->setChecked(info.enableV0Command);
	ui.checkBox_enableRCommand->setChecked(info.enableRCommand);

	ui.lineEdit_lowSpeed->setText(QString::number(info.manualSpeed[0]));
	ui.lineEdit_midSpeed->setText(QString::number(info.manualSpeed[1]));
	ui.lineEdit_hightSpeed->setText(QString::number(info.manualSpeed[2]));
	ui.lineEdit_saveZ->setText(QString::number(info.safeHeightZ));
	ui.lineEdit_feed_max_tray_num->setText(QString::number(info.feed_max_tray_num));
	ui.lineEdit_feed_z_offset->setText(QString::number(info.feed_z_offset));
	ui.lineEdit_tray_row_space->setText(QString::number(info.tray_row_space));
	ui.lineEdit_tray_col_space->setText(QString::number(info.tray_col_space));
	ui.lineEdit_tray_row_num->setText(QString::number(info.tray_row_num));
	ui.lineEdit_tray_col_num->setText(QString::number(info.tray_col_num));
	ui.comboBox_laser_version->setCurrentIndex(info.laserVersion);
	ui.comboBox_vision_version->setCurrentIndex(info.visionVersion);
}

void SystemWidget::widget2SysInfo()
{
	SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
	sysInfo.manualSpeed[0] = ui.lineEdit_lowSpeed->text().toDouble();
	sysInfo.manualSpeed[1] = ui.lineEdit_midSpeed->text().toDouble();
	sysInfo.manualSpeed[2] = ui.lineEdit_hightSpeed->text().toDouble();
	sysInfo.safeHeightZ = ui.lineEdit_saveZ->text().toDouble();
	sysInfo.enableSafeBar = ui.checkBox_safeBar->isChecked();
	sysInfo.enableSafeDoor = ui.checkBox_safeDoor->isChecked();
	sysInfo.enableVisionProtect = ui.checkBox_visionProtect->isChecked();
	sysInfo.enableWipeNozzle = ui.checkBox_wipeNozzleModule->isChecked();
	sysInfo.enableShowTrack = ui.checkBox_showTrack->isChecked();
	sysInfo.XYAngleAffine = ui.checkBox_XYAngleAffine->isChecked();
	sysInfo.enableDryRun = ui.checkBox_dryrun->isChecked();
	sysInfo.enableLaser = ui.checkBox_enableMakeBar->isChecked();
	sysInfo.enableV0Command = ui.checkBox_enableV0Command->isChecked();
	sysInfo.enableRCommand = ui.checkBox_enableRCommand->isChecked();
	sysInfo.enableBuzzer = ui.checkBox_enbleBuzzing->isChecked();
	sysInfo.feed_max_tray_num = ui.lineEdit_feed_max_tray_num->text().toInt();
	sysInfo.feed_z_offset = ui.lineEdit_feed_z_offset->text().toDouble();
	sysInfo.tray_row_space = ui.lineEdit_tray_row_space->text().toDouble();
	sysInfo.tray_col_space = ui.lineEdit_tray_col_space->text().toDouble();
	sysInfo.tray_row_num = ui.lineEdit_tray_row_num->text().toInt();
	sysInfo.tray_col_num = ui.lineEdit_tray_col_num->text().toInt();
	sysInfo.laserVersion = ui.comboBox_laser_version->currentIndex();
	sysInfo.visionVersion = ui.comboBox_vision_version->currentIndex();
	CONFIG_INSTANCE->setSysInfo(sysInfo);
}

void SystemWidget::onEdit()
{
	ui.pushButton_edit->setVisible(false);
	ui.pushButton_save->setVisible(true);
	ui.pushButton_cancel->setVisible(true);
	enableAllCtrls(true);
}

void SystemWidget::onSave()
{
	widget2SysInfo();
	ui.pushButton_edit->setVisible(true);
	ui.pushButton_save->setVisible(false);
	ui.pushButton_cancel->setVisible(false);
	enableAllCtrls(false);
}

void SystemWidget::onCancel()
{
	sysInfo2Widget();
	ui.pushButton_edit->setVisible(true);
	ui.pushButton_save->setVisible(false);
	ui.pushButton_cancel->setVisible(false);
	enableAllCtrls(false);
}

void SystemWidget::onOpenLight()
{
	
	
}

void SystemWidget::onCloseLight()
{
}

void SystemWidget::onReload()
{
	CONFIG_INSTANCE->loadSysInfo();
	sysInfo2Widget();
}

void SystemWidget::onMaintain()
{
	SystemInfo sys = CONFIG_INSTANCE->getSysInfo();
	QDateTime curTime = QDateTime::currentDateTime();
	QString strTime = curTime.toString("yyyyMMdd");
	sys.lastMaintainDate = strTime;
	CONFIG_INSTANCE->setSysInfo(sys);
	sysInfo2Widget();
}

void SystemWidget::onUpdateUI()
{
	sysInfo2Widget();
}


void SystemWidget::changeEvent(QEvent* event)
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

void SystemWidget::enableAllCtrls(bool enable)
{

	ui.lineEdit_lowSpeed->setEnabled(enable);
	ui.lineEdit_midSpeed->setEnabled(enable);
	ui.lineEdit_hightSpeed->setEnabled(enable);
	ui.lineEdit_saveZ->setEnabled(enable);
	ui.checkBox_safeBar->setEnabled(enable);
	ui.checkBox_safeDoor->setEnabled(enable);
	ui.checkBox_visionProtect->setEnabled(enable);
	ui.checkBox_wipeNozzleModule->setEnabled(enable);
	ui.checkBox_XYAngleAffine->setEnabled(enable);
	ui.checkBox_showTrack->setEnabled(enable);
	ui.checkBox_enbleBuzzing->setEnabled(enable);
	ui.lineEdit_feed_max_tray_num->setEnabled(enable);
	ui.lineEdit_feed_z_offset->setEnabled(enable);
	ui.checkBox_dryrun->setEnabled(enable);
	ui.checkBox_enableMakeBar->setEnabled(enable);
	ui.checkBox_enableV0Command->setEnabled(enable);
	ui.checkBox_enableRCommand->setEnabled(enable);
	ui.lineEdit_tray_row_space->setEnabled(enable);
	ui.lineEdit_tray_col_space->setEnabled(enable);
	ui.lineEdit_tray_row_num->setEnabled(enable);
	ui.lineEdit_tray_col_num->setEnabled(enable);
	ui.comboBox_laser_version->setEnabled(enable);
	ui.comboBox_vision_version->setEnabled(enable);
}