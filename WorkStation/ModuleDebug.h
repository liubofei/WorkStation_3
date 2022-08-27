#pragma once

#include "../Utility/XWindow/XWindow.h"
#include "ui_ModuleDebug.h"
#include "../../include/Common.h"

class ModuleDebug : public XWindow
{
	Q_OBJECT

public:
	ModuleDebug(QDialog *parent = Q_NULLPTR);
	~ModuleDebug();

public slots:
	void onFeedReset();
	void onFeedStart();
	void onCarryReset();
	void onCarryStart();
	void onScanReset();
	void onScanStart();
	void onSortReset();
	void onSortStart();
	void onUnloadReset();
	void onUnloadStart();

private:
	Ui::ModuleDebug ui;

};
