#include "ChangePWWidget.h"
#include "../../Utility/System/Config.h"
#include<QLineEdit>
#include<QMessageBox>


ChangePWWidget::ChangePWWidget(QWidget *parent)
	: XWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QStringLiteral("ÐÞ¸ÄÃÜÂë"));
	init();
}

ChangePWWidget::~ChangePWWidget()
{
}

void ChangePWWidget::init()
{
	m_sysInfo = CONFIG_INSTANCE->getSysInfo();
	PW = CONFIG_INSTANCE->getSysInfo().passwordAdmin;
	connect(ui.pushButton_changePW, &QPushButton::clicked, this, &ChangePWWidget::onchangePW);
}

void ChangePWWidget::onchangePW()
{
	if ((PW == (ui.lineEdit_oldPW->text())) && ((ui.lineEdit_newPW->text()) == (ui.lineEdit_checkNewPW->text())))
	{
		m_sysInfo.passwordAdmin = ui.lineEdit_checkNewPW->text();
		CONFIG_INSTANCE->setSysInfo(m_sysInfo);
		this->close();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("PassWord Error");
		msgBox.exec();
	}
}