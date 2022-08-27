#include "XMessageBox.h"
#include "../XWindow/XWindow.h"
#include "MessageBox.h"

//���¶Ի�����Ҫ�ֶ����٣���Ϊ������ dialog->setAttribute(Qt::WA_DeleteOnClose);

int XMessageBox::show(const QString & msg)
{
	MessageBox *pMb = new MessageBox(MessageBox::MESSAGEBOX_SHOW, msg);
	return pMb->exec();
}

int XMessageBox::warn(const QString & msg)
{
	MessageBox *pMb = new MessageBox(MessageBox::MESSAGEBOX_WARN, msg);
	return pMb->exec();
}

int XMessageBox::error(const QString & msg)
{
	MessageBox *pMb = new MessageBox(MessageBox::MESSAGEBOX_ERROR, msg);
	return pMb->exec();
}

int XMessageBox::ask(const QString & msg)
{
	MessageBox *pMb = new MessageBox(MessageBox::MESSAGEBOX_ASK, msg);
	return pMb->exec();
}

