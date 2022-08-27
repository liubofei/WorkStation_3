#pragma once
#include <QWidget>
#include "ui_AxisMoveWidget.h"


class AxisMoveWidget : public QWidget
{
	Q_OBJECT

public:
	AxisMoveWidget(QWidget *parent = nullptr);
	~AxisMoveWidget();

public slots:
	void onSpeedRadoiClicked();

	void onLaserXPClicked();
	void onLaserXPReleased();

	void onLaserXNClicked();
	void onLaserXNReleased();

	void onLaserYPClicked();
	void onLaserYPReleased();

	void onLaserYNClicked();
	void onLaserYNReleased();


	void onCarryXPClicked();
	void onCarryXPReleased();

	void onCarryXNClicked();
	void onCarryXNReleased();

	void onFeedZPClicked();
	void onFeedZPReleased();

	void onFeedZNClicked();
	void onFeedZNReleased();

	void onUnLoadZPClicked();
	void onUnLoadZPReleased();

	void onUnLoadZNClicked();
	void onUnLoadZNReleased();


private:
	void initData();
	void initUI();
	void timerEvent(QTimerEvent *event);
	void updateAxisPos();
	void axisMove(const QString& axisName, int dir);

private:
	Ui::AxisMoveWidget ui;
	int m_speedMode;
	int	m_updatePosID;
};
