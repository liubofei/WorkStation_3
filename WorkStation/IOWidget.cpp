#include "IOWidget.h"
#include "../../include/Motion.h"
#include "../../Motion/Motion_dmc/Motion_dmc.h"
#include "../../Utility/Utility/Utility.h"
#include "../../Utility/System/Config.h"
#include "../../Utility/XMessageBox/XMessageBox.h"
#include <QMenu>

IOWidget::IOWidget(QWidget *parent)
	: QWidget(parent), m_timerID(-1)
{
	ui.setupUi(this);

	m_leftSpace   = 10;
	m_RightSpace  = 10;
	m_TopSpace    = 20;
	m_BottomSpace = 20;
	m_ColumnSpace = 20;
	m_RowSpace    = 10;
	m_BtnWidth    = 140;
	m_BtnHeight   = 30;

	CONFIG_INSTANCE->getInputInfo(m_vecInputInfo);
	CONFIG_INSTANCE->getOutputInfo(m_vecOutputInfo);

	updateWidgetSize();
	updateIOButton();
	initConfigWidget();

	ui.tabWidget->setCurrentIndex(0);
	m_timerID = this->startTimer(50);
}

IOWidget::~IOWidget()
{
	qDebug() << "~IOWidget()";
}

void IOWidget::updateIOButton()
{
	if (m_timerID > 0)
	{
		killTimer(m_timerID);
	}
	
	//1.释放以前的按钮对象
	for (int i = 0; i < m_vecInputBtn.size();i++)
	{
		if (m_vecInputBtn[i] != nullptr)
		{
			delete m_vecInputBtn[i];
		}
	}

	for (int i = 0; i < m_vecOutputBtn.size(); i++)
	{
		disconnect(m_vecOutputBtn[i], &QPushButton::clicked, this, &IOWidget::onOutBtnClicked);

		if (m_vecOutputBtn[i] != nullptr)
		{
			delete m_vecOutputBtn[i];
		}
	}

	//2.删除以前的元素
	m_vecInputBtn.clear();
	m_vecOutputBtn.clear();

	//3.重新创建按钮
	for (int i = 0; i < m_vecInputInfo.size(); i++)
	{
		QToolButton *btn = new QToolButton(ui.widget_in);
		m_vecInputBtn.push_back(btn);
		btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
		btn->setStyleSheet("border: none;margin:0px;");
		btn->setIcon(QIcon(":/WorkStation/gray.png"));
		btn->setText(m_vecInputInfo[i].name);
		btn->setIconSize(QSize(32, 32));
	}

	for (int i = 0; i < m_vecOutputInfo.size(); i++)
	{
		BtnData*  pbtnData = new BtnData(i);
		QPushButton *btn = new QPushButton(ui.widget_out);
		m_vecOutputBtn.push_back(btn);
		btn->setStyleSheet("background-color:rgb(0, 0, 255)");
		btn->setUserData(Qt::UserRole, pbtnData);
		btn->setText(m_vecOutputInfo[i].name);
		connect(btn, &QPushButton::clicked, this, &IOWidget::onOutBtnClicked);
	}

	//4.输入按钮布局
	QMap<int, int>::iterator iter = m_mapInputGroup.begin();

	for (int group = 0; group < m_mapInputGroup.size(); group++)
	{
		for (int i = 0,row = 0; i < m_vecInputInfo.size(); i++)
		{
			if (m_vecInputInfo[i].group == iter.key())
			{
				QRect rect;
				rect.setX(m_leftSpace + group*(m_BtnWidth + m_ColumnSpace));
				rect.setY(m_TopSpace +  row*(m_BtnHeight + m_RowSpace));
				rect.setWidth(m_BtnWidth);
				rect.setHeight(m_BtnHeight);
				m_vecInputBtn[i]->setGeometry(rect);

				row++;
			}			
		}

		iter++;
	}

	//4.输出按钮布局
	iter = m_mapOutputGroup.begin();

	for (int group = 0; group < m_mapOutputGroup.size(); group++)
	{

		for (int i = 0, row = 0; i < m_vecOutputInfo.size(); i++)
		{
			if (m_vecOutputInfo[i].group == iter.key())
			{
				QRect rect;
				rect.setX(m_leftSpace + group*(m_BtnWidth + m_ColumnSpace));
				rect.setY(m_TopSpace +  row*(m_BtnHeight + m_RowSpace));
				rect.setWidth(m_BtnWidth);
				rect.setHeight(m_BtnHeight);
				m_vecOutputBtn[i]->setGeometry(rect);

				row++;
			}
		}

		iter++;
	}

	//重启定时器
	m_timerID = this->startTimer(50);
}

