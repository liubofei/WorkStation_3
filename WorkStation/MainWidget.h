#pragma once
#include <QWidget>
#include "ui_MainWidget.h"
#include "../include/Common.h"

class TrimArray;

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = Q_NULLPTR);
	~MainWidget();

	void clearLog();
	void printLog(QString msg);

public slots :
	void onPrintLog(QString msg);
	void onSetUISysStatus(SYSTEM_STATUS status);
	void onSysCtrlReset();
	void onSysCtrlStart();
	void onSysCtrlStop();
	void onSysCtrlConti();
	void onUserModeChanged(USERMODE mode);
	void onTextEidtLogMenu();
	void onTextEditMenuRequested(const QPoint& pos);
	void onAppInit();
	void onExitApp();

	void onUnloadTrayTaked();

	void onHintAddFeedTray();  	//上料模组请求添加料盘
	void onHintTakeUnloadTray();	//提示取走下料仓料盘
	void onLaserCalib();

signals:
	void showMessage(QString msg);

private:
	void initData();
	void initUI();
	void timerEvent(QTimerEvent *event);
	void changeEvent(QEvent* event);

private:
	Ui::MainWidget	ui;
	USERMODE		m_userMode;
	TrimArray*      m_laserArryWidget;
	int				m_updateTimerID;
};
