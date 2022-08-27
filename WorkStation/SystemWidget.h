#pragma once

#include <QWidget>
#include "ui_SystemWidget.h"

class SystemWidget : public QWidget
{
	Q_OBJECT

public:
	SystemWidget(QWidget *parent = Q_NULLPTR);
	~SystemWidget();

protected slots:
	void onEdit();
	void onSave();
	void onCancel();
	void onOpenLight();
	void onCloseLight();
	void onReload();
	void onMaintain();

	//��ǰ���������ı䣬UI����
	void onUpdateUI();
protected:
	void changeEvent(QEvent* event);
	void init();
	void enableAllCtrls(bool enable = true);
	void sysInfo2Widget();
	void widget2SysInfo();

private:
	Ui::SystemWidget ui;
};
