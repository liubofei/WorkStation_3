#pragma once

#include <QFont>
#include <QLabel>
#include <QPushButton>

class  XIcon
{
public:

	static XIcon *Instance()
	{
		static QMutex mutex;
		if (!m_instance) {
			QMutexLocker locker(&mutex);
			if (!m_instance) {
				m_instance = new XIcon();
			}
		}
		return m_instance;
	}

	static void SetIcon(QLabel* lab, QChar c, QColor color = QColor(0, 0, 0), int size = 10);
	static void SetIcon(QPushButton* btn, QChar c, QColor color = QColor(0, 0, 0), int size = 10);

private:
	XIcon();

	QFont		    m_Iconfont;
	static XIcon *  m_instance;
};

