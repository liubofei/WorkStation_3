#pragma once

#include <QWidget>
#include "ui_MessageBox.h"
#include "../XWindow/XWindow.h"

class MessageBox : public XWindow
{
	Q_OBJECT

public:

	enum MESSAGEBOX_MODE
	{
		MESSAGEBOX_SHOW,
		MESSAGEBOX_WARN,
		MESSAGEBOX_ERROR,
		MESSAGEBOX_ASK
	};

	MessageBox(MESSAGEBOX_MODE mode, QString msg);
	~MessageBox();

private:
	Ui::MessageBox ui;

	void initWidget(MESSAGEBOX_MODE mode, QString msg);

	private slots:

	void onOKClicked();
	void onCancelClicked();
};
