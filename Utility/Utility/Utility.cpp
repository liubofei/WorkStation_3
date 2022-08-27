#include "Utility.h"
#include <QApplication>
#include <QGuiApplication>
#include <QtGui>
#include <QDesktopWidget>
#include <QMenuBar>
#include "../../include/Common.h"
#include "XIcon.h"

//设置为开机启动
void AutoRunWithSystem(bool IsAutoRun, QString AppName, QString AppPath)
{
	AppPath.replace("/", "\\");

	QSettings *reg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);

	if (IsAutoRun) {
		reg->setValue(AppName, AppPath);
	}
	else {
		reg->setValue(AppName, "");
	}
}

//延时
void sleepMS(int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime) 
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

void FormInCenter(QWidget *frm)
{
	int frmX = frm->width();
	int frmY = frm->height();
	QDesktopWidget w;
	int deskWidth = w.width();
	int deskHeight = w.height();
	QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
	frm->move(movePoint);
}

void SetUTF8Code()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
#endif
}

//qss为了能在调试阶段每次不需要编译加载，选择使用相对路径
//注意qrc是编译成二进制的
void SetStyle(QWidget *widget,const QString &styleName)
{
	QString filePath = CFGDIR("Config/") + styleName;

	QFile file(filePath);

	if (file.open(QFile::ReadOnly))
	{
		QString qss = GetCorrectUnicode(file.readAll());
		widget->setStyleSheet(qss);
	}
	else
	{
		qDebug() << "SetStyle -> "<<styleName <<"read failed";
	}

}

void SetChinese()
{
	QTranslator *translator = new QTranslator(qApp);
	translator->load(":/WorkStation/qt_zh_CN.qm");
	qApp->installTranslator(translator);
}

bool IsIP(QString IP)
{
	QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	return RegExp.exactMatch(IP);
}

QString GetCorrectUnicode(const QByteArray &ba)
{
	QTextCodec::ConverterState state;
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
	if (state.invalidChars > 0)
	{
		text = QTextCodec::codecForName("GBK")->toUnicode(ba);
	}
	else
	{
		text = ba;
	}

	return text;
}

bool isFileExist(QString filePath)
{
	QFileInfo info(filePath);
	return info.isFile();
}

bool isDirExist(QString fullPath)
{
	QDir dir(fullPath);
	return dir.exists();
}

bool createDir(QString dirPath)
{
	if (dirPath.isNull())
	{
		return false;
	}

	if (isDirExist(dirPath))
	{
		return true;
	}

	QDir dir;
	return dir.mkpath(dirPath);
}

QString getExecPath()
{
	return QCoreApplication::applicationDirPath();
}

QFileInfoList GetFileList(QString path)
{
	QDir dir(path);
	QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

	for (int i = 0; i != folder_list.size(); i++)
	{
		QString name = folder_list.at(i).absoluteFilePath();
		QFileInfoList child_file_list = GetFileList(name);
		file_list.append(child_file_list);
	}

	return file_list;
}

//防止 1 转成double （0.999999），在转成int（0）精度丢失
int	doubleToInt(double dValue)
{
	if (dValue< -COMM_0F)
	{
		dValue -= COMM_0F;
	}
	else if (dValue > COMM_0F)
	{
		dValue += COMM_0F;
	}

	return (int)dValue;
}

void SetIcon(QLabel* lab, QChar c, QColor color, int size)
{
	XIcon::Instance()->SetIcon(lab, c, color, size);
}

void SetIcon(QPushButton* btn, QChar c, QColor color, int size)
{
	XIcon::Instance()->SetIcon(btn, c, color, size);
}


bool  delDir(const QString &path)
{
	if (path.isEmpty())
	{
		return false;
	}

	QDir dir(path);

	if (!dir.exists())
	{
		return true;
	}

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

	QFileInfoList fileList = dir.entryInfoList();

	for each (QFileInfo file in fileList)
	{
		if (file.isFile())
		{
			file.dir().remove(file.fileName());
		}
		else
		{
			delDir(file.absoluteFilePath());
		}
	}

	return dir.rmpath(dir.absolutePath());
}


bool  getDelPath(QString path, QStringList& subPathList, int days)
{
	if (path.isEmpty())
		return false;
	
	QDir dir(path);

	if (!dir.exists())	
		return false;
	
	subPathList.clear();
	QDateTime curTime = QDateTime::currentDateTime();
	QString curYear = curTime.toString("yyyy");
	QString lastYear = curTime.addYears(-1).toString("yyyy");
	QStringList filter;
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	for (int i = 0; i < fileInfo->count(); ++i)
	{
		QString subName = fileInfo->at(i).fileName();
		if (subName.contains(curYear) || subName.contains(lastYear))
		{
			QDateTime dtTemp = QDateTime::fromString(subName, "yyyy-MM-dd");
			QDateTime lastDate = dtTemp.addDays(days);
			if (lastDate < curTime)		
				subPathList.append(fileInfo->at(i).filePath());		
		}
	}

	delete fileInfo;
	return true;
}

QByteArray hexToByte(QString msg)
{
	QStringList strList = msg.split(" ");

	int len = strList.size();

	QByteArray buff;

	bool isOK = false;
	for (int i = 0; i < len; ++i)
	{
		buff.append(strList.at(i).toInt(&isOK, 16));
	}
	return buff;
}

