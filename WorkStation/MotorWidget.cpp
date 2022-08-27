#include "MotorWidget.h"
#include <QTreeWidgetItem>
#include <QTextCodec>
#include "../../Utility/Utility/Utility.h"
#include "../../include/Motion.h"
#include "../../Utility/System/Config.h"
#include "../../Utility/XMessageBox/XMessageBox.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Motion/Motion_dmc/CardInterfaceManager.h"

MotorWidget::MotorWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	CONFIG_INSTANCE->getCardInfo(m_vecCardInfo);

	init();
}

MotorWidget::~MotorWidget()
{
}

void MotorWidget::init()
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));


	SetIcon(ui.label_warn,		QChar(0xf111), QColor(180, 180, 180), 12);
	SetIcon(ui.label_home,		QChar(0xf111), QColor(180, 180, 180), 12);
	SetIcon(ui.label_plimits,	QChar(0xf111), QColor(180, 180, 180), 12);
	SetIcon(ui.label_nlimits,	QChar(0xf111), QColor(180, 180, 180), 12);
	SetIcon(ui.label_inplace,	QChar(0xf111), QColor(180, 180, 180), 12);

	initControl();

	ui.lineEdit_step->setText("0.1");
	setContextMenuPolicy(Qt::DefaultContextMenu);  

	connect(ui.pushButton_home,  &QPushButton::clicked, this, &MotorWidget::onHomeBtnClicked);
	connect(ui.pushButton_moven, &QPushButton::clicked, this, &MotorWidget::onMoveBtnClicked);
	connect(ui.pushButton_movep, &QPushButton::clicked, this, &MotorWidget::onMoveBtnClicked);
	connect(ui.pushButton_stop,  &QPushButton::clicked, this, &MotorWidget::onStopBtnClicked);
	connect(ui.checkBox_enable,  &QPushButton::clicked, this, &MotorWidget::onCheckEnableClicked);
	connect(ui.pushButton_moven, &QPushButton::pressed, this, &MotorWidget::onMoveBtnPressed);
	connect(ui.pushButton_movep, &QPushButton::pressed, this, &MotorWidget::onMoveBtnPressed);
	connect(ui.pushButton_moven, &QPushButton::released, this, &MotorWidget::onMoveBtnRelease);
	connect(ui.pushButton_movep, &QPushButton::released, this, &MotorWidget::onMoveBtnRelease);

	m_curCardIndex  = 0;
	m_curAxisIndex  = 0;
	m_copyAxisIndex = -1;
	m_copyCardIndex = -1;

	initTreeCtrl();
	cardInfo2Widget(m_curCardIndex, m_curAxisIndex);

	enableCtrls(false);
	
	m_timerID = this->startTimer(200);
}

void        MotorWidget::initControl()
{
	ui.comboBox_motortype->clear();
	ui.comboBox_motortype->addItem(tr("servo"));
	ui.comboBox_motortype->addItem(tr("stepper"));
	ui.comboBox_motortype->addItem(tr("DD motor"));
	ui.comboBox_motortype->addItem(tr("assembly line"));

	ui.comboBox_home_sense->clear();
	ui.comboBox_home_sense->addItem(tr("low effect"));
	ui.comboBox_home_sense->addItem(tr("high effect"));

	ui.comboBox_limits_mode->clear();
	ui.comboBox_limits_mode->addItem(tr("P and N disable"));
	ui.comboBox_limits_mode->addItem(tr("P and N enable"));
	ui.comboBox_limits_mode->addItem(tr("P disable,N enable"));
	ui.comboBox_limits_mode->addItem(tr("P enable,N disable"));

	ui.comboBox_limits_sense->clear();
	ui.comboBox_limits_sense->addItem(tr("P and N low"));
	ui.comboBox_limits_sense->addItem(tr("P and N high"));
	ui.comboBox_limits_sense->addItem(tr("P low,N high"));
	ui.comboBox_limits_sense->addItem(tr("P high,N low"));

	ui.comboBox_alarm_mode->clear();
	ui.comboBox_alarm_mode->addItem(tr("Disable"));
	ui.comboBox_alarm_mode->addItem(tr("Enable"));

	ui.comboBox_alarm_sense->clear();
	ui.comboBox_alarm_sense->addItem(tr("low effect"));
	ui.comboBox_alarm_sense->addItem(tr("high effect"));

	ui.comboBox_home_dir->clear();
	ui.comboBox_home_dir->addItem(tr("go N limit"));
	ui.comboBox_home_dir->addItem(tr("go P limit"));
	ui.comboBox_home_dir->addItem(tr("No limit"));

	ui.comboBox_home_mode->clear();
	ui.comboBox_home_mode->addItem(tr("normal"));
	ui.comboBox_home_mode->addItem(tr("capture"));
	ui.comboBox_home_mode->addItem(tr("precise"));
	ui.comboBox_home_mode->addItem(tr("user-defined"));

	ui.comboBox_stopMode->clear();
	ui.comboBox_stopMode->addItem(tr("immediate"));
	ui.comboBox_stopMode->addItem(tr("smooth"));
}

