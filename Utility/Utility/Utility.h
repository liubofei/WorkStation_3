#pragma once

#include "utility_global.h"
#include <QtCore>
#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QFileInfoList>

void			UTILITY_EXPORT AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath);	//����Ϊ��������

void			UTILITY_EXPORT sleepMS(int msec); //��ʱ

void			UTILITY_EXPORT FormInCenter(QWidget *frm); //���������ʾ

void			UTILITY_EXPORT SetUTF8Code(); //���ñ���ΪUTF8

void			UTILITY_EXPORT SetStyle(QWidget *widget, const QString &styleName);//����Ƥ����ʽ

void			UTILITY_EXPORT SetChinese(); //���������ַ�

bool			UTILITY_EXPORT IsIP(QString IP); //�ж��Ƿ���IP��ַ

QString			UTILITY_EXPORT GetCorrectUnicode(const QByteArray &ba);

bool			UTILITY_EXPORT isFileExist(QString filePath);

bool			UTILITY_EXPORT isDirExist(QString dirPath);

bool			UTILITY_EXPORT createDir(QString dirPath);

QString			UTILITY_EXPORT getExecPath();

QFileInfoList	UTILITY_EXPORT GetFileList(QString path);

int				UTILITY_EXPORT doubleToInt(double dValue);

void			UTILITY_EXPORT SetIcon(QLabel* lab, QChar c, QColor color = QColor(0,0,0),int size = 10);

void			UTILITY_EXPORT SetIcon(QPushButton* btn, QChar c, QColor color = QColor(0, 0, 0), int size = 10);

bool            UTILITY_EXPORT delDir(const QString &path); //ɾ���ļ�������������

bool            UTILITY_EXPORT getDelPath(QString path, QStringList& subPathList, int days);		//ɾ��ͼ���ļ� days��������

QByteArray      UTILITY_EXPORT hexToByte(QString msg);