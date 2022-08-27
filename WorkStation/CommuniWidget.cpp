#include "CommuniWidget.h"
#include <QComboBox>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QPushButton>
#include "../../Utility/System/Config.h"
#include "../../Utility/SerialPort/SerialPort.h"
#include "../../Utility/NetWork/NetWork.h"
#include "../../Utility/XMessageBox/XMessageBox.h"
#include <QMenu>

CommuniWidget::CommuniWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initData();
	initTcpWidget();
	initComWidget();
	tcpInfo2Widget();
	comInfo2Widget();

	ui.tabWidget->setCurrentIndex(0);
	connect(NETWORK_INSTANCE.data(), &NetWork::recvTcpMessage, this, &CommuniWidget::onRecvTcpMessage);
	m_comStatusId = startTimer(1000);
}

CommuniWidget::~CommuniWidget()
{
}

void	CommuniWidget::initData()
{
	m_strListComnum   << "COM1" << "COM2" << "COM3" << "COM4" << "COM5" << "COM6" << "COM7"<< "COM8";
	m_strListBaudrate <<"1200" <<"2400"<<"4800"<<"9600"<<"19200"<<"38400"<<"57600"<<"115200";
	m_strListParity << QStringLiteral("无") << QStringLiteral("偶") << QStringLiteral("奇");
	m_strListDatabit << "5" << "6" << "7"<<"8";
	m_strListstopbit << "1" << "1.5" << "2" ;

	CONFIG_INSTANCE->getTcpInfo(m_vecTcpInfo);
	CONFIG_INSTANCE->getSerPortInfo(m_vecSerPortInfo);
}

void	CommuniWidget::initTcpWidget()
{
	QStringList header;
	header.append(QStringLiteral("名称"));
	header.append(QStringLiteral("描述"));
	header.append(QStringLiteral("地址"));
	header.append(QStringLiteral("端口"));
	header.append(QStringLiteral("类型"));

	ui.tableWidget_tcp->setColumnCount(header.size());
	ui.tableWidget_tcp->setColumnWidth(0, 100);
	ui.tableWidget_tcp->setColumnWidth(1, 100);
	ui.tableWidget_tcp->setColumnWidth(2, 80);
	ui.tableWidget_tcp->setColumnWidth(3, 80);
	ui.tableWidget_tcp->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
	ui.tableWidget_tcp->setHorizontalHeaderLabels(header);

	ui.tableWidget_tcp->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行  
	ui.tableWidget_tcp->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中  
	ui.tableWidget_tcp->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改  
	ui.tableWidget_tcp->setAlternatingRowColors(true);

	ui.pushButton_cancel_com->setVisible(false);
	ui.pushButton_save_com->setVisible(false);

	ui.pushButton_cancel_tcp->setVisible(false);
	ui.pushButton_save_tcp->setVisible(false);

	ui.tableWidget_tcp->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.tableWidget_tcp, &QTableWidget::customContextMenuRequested, this, &CommuniWidget::onRClickedTcp);

}

void    CommuniWidget::tcpInfo2Widget()
{
	for (int i = 0; i < m_vecTcpInfo.size(); i++)
	{
		ui.tableWidget_tcp->insertRow(i);

		QTableWidgetItem*	item_0 = new QTableWidgetItem();
		ui.tableWidget_tcp->setItem(i, 0, item_0);
		QTableWidgetItem*	item_1 = new QTableWidgetItem();
		ui.tableWidget_tcp->setItem(i, 1, item_1);
		QTableWidgetItem*	item_2 = new QTableWidgetItem();
		ui.tableWidget_tcp->setItem(i, 2, item_2);
		QTableWidgetItem*	item_3 = new QTableWidgetItem();
		ui.tableWidget_tcp->setItem(i, 3, item_3);
		QComboBox*			item_4 = new QComboBox(ui.tableWidget_tcp); 
		ui.tableWidget_tcp->setCellWidget(i, 4, (QWidget*)item_4);

		item_4->addItem(QStringLiteral("服务端"));
		item_4->addItem(QStringLiteral("客户端"));

		ui.tableWidget_tcp->item(i, 0)->setText(m_vecTcpInfo[i].name);
		ui.tableWidget_tcp->item(i, 1)->setText(m_vecTcpInfo[i].desc);
		ui.tableWidget_tcp->item(i, 2)->setText(m_vecTcpInfo[i].ip);
		ui.tableWidget_tcp->item(i, 3)->setText(QString::number(m_vecTcpInfo[i].port));

		item_4->setCurrentIndex(m_vecTcpInfo[i].type);
	}
}