void MotorWidget::initTreeCtrl()
{
	connect(ui.treeWidget_card, &QTreeWidget::currentItemChanged, this, &MotorWidget::onCurItemChanged);
	connect(ui.treeWidget_card, &QTreeWidget::customContextMenuRequested, this, &MotorWidget::onCustomContextMenuRequested);

	ui.treeWidget_card->setColumnCount(1);
	ui.treeWidget_card->setHeaderLabel(QStringLiteral("卡列表"));
	ui.treeWidget_card->setContextMenuPolicy(Qt::CustomContextMenu);

	initRMenu();
	updateTreeCtrl();
}

void MotorWidget::initRMenu()
{
	m_menuCard = new QMenu(this);
	m_menuAxis = new QMenu(this);

	deleteCard = m_menuCard->addAction(tr("Delete Card"), this, &MotorWidget::onTreeCardRMenuClicked);
	addCard = m_menuCard->addAction(tr("Add Card"), this, &MotorWidget::onTreeCardRMenuClicked);
	addAxis = m_menuCard->addAction(tr("Add Axis"), this, &MotorWidget::onTreeCardRMenuClicked);
	editPara = m_menuAxis->addAction(tr("Edit Parameter"), this, &MotorWidget::onTreeAxisRMenuClicked);
	coypPara = m_menuAxis->addAction(tr("Copy Parameter"), this, &MotorWidget::onTreeAxisRMenuClicked);
	pastePara = m_menuAxis->addAction(tr("Paste Parameter"), this, &MotorWidget::onTreeAxisRMenuClicked);
	deleteAxis = m_menuAxis->addAction(tr("Delete Axis"), this, &MotorWidget::onTreeAxisRMenuClicked);
}


void  MotorWidget::nameAction()
{
	deleteCard->setText(tr("Delete Card"));
	addCard->setText(tr("Add Card"));
	addAxis->setText(tr("Add Axis"));
	editPara->setText(tr("Edit Parameter"));
	coypPara->setText(tr("Copy Parameter"));
	pastePara->setText(tr("Paste Parameter"));
	deleteAxis->setText(tr("Delete Axis"));
}

void  MotorWidget::updateTreeCtrl()
{
	disconnect(ui.treeWidget_card, &QTreeWidget::currentItemChanged, this, &MotorWidget::onCurItemChanged);
	disconnect(ui.treeWidget_card, &QTreeWidget::customContextMenuRequested, this, &MotorWidget::onCustomContextMenuRequested);

	ui.treeWidget_card->clear();

	connect(ui.treeWidget_card, &QTreeWidget::currentItemChanged, this, &MotorWidget::onCurItemChanged);
	connect(ui.treeWidget_card, &QTreeWidget::customContextMenuRequested, this, &MotorWidget::onCustomContextMenuRequested);


	for (int i = 0; i < m_vecCardInfo.size(); i++)
	{
		QString strCrad = QString("Card%1").arg(i);
		QTreeWidgetItem *cardItem = new QTreeWidgetItem(ui.treeWidget_card, QStringList(strCrad));

		for (int j = 0; j < m_vecCardInfo[i].vecAxisParam.size(); j++)
		{
			QString strAxis = QString("Axis%1").arg(j);
			QTreeWidgetItem *axisItem = new QTreeWidgetItem(cardItem, QStringList(strAxis));
		}
	}

	ui.treeWidget_card->expandAll();
	
}

