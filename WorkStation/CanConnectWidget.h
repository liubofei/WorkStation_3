#pragma once
#include <QWidget>
#include "../Utility/XWindow/XWindow.h"
#include "ui_CanConnectWidget.h"
#include "../../include/Common.h"

class CanConnectWidget : public QWidget
{
	Q_OBJECT

public:
	CanConnectWidget(QWidget *parent = Q_NULLPTR);
	~CanConnectWidget();

private slots :
	void onSave();
	void onCancel();

private:
	void initUI();
	void initData();

	void setStatusUI(unsigned short status);
	void showConnectResults(unsigned short status);

private:
	Ui::CanConnectWidget	ui;
	std::map<int, QString>	m_mapCANState;
	std::map<int, QString>	m_mapCANBaud;
};
