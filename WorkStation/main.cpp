#include "WorkStation.h"
#include "../include/Common.h"
#include "../Utility/Utility/Utility.h"
#include "../Utility/System/Config.h"
#include <QtWidgets/QApplication>
#include <QMetaType>    
#include <QSystemSemaphore>
#include <QMessageBox>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSystemSemaphore semaphore("ProgramKey", 1, QSystemSemaphore::Open);
	semaphore.acquire();
	QSharedMemory memory("Program");
	if (!memory.create(1))
	{
		QMessageBox::information(0, "Warning", "Program hasbeen running!");
		semaphore.release();
		return 0;
	}
	semaphore.release();


	//设置程序开机启动
	//AutoRunWithSystem(CONFIG_INSTANCE->getSysInfo().autoRun, "GlueSystem", QCoreApplication::applicationFilePath());

	qRegisterMetaType<SYSTEM_STATUS>("SYSTEM_STATUS");
	qRegisterMetaType<SystemInfo>("SystemInfo");
	WorkStation w;
	w.show();
	return a.exec();
}
