#pragma once

#include <QWidget>
#include <QMenu>
#include <QTreeWidgetItem>
#include "ui_MotorWidget.h"
#include "../../include/Common.h"
#include "../../include/Motion.h"

class MotorWidget : public QWidget
{
	Q_OBJECT

public:
	MotorWidget(QWidget *parent = Q_NULLPTR);
	~MotorWidget();

public slots:
	void onCurItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous); //树形被选中时候触发
	void onCustomContextMenuRequested(const QPoint& point);	//鼠标右击触发
	void onTreeCardRMenuClicked();		//弹出的卡菜单被选中
	void onTreeAxisRMenuClicked();		//弹出的轴菜单被选中
	void onHomeBtnClicked();
	void onMoveBtnPressed();
	void onMoveBtnRelease();
	void onMoveBtnClicked();
	void onStopBtnClicked();
	void onCheckEnableClicked();
	void onCancel();
	void onSave();		
	void onEdit();

protected:
	void timerEvent(QTimerEvent *event);
	void changeEvent(QEvent* event);
	void init();
	void initControl();
	void initTreeCtrl();
	void initRMenu();
	void nameAction();
	void updateTreeCtrl();
	void updateAxisStatus();
	void cardInfo2Widget(int card, int axis);
	void widget2CardInfo(int card, int axis);
	void enableCtrls(bool enable);
	QAction* getMenuBarAction(QMenu*menu, QString name);


private:
	Ui::MotorWidget ui;
	int						m_timerID; 
	QMenu*					m_menuAxis;
	QMenu*					m_menuCard;
	int						m_curCardIndex;	//当前选中的卡序号
	int						m_curAxisIndex;	//当前选中的轴序号	
	int						m_copyAxisIndex; //被复制的卡序号
	int						m_copyCardIndex; //被复制的轴序号
	QAction*				deleteCard;
	QAction*				addCard;
	QAction*				addAxis;
	QAction*				editPara;
	QAction*				coypPara;
	QAction*				pastePara;
	QAction*				deleteAxis;
	QVector<CardInfo>	m_vecCardInfo;
};
