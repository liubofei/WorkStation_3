#pragma once

#include <QWidget>
#include "ui_LoginWidget.h"
#include "../../Utility/XWindow/XWindow.h"


class LoginWidget : public XWindow
{
	Q_OBJECT

public:
	LoginWidget();
	~LoginWidget();

public slots:
	void login();
	void onChangePW();

private:
	Ui::LoginWidget ui;	
};
