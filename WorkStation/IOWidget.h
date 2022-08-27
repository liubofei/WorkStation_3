#pragma once

#include <QWidget>
#include <QToolButton>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "ui_IOWidget.h"
#include "../include/Motion.h"

struct BtnData : QObjectUserData {
	int nID;

	BtnData(int _nID)
		:nID(_nID)
	{
	}
};

class IOWidget : public QWidget
{
	Q_OBJECT

public:
	IOWidget(QWidget *parent = Q_NULLPTR);
	~IOWidget();

public slots:
	void onCustomContextMenuRequested(const QPoint& pos);
	void onMenuClicked();
	void onListItemCliecked();
	void onBtnCancelClicked();
	void onBtnSaveClicked();
	void onOutBtnClicked();

protected:
	void timerEvent(QTimerEvent *event);
	void changeEvent(QEvent* event);
	void updateWidgetSize();			//更新窗口大小
	void updateIOButton();				//更新按钮
	void initConfigWidget();			//初始化IO配置页面	
	void updateIOStatus();				//更新IO监控页面的IO状态
	void updateConfigInfo();			//更新配置页面信息，复选框选中是切换
	void addIOInfo();					//配置页面添加IO配置
	void deleteIOInfo();				//配置页面删除IO配置
	void IOInfo2Widget(IOInfo &info);	//IO配置显示到页面
	void Widget2IOInfo(IOInfo &info);	//页面信息保存到IO配置中
	void enableCtrls(bool enable);		//配置页面控制使能

private:
	Ui::IOWidget ui;
	int                         m_timerID;
	bool		                m_bNewInfo;
	int							m_leftSpace;
	int							m_RightSpace;
	int							m_TopSpace;
	int							m_BottomSpace;
	int							m_ColumnSpace;
	int							m_RowSpace;
	int							m_BtnWidth;
	int							m_BtnHeight;
	QVector<IOInfo>			m_vecInputInfo;
	QVector<IOInfo>			m_vecOutputInfo;
	QMap<int, int>			m_mapInputGroup;
	QMap<int, int>			m_mapOutputGroup;
	QVector<QToolButton*>   m_vecInputBtn;
	QVector<QPushButton*>   m_vecOutputBtn;
};