void	 MotorWidget::updateAxisStatus()
{
	double pos = 0;
	short  val = 0;
	QColor color;

	if (!this->isVisible())
	{
		return;
	}

	MOTION_INSTANCE->ReadInBit_Enable(m_curCardIndex, m_curAxisIndex, val);
	ui.checkBox_enable->setChecked(val!=0? 0:1);

	MOTION_INSTANCE->Get_Panning_Pos(m_curCardIndex, m_curAxisIndex, pos);
	ui.label_pos_to->setText(QString::number(pos));

	MOTION_INSTANCE->Get_Current_Pos(m_curCardIndex, m_curAxisIndex, pos);
	ui.label_pos_real->setText(QString::number(pos));

	MOTION_INSTANCE->ReadInBit_Alarm(m_curCardIndex, m_curAxisIndex, val);
	color = val == 1 ? QColor(0, 255, 0) : QColor(180, 180, 180);
	SetIcon(ui.label_warn, QChar(0xf111), color, 12);

	MOTION_INSTANCE->ReadInBit_Origin(m_curCardIndex, m_curAxisIndex, val);
	color = val == 1 ? QColor(0, 255, 0) : QColor(180, 180, 180);
	SetIcon(ui.label_home, QChar(0xf111), color, 12);

	MOTION_INSTANCE->ReadInBit_LimitP(m_curCardIndex, m_curAxisIndex, val);
	color = val == 1 ? QColor(0, 255, 0) : QColor(180, 180, 180);
	SetIcon(ui.label_plimits, QChar(0xf111), color, 12);

	MOTION_INSTANCE->ReadInBit_LimitN(m_curCardIndex, m_curAxisIndex, val);
	color = val == 1 ? QColor(0, 255, 0) : QColor(180, 180, 180);
	SetIcon(ui.label_nlimits, QChar(0xf111), color, 12);

	MOTION_INSTANCE->ReadInBit_Inplace(m_curCardIndex, m_curAxisIndex, val);
	color = val == 1 ? QColor(0, 255, 0) : QColor(180, 180, 180);
	SetIcon(ui.label_inplace, QChar(0xf111), color, 12);
}

void MotorWidget::cardInfo2Widget(int card, int axis)
{
	QString str;

	if (card>=m_vecCardInfo.size())
	{
		return;
	}
	else if (axis >= m_vecCardInfo[card].vecAxisParam.size())
	{
		return;
	}
	
	AxisParam axisParam = m_vecCardInfo[card].vecAxisParam[axis];

	ui.lineEdit_axisName	->setText(axisParam.axisName);
	ui.checkBox_disableAxis ->setChecked(!axisParam.enable);
	ui.comboBox_motortype	->setCurrentIndex(axisParam.motorType);
	ui.comboBox_home_sense  ->setCurrentIndex(axisParam.homeSense);
	ui.comboBox_limits_mode ->setCurrentIndex(axisParam.limitMode);
	ui.comboBox_limits_sense->setCurrentIndex(axisParam.limitSense);
	ui.comboBox_alarm_mode  ->setCurrentIndex(axisParam.almMode);
	ui.comboBox_alarm_sense ->setCurrentIndex(axisParam.almSense);
	ui.comboBox_home_mode   ->setCurrentIndex(axisParam.homeType);
	ui.comboBox_home_dir	->setCurrentIndex(axisParam.homeDir);
	ui.comboBox_stopMode    ->setCurrentIndex(axisParam.stopMode);


	str = QString::number(axisParam.stepvalue);
	ui.lineEdit_stepvalue->setText(str);

	str = QString::number(axisParam.limitN);
	ui.lineEdit_limitN->setText(str);

	str = QString::number(axisParam.limitP);
	ui.lineEdit_limitP->setText(str);

	str = QString::number(axisParam.vel);
	ui.lineEdit_vel->setText(str);

	str = QString::number(axisParam.accTime);
	ui.lineEdit_accTime->setText(str);

	str = QString::number(axisParam.decTime);
	ui.lineEdit_decTime->setText(str);

	str = QString::number(axisParam.sreachhomePos);
	ui.lineEdit_sreachhomePos->setText(str);

	str = QString::number(axisParam.inHomeOffset);
	ui.lineEdit_inHomeOffset->setText(str);

	str = QString::number(axisParam.afterhomeOffset);
	ui.lineEdit_afterhomeOffset->setText(str);

	str = QString::number(axisParam.homeVel);
	ui.lineEdit_homeVel->setText(str);

	str = QString::number(axisParam.homeAccTime);
	ui.lineEdit_homeAccTime->setText(str);

	str = QString::number(axisParam.homeAccTime);
	ui.lineEdit_homeDecTime->setText(str);

	str = QString::number(axisParam.stopTime);
	ui.lineEdit_stopTime->setText(str);

	m_curCardIndex = card;
	m_curAxisIndex = axis;
}

