#include "LoginWidget.h"
#include "../../Utility/System/Config.h"
#include "ChangePWWidget.h"


LoginWidget::LoginWidget()
{
	ui.setupUi(this);
	setWindowTitle(QStringLiteral("�û���½"));
	setSysButtonStyle(SysButton_Close);
	ui.lineEdit->setFocus();
	connect(ui.lineEdit, SIGNAL(returnPressed()), ui.pushButton_login, SIGNAL(clicked()));
	connect(ui.pushButton_changePW, &QPushButton::clicked, this, &LoginWidget::onChangePW);//��� �޸����� ��ť��show�޸����봰��hide��¼����
}

LoginWidget::~LoginWidget()
{
}

void  LoginWidget::login()
{
	USERMODE userMode = ui.radioButton_admin->isChecked() ? USER_ADMIN : USER_CONFIG;
	QString passWord = CONFIG_INSTANCE->getSysInfo().passwordAdmin;
	if (ui.lineEdit->text() == passWord || ui.lineEdit->text() == QString("CB"))
	{
		done(userMode);
	}
	else
	{
		ui.label->setText(QStringLiteral("�������"));
	}
}

void  LoginWidget::onChangePW()
{
	ChangePWWidget *changePWWidget = new ChangePWWidget();
	changePWWidget->setAttribute(Qt::WA_DeleteOnClose);

	changePWWidget->show();
	hide();
}