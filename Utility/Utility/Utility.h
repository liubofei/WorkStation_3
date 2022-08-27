#pragma once

#include "utility_global.h"
#include <QtCore>
#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QFileInfoList>

void			UTILITY_EXPORT AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath);	//设置为开机启动

void			UTILITY_EXPORT sleepMS(int msec); //延时

void			UTILITY_EXPORT FormInCenter(QWidget *frm); //窗体居中显示

void			UTILITY_EXPORT SetUTF8Code(); //设置编码为UTF8

void			UTILITY_EXPORT SetStyle(QWidget *widget, const QString &styleName);//设置皮肤样式

void			UTILITY_EXPORT SetChinese(); //加载中文字符

bool			UTILITY_EXPORT IsIP(QString IP); //判断是否是IP地址

QString			UTILITY_EXPORT GetCorrectUnicode(const QByteArray &ba);

bool			UTILITY_EXPORT isFileExist(QString filePath);

bool			UTILITY_EXPORT isDirExist(QString dirPath);

bool			UTILITY_EXPORT createDir(QString dirPath);

QString			UTILITY_EXPORT getExecPath();

QFileInfoList	UTILITY_EXPORT GetFileList(QString path);

int				UTILITY_EXPORT doubleToInt(double dValue);

void			UTILITY_EXPORT SetIcon(QLabel* lab, QChar c, QColor color = QColor(0,0,0),int size = 10);

void			UTILITY_EXPORT SetIcon(QPushButton* btn, QChar c, QColor color = QColor(0, 0, 0), int size = 10);

bool            UTILITY_EXPORT delDir(const QString &path); //删除文件夹下所有内容

bool            UTILITY_EXPORT getDelPath(QString path, QStringList& subPathList, int days);		//删除图像文件 days保留天数

QByteArray      UTILITY_EXPORT hexToByte(QString msg);