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
	void onCurItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous); //���α�ѡ��ʱ�򴥷�
	void onCustomContextMenuRequested(const QPoint& point);	//����һ�����
	void onTreeCardRMenuClicked();		//�����Ŀ��˵���ѡ��
	void onTreeAxisRMenuClicked();		//��������˵���ѡ��
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
	int						m_curCardIndex;	//��ǰѡ�еĿ����
	int						m_curAxisIndex;	//��ǰѡ�е������	
	int						m_copyAxisIndex; //�����ƵĿ����
	int						m_copyCardIndex; //�����Ƶ������
	QAction*				deleteCard;
	QAction*				addCard;
	QAction*				addAxis;
	QAction*				editPara;
	QAction*				coypPara;
	QAction*				pastePara;
	QAction*				deleteAxis;
	QVector<CardInfo>	m_vecCardInfo;
};
