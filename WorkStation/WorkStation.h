#pragma once
#include <QMainWindow>
#include <QStatusBar>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QLabel>
#include <QDateTime>
#include <QTranslator>
#include "../../include/Common.h"

class ModuleDebug;
class CanConnectWidget;
class MainWidget;
class ParamWidget;
class AxisMoveWidget;

class WorkStation : public QMainWindow
{
	Q_OBJECT

public:
	WorkStation(QWidget *parent = Q_NULLPTR);
	~WorkStation();

signals:
	void AppExit();
	void AppInit();
	void userModeChanged(USERMODE mode);
	void clearWorkCount();
	void chanageLanguage(int id);

protected slots:
	void onMenuBtnClicked();
	void onMenuChinese();
	void onMenuVietnamese();
	void onMenuEnglish();
	void onUpdateOutput(unsigned int total, unsigned int ngNum);

protected:
	void closeEvent(QCloseEvent *event);
	void timerEvent(QTimerEvent *event);
	void changeEvent(QEvent* event);

private:
	void		initData();
	void		initUI();
	void		initLayout();
	void		initMenuBar();
	void		initStatusBar();
	void		configUser();
	void		initConnection();
	void		menuClickedLogin(QString &menuText);	
	void        retranslateUi();
	void		initStyle(QString filePath);
	QAction*	getMenuBarAction(QMenu* menu, QString name);

private:
	int	m_updateModuleStatus;

	QMenuBar*	m_menuBar;
	QStatusBar*	m_statusBar;
	QMenu*		m_menuDebug;
	QMenu*		m_menuSet;
	QMenu*		m_menuRun;
	QMenu*		m_menuLogin;
	QMenu*		m_menuLanguage;	
	QLabel*		m_statusLabel;
	QLabel*		m_logStatus;
	QLabel*		m_productLabel;
	QLabel*		m_ngNumLabel;
	QLabel*		m_feedStatusLabel;
	QLabel*		m_carryStatusLabel;
	QLabel*		m_laserStatusLabel;
	QLabel*		m_unloadStatusLabel;

	MainWidget*	m_mainWidget;
	ParamWidget* m_paramWidget;
	ModuleDebug* m_moduleDebug;
	AxisMoveWidget* m_axisMoveWidget;
	CanConnectWidget* m_canConnectWidget;
	QTranslator* m_translator;

	QAction *actSet;
	QAction *actMotor;
	QAction *actCommu;
	QAction *actPoints;
	QAction *actIO;
	QAction *actAutoMode;
	QAction *actClearMode;
	QAction *actModuleDebugWidget;
	QAction *actAxisDebugWidget;;
	QAction *actCanConnectWidget;
	QAction *actLog;
	QAction *actLogin;
	QAction *actZw;
	QAction *actVietnamese;
	QAction *actEnglish;	
};
