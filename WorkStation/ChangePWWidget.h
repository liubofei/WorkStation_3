#pragma once

#include <QWidget>
#include "ui_ChangePWWidget.h"
#include "../../Utility/XWindow/XWindow.h"
#include "../../include/Common.h"

class ChangePWWidget : public XWindow
{
	Q_OBJECT

public:
	ChangePWWidget(QWidget *parent = Q_NULLPTR);
	~ChangePWWidget();
	protected slots:
	void onchangePW();

private:
	Ui::ChangePWWidget ui;
	QString PW;
	SystemInfo							m_sysInfo;

	void init();
};
