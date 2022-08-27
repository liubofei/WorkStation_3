/********************************************************************************
** Form generated from reading UI file 'PointsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTSWIDGET_H
#define UI_POINTSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PointsWidget
{
public:
    QGroupBox *groupBox_pointList;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_pointOpt;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_goto;
    QPushButton *pushButton_getpos;
    QPushButton *pushButton_reload;
    QPushButton *pushButton_stop;

    void setupUi(QWidget *PointsWidget)
    {
        if (PointsWidget->objectName().isEmpty())
            PointsWidget->setObjectName(QStringLiteral("PointsWidget"));
        PointsWidget->resize(961, 610);
        groupBox_pointList = new QGroupBox(PointsWidget);
        groupBox_pointList->setObjectName(QStringLiteral("groupBox_pointList"));
        groupBox_pointList->setGeometry(QRect(10, 12, 781, 541));
        horizontalLayout = new QHBoxLayout(groupBox_pointList);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(groupBox_pointList);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout->addWidget(tableView);

        layoutWidget = new QWidget(PointsWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(4, 566, 849, 35));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_save = new QPushButton(layoutWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setMinimumSize(QSize(80, 30));

        horizontalLayout_2->addWidget(pushButton_save);

        pushButton_cancel = new QPushButton(layoutWidget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(80, 30));

        horizontalLayout_2->addWidget(pushButton_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        groupBox_pointOpt = new QGroupBox(PointsWidget);
        groupBox_pointOpt->setObjectName(QStringLiteral("groupBox_pointOpt"));
        groupBox_pointOpt->setGeometry(QRect(805, 14, 141, 537));
        verticalLayout = new QVBoxLayout(groupBox_pointOpt);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_goto = new QPushButton(groupBox_pointOpt);
        pushButton_goto->setObjectName(QStringLiteral("pushButton_goto"));
        pushButton_goto->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(pushButton_goto);

        pushButton_getpos = new QPushButton(groupBox_pointOpt);
        pushButton_getpos->setObjectName(QStringLiteral("pushButton_getpos"));
        pushButton_getpos->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(pushButton_getpos);

        pushButton_reload = new QPushButton(groupBox_pointOpt);
        pushButton_reload->setObjectName(QStringLiteral("pushButton_reload"));
        pushButton_reload->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(pushButton_reload);

        pushButton_stop = new QPushButton(groupBox_pointOpt);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setMinimumSize(QSize(0, 40));

        verticalLayout->addWidget(pushButton_stop);


        retranslateUi(PointsWidget);
        QObject::connect(pushButton_goto, SIGNAL(clicked()), PointsWidget, SLOT(onGoto()));
        QObject::connect(pushButton_getpos, SIGNAL(clicked()), PointsWidget, SLOT(onGetPos()));
        QObject::connect(pushButton_reload, SIGNAL(clicked()), PointsWidget, SLOT(onReLoad()));
        QObject::connect(pushButton_save, SIGNAL(clicked()), PointsWidget, SLOT(onSave()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), PointsWidget, SLOT(onCancel()));

        QMetaObject::connectSlotsByName(PointsWidget);
    } // setupUi

    void retranslateUi(QWidget *PointsWidget)
    {
        PointsWidget->setWindowTitle(QApplication::translate("PointsWidget", "PointsWidget", Q_NULLPTR));
        groupBox_pointList->setTitle(QApplication::translate("PointsWidget", "Point list", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("PointsWidget", "Save", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("PointsWidget", "Cancel", Q_NULLPTR));
        groupBox_pointOpt->setTitle(QApplication::translate("PointsWidget", "Debug", Q_NULLPTR));
        pushButton_goto->setText(QApplication::translate("PointsWidget", "Location", Q_NULLPTR));
        pushButton_getpos->setText(QApplication::translate("PointsWidget", "Teach", Q_NULLPTR));
        pushButton_reload->setText(QApplication::translate("PointsWidget", "ReLoad", Q_NULLPTR));
        pushButton_stop->setText(QApplication::translate("PointsWidget", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PointsWidget: public Ui_PointsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTSWIDGET_H
