#include "MessageBox.h"
#include <QDesktopWidget>
#include <QDebug>
#include "../Utility/Utility.h"

MessageBox::MessageBox(MESSAGEBOX_MODE mode,QString msg)
{
	ui.setupUi(this);

	this->setSysButtonStyle(0);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowStaysOnTopHint);

	initWidget(mode, msg);
	FormInCenter(this);
}

MessageBox::~MessageBox()
{

}

void MessageBox::initWidget(MESSAGEBOX_MODE mode, QString msg)
{
	switch (mode)
	{
		case MessageBox::MESSAGEBOX_SHOW:
		{
			setWindowTitle(QStringLiteral("提示"));
			ui.label_icon->setStyleSheet("border-image: url(:/WorkStation/info.png);");
			ui.label_message->setText(msg);
			ui.pushButton_cancel->setVisible(false);
		}break;
		case MessageBox::MESSAGEBOX_WARN:
		{
			setWindowTitle(QStringLiteral("警告"));
			ui.label_icon->setStyleSheet("border-image: url(:/WorkStation/warn.png);");
			ui.label_message->setText(msg);
			ui.pushButton_cancel->setVisible(false);

		}break;
		case MessageBox::MESSAGEBOX_ERROR:
		{
			setWindowTitle(QStringLiteral("错误"));
			ui.label_icon->setStyleSheet("border-image: url(:/WorkStation/error.png);");
			ui.label_message->setText(msg);
			ui.pushButton_cancel->setVisible(false);

		}break;
		case MessageBox::MESSAGEBOX_ASK:
		{
			setWindowTitle(QStringLiteral("询问"));
			ui.label_icon->setStyleSheet("border-image: url(:/WorkStation/question.png);");
			ui.label_message->setText(msg);
			ui.pushButton_cancel->setVisible(true);

		}break;
		default:
		break;
	}

	//根据内容调整高度
	
	this->setGeometry(this->x(), this->y(), this->width(), this->height() + 15 * (msg.size() / 25));
}


void MessageBox::onOKClicked()
{
	done(1);
	this->close();
}

void MessageBox::onCancelClicked()
{
	done(0);
	this->close();
}
