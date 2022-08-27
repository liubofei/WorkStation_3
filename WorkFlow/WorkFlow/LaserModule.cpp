#include "LaserModule.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Utility/NetWork/NetWork.h"
#include "../../Utility/System/Config.h"
#include "../../include/Motion.h"


LaserModule::LaserModule(QObject *parent)
	: MyModule(parent)
{
	initData();
	setLaserPts();
}

LaserModule::~LaserModule()
{
}

bool LaserModule::moduleReset()
{
	setReady(false);
	m_breakPos = 1;
	m_bIsHome = false;
	QString xName = "Laser_X", yName = "Laser_Y";
	int xCard = 0, xAxis = 0, xHomeResult = 0;
	int yCard = 0, yAxis = 0, yHomeResult = 0;

	if (0 != MANAGER->setCylinder(QStringLiteral("镭码定位"), QStringLiteral("镭码定位+"), QStringLiteral("镭码定位-"), 3000, 0))
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 镭码定位气缸 关闭失败"));
		return false;
	}
	if (!MANAGER->findAxis(xName, xCard, xAxis))
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 Laser_X轴不存在"));
		return false;
	}
	if (!MANAGER->findAxis(yName, yCard, yAxis))
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 Laser_Y轴不存在"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(xCard, xAxis))
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 启动Laser_X轴回原失败"));
		return false;
	}
	if (0 != MOTION_INSTANCE->Axis_Home(yCard, yAxis))
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 启动Laser_Y轴回原失败"));
		return false;
	}

	xHomeResult = MOTION_INSTANCE->Axis_WaiteHome(xCard, xAxis);
	yHomeResult = MOTION_INSTANCE->Axis_WaiteHome(yCard, yAxis);
	if (xHomeResult != 0)
	{	
		emit printUILog(QStringLiteral("[Error] 镭码模组 Laser_X回原失败"));	
		return false;
	}
	if (yHomeResult != 0)
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 Laser_Y回原失败"));
		return false;
	}

	if (0 != MANAGER->pointMoveSync("Laser_Load_Pos"))
	{
		emit printUILog(QStringLiteral("[Error] 镭码模组 移动到点Laser_Load_Pos失败"));
		return false;
	}

	emit printUILog(QStringLiteral("[OK] 镭码模组复位成功"));
	setReady(true);
	m_bIsHome = true;
	return true;
}

bool LaserModule::moduleResetAsync()
{
	if (m_homeFuture.isRunning())
	{
		emit printUILog(QStringLiteral("[Warn] 镭码模组正在复位中...,请等待完成"));
		return false;
	}

	m_homeFuture = QtConcurrent::run(this, &LaserModule::moduleReset);
	return true;
}

void LaserModule::pause()
{
	m_mutex.lock();
}

void LaserModule::resume()
{
	m_mutex.unlock();
}

//测试用
void LaserModule::test()
{
	static int times = 1;

	if (times > 96)
	{
		emit initLaserResult();
		times = 1;
	}
	else
	{
		int row, col;
		getRowCol(times, 8, 12, row, col);
		emit updateLaserResult(row, col, m_bLaserResult[row][col]);
		times++;
		m_total++;
		m_ngNum++;
		emit updateOutput(m_total, m_ngNum);
	}
}

int LaserModule::calibLaserFun()
{
	QString sendVisionMsg = QString("B");
	QString recvVisionMsg;
	RunPoint calibPt;

	if (!MANAGER->findPoint("Point_Calib_OutLaser", calibPt)) return 1;

	if (0 != MANAGER->pointMoveSync(calibPt))
	{
		emit printUILog(QStringLiteral("[Error] 移动到标定激光出光位失败"));
		MANAGER->pointMoveSync("Point_Init");
		return 1;
	}

	if (!laserMarking())
	{
		emit printUILog(QStringLiteral("[Error] 打标失败"));
		return 1;
	}

	MANAGER->setOutputStatus(QStringLiteral("光源"), 1);
	if (!visionCommuni(sendVisionMsg, recvVisionMsg))
	{
		emit printUILog(QStringLiteral("[Error] 标定失败,请检查软件是否和视觉系统的通信"));
	}

	if (recvVisionMsg == QString("1"))
	{
		emit printUILog(QStringLiteral("[OK] 标定成功"));
	}
	else
	{
		emit printUILog(QStringLiteral("[Error] 标定失败"));
	}	

	MANAGER->setOutputStatus(QStringLiteral("光源"), 0);

	if (0 != MANAGER->pointMoveSync("Point_Init"))
	{
		emit printUILog(QStringLiteral("[Error] 移动到初始位失败"));
		return 1;
	}

	return 0;
}