void	CommuniWidget::initComWidget()
{
	QStringList header;
	header.append(QStringLiteral("名称"));
	header.append(QStringLiteral("描述"));
	header.append(QStringLiteral("串口号"));
	header.append(QStringLiteral("波特率"));
	header.append(QStringLiteral("校验"));
	header.append(QStringLiteral("数据位"));
	header.append(QStringLiteral("停止位"));
	header.append(QStringLiteral("状态"));

	ui.tableWidget_com->setColumnCount(header.size());
	ui.tableWidget_com->setHorizontalHeaderLabels(header);
	ui.tableWidget_com->setColumnWidth(2, 70);
	ui.tableWidget_com->setColumnWidth(3, 80);
	ui.tableWidget_com->setColumnWidth(4, 60);
	ui.tableWidget_com->setColumnWidth(5, 50);
	ui.tableWidget_com->setColumnWidth(6, 50);
	ui.tableWidget_com->setColumnWidth(7, 60);
	ui.tableWidget_com->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui.tableWidget_com->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

	ui.tableWidget_com->setSelectionBehavior(QAbstractItemView::SelectRows);  //单击选择一行  
	ui.tableWidget_com->setSelectionMode(QAbstractItemView::SingleSelection); //设置只能选择一行，不能多行选中  
	ui.tableWidget_com->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改  
	ui.tableWidget_com->setAlternatingRowColors(true);

	ui.tableWidget_com->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.tableWidget_com, &QTableWidget::customContextMenuRequested, this, &CommuniWidget::onRClickedCom);
}

void   CommuniWidget::comInfo2Widget()
{
	for (int i = 0; i < m_vecSerPortInfo.size(); i++)
	{
		ui.tableWidget_com->insertRow(i);

		QTableWidgetItem*	item_0 = new QTableWidgetItem();
		ui.tableWidget_com->setItem(i, 0, item_0);
		QTableWidgetItem*	item_1 = new QTableWidgetItem();
		ui.tableWidget_com->setItem(i, 1, item_1);
		QComboBox*			item_2 = new QComboBox(ui.tableWidget_tcp);
		ui.tableWidget_com->setCellWidget(i, 2, (QWidget*)item_2);
		QComboBox*			item_3 = new QComboBox(ui.tableWidget_tcp);
		ui.tableWidget_com->setCellWidget(i, 3, (QWidget*)item_3);
		QComboBox*			item_4 = new QComboBox(ui.tableWidget_tcp);
		ui.tableWidget_com->setCellWidget(i, 4, (QWidget*)item_4);
		QComboBox*			item_5 = new QComboBox(ui.tableWidget_tcp);
		ui.tableWidget_com->setCellWidget(i, 5, (QWidget*)item_5);
		QComboBox*			item_6 = new QComboBox(ui.tableWidget_tcp);
		ui.tableWidget_com->setCellWidget(i, 6, (QWidget*)item_6);

		QTableWidgetItem*	item_7 = new QTableWidgetItem();
		ui.tableWidget_com->setItem(i, 7, item_7);

		item_2->addItems(m_strListComnum);
		item_3->addItems(m_strListBaudrate);
		item_4->addItems(m_strListParity);
		item_5->addItems(m_strListDatabit);
		item_6->addItems(m_strListstopbit);

		ui.tableWidget_com->item(i, 0)->setText(m_vecSerPortInfo[i].name);
		ui.tableWidget_com->item(i, 1)->setText(m_vecSerPortInfo[i].desc);
		item_2->setCurrentText(m_vecSerPortInfo[i].comNO);
		item_3->setCurrentText(m_vecSerPortInfo[i].baudrate);
		item_4->setCurrentText(m_vecSerPortInfo[i].parity);
		item_5->setCurrentText(m_vecSerPortInfo[i].databits);
		item_6->setCurrentText(m_vecSerPortInfo[i].stopbits);	
	}
}


void CommuniWidget::timerEvent(QTimerEvent *event)
{
	if (this->isVisible()){
		if (event->timerId() == m_comStatusId){
			for (int i = 0; i<m_vecSerPortInfo.size();i++){
				bool isOpen = SERIALPORT_INSTANCE->isOpened(m_vecSerPortInfo[i].name);
				QTableWidgetItem* item = ui.tableWidget_com->item(i, 7);
				QString status = isOpen ? QStringLiteral("已连接") : QStringLiteral("未连接");
				item->setText(status);
			}
		}
	}
}