void IOWidget::updateWidgetSize()
{
	int		maxInputCnt = 0;
	int		maxOutputCnt = 0;

	//输入分组信息
	m_mapInputGroup.clear();
	for (int i = 0; i < m_vecInputInfo.size();i++)
	{
		if (m_mapInputGroup.find(m_vecInputInfo[i].group) == m_mapInputGroup.end())
			m_mapInputGroup[m_vecInputInfo[i].group] = 1;
		else	
			m_mapInputGroup[m_vecInputInfo[i].group] += 1;	
	}

	//最长的一组
	for (int i = 0; i < m_mapInputGroup.size(); i++)
	{
		maxInputCnt = std::max(m_mapInputGroup[i], maxInputCnt);
	}

	//输入分组信息
	m_mapOutputGroup.clear();
	for (int i = 0; i < m_vecOutputInfo.size(); i++)
	{
		if (m_mapOutputGroup.find(m_vecOutputInfo[i].group) == m_mapOutputGroup.end())
			m_mapOutputGroup[m_vecOutputInfo[i].group] = 1;
		else
			m_mapOutputGroup[m_vecOutputInfo[i].group] += 1;
	}

	//最长的一组
	for (int i = 0; i < m_mapOutputGroup.size(); i++)
	{
		maxOutputCnt = std::max(m_mapOutputGroup[i], maxOutputCnt);
	}

	int inputWidth = m_leftSpace + m_RightSpace 
		+ m_mapInputGroup.size()*m_BtnWidth
		+ (m_mapInputGroup.size() - 1)*m_ColumnSpace;
	
	int inputHeight = m_TopSpace + m_BottomSpace 
		+ maxInputCnt*m_BtnHeight
		+ (maxInputCnt - 1)*m_RowSpace;

	int outputWidth = m_leftSpace + m_RightSpace 
		+ m_mapOutputGroup.size()*m_BtnWidth
		+ (m_mapOutputGroup.size() - 1)*m_ColumnSpace;

	int outputHeight = m_TopSpace + m_BottomSpace
		+ maxOutputCnt*m_BtnHeight
		+ (maxOutputCnt - 1)*m_RowSpace;

	ui.widget_in ->setFixedSize(inputWidth, std::max(inputHeight, outputHeight));
	ui.widget_out->setFixedSize(outputWidth, std::max(inputHeight, outputHeight));
}

void IOWidget::initConfigWidget()
{
	QStringList strCardType,strCardList,strCanList,strIOList;

	strCardType << QStringLiteral("控制卡") << QStringLiteral("IO0640") << QStringLiteral("Can总线");
	
	for (int i = 0; i < 8;i++)
	{
		strCardList.append(QString::number(i));
		strCanList.append(QString::number(i));
	}

	for (int i = 0; i < 48;i++)
	{
		strIOList.append(QString::number(i));
	}

	ui.radioButton_in    ->setChecked(true);
	ui.comboBox_cardtype ->addItems(strCardType);
	ui.comboBox_cardindex->addItems(strCardList);
	ui.comboBox_card_node->addItems(strCanList);
	ui.comboBox_IOIndex  ->addItems(strIOList);

	ui.comboBox_sense    ->addItem(QStringLiteral("高电平"));
	ui.comboBox_sense    ->addItem(QStringLiteral("低电平"));

	for (int i = 0; i < 5;i++)
	{
		ui.comboBox_group->addItem(QString::number(i));
	}

	ui.listWidget_IO     ->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui.listWidget_IO,  &QListWidget::customContextMenuRequested, this, &IOWidget::onCustomContextMenuRequested);
	connect(ui.listWidget_IO,  &QListWidget::itemSelectionChanged,		 this, &IOWidget::onListItemCliecked);
	connect(ui.radioButton_in, &QRadioButton::toggled,					 this, &IOWidget::updateConfigInfo);

	updateConfigInfo();
	enableCtrls(false);
}

void IOWidget::onCustomContextMenuRequested(const QPoint& pos)
{
	QListWidgetItem* curItem = ui.listWidget_IO->itemAt(pos);

	if (curItem != nullptr)
	{
		QMenu *menu = new QMenu(ui.listWidget_IO);
		menu->addAction(QStringLiteral("修改"), this, &IOWidget::onMenuClicked);
		menu->addAction(QStringLiteral("删除"), this, &IOWidget::onMenuClicked);
		menu->addAction(QStringLiteral("增加"), this, &IOWidget::onMenuClicked);
		menu->exec(QCursor::pos());
	}
	else
	{
		QMenu *menu = new QMenu(ui.listWidget_IO);
		menu->addAction(QStringLiteral("增加"), this, &IOWidget::onMenuClicked);
		menu->exec(QCursor::pos());
	}
}