void MotorWidget::onCurItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	QString strText = current->text(0);

	if (strText.contains("Card"))
	{
		int cardIndex = strText.mid(4).toInt();
		qDebug() << cardIndex;

		cardInfo2Widget(cardIndex, 0);	//默认显示选中卡的第一个轴
	}
	else if (strText.contains("Axis"))
	{
		int axisIndex   = strText.mid(4).toInt();

		QString strCard = current->parent()->text(0);
		int cardIndex	= strCard.mid(4).toInt();

		cardInfo2Widget(cardIndex, axisIndex);

		qDebug() << axisIndex;
	}
}

void MotorWidget::widget2CardInfo(int card, int axis)
{
	AxisParam	&axisParam = m_vecCardInfo[m_curCardIndex].vecAxisParam[m_curAxisIndex];
	QString		str, strName;

	axisParam.cardIndex			= card;
	axisParam.axisIndex			= axis;
	axisParam.axisName          = ui.lineEdit_axisName->text();
	axisParam.enable			= !ui.checkBox_disableAxis->isChecked();
	axisParam.motorType		    = ui.comboBox_motortype->currentIndex();
	axisParam.homeSense		    = ui.comboBox_home_sense->currentIndex();
	axisParam.limitMode		    = ui.comboBox_limits_mode->currentIndex();
	axisParam.limitSense		= ui.comboBox_limits_sense->currentIndex();
	axisParam.almMode			= ui.comboBox_alarm_mode->currentIndex();
	axisParam.almSense		    = ui.comboBox_alarm_sense->currentIndex();
	axisParam.homeDir			= ui.comboBox_home_dir->currentIndex();
	axisParam.homeType		    = ui.comboBox_home_mode->currentIndex();
	axisParam.stopMode          = ui.comboBox_stopMode->currentIndex();
	axisParam.stepvalue		    = ui.lineEdit_stepvalue->text().toDouble();
	axisParam.limitN			= ui.lineEdit_limitN->text().toDouble();
	axisParam.limitP			= ui.lineEdit_limitP->text().toDouble();
	axisParam.vel				= ui.lineEdit_vel->text().toDouble();
	axisParam.accTime			= ui.lineEdit_accTime->text().toDouble();
	axisParam.decTime			= ui.lineEdit_decTime->text().toDouble();
	axisParam.sreachhomePos	    = ui.lineEdit_sreachhomePos->text().toDouble();
	axisParam.inHomeOffset		= ui.lineEdit_inHomeOffset->text().toDouble();
	axisParam.afterhomeOffset	= ui.lineEdit_afterhomeOffset->text().toDouble();
	axisParam.homeVel			= ui.lineEdit_homeVel->text().toDouble();
	axisParam.homeAccTime		= ui.lineEdit_homeAccTime->text().toDouble();
	axisParam.homeDecTime		= ui.lineEdit_homeDecTime->text().toDouble();
	axisParam.stopTime          = ui.lineEdit_stopTime->text().toDouble();

	CONFIG_INSTANCE->setCardInfo(m_vecCardInfo);
}

void MotorWidget::enableCtrls(bool enable)
{
	ui.lineEdit_axisName		->setEnabled(enable);
	ui.checkBox_disableAxis		->setEnabled(enable);
	ui.comboBox_motortype		->setEnabled(enable);
	ui.comboBox_home_sense		->setEnabled(enable);
	ui.comboBox_limits_mode	    ->setEnabled(enable);
	ui.comboBox_limits_sense	->setEnabled(enable);
	ui.comboBox_alarm_mode		->setEnabled(enable);
	ui.comboBox_alarm_sense	    ->setEnabled(enable);
	ui.comboBox_home_dir		->setEnabled(enable);
	ui.comboBox_home_mode		->setEnabled(enable);
	ui.comboBox_stopMode        ->setEnabled(enable);
	ui.lineEdit_stepvalue		->setEnabled(enable);
	ui.lineEdit_limitN		    ->setEnabled(enable);
	ui.lineEdit_limitP		    ->setEnabled(enable);
	ui.lineEdit_vel			    ->setEnabled(enable);
	ui.lineEdit_accTime		    ->setEnabled(enable);
	ui.lineEdit_decTime		    ->setEnabled(enable);
	ui.lineEdit_afterhomeOffset ->setEnabled(enable);
	ui.lineEdit_sreachhomePos	->setEnabled(enable);
	ui.lineEdit_inHomeOffset	->setEnabled(enable);
	ui.lineEdit_sreachhomePos	->setEnabled(enable);
	ui.lineEdit_homeVel		    ->setEnabled(enable);
	ui.lineEdit_homeAccTime	    ->setEnabled(enable);
	ui.lineEdit_homeDecTime	    ->setEnabled(enable);
	ui.lineEdit_stopTime        ->setEnabled(enable);
	ui.pushButton_cancel		->setHidden(!enable);
	ui.pushButton_save		    ->setHidden(!enable);
}

