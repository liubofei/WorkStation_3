#pragma once

#include <QWidget>
#include "ui_PointsWidget.h"
#include "../../include/Common.h"
#include "../../include/Motion.h"

class QStandardItemModel;
class QStandardItem;

class PointsWidget : public QWidget
{
	Q_OBJECT

public:
	PointsWidget(QWidget *parent = Q_NULLPTR);
	~PointsWidget();

protected slots:
	void onGoto();
	void onGetPos();
	void onSave();
	void onReLoad();
	void onCancel();
	void onItemChanged(QStandardItem *item);

protected:
	void changeEvent(QEvent* event);
	void initData();
	void iniUI();
	void pointInfo2Widget(const QVector<RunPoint> &vpt);

private:
	Ui::PointsWidget ui;
	bool				m_bEditing;
	QVector<RunPoint>	m_vRunPoint;
	QVector<RunPoint>	m_vTemp;
	QStandardItemModel* m_tableModel;
};
