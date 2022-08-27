/********************************************************************************
** Form generated from reading UI file 'MotorWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTORWIDGET_H
#define UI_MOTORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MotorWidget
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_11;
    QTreeWidget *treeWidget_card;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_28;
    QLineEdit *lineEdit_axisName;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *checkBox_disableAxis;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label;
    QComboBox *comboBox_motortype;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_23;
    QComboBox *comboBox_limits_mode;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_24;
    QComboBox *comboBox_alarm_mode;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_20;
    QComboBox *comboBox_home_sense;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_2;
    QComboBox *comboBox_limits_sense;
    QHBoxLayout *horizontalLayout_29;
    QLabel *label_25;
    QComboBox *comboBox_alarm_sense;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QLineEdit *lineEdit_stepvalue;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_4;
    QLineEdit *lineEdit_limitN;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_5;
    QLineEdit *lineEdit_limitP;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_11;
    QLineEdit *lineEdit_vel;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QLineEdit *lineEdit_accTime;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QLineEdit *lineEdit_decTime;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_30;
    QLineEdit *lineEdit_stopTime;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_29;
    QComboBox *comboBox_stopMode;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QComboBox *comboBox_home_dir;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QComboBox *comboBox_home_mode;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_6;
    QLineEdit *lineEdit_sreachhomePos;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_14;
    QLineEdit *lineEdit_inHomeOffset;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_8;
    QLineEdit *lineEdit_afterhomeOffset;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_9;
    QLineEdit *lineEdit_homeVel;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_26;
    QLineEdit *lineEdit_homeAccTime;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_27;
    QLineEdit *lineEdit_homeDecTime;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_home;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_22;
    QLabel *label_21;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_pos_to;
    QLabel *label_pos_real;
    QLabel *label_warn;
    QLabel *label_home;
    QLabel *label_plimits;
    QLabel *label_nlimits;
    QLabel *label_inplace;
    QPushButton *pushButton_stop;
    QLineEdit *lineEdit_step;
    QCheckBox *checkBox_Pmove;
    QLabel *label_axisInfo_2;
    QCheckBox *checkBox_enable;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_moven;
    QPushButton *pushButton_movep;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *MotorWidget)
    {
        if (MotorWidget->objectName().isEmpty())
            MotorWidget->setObjectName(QStringLiteral("MotorWidget"));
        MotorWidget->resize(963, 700);
        MotorWidget->setMinimumSize(QSize(780, 550));
        MotorWidget->setMaximumSize(QSize(1900, 700));
        groupBox = new QGroupBox(MotorWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 8, 151, 561));
        verticalLayout_11 = new QVBoxLayout(groupBox);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        treeWidget_card = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_card->setHeaderItem(__qtreewidgetitem);
        treeWidget_card->setObjectName(QStringLiteral("treeWidget_card"));
        treeWidget_card->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_11->addWidget(treeWidget_card);

        groupBox_2 = new QGroupBox(MotorWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(172, 14, 541, 561));
        verticalLayout_13 = new QVBoxLayout(groupBox_2);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QStringLiteral("label_28"));

        horizontalLayout_5->addWidget(label_28);

        lineEdit_axisName = new QLineEdit(groupBox_2);
        lineEdit_axisName->setObjectName(QStringLiteral("lineEdit_axisName"));

        horizontalLayout_5->addWidget(lineEdit_axisName);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        horizontalLayout_8->addLayout(horizontalLayout_5);

        checkBox_disableAxis = new QCheckBox(groupBox_2);
        checkBox_disableAxis->setObjectName(QStringLiteral("checkBox_disableAxis"));

        horizontalLayout_8->addWidget(checkBox_disableAxis);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);


        verticalLayout_12->addLayout(horizontalLayout_8);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setAlignment(Qt::AlignCenter);
        horizontalLayout = new QHBoxLayout(groupBox_4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_24->addWidget(label);

        comboBox_motortype = new QComboBox(groupBox_4);
        comboBox_motortype->setObjectName(QStringLiteral("comboBox_motortype"));

        horizontalLayout_24->addWidget(comboBox_motortype);

        horizontalLayout_24->setStretch(0, 2);
        horizontalLayout_24->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_25->addWidget(label_23);

        comboBox_limits_mode = new QComboBox(groupBox_4);
        comboBox_limits_mode->setObjectName(QStringLiteral("comboBox_limits_mode"));

        horizontalLayout_25->addWidget(comboBox_limits_mode);

        horizontalLayout_25->setStretch(0, 2);
        horizontalLayout_25->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_26->addWidget(label_24);

        comboBox_alarm_mode = new QComboBox(groupBox_4);
        comboBox_alarm_mode->setObjectName(QStringLiteral("comboBox_alarm_mode"));

        horizontalLayout_26->addWidget(comboBox_alarm_mode);

        horizontalLayout_26->setStretch(0, 2);
        horizontalLayout_26->setStretch(1, 3);

        verticalLayout->addLayout(horizontalLayout_26);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_27->addWidget(label_20);

        comboBox_home_sense = new QComboBox(groupBox_4);
        comboBox_home_sense->setObjectName(QStringLiteral("comboBox_home_sense"));

        horizontalLayout_27->addWidget(comboBox_home_sense);

        horizontalLayout_27->setStretch(0, 2);
        horizontalLayout_27->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_27);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_28->addWidget(label_2);

        comboBox_limits_sense = new QComboBox(groupBox_4);
        comboBox_limits_sense->setObjectName(QStringLiteral("comboBox_limits_sense"));

        horizontalLayout_28->addWidget(comboBox_limits_sense);

        horizontalLayout_28->setStretch(0, 2);
        horizontalLayout_28->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_28);

        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_29->addWidget(label_25);

        comboBox_alarm_sense = new QComboBox(groupBox_4);
        comboBox_alarm_sense->setObjectName(QStringLiteral("comboBox_alarm_sense"));

        horizontalLayout_29->addWidget(comboBox_alarm_sense);

        horizontalLayout_29->setStretch(0, 2);
        horizontalLayout_29->setStretch(1, 3);

        verticalLayout_2->addLayout(horizontalLayout_29);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 3);

        verticalLayout_12->addWidget(groupBox_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setAlignment(Qt::AlignCenter);
        verticalLayout_7 = new QVBoxLayout(groupBox_5);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, 3, -1, 3);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_10->addWidget(label_7);

        lineEdit_stepvalue = new QLineEdit(groupBox_5);
        lineEdit_stepvalue->setObjectName(QStringLiteral("lineEdit_stepvalue"));

        horizontalLayout_10->addWidget(lineEdit_stepvalue);

        horizontalLayout_10->setStretch(0, 2);
        horizontalLayout_10->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_11->addWidget(label_4);

        lineEdit_limitN = new QLineEdit(groupBox_5);
        lineEdit_limitN->setObjectName(QStringLiteral("lineEdit_limitN"));

        horizontalLayout_11->addWidget(lineEdit_limitN);

        horizontalLayout_11->setStretch(0, 2);
        horizontalLayout_11->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_12->addWidget(label_5);

        lineEdit_limitP = new QLineEdit(groupBox_5);
        lineEdit_limitP->setObjectName(QStringLiteral("lineEdit_limitP"));

        horizontalLayout_12->addWidget(lineEdit_limitP);

        horizontalLayout_12->setStretch(0, 2);
        horizontalLayout_12->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_13->addWidget(label_11);

        lineEdit_vel = new QLineEdit(groupBox_5);
        lineEdit_vel->setObjectName(QStringLiteral("lineEdit_vel"));

        horizontalLayout_13->addWidget(lineEdit_vel);

        horizontalLayout_13->setStretch(0, 2);
        horizontalLayout_13->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_14->addWidget(label_12);

        lineEdit_accTime = new QLineEdit(groupBox_5);
        lineEdit_accTime->setObjectName(QStringLiteral("lineEdit_accTime"));

        horizontalLayout_14->addWidget(lineEdit_accTime);

        horizontalLayout_14->setStretch(0, 2);
        horizontalLayout_14->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_15->addWidget(label_13);

        lineEdit_decTime = new QLineEdit(groupBox_5);
        lineEdit_decTime->setObjectName(QStringLiteral("lineEdit_decTime"));

        horizontalLayout_15->addWidget(lineEdit_decTime);

        horizontalLayout_15->setStretch(0, 2);
        horizontalLayout_15->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName(QStringLiteral("label_30"));

        horizontalLayout_16->addWidget(label_30);

        lineEdit_stopTime = new QLineEdit(groupBox_5);
        lineEdit_stopTime->setObjectName(QStringLiteral("lineEdit_stopTime"));

        horizontalLayout_16->addWidget(lineEdit_stopTime);

        horizontalLayout_16->setStretch(0, 2);
        horizontalLayout_16->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_29 = new QLabel(groupBox_5);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout_17->addWidget(label_29);

        comboBox_stopMode = new QComboBox(groupBox_5);
        comboBox_stopMode->setObjectName(QStringLiteral("comboBox_stopMode"));

        horizontalLayout_17->addWidget(comboBox_stopMode);

        horizontalLayout_17->setStretch(0, 2);
        horizontalLayout_17->setStretch(1, 3);

        verticalLayout_7->addLayout(horizontalLayout_17);


        horizontalLayout_4->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setAlignment(Qt::AlignCenter);
        verticalLayout_8 = new QVBoxLayout(groupBox_6);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, 3, -1, 3);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_10 = new QLabel(groupBox_6);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_6->addWidget(label_10);

        comboBox_home_dir = new QComboBox(groupBox_6);
        comboBox_home_dir->setObjectName(QStringLiteral("comboBox_home_dir"));

        horizontalLayout_6->addWidget(comboBox_home_dir);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        comboBox_home_mode = new QComboBox(groupBox_6);
        comboBox_home_mode->setObjectName(QStringLiteral("comboBox_home_mode"));

        horizontalLayout_7->addWidget(comboBox_home_mode);

        horizontalLayout_7->setStretch(0, 2);
        horizontalLayout_7->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_18->addWidget(label_6);

        lineEdit_sreachhomePos = new QLineEdit(groupBox_6);
        lineEdit_sreachhomePos->setObjectName(QStringLiteral("lineEdit_sreachhomePos"));

        horizontalLayout_18->addWidget(lineEdit_sreachhomePos);

        horizontalLayout_18->setStretch(0, 2);
        horizontalLayout_18->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_19->addWidget(label_14);

        lineEdit_inHomeOffset = new QLineEdit(groupBox_6);
        lineEdit_inHomeOffset->setObjectName(QStringLiteral("lineEdit_inHomeOffset"));

        horizontalLayout_19->addWidget(lineEdit_inHomeOffset);

        horizontalLayout_19->setStretch(0, 2);
        horizontalLayout_19->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_20->addWidget(label_8);

        lineEdit_afterhomeOffset = new QLineEdit(groupBox_6);
        lineEdit_afterhomeOffset->setObjectName(QStringLiteral("lineEdit_afterhomeOffset"));

        horizontalLayout_20->addWidget(lineEdit_afterhomeOffset);

        horizontalLayout_20->setStretch(0, 2);
        horizontalLayout_20->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_21->addWidget(label_9);

        lineEdit_homeVel = new QLineEdit(groupBox_6);
        lineEdit_homeVel->setObjectName(QStringLiteral("lineEdit_homeVel"));

        horizontalLayout_21->addWidget(lineEdit_homeVel);

        horizontalLayout_21->setStretch(0, 2);
        horizontalLayout_21->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_22->addWidget(label_26);

        lineEdit_homeAccTime = new QLineEdit(groupBox_6);
        lineEdit_homeAccTime->setObjectName(QStringLiteral("lineEdit_homeAccTime"));

        horizontalLayout_22->addWidget(lineEdit_homeAccTime);

        horizontalLayout_22->setStretch(0, 2);
        horizontalLayout_22->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_27 = new QLabel(groupBox_6);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_23->addWidget(label_27);

        lineEdit_homeDecTime = new QLineEdit(groupBox_6);
        lineEdit_homeDecTime->setObjectName(QStringLiteral("lineEdit_homeDecTime"));

        horizontalLayout_23->addWidget(lineEdit_homeDecTime);

        horizontalLayout_23->setStretch(0, 2);
        horizontalLayout_23->setStretch(1, 3);

        verticalLayout_8->addLayout(horizontalLayout_23);


        horizontalLayout_4->addWidget(groupBox_6);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_12->addLayout(horizontalLayout_4);

        verticalLayout_12->setStretch(1, 1);
        verticalLayout_12->setStretch(2, 3);

        verticalLayout_13->addLayout(verticalLayout_12);

        groupBox_3 = new QGroupBox(MotorWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(730, 8, 179, 561));
        pushButton_home = new QPushButton(groupBox_3);
        pushButton_home->setObjectName(QStringLiteral("pushButton_home"));
        pushButton_home->setGeometry(QRect(40, 120, 103, 29));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(8, 260, 163, 287));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_22 = new QLabel(layoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_22);

        label_21 = new QLabel(layoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_21);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_15);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_16);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_17);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_18);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(label_19);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_pos_to = new QLabel(layoutWidget);
        label_pos_to->setObjectName(QStringLiteral("label_pos_to"));
        label_pos_to->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_pos_to);

        label_pos_real = new QLabel(layoutWidget);
        label_pos_real->setObjectName(QStringLiteral("label_pos_real"));
        label_pos_real->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_pos_real);

        label_warn = new QLabel(layoutWidget);
        label_warn->setObjectName(QStringLiteral("label_warn"));
        label_warn->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_warn);

        label_home = new QLabel(layoutWidget);
        label_home->setObjectName(QStringLiteral("label_home"));
        label_home->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_home);

        label_plimits = new QLabel(layoutWidget);
        label_plimits->setObjectName(QStringLiteral("label_plimits"));
        label_plimits->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_plimits);

        label_nlimits = new QLabel(layoutWidget);
        label_nlimits->setObjectName(QStringLiteral("label_nlimits"));
        label_nlimits->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_nlimits);

        label_inplace = new QLabel(layoutWidget);
        label_inplace->setObjectName(QStringLiteral("label_inplace"));
        label_inplace->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_inplace);


        horizontalLayout_2->addLayout(verticalLayout_6);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 2);
        pushButton_stop = new QPushButton(groupBox_3);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(94, 178, 57, 29));
        pushButton_stop->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        lineEdit_step = new QLineEdit(groupBox_3);
        lineEdit_step->setObjectName(QStringLiteral("lineEdit_step"));
        lineEdit_step->setGeometry(QRect(66, 28, 63, 20));
        checkBox_Pmove = new QCheckBox(groupBox_3);
        checkBox_Pmove->setObjectName(QStringLiteral("checkBox_Pmove"));
        checkBox_Pmove->setGeometry(QRect(18, 30, 47, 16));
        label_axisInfo_2 = new QLabel(groupBox_3);
        label_axisInfo_2->setObjectName(QStringLiteral("label_axisInfo_2"));
        label_axisInfo_2->setGeometry(QRect(138, 28, 31, 20));
        label_axisInfo_2->setAlignment(Qt::AlignCenter);
        checkBox_enable = new QCheckBox(groupBox_3);
        checkBox_enable->setObjectName(QStringLiteral("checkBox_enable"));
        checkBox_enable->setGeometry(QRect(34, 186, 47, 16));
        layoutWidget1 = new QWidget(groupBox_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(19, 66, 143, 33));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        pushButton_moven = new QPushButton(layoutWidget1);
        pushButton_moven->setObjectName(QStringLiteral("pushButton_moven"));
        pushButton_moven->setMinimumSize(QSize(0, 30));
        pushButton_moven->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_9->addWidget(pushButton_moven);

        pushButton_movep = new QPushButton(layoutWidget1);
        pushButton_movep->setObjectName(QStringLiteral("pushButton_movep"));
        pushButton_movep->setMinimumSize(QSize(0, 30));
        pushButton_movep->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_9->addWidget(pushButton_movep);

        layoutWidget2 = new QWidget(MotorWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(4, 620, 847, 32));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_save = new QPushButton(layoutWidget2);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_save->sizePolicy().hasHeightForWidth());
        pushButton_save->setSizePolicy(sizePolicy);
        pushButton_save->setMinimumSize(QSize(75, 30));

        horizontalLayout_3->addWidget(pushButton_save);

        pushButton_cancel = new QPushButton(layoutWidget2);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        sizePolicy.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy);
        pushButton_cancel->setMinimumSize(QSize(75, 30));

        horizontalLayout_3->addWidget(pushButton_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        retranslateUi(MotorWidget);
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), MotorWidget, SLOT(onCancel()));
        QObject::connect(pushButton_save, SIGNAL(clicked()), MotorWidget, SLOT(onSave()));

        QMetaObject::connectSlotsByName(MotorWidget);
    } // setupUi

    void retranslateUi(QWidget *MotorWidget)
    {
        MotorWidget->setWindowTitle(QApplication::translate("MotorWidget", "MotorWidget", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MotorWidget", "Motor list", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        label_28->setText(QApplication::translate("MotorWidget", "Axis name", Q_NULLPTR));
        checkBox_disableAxis->setText(QApplication::translate("MotorWidget", "ban", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        label->setText(QApplication::translate("MotorWidget", "Motor type", Q_NULLPTR));
        label_23->setText(QApplication::translate("MotorWidget", "Enable limit", Q_NULLPTR));
        label_24->setText(QApplication::translate("MotorWidget", "Enable Alarm", Q_NULLPTR));
        label_20->setText(QApplication::translate("MotorWidget", "Home sense", Q_NULLPTR));
        label_2->setText(QApplication::translate("MotorWidget", "Limit sense", Q_NULLPTR));
        label_25->setText(QApplication::translate("MotorWidget", "Alarm sense", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MotorWidget", "Work Parameter", Q_NULLPTR));
        label_7->setText(QApplication::translate("MotorWidget", "Step value", Q_NULLPTR));
        label_4->setText(QApplication::translate("MotorWidget", "Negative soft limit", Q_NULLPTR));
        label_5->setText(QApplication::translate("MotorWidget", "positive soft limit", Q_NULLPTR));
        label_11->setText(QApplication::translate("MotorWidget", "Speed", Q_NULLPTR));
        label_12->setText(QApplication::translate("MotorWidget", "Work acc time", Q_NULLPTR));
        label_13->setText(QApplication::translate("MotorWidget", "Work dec time", Q_NULLPTR));
        label_30->setText(QApplication::translate("MotorWidget", "Stop stime", Q_NULLPTR));
        label_29->setText(QApplication::translate("MotorWidget", "Stop mode", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MotorWidget", "Home Parameter", Q_NULLPTR));
        label_10->setText(QApplication::translate("MotorWidget", "Home dir", Q_NULLPTR));
        label_3->setText(QApplication::translate("MotorWidget", "Home type", Q_NULLPTR));
        label_6->setText(QApplication::translate("MotorWidget", "search distance", Q_NULLPTR));
        label_14->setText(QApplication::translate("MotorWidget", "Offset", Q_NULLPTR));
        label_8->setText(QApplication::translate("MotorWidget", "After home offset", Q_NULLPTR));
        label_9->setText(QApplication::translate("MotorWidget", "Home speed", Q_NULLPTR));
        label_26->setText(QApplication::translate("MotorWidget", "Home acc time", Q_NULLPTR));
        label_27->setText(QApplication::translate("MotorWidget", "Home dec time", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MotorWidget", "Axis Debug", Q_NULLPTR));
        pushButton_home->setText(QApplication::translate("MotorWidget", "home", Q_NULLPTR));
        label_22->setText(QApplication::translate("MotorWidget", "target pos", Q_NULLPTR));
        label_21->setText(QApplication::translate("MotorWidget", "current pos", Q_NULLPTR));
        label_15->setText(QApplication::translate("MotorWidget", "servo alarm", Q_NULLPTR));
        label_16->setText(QApplication::translate("MotorWidget", "Origin", Q_NULLPTR));
        label_17->setText(QApplication::translate("MotorWidget", "Positive Limit", Q_NULLPTR));
        label_18->setText(QApplication::translate("MotorWidget", "Negative Limit", Q_NULLPTR));
        label_19->setText(QApplication::translate("MotorWidget", " Position signal", Q_NULLPTR));
        label_pos_to->setText(QApplication::translate("MotorWidget", "0", Q_NULLPTR));
        label_pos_real->setText(QApplication::translate("MotorWidget", "0", Q_NULLPTR));
        label_warn->setText(QString());
        label_home->setText(QString());
        label_plimits->setText(QString());
        label_nlimits->setText(QString());
        label_inplace->setText(QString());
        pushButton_stop->setText(QApplication::translate("MotorWidget", "Stop", Q_NULLPTR));
        checkBox_Pmove->setText(QApplication::translate("MotorWidget", "Jog", Q_NULLPTR));
        label_axisInfo_2->setText(QApplication::translate("MotorWidget", "mm", Q_NULLPTR));
        checkBox_enable->setText(QApplication::translate("MotorWidget", "Enable", Q_NULLPTR));
        pushButton_moven->setText(QApplication::translate("MotorWidget", "-", Q_NULLPTR));
        pushButton_movep->setText(QApplication::translate("MotorWidget", "+", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("MotorWidget", "Save", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("MotorWidget", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MotorWidget: public Ui_MotorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTORWIDGET_H
