#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QGroupBox>
#include <QPainter>
#include "XWindow.h"
#include "../Utility/Utility.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

XWindow::XWindow(QWidget *parent)
: QDialog(parent)
, m_bIsMaximize(false)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

	initTitle();

	SetStyle(this,"Skin.qss");

}

//注意，不能添加顶级layout
void XWindow::initTitle()
{
	m_mousePressed = false;
	m_bIsMaximize  = false;

	m_titleWidget  = new QWidget(this);
	m_titleWidget->setObjectName("BarWidget");

	m_pIconLabel      = new QLabel(this);
	m_pTitleLabel     = new QLabel(this);
	m_pMinimizeButton = new QPushButton(this);
	m_pMaximizeButton = new QPushButton(this);
	m_pCloseButton    = new QPushButton(this);

	m_pIconLabel->setFixedSize(30, 30);
	m_pIconLabel->setScaledContents(true);

	QFont font;
	font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
	font.setPointSize(11);
	m_pIconLabel     ->setFixedSize(32,32);
	m_pTitleLabel    ->setFont(font);
	m_pTitleLabel    ->setFixedHeight(30);
	m_pTitleLabel    ->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_pMinimizeButton->setFixedSize(30, 30);
	m_pMaximizeButton->setFixedSize(30, 30);
	m_pCloseButton   ->setFixedSize(30, 30);

	m_titleWidget    ->setObjectName("widget_background");
	m_pIconLabel     ->setObjectName("titleIconLabel");
	m_pTitleLabel    ->setObjectName("titleTextLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton   ->setObjectName("closeButton");

	m_pMinimizeButton->setToolTip(QStringLiteral("最小化"));
	m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
	m_pCloseButton   ->setToolTip(QStringLiteral("关闭"));

	QPixmap pixmap(":/WorkStation/logo_min.png");
	m_pIconLabel->setScaledContents(true);
	m_pIconLabel->setPixmap(pixmap);

	SetIcon(m_pMinimizeButton,  QChar(0xf068), QColor(0, 0, 0), 10);
	SetIcon(m_pMaximizeButton,  QChar(0xf096), QColor(0, 0, 0), 10);
	SetIcon(m_pCloseButton,		QChar(0xf00d), QColor(0, 0, 0), 10);

	QHBoxLayout *pHBoxLayout = new QHBoxLayout(m_titleWidget);
	pHBoxLayout  ->addSpacing(5);
	pHBoxLayout  ->addWidget(m_pIconLabel);
	pHBoxLayout  ->addSpacing(5);
	pHBoxLayout  ->addWidget(m_pTitleLabel);
	pHBoxLayout  ->addWidget(m_pMinimizeButton);
	pHBoxLayout  ->addWidget(m_pMaximizeButton);
	pHBoxLayout  ->addWidget(m_pCloseButton);
	pHBoxLayout  ->setSpacing(0);
	pHBoxLayout  ->setContentsMargins(0, 0, 0, 0);
	m_titleWidget->setLayout(pHBoxLayout);

	m_pTitleLabel->installEventFilter(this);

	connect(m_pMinimizeButton, &QPushButton::clicked, this, &XWindow::onMinClicked);
	connect(m_pMaximizeButton, &QPushButton::clicked, this, &XWindow::onMaxClicked);
	connect(m_pCloseButton,    &QPushButton::clicked, this, &XWindow::onCloseClicked);
}

void XWindow::setWindowTitle(const QString &title)
{
	m_pTitleLabel->setText(title);
	
	QDialog::setWindowTitle(title);
}

void XWindow::setSysButtonStyle(int style)
{
	bool enable = 0;

	enable = style & 0x01;
	m_pCloseButton->setVisible(enable);

	enable = style & 0x02;
	m_pMaximizeButton->setVisible(enable);

	enable = style & 0x04;
	m_pMinimizeButton->setVisible(enable);

}


bool XWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick ) {
		this->onMaxClicked();
		return true;
	}

	return QObject::eventFilter(obj, event);
}


void XWindow::mouseMoveEvent(QMouseEvent *e)
{
	if (m_mousePressed && (e->buttons() && Qt::LeftButton) && !m_bIsMaximize) {
		this->move(e->globalPos() - m_mousePoint);
		e->accept();
	}
}

void XWindow::mousePressEvent(QMouseEvent *e)
{
	QRect titleLabelRect = m_pTitleLabel->geometry();
	QPoint mousePos = e->pos();
	// just drag title bar can move window
	if (titleLabelRect.contains(mousePos))
	{
		if (e->button() == Qt::LeftButton) {
			m_mousePressed = true;
			m_mousePoint = e->globalPos() - this->pos();
			e->accept();
		}
	}

}

void XWindow::mouseReleaseEvent(QMouseEvent *)
{
	m_mousePressed = false;
}

void XWindow::resizeEvent(QResizeEvent *event)
{
	m_titleWidget->setGeometry(0, 0, this->width(), 30);
}

void    XWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
	case Qt::Key_Enter:
	case Qt::Key_Return:
	case Qt::Key_Space:
	break;
	default:
		QDialog::keyPressEvent(event);
	}
}

void XWindow::onMinClicked()
{
	this->showMinimized();
}

void XWindow::onMaxClicked()
{
	if (m_bIsMaximize) {
		this->setGeometry(m_oldGeometry);
		SetIcon(m_pMaximizeButton, QChar(0xf096), QColor(0, 0, 0), 10);
		m_pMaximizeButton->setToolTip(QStringLiteral("最大化"));
	}
	else {
		m_oldGeometry = this->geometry();
		this->setGeometry(qApp->desktop()->availableGeometry());
		SetIcon(m_pMaximizeButton, QChar(0xf079), QColor(0, 0, 0), 10);
		m_pMaximizeButton->setToolTip(QStringLiteral("还原"));
	}

	m_bIsMaximize = !m_bIsMaximize;
}

void XWindow::onCloseClicked()
{
	close();
}

