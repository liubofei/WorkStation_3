#pragma once

#include <QWidget>
#include <QKeyEvent>
#include "ui_ParamWidget.h"
#include "../../Utility/XWindow/XWindow.h"
#include "SystemWidget.h"
#include "MotorWidget.h"
#include "IOWidget.h"
#include "PointsWidget.h"
#include "CommuniWidget.h"

class ParamWidget : public XWindow
{
	Q_OBJECT

public:
	ParamWidget();
	~ParamWidget();

	void setCurTab(int index);
	void setUserConfig(USERMODE userMode);
	void onSysChanged(SYSTEM_STATUS status);
	void onExitApp();

protected:
	void keyPressEvent(QKeyEvent *e);
	void changeEvent(QEvent* event);
	void init();
	void initTable();

private:
	Ui::ParamWidget ui;

	SystemWidget*		m_systemWidget;
	MotorWidget*		m_motorWidget;
	IOWidget*		    m_IOConfigWidget;
	PointsWidget*		m_pointsWidget;
	CommuniWidget*	    m_communiWidget;
};
