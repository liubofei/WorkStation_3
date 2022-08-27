#pragma once

#include "xmessagebox_global.h"
#include <QtWidgets/QWidget>

class XMESSAGEBOX_EXPORT XMessageBox
{
public:
	static int show(const QString & msg);
	static int warn(const QString & msg);
	static int error(const QString & msg);
	static int ask(const QString & msg);

private:
	explicit XMessageBox(){};

};