void MotorWidget::onCancel()
{
	cardInfo2Widget(m_curCardIndex, m_curAxisIndex);
	ui.treeWidget_card->setEnabled(true);
	enableCtrls(false);
}

void MotorWidget::onSave()
{
	widget2CardInfo(m_curCardIndex, m_curAxisIndex);
	ui.treeWidget_card->setEnabled(true);
	enableCtrls(false);
}

void MotorWidget::onEdit()
{
	ui.treeWidget_card->setEnabled(false);
	enableCtrls(true);
}

void MotorWidget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_timerID){
		if (this->isVisible()){
			updateAxisStatus();
		}	
	}
}

void MotorWidget::onCustomContextMenuRequested(const QPoint& point)
{
	QTreeWidgetItem* curItem = ui.treeWidget_card->itemAt(point);  

	if (curItem == NULL)
	{
		deleteCard->setEnabled(false);
		addCard->setEnabled(true);
		addAxis->setEnabled(false);
		m_menuCard->exec(QCursor::pos());
	}
	else if (curItem->text(0).contains("Card"))
	{
		deleteCard->setEnabled(true);
		addCard->setEnabled(true);
		addAxis->setEnabled(true);
		m_menuCard->exec(QCursor::pos());
	}
	else
	{
		if (-1 == m_copyAxisIndex && -1 == m_copyCardIndex)
		{
			pastePara->setEnabled(false);
		}
		else
		{
			pastePara->setEnabled(true);
		}

		m_menuAxis->exec(QCursor::pos());
	}
}


void MotorWidget::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		initControl();
		nameAction();
		break;
	default:
		break;
	}
}


void MotorWidget::onTreeCardRMenuClicked()
{
	QAction* action = qobject_cast<QAction*>(sender());
	QString objText = action->text();
	qDebug() << objText;


	if (tr("Delete Card") == objText)
	{
		auto iter = m_vecCardInfo.begin();
		m_vecCardInfo.erase(iter);
		updateTreeCtrl();
	}
	else if (tr("Add Card") == objText)
	{
		if (m_curCardIndex >= 7)		//最多8张卡
		{
			return;
		}
		else
		{
			CardInfo info;
			info.bInit = false;
			m_vecCardInfo.push_back(info);
			updateTreeCtrl();
		}
	}
	else if (tr("Add Axis") == objText)
	{
		if (m_vecCardInfo[m_curCardIndex].vecAxisParam.size() >= 7)	//最多8个轴
		{
			return;
		}
		else
		{
			AxisParam info;
			m_vecCardInfo[m_curCardIndex].vecAxisParam.push_back(info);
			updateTreeCtrl();
		}
	}

	CONFIG_INSTANCE->setCardInfo(m_vecCardInfo);
}