void IOWidget::onListItemCliecked()
{
	int row = ui.listWidget_IO->currentRow();
	if (ui.radioButton_in->isChecked())
		IOInfo2Widget(m_vecInputInfo[row]);	
	else	
		IOInfo2Widget(m_vecOutputInfo[row]);
}

void IOWidget::onMenuClicked()
{
	QAction* action = qobject_cast<QAction*>(sender());
	QString objText = action->text();

	if (QStringLiteral("修改") == objText)
	{
		m_bNewInfo = false;
		enableCtrls(true);
	}
	else if (QStringLiteral("删除") == objText)
	{
		deleteIOInfo();
	}
	else if (QStringLiteral("增加") == objText)
	{
		m_bNewInfo = true;
		enableCtrls(true);
		addIOInfo();
	}
}

void IOWidget::onBtnCancelClicked()
{
	int row = ui.listWidget_IO->currentRow();

	ui.listWidget_IO->setEnabled(true);

	enableCtrls(false);

	if (ui.radioButton_in->isChecked())
		IOInfo2Widget(m_vecInputInfo[row]);	
	else	
		IOInfo2Widget(m_vecOutputInfo[row]);	
}

void IOWidget::onBtnSaveClicked()
{
	//新增查重
	if (m_bNewInfo)
	{
		if (ui.radioButton_in->isChecked())
		{
			for (int i = 0; i < m_vecInputInfo.size(); i++)
			{
				if (m_vecInputInfo[i].name == ui.lineEdit_name->text())
				{
					if (i == ui.listWidget_IO->currentRow() && false == m_bNewInfo)				
						continue;					
					else
					{
						XMessageBox::error(tr("The name already exists, please enter it again!"));
						return;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < m_vecOutputInfo.size(); i++)
			{
				if (m_vecOutputInfo[i].name == ui.lineEdit_name->text())
				{
					if (i == ui.listWidget_IO->currentRow() && false == m_bNewInfo)					
						continue;				
					else
					{
						XMessageBox::error(tr("The name already exists, please enter it again!"));
						return;
					}
				}
			}
		}
	}


	// 新增配置
	if (m_bNewInfo)
	{
		IOInfo info;
		Widget2IOInfo(info);
		
		if (ui.radioButton_in->isChecked())
		{
			m_vecInputInfo.push_back(info);
			CONFIG_INSTANCE->setInputInfo(m_vecInputInfo);
		}
		else
		{
			m_vecOutputInfo.push_back(info);
			CONFIG_INSTANCE->setOutputInfo(m_vecOutputInfo);
		}
	}
	//修改配置
	else
	{
		int row = ui.listWidget_IO->currentRow();

		if (ui.radioButton_in->isChecked())
		{
			Widget2IOInfo(m_vecInputInfo[row]);
			CONFIG_INSTANCE->setInputInfo(m_vecInputInfo);
		}
		else
		{
			Widget2IOInfo(m_vecOutputInfo[row]);
			CONFIG_INSTANCE->setOutputInfo(m_vecOutputInfo);
		}
	}

	updateConfigInfo();
	updateWidgetSize();
	updateIOButton();
	enableCtrls(false);
}

void IOWidget::onOutBtnClicked()
{
	QPushButton *pButton = qobject_cast<QPushButton *>(this->sender());
	BtnData *pData = (BtnData *)(pButton->userData(Qt::UserRole));
	int   nID = pData->nID;
	if (nID < 0 || nID >= m_vecOutputInfo.size()) return;

	short val = 0;
	MOTION_INSTANCE->ReadOutBit(m_vecOutputInfo[nID].cardIndex, m_vecOutputInfo[nID].cardNode, m_vecOutputInfo[nID].ioIndex, val, m_vecOutputInfo[nID].cardType);
	MOTION_INSTANCE->writeOutBit(m_vecOutputInfo[nID].cardIndex, m_vecOutputInfo[nID].cardNode, m_vecOutputInfo[nID].ioIndex, !val, m_vecOutputInfo[nID].cardType);
}

void IOWidget::enableCtrls(bool enable)
{
	ui.lineEdit_name     ->setEnabled(enable);
	ui.comboBox_cardtype ->setEnabled(enable);
	ui.comboBox_cardindex->setEnabled(enable);
	ui.comboBox_card_node->setEnabled(enable);
	ui.comboBox_IOIndex  ->setEnabled(enable);
	ui.comboBox_sense    ->setEnabled(enable);
	ui.comboBox_group	 ->setEnabled(enable);
	ui.listWidget_IO     ->setEnabled(!enable);
	ui.radioButton_in    ->setEnabled(!enable);
	ui.radioButton_out   ->setEnabled(!enable);
	ui.pushButton_cancel ->setHidden(!enable);
	ui.pushButton_save   ->setHidden(!enable);
}


void IOWidget::updateIOStatus()
{
	short val = 0;

	for (int i = 0; i <m_vecInputInfo.size(); i++)
	{
		MOTION_INSTANCE->ReadInBit(m_vecInputInfo[i].cardIndex, m_vecInputInfo[i].cardNode, m_vecInputInfo[i].ioIndex, val, m_vecInputInfo[i].cardType);
		
		val = (m_vecInputInfo[i].sense == val ? 1 : 0);

		if (0 == val)	
			m_vecInputBtn[i]->setIcon(QIcon(":/WorkStation/gray.png"));	
		else	
			m_vecInputBtn[i]->setIcon(QIcon(":/WorkStation/green.png"));		
	}

	for (int i = 0; i < m_vecOutputInfo.size(); i++)
	{
		MOTION_INSTANCE->ReadOutBit(m_vecOutputInfo[i].cardIndex, m_vecOutputInfo[i].cardNode, m_vecOutputInfo[i].ioIndex, val, m_vecOutputInfo[i].cardType);
		
		val = (m_vecOutputInfo[i].sense == val ? 1 : 0);

		if (0 == val)	
			m_vecOutputBtn[i]->setStyleSheet("background-color:rgb(180,180,180)");	
		else	
			m_vecOutputBtn[i]->setStyleSheet("background-color:rgb(38,181,217)");		
	}
}

void IOWidget::updateConfigInfo()
{
	bool mode = ui.radioButton_in->isChecked() ? true : false;

	disconnect(ui.listWidget_IO, &QListWidget::customContextMenuRequested, this, &IOWidget::onCustomContextMenuRequested);
	disconnect(ui.listWidget_IO, &QListWidget::itemSelectionChanged, this, &IOWidget::onListItemCliecked);
	ui.listWidget_IO->clear();
	connect(ui.listWidget_IO, &QListWidget::customContextMenuRequested, this, &IOWidget::onCustomContextMenuRequested);
	connect(ui.listWidget_IO, &QListWidget::itemSelectionChanged, this, &IOWidget::onListItemCliecked);
	if (mode)
	{
		for each (auto &var in m_vecInputInfo)	
			ui.listWidget_IO->addItem(var.name);	
	}
	else
	{
		for each (auto &var in m_vecOutputInfo)	
			ui.listWidget_IO->addItem(var.name);		
	}
}


void IOWidget::addIOInfo()
{
	IOInfo info;
	IOInfo2Widget(info);
}

void IOWidget::deleteIOInfo()
{
	int row = ui.listWidget_IO->currentRow();
	if (ui.radioButton_in->isChecked())
	{
		auto iter = m_vecInputInfo.begin();
		m_vecInputInfo.erase(iter + row);
		CONFIG_INSTANCE->setInputInfo(m_vecInputInfo);
	}
	else
	{
		auto iter = m_vecOutputInfo.begin();
		m_vecOutputInfo.erase(iter + row);
		CONFIG_INSTANCE->setOutputInfo(m_vecOutputInfo);
	}

	updateConfigInfo();
	updateWidgetSize();
	updateIOButton();
}

void IOWidget::IOInfo2Widget(IOInfo &info)
{
	ui.lineEdit_name		->setText(info.name);
	ui.comboBox_cardtype	->setCurrentIndex(info.cardType);
	ui.comboBox_cardindex	->setCurrentIndex(info.cardIndex);
	ui.comboBox_card_node	->setCurrentIndex(info.cardNode);
	ui.comboBox_IOIndex		->setCurrentIndex(info.ioIndex);
	ui.comboBox_sense		->setCurrentIndex(info.sense);
	ui.comboBox_group		->setCurrentIndex(info.group);

}

void IOWidget::Widget2IOInfo(IOInfo &info)
{
	info.name		= ui.lineEdit_name->text();
	info.cardType	= ui.comboBox_cardtype->currentIndex();
	info.cardIndex	= ui.comboBox_cardindex->currentIndex();
	info.cardNode	= ui.comboBox_card_node->currentIndex();
	info.ioIndex	= ui.comboBox_IOIndex->currentIndex();
	info.sense		= ui.comboBox_sense->currentIndex();
	info.group		= ui.comboBox_group->currentIndex();
}

void IOWidget::timerEvent(QTimerEvent *event)
{
	if (event->timerId() == m_timerID && this->isVisible())
		updateIOStatus();
}

void IOWidget::changeEvent(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::LanguageChange:
		ui.retranslateUi(this);
		break;
	default:
		break;
	}
}