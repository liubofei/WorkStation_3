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
	void updateWidgetSize();			//���´��ڴ�С
	void updateIOButton();				//���°�ť
	void initConfigWidget();			//��ʼ��IO����ҳ��	
	void updateIOStatus();				//����IO���ҳ���IO״̬
	void updateConfigInfo();			//��������ҳ����Ϣ����ѡ��ѡ�����л�
	void addIOInfo();					//����ҳ�����IO����
	void deleteIOInfo();				//����ҳ��ɾ��IO����
	void IOInfo2Widget(IOInfo &info);	//IO������ʾ��ҳ��
	void Widget2IOInfo(IOInfo &info);	//ҳ����Ϣ���浽IO������
	void enableCtrls(bool enable);		//����ҳ�����ʹ��

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
