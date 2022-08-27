#include "ModuleDebug.h"
#include "../../Utility/System/Config.h"
#include "../../WorkFlow/WorkFlow/WorkFlow.h"
#include "../../Utility/XMessageBox/XMessageBox.h"

ModuleDebug::ModuleDebug(QDialog *parent)
	: XWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton_feed_reset, &QPushButton::clicked, this, &ModuleDebug::onFeedReset);
	connect(ui.pushButton_feed_start, &QPushButton::clicked, this, &ModuleDebug::onFeedStart);
	connect(ui.pushButton_carry_reset, &QPushButton::clicked, this, &ModuleDebug::onCarryReset);
	connect(ui.pushButton_carry_start, &QPushButton::clicked, this, &ModuleDebug::onCarryStart);
	connect(ui.pushButton_scan_reset, &QPushButton::clicked, this, &ModuleDebug::onScanReset);
	connect(ui.pushButton_scan_start, &QPushButton::clicked, this, &ModuleDebug::onScanStart);
	connect(ui.pushButton_sort_reset, &QPushButton::clicked, this, &ModuleDebug::onSortReset);
	connect(ui.pushButton_sort_start, &QPushButton::clicked, this, &ModuleDebug::onSortStart);
	connect(ui.pushButton_unload_reset, &QPushButton::clicked, this, &ModuleDebug::onUnloadReset);
	connect(ui.pushButton_unload_start, &QPushButton::clicked, this, &ModuleDebug::onUnloadStart);
}

ModuleDebug::~ModuleDebug()
{
}

void ModuleDebug::onFeedReset()
{
	WORKFLOW_INSTANCE->testFun("Feed_home");
}

void ModuleDebug::onFeedStart()
{
	WORKFLOW_INSTANCE->testFun("Feed_start");
}

void ModuleDebug::onCarryReset()
{
	WORKFLOW_INSTANCE->testFun("Carry_home");
}

void ModuleDebug::onCarryStart()
{
	WORKFLOW_INSTANCE->testFun("Carry_start");
}

void ModuleDebug::onScanReset()
{
	WORKFLOW_INSTANCE->testFun("Scan_home");
}

void ModuleDebug::onScanStart()
{
	WORKFLOW_INSTANCE->testFun("Scan_start");
}

void ModuleDebug::onSortReset()
{
	WORKFLOW_INSTANCE->testFun("Sort_home");
}

void ModuleDebug::onSortStart()
{
	WORKFLOW_INSTANCE->testFun("Sort_start");
}

void ModuleDebug::onUnloadReset()
{
	WORKFLOW_INSTANCE->testFun("UnLoad_home");
}

void ModuleDebug::onUnloadStart()
{
	WORKFLOW_INSTANCE->testFun("UnLoad_start");
}

