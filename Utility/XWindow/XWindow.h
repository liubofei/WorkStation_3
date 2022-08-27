#pragma once

#include "xwindow_global.h"
#include <QtWidgets/QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>

class XWINDOW_EXPORT XWindow : public QDialog
{
	Q_OBJECT

public:
	XWindow(QWidget *parent = nullptr);

private:

	QLabel *			m_pIconLabel;
	QLabel *			m_pTitleLabel;
	QPushButton *		m_pMinimizeButton;
	QPushButton *		m_pMaximizeButton;
	QPushButton *		m_pCloseButton;


	QPoint			    m_mousePoint;
	bool				m_mousePressed;
	bool				m_bIsMaximize;
	QRect			    m_oldGeometry;	//窗口最大化之前的大小
	QWidget*			m_titleWidget;

public:

	enum SysButton
	{
		SysButton_Close = 0x01 << 0,
		SysButton_Max   = 0x01 << 1,
		SysButton_Min   = 0x01 << 2,
	};

	void			setWindowTitle(const QString &);
	void			setSysButtonStyle(int style = SysButton_Min | SysButton_Max | SysButton_Close);
	void			setTitleHeight(int height);

protected:
	virtual bool	eventFilter(QObject *obj, QEvent *event);
	virtual void	mouseMoveEvent(QMouseEvent *e);
	virtual void	mousePressEvent(QMouseEvent *e);
	virtual void	mouseReleaseEvent(QMouseEvent *);
	virtual void    keyPressEvent(QKeyEvent *);
	virtual void	resizeEvent(QResizeEvent *event);

private:
	void			updateMaximize();
	void			initTitle();

protected slots :
	virtual void	onCloseClicked();
	void			onMaxClicked();
	void			onMinClicked();

};