void	CommuniWidget::onRClickedTcp(const QPoint& pos)
{
	QTableWidgetItem* selectedItem = ui.tableWidget_tcp->itemAt(pos);

	if (nullptr != selectedItem)
	{
		int curRow = ui.tableWidget_tcp->row(selectedItem);
		QMenu *menu = new QMenu(ui.tableWidget_tcp);
		menu->addAction(QStringLiteral("连接"), this, &CommuniWidget::onTcpConnect);
		menu->addAction(QStringLiteral("断开"), this, &CommuniWidget::onTcpDisconnect);
		menu->exec(QCursor::pos());					
	}
}

void	CommuniWidget::onRClickedCom(const QPoint& pos)
{
	QTableWidgetItem* selectedItem = ui.tableWidget_com->itemAt(pos);

	if (nullptr != selectedItem)
	{
		int curRow = ui.tableWidget_com->row(selectedItem);
		QMenu *menu = new QMenu(ui.tableWidget_com);
		menu->addAction(QStringLiteral("连接"), this, &CommuniWidget::onComConnect);
		menu->addAction(QStringLiteral("断开"), this, &CommuniWidget::onComDisconnect);
		menu->exec(QCursor::pos());
	}
}

void	CommuniWidget::onTcpConnect()
{
	int cur = ui.tableWidget_tcp->currentRow();

	if (!NETWORK_INSTANCE->clientReConnect(cur))
	{
		XMessageBox::error(QStringLiteral("连接失败"));
	}
}

void	CommuniWidget::onTcpDisconnect()
{
	int cur = ui.tableWidget_tcp->currentRow();

	NETWORK_INSTANCE->clientDisconnect(cur);
}

void    CommuniWidget::onComConnect()
{
	int cur = ui.tableWidget_com->currentRow();

	if (!SERIALPORT_INSTANCE->isOpened(m_vecSerPortInfo[cur].name))
	{
		SERIALPORT_INSTANCE->reOpenPort(m_vecSerPortInfo[cur].name);
		QThread::msleep(2000);
		if (!SERIALPORT_INSTANCE->isOpened(m_vecSerPortInfo[cur].name))
		{
			XMessageBox::error(QStringLiteral("打开失败"));
		}
	}
	else
	{
		XMessageBox::show(QStringLiteral("已连接"));
	}
}

void    CommuniWidget::onComDisconnect()
{
	int cur = ui.tableWidget_com->currentRow();
	SERIALPORT_INSTANCE->closePort(m_vecSerPortInfo[cur].name);
}

void	CommuniWidget::onTcpBtnClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();
	qDebug() << objText << "Clikced";


	if (tr("Send") == objText)
	{
		int     curIndex = ui.tableWidget_tcp->currentRow();
		QString strSend = ui.lineEdit_send_tcp->text();

		if (strSend.isEmpty())
		{
			XMessageBox::warn(tr("Please enter the information sent"));
		}
		else if (curIndex != -1)
		{
			QString tcpName = m_vecTcpInfo[curIndex].name;
			if (!NETWORK_INSTANCE->sendData(tcpName, strSend))
			{
				XMessageBox::error(tr("Failed to send"));
			}
		}
		else
		{
			XMessageBox::warn(tr("Please select a network terminal"));
		}
	}
}

void	CommuniWidget::onComBtnClicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();
	qDebug() << objText << "Clikced";

	if (tr("Send") == objText)
	{
		int     curIndex = ui.tableWidget_com->currentRow();
		QString strSend = ui.lineEdit_send_com->text();

		if (strSend.isEmpty())
		{
			XMessageBox::warn(tr("Please enter the information sent"));
		}
		else if (curIndex != -1)
		{
			QString recv;
			QString portName = m_vecSerPortInfo[curIndex].name;
			if (SERIALPORT_INSTANCE->sendRecive(portName, strSend, recv)){
				ui.textEdit_recv_com->append(portName + ":" + recv);
			}
			else{
				XMessageBox::error(tr("Failed to send"));
			}
		}
		else
		{
			XMessageBox::warn(tr("Please select the serial port"));
		}
	}
}

//void    CommuniWidget::onRecvComMessage(QString name, QString msg)
//{
//	if (this->isVisible())
//	{
//		ui.textEdit_recv_com->append(name + ":" + msg);
//	}
//}

void    CommuniWidget::onRecvTcpMessage(QString name, QString msg)
{
	if (this->isVisible())
	{
		ui.textEdit_recv_tcp->append(name + ":" + msg);
	}
}

void   CommuniWidget::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		break;
	default:
		break;
	}
}
