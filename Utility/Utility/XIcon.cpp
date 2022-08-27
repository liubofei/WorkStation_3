#include "XIcon.h"
#include <QFontDatabase>

XIcon* XIcon::m_instance = 0;

XIcon::XIcon()
{
	int fontId = QFontDatabase::addApplicationFont(":/WorkStation/fontawesome-webfont.ttf");
	QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
	m_Iconfont = QFont(fontName);
}

void XIcon::SetIcon(QLabel* lab, QChar c, QColor color, int size)
{
	Instance()->m_Iconfont.setPointSize(size);
	lab->setFont(Instance()->m_Iconfont);
	lab->setText(c);

	QRgb mRgb = qRgb(color.red(), color.green(), color.blue());
	QString mRgbStr = QString::number(mRgb, 16);
	QString style = QString("color:#%1").arg(mRgbStr);
	lab->setStyleSheet(style);
}

void XIcon::SetIcon(QPushButton* btn, QChar c, QColor color, int size)
{
	Instance()->m_Iconfont.setPointSize(size);
	btn->setFont(Instance()->m_Iconfont);
	btn->setText(c);
	
	QPalette pt;
	pt.setColor(QPalette::WindowText, color);
	btn->setPalette(pt);
}
