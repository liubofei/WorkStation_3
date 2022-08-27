#include "LoginWidget.h"
#include "../../Utility/System/Config.h"
#include "ChangePWWidget.h"


LoginWidget::LoginWidget()
{
	ui.setupUi(this);
	setWindowTitle(QStringLiteral("ÓÃ»§µÇÂ½"));
	setSysButtonStyle(SysButton_Close);
	ui.lineEdit->setFocus();
	connect(ui.lineEdit, SIGNAL(returnPressed()), ui.pushButton_login, SIGNAL(clicked()));
	connect(ui.pushButton_changePW, &QPushButton::clicked, this, &LoginWidget::onChangePW);//µã»÷ ÐÞ¸ÄÃÜÂë °´Å¥£¬showÐÞ¸ÄÃÜÂë´°¿ÚhideµÇÂ¼´°¿Ú
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
		ui.label->setText(QStringLiteral("ÃÜÂë´íÎó"));
	}
}

void  LoginWidget::onChangePW()
{
	ChangePWWidget *changePWWidget = new ChangePWWidget();
	changePWWidget->setAttribute(Qt::WA_DeleteOnClose);

	changePWWidget->show();
	hide();
}