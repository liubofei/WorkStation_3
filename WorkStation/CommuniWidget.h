#pragma once

#include <QWidget>
#include "ui_CommuniWidget.h"
#include "../../include/Common.h"

class CommuniWidget : public QWidget
{
	Q_OBJECT

public:
	CommuniWidget(QWidget *parent = Q_NULLPTR);
	~CommuniWidget();

protected slots:
	void onComBtnClicked();
	void onTcpBtnClicked();
	void onRClickedTcp(const QPoint& pos);
	void onRClickedCom(const QPoint& pos);
	void onRecvTcpMessage(QString name, QString msg);
	void onTcpConnect();
	void onTcpDisconnect();
	void onComConnect();
	void onComDisconnect();

protected:
	void changeEvent(QEvent* event);
	void timerEvent(QTimerEvent *event);
	void initData();
	void initTcpWidget();
	void initComWidget();
	void tcpInfo2Widget();
	void comInfo2Widget();
	void save_tcp();
	void cancel_tcp();
	void save_com();
	void cancel_com();
	
private:
	Ui::CommuniWidget		ui;
	QVector<TcpInfo>		m_vecTcpInfo;
	QVector<SeriaPortInfo>	m_vecSerPortInfo;

	QStringList			m_strListComnum;
	QStringList			m_strListBaudrate;
	QStringList			m_strListParity;
	QStringList			m_strListDatabit;
	QStringList			m_strListstopbit;
	int                 m_comStatusId;
};