void MotorWidget::onTreeAxisRMenuClicked()
{
	QAction* action = qobject_cast<QAction*>(sender());
	QString objText = action->text();
	qDebug() << objText;

	if (tr("Edit Parameter") == objText)
	{
		onEdit();
	}
	else if (tr("Copy Parameter") == objText)
	{
		m_copyCardIndex = m_curCardIndex;
		m_copyAxisIndex = m_curAxisIndex;
	}
	else if (tr("Paste Parameter") == objText)
	{
		QString strInfo = QStringLiteral("复制卡%1轴%2的配置到卡%3轴%4").arg(m_copyCardIndex).arg(m_copyAxisIndex).arg(m_curCardIndex).arg(m_curAxisIndex);
		int rtn = XMessageBox::ask(strInfo);
		if (rtn)
		{
			AxisParam axisParam = m_vecCardInfo[m_copyCardIndex].vecAxisParam[m_copyAxisIndex];
			axisParam.cardIndex = m_curCardIndex;
			axisParam.axisIndex = m_curAxisIndex;
			axisParam.axisName += "_1";
			m_vecCardInfo[m_curCardIndex].vecAxisParam[m_curAxisIndex] = axisParam;
			
			CONFIG_INSTANCE->setCardInfo(m_vecCardInfo);
			cardInfo2Widget(m_curCardIndex, m_curAxisIndex);
		}

	}
	else if (tr("Delete Axis") == objText)
	{
		auto iter = m_vecCardInfo[m_curCardIndex].vecAxisParam.begin();
		m_vecCardInfo[m_curCardIndex].vecAxisParam.erase(iter + m_curAxisIndex);
		CONFIG_INSTANCE->setCardInfo(m_vecCardInfo);
		updateTreeCtrl();
	}

}

void	 MotorWidget::onHomeBtnClicked()
{
	if (MANAGER->isNearPoint("Point_AutoGlue", 0.1))
	{
		XMessageBox::warn(tr("Near the automatic dispensing point, it is prohibited to return to zero"));
		return;
	}

	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();
	qDebug() << objText << "HomeBtnClicked";
	MOTION_INSTANCE->Axis_Home(m_curCardIndex, m_curAxisIndex);
}

void	 MotorWidget::onMoveBtnPressed()
{
	if (MANAGER->isNearPoint("Point_AutoGlue", 0.1))
	{
		XMessageBox::warn(tr("Prohibit shaft movement near automatic dispensing point"));
		return;
	}


	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();

	if (ui.checkBox_Pmove->isChecked())
	{
		return;
	}

	qDebug() << objText << "MoveBtnPressed";

	if ("-" == objText)
	{
		MOTION_INSTANCE->Move_Jog(m_curCardIndex, m_curAxisIndex, 0);
	}
	else if ("+" == objText)
	{
		MOTION_INSTANCE->Move_Jog(m_curCardIndex, m_curAxisIndex, 1);
	}
}

void	 MotorWidget::onMoveBtnRelease()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();

	if (ui.checkBox_Pmove->isChecked())
	{
		return;
	}

	qDebug() << objText << "MoveBtnRelease";

	if ("-" == objText)
	{
		MOTION_INSTANCE->Axis_Stop(m_curCardIndex, m_curAxisIndex,0);
	}
	else if ("+" == objText)
	{
		MOTION_INSTANCE->Axis_Stop(m_curCardIndex, m_curAxisIndex, 0);
	}
}

void	 MotorWidget::onMoveBtnClicked()
{
	if (MANAGER->isNearPoint("Point_AutoGlue", 0.1))
	{
		XMessageBox::warn(tr("Prohibit shaft movement near automatic dispensing point"));
		return;
	}

	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	QString objText = btn->text();

	if (!ui.checkBox_Pmove->isChecked())
	{
		return;
	}

	qDebug() << objText << "Clicked";

	if ("-"==objText)
	{
		double offset = ui.lineEdit_step->text().toDouble();
		MOTION_INSTANCE->Move_Offset(m_curCardIndex, m_curAxisIndex, -offset, 0, 0, 0);
	}
	else if ("+" == objText)
	{
		double offset = ui.lineEdit_step->text().toDouble();
		MOTION_INSTANCE->Move_Offset(m_curCardIndex, m_curAxisIndex, offset, 0, 0, 0);
	}
}

QAction*  MotorWidget::getMenuBarAction(QMenu *menu, QString name)
{
	QList<QAction*> actions = menu->actions();

	for each (auto action in actions)
	{
		QString strTest = action->text();

		if (strTest == name)
		{
			return action;
		}
	}

	return nullptr;
}

void  MotorWidget::onStopBtnClicked()
{
	MOTION_INSTANCE->Axis_Stop(m_curCardIndex, m_curAxisIndex, 0);

	//退出回原动作....
}

void  MotorWidget::onCheckEnableClicked()
{
	MOTION_INSTANCE->writeOutBit_Enable(m_curCardIndex, m_curAxisIndex, ui.checkBox_enable->isChecked()?0:1);
}