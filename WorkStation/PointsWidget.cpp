#include "PointsWidget.h"
#include "../WorkFlow/WorkFlow/WorkFlow.h"
#include "../Utility/XMessageBox/XMessageBox.h"
#include "../Utility/System/Config.h"
#include "../WorkFlow/WorkFlow/WorkFlow.h"
#include "../Motion/Motion_dmc/CardInterfaceManager.h"
#include <QStandardItemModel>


PointsWidget::PointsWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initData();
	iniUI();
	pointInfo2Widget(m_vRunPoint);
}

PointsWidget::~PointsWidget()
{

}

void	PointsWidget::initData()
{
	m_bEditing = false;
	CONFIG_INSTANCE->getRunPointInfo(m_vRunPoint);
	m_vTemp = m_vRunPoint;
	m_tableModel = new QStandardItemModel(0, 7, this);
}

void	PointsWidget::iniUI()
{
	QStringList header;
	header << QStringLiteral("Ãû³Æ") << QStringLiteral("ÃèÊö") << "X" << "Y" << "Z" << "U" << "V";
	m_tableModel->setHorizontalHeaderLabels(header);

	ui.tableView->setModel(m_tableModel);
	ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui.tableView->setAlternatingRowColors(true);

	connect(m_tableModel, &QStandardItemModel::itemChanged, this, &PointsWidget::onItemChanged);

	ui.pushButton_save->setVisible(false);
	ui.pushButton_cancel->setVisible(false);
}

void	 PointsWidget::pointInfo2Widget(const QVector<RunPoint> &vpt)
{
	m_tableModel->setRowCount(vpt.size());
	QStandardItem *item1, *item2, *itemX, *itemY, *itemZ, *itemU, *itemV;
	for (int i = 0; i < vpt.size(); i++)
	{
		QString str, str1, str2, str3, str4, str5;
		if (!vpt[i].dimension.axisNameX.isEmpty()){
			str = QString("%1:%2").arg(vpt[i].dimension.axisNameX).arg(vpt[i].pos[0]);
		}
		if (!vpt[i].dimension.axisNameY.isEmpty()){
			str1 = QString("%1:%2").arg(vpt[i].dimension.axisNameY).arg(vpt[i].pos[1]);
		}
		if (!vpt[i].dimension.axisNameZ.isEmpty()){
			str2 = QString("%1:%2").arg(vpt[i].dimension.axisNameZ).arg(vpt[i].pos[2]);
		}
		if (!vpt[i].dimension.axisNameU.isEmpty()){
			str3 = QString("%1:%2").arg(vpt[i].dimension.axisNameU).arg(vpt[i].pos[3]);
		}
		if (!vpt[i].dimension.axisNameV.isEmpty()){
			str4 = QString("%1:%2").arg(vpt[i].dimension.axisNameV).arg(vpt[i].pos[4]);
		}

		item1 = new QStandardItem(vpt[i].name);
		item2 = new QStandardItem(vpt[i].desc);
		itemX = new QStandardItem(str);
		itemY = new QStandardItem(str1);
		itemZ = new QStandardItem(str2);
		itemU = new QStandardItem(str3);
		itemV = new QStandardItem(str4);
		item1->setEditable(false);
		item2->setEditable(false);
		
		m_tableModel->setItem(i, 0, item1);
		m_tableModel->setItem(i, 1, item2);
		m_tableModel->setItem(i, 2, itemX);
		m_tableModel->setItem(i, 3, itemY);
		m_tableModel->setItem(i, 4, itemZ);
		m_tableModel->setItem(i, 5, itemU);
		m_tableModel->setItem(i, 6, itemV);
	}
}

void PointsWidget::onGoto()
{
	QString strError;
	QModelIndex index = ui.tableView->currentIndex();
	if (index.row() == -1){
		XMessageBox::warn(tr("Please select a point"));
		return;
	}
	else if (index.row() > m_vRunPoint.size()){
		return;
	}


	RunPoint point = m_vTemp[index.row()];
	MANAGER->pointSafeMoveAsync(point);
}

void PointsWidget::onGetPos()
{
	QString strError;
	QModelIndex index = ui.tableView->currentIndex();

	if (index.row() == -1){
		XMessageBox::warn(tr("Please select a point"));
		return;
	}
	else if (index.row() > m_vRunPoint.size()){
		return;
	}

	RunPoint pt = m_vRunPoint[index.row()];

	if (!pt.dimension.axisNameX.isEmpty())
		pt.pos[0] = MANAGER->getAxisPos(pt.dimension.axisNameX);
	if (!pt.dimension.axisNameY.isEmpty())
		pt.pos[1] = MANAGER->getAxisPos(pt.dimension.axisNameY);
	if (!pt.dimension.axisNameZ.isEmpty())
		pt.pos[2] = MANAGER->getAxisPos(pt.dimension.axisNameZ);
	if (!pt.dimension.axisNameU.isEmpty())
		pt.pos[3] = MANAGER->getAxisPos(pt.dimension.axisNameU);
	if (!pt.dimension.axisNameV.isEmpty())
		pt.pos[4] = MANAGER->getAxisPos(pt.dimension.axisNameV);
	
	m_vTemp[index.row()] = pt;
	pointInfo2Widget(m_vTemp);
}

void PointsWidget::onSave()
{
	CONFIG_INSTANCE->setPointInfo(m_vTemp);
	m_vRunPoint = m_vTemp;
	ui.pushButton_save->setVisible(false);
	ui.pushButton_cancel->setVisible(false);
	ui.pushButton_getpos->setEnabled(true);
	ui.pushButton_goto->setEnabled(true);
	ui.pushButton_stop->setEnabled(true);
	m_bEditing = false;
}

void PointsWidget::onReLoad()
{
	CONFIG_INSTANCE->getRunPointInfo(m_vRunPoint);
	onCancel();
}

void PointsWidget::onCancel()
{
	pointInfo2Widget(m_vRunPoint);
	ui.pushButton_save->setVisible(false);
	ui.pushButton_cancel->setVisible(false);
	ui.pushButton_getpos->setEnabled(true);
	ui.pushButton_goto->setEnabled(true);
	ui.pushButton_stop->setEnabled(true);
}

void PointsWidget::onItemChanged(QStandardItem *item)
{
	if (isVisible()){
		m_bEditing = true;
		ui.pushButton_save->setVisible(true);
		ui.pushButton_cancel->setVisible(true);
		ui.pushButton_getpos->setEnabled(false);
		ui.pushButton_goto->setEnabled(false);
		ui.pushButton_stop->setEnabled(false);

		RunPoint pt = m_vTemp[item->row()];
		int col = item->column();

		if (!item->text().isEmpty()){
			QStringList lst = item->text().split(':');
			if (lst.size() == 2){
				if (2 == col){
					pt.dimension.axisNameX = lst[0];
					pt.pos[0] = lst[1].toDouble();
				}
				else if (3 == col){
					pt.dimension.axisNameY = lst[0];
					pt.pos[1] = lst[1].toDouble();
				}
				else if (4 == col){
					pt.dimension.axisNameZ = lst[0];
					pt.pos[2] = lst[1].toDouble();
				}
				else if (5 == col){
					pt.dimension.axisNameU = lst[0];
					pt.pos[3] = lst[1].toDouble();
				}
				else if (6 == col){
					pt.dimension.axisNameV = lst[0];
					pt.pos[4] = lst[1].toDouble();
				}

				m_vTemp[item->row()] = pt;
				return;
			}
		}

		if (2 == col){
			pt.dimension.axisNameX = "";
			pt.pos[0] = 0;
		}
		else if (3 == col){
			pt.dimension.axisNameY = "";
			pt.pos[1] = 0;
		}
		else if (4 == col){
			pt.dimension.axisNameZ = "";
			pt.pos[2] = 0;
		}
		else if (5 == col){
			pt.dimension.axisNameU = "";
			pt.pos[3] = 0;
		}
		else if (6 == col){
			pt.dimension.axisNameV = "";
			pt.pos[4] = 0;
		}

		m_vTemp[item->row()] = pt;

			
		
	}
}

void PointsWidget::changeEvent(QEvent* event)
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