void LaserModule::initData()
{
	m_row = 8;
	m_col = 12;
	m_breakPos = 1;

	m_total = 0;
	m_ngNum = 0;

	m_bLaserResult = new bool *[m_row];
	m_laserPt = new RunPoint *[m_row];
	m_laserInfo = new LaserInfo *[m_row];

	for (int i = 0; i < m_row; ++i)
	{
		m_bLaserResult[i] = new bool[m_col];
		m_laserPt[i] = new RunPoint[m_col];
		m_laserInfo[i] = new LaserInfo[m_col];
	}

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			m_bLaserResult[i][j] = true;
		}
	}
}

bool LaserModule::setLaserPts()
{
	SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
	RunPoint startPt;
	double rowOffset = sysInfo.tray_row_space;
	double colOffset = sysInfo.tray_col_space;
	if (MANAGER->findPoint("Laser_Tray_First_Pos", startPt))
	{
		for (int row = 0; row < m_row; ++row)
		{
			for (int col = 0; col < m_col; ++col)
			{
				m_laserPt[row][col] = startPt;
				m_laserPt[row][col].pos[0] += colOffset*col;
				m_laserPt[row][col].pos[1] += rowOffset*row;			//注意，+还是减和Y的安装方式有关
			}
		}
		return true;
	}

	return false;
}

bool LaserModule::setLaserResult(int row, int col, bool isOk)
{
	if (row < m_row && row >= 0 && col < m_col && col >= 0)
	{
		m_bLaserResult[row][col] = isOk;
		emit updateLaserResult(row, col, isOk);
		return true;
	}
	return false;
}

void LaserModule::run()
{
	setReady(false);

	if (runFun())
	{
		setReady(true);
		emit sendReady(LASER);
	}
	else
	{
		emit printUILog(m_strError);
	}
}

bool LaserModule::runFun()
{
	if (!m_bIsHome)
	{
		m_strError = QStringLiteral("[Error] 镭码模块未回原，请回原后继续");
		return false;
	}
	if (0 == MANAGER->getInputStatus(QStringLiteral("镭码料盘感应")))
	{
		emit printUILog(QStringLiteral("[OK] 镭码模组无料盘，已返回"));
		return true;
	}
	if (0 != MANAGER->setCylinder(QStringLiteral("镭码定位"), QStringLiteral("镭码定位+"), QStringLiteral("镭码定位-"), 3000, 1))
	{
		m_strError = QStringLiteral("[Error] 镭码模组 镭码定位气缸未打开，请检查");
		return false;
	}

	if (m_breakPos > m_col * m_row)
	{
		emit initLaserResult();
		m_breakPos = 1;
	}

	int row = 0, col = 0;
	int ptNum = m_col * m_row;
	for (; m_breakPos <= ptNum; ++m_breakPos)
	{
		QMutexLocker lock(&m_mutex);		//用于暂停
		getRowCol(m_breakPos, m_row, m_col, row, col);
		if (0 != MANAGER->pointMoveSyncInterrupable(m_laserPt[row][col]))
		{
			m_strError = QStringLiteral("[Error] 镭码模组 移动到第%1个点失败,退出流程").arg(m_breakPos);
			return false;
		}

		m_total += 1;

		if (!ccdLocation(row, col))
		{
			setLaserResult(row, col, false);
			m_ngNum += 1;
			emit printUILog(m_strError);
			continue;
		}
		if (!laserModel(row, col))
		{
			setLaserResult(row, col, false);
			m_ngNum += 1;
			emit printUILog(m_strError);
			continue;
		}

		setLaserResult(row, col, true);
		emit updateOutput(m_total, m_ngNum);
	}

	if (0 != MANAGER->pointMoveSyncInterrupable("Laser_Load_Pos"))
	{
		m_strError = QStringLiteral("[Error] 镭码模组 移动到点位 Laser_Load_Pos 失败");
		return false;
	}
	if (0 != MANAGER->setCylinder(QStringLiteral("镭码定位"), QStringLiteral("镭码定位+"), QStringLiteral("镭码定位-"), 3000, 0))
	{
		m_strError = QStringLiteral("[Error]  镭码模组 镭码定位气缸未松开，请检查");
		return false;
	}
	return true;
}


void LaserModule::getRowCol(int id, int rowNum, int colNum, int &row, int &col)
{
	int index = id - 1;
	row = index / colNum;
	int Oddeven = row % 2;
	int remainder = index % colNum;
	col = Oddeven == 0 ? remainder : colNum - 1 - remainder;
}

bool LaserModule::laserCommuni(const QString &send, QString &recv)
{
	if (!NETWORK_INSTANCE->sendData("Laser", send))
	{
		m_strError = QStringLiteral("[Warn] 镭码数据发送失败");
		return false;
	}
	if (!NETWORK_INSTANCE->recvData("Laser", recv))
	{
		m_strError = QStringLiteral("[Warn] 镭码数据接收失败");
		return false;
	}
	return true;
}

bool LaserModule::visionCommuni(const QString &send, QString &recv, int msTimeOut)
{
	if (!NETWORK_INSTANCE->sendData("Vision", send))
	{
		m_strError = QStringLiteral("[Warn] 视觉数据发送失败");
		return false;
	}
	if (!NETWORK_INSTANCE->recvData("Vision", recv, 6000))
	{
		m_strError = QStringLiteral("[Warn] 视觉数据发送接收");
		return false;
	}
	return true;	
}

bool LaserModule::laserModel(int row, int col)
{
	SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
	QString sendStrInfo, recvStrInfo, sendRadiusStr, recvRadiusStr;
	double xPos, yPos, ang, radius;

	xPos = m_laserInfo[row][col].laserXY[0];
	yPos = m_laserInfo[row][col].laserXY[1];
	ang = m_laserInfo[row][col].angle;
	radius = m_laserInfo[row][col].radius;

	sendStrInfo = QString("V0,%1,1,%2,%3,%4\r").arg(sysInfo.laserVersion).arg(xPos).arg(yPos).arg(ang);
	sendRadiusStr = QString("WX,PRG=%1,BLK=1,BlockPosition=%2,0000.000,9999.999\r").arg(sysInfo.laserVersion).arg(radius);

	if (1 != sysInfo.enableV0Command && 1 != sysInfo.enableRCommand)
	{
		m_strError = QStringLiteral("[Warn] 打标指令异常，请从V0和R指令中至少选择一项指令");
		return false;
	}
	if (1 == sysInfo.enableV0Command)
	{
		if (!laserCommuni(sendStrInfo, recvStrInfo)) return false;
		if (recvStrInfo != QString("V0,0"))
		{
			m_strError = QStringLiteral("[Warn] V0指令回传信息不匹配！");
			return false;
		}
	}
	if (1 == sysInfo.enableRCommand)
	{
		if (!laserCommuni(sendRadiusStr, recvRadiusStr)) return false;
		if (recvRadiusStr != QString("WX,OK"))
		{
			m_strError = QStringLiteral("[Warn] WX指令回传信息不匹配！");
			return false;
		}
	}
	if (1 == sysInfo.enableLaser)		//打激光
	{		
		QString strLaserSend = "NT\r";
		QString strLaserRecv;
		if (!laserCommuni(strLaserSend, strLaserRecv)) return false;
		if (strLaserRecv != QString("NT,0"))
		{
			m_strError = QStringLiteral("[Warn] 刻印失败");
			return false;
		}
	}

	return true;
}

bool LaserModule::ccdLocation(int row, int col)
{
	SystemInfo sysInfo = CONFIG_INSTANCE->getSysInfo();
	QString strSend, strRecv;
	
	strSend = QString("D,%1,%2,%3\r").arg(sysInfo.visionVersion).arg(m_laserPt[row][col].pos[0]).arg(m_laserPt[row][col].pos[1]);

	if (!visionCommuni(strSend, strRecv)) return false;
	if (!checkVisionResult(strRecv, 5)) return false;

	QStringList recvList = strRecv.split(",");

	m_laserInfo[row][col].laserXY[0] = recvList[1].toDouble();
	m_laserInfo[row][col].laserXY[1] = recvList[2].toDouble();
	m_laserInfo[row][col].angle = recvList[3].toDouble();
	m_laserInfo[row][col].radius = recvList[4].toDouble();
	return true;
}

bool LaserModule::checkVisionResult(const QString &recv, int size)
{
	if (!recv.contains(","))
	{
		m_strError = QStringLiteral("[Warn] 定位回传数据中不包含 '，'");
		return false;
	}
	QStringList strList = recv.split(",");
	if (strList.size() != size)
	{
		m_strError = QStringLiteral("[Warn] 定位回传数据，数据长度异常！");
		return false;
	}

	if (strList[0] == "1")
	{
		return true;
	}
	else if (strList[0] == "0")
	{
		m_strError = QStringLiteral("[Warn] 视觉定位NG");
		return false;
	}

	return false;
}

bool LaserModule::laserMarking()
{
	QString strSend = "NT\r";
	QString strRecv;

	if (!laserCommuni(strSend, strRecv)) return false;

	if (strRecv == QString("NT,0")) return true;

	m_strError = QStringLiteral("[Warn] 刻印失败");
	return false;	
}
