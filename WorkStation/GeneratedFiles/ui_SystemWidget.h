/********************************************************************************
** Form generated from reading UI file 'SystemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMWIDGET_H
#define UI_SYSTEMWIDGET_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemWidget
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_edit;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_reload;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_50;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_35;
    QLineEdit *lineEdit_feed_z_offset;
    QSpacerItem *horizontalSpacer_26;
    QHBoxLayout *horizontalLayout_49;
    QLabel *label_36;
    QLineEdit *lineEdit_feed_max_tray_num;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_35;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_lowSpeed;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_midSpeed;
    QHBoxLayout *horizontalLayout_36;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *lineEdit_hightSpeed;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit_saveZ;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_54;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_41;
    QLineEdit *lineEdit_tray_row_space;
    QSpacerItem *horizontalSpacer_29;
    QHBoxLayout *horizontalLayout_55;
    QLabel *label_43;
    QLineEdit *lineEdit_tray_col_space;
    QHBoxLayout *horizontalLayout_56;
    QHBoxLayout *horizontalLayout_57;
    QLabel *label_44;
    QLineEdit *lineEdit_tray_row_num;
    QSpacerItem *horizontalSpacer_30;
    QHBoxLayout *horizontalLayout_58;
    QLabel *label_45;
    QLineEdit *lineEdit_tray_col_num;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_safeBar;
    QCheckBox *checkBox_safeDoor;
    QCheckBox *checkBox_enbleBuzzing;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *checkBox_wipeNozzleModule;
    QCheckBox *checkBox_visionProtect;
    QCheckBox *checkBox_XYAngleAffine;
    QHBoxLayout *horizontalLayout_66;
    QCheckBox *checkBox_showTrack;
    QCheckBox *checkBox_dryrun;
    QCheckBox *checkBox_enableMakeBar;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *checkBox_enableV0Command;
    QCheckBox *checkBox_enableRCommand;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QComboBox *comboBox_laser_version;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QComboBox *comboBox_vision_version;

    void setupUi(QWidget *SystemWidget)
    {
        if (SystemWidget->objectName().isEmpty())
            SystemWidget->setObjectName(QStringLiteral("SystemWidget"));
        SystemWidget->resize(916, 626);
        layoutWidget = new QWidget(SystemWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 500, 801, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_edit = new QPushButton(layoutWidget);
        pushButton_edit->setObjectName(QStringLiteral("pushButton_edit"));
        pushButton_edit->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_edit);

        pushButton_save = new QPushButton(layoutWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_save);

        pushButton_cancel = new QPushButton(layoutWidget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_cancel);

        pushButton_reload = new QPushButton(layoutWidget);
        pushButton_reload->setObjectName(QStringLiteral("pushButton_reload"));
        pushButton_reload->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_reload);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        groupBox_12 = new QGroupBox(SystemWidget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(20, 20, 431, 71));
        groupBox_12->setMinimumSize(QSize(0, 0));
        groupBox_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_5 = new QVBoxLayout(groupBox_12);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_50 = new QHBoxLayout();
        horizontalLayout_50->setSpacing(6);
        horizontalLayout_50->setObjectName(QStringLiteral("horizontalLayout_50"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_35 = new QLabel(groupBox_12);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setMinimumSize(QSize(80, 0));

        horizontalLayout_26->addWidget(label_35);

        lineEdit_feed_z_offset = new QLineEdit(groupBox_12);
        lineEdit_feed_z_offset->setObjectName(QStringLiteral("lineEdit_feed_z_offset"));
        lineEdit_feed_z_offset->setMinimumSize(QSize(60, 0));
        lineEdit_feed_z_offset->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_26->addWidget(lineEdit_feed_z_offset);


        horizontalLayout_50->addLayout(horizontalLayout_26);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_50->addItem(horizontalSpacer_26);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QStringLiteral("horizontalLayout_49"));
        label_36 = new QLabel(groupBox_12);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setMinimumSize(QSize(80, 0));

        horizontalLayout_49->addWidget(label_36);

        lineEdit_feed_max_tray_num = new QLineEdit(groupBox_12);
        lineEdit_feed_max_tray_num->setObjectName(QStringLiteral("lineEdit_feed_max_tray_num"));
        lineEdit_feed_max_tray_num->setMinimumSize(QSize(60, 0));
        lineEdit_feed_max_tray_num->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_49->addWidget(lineEdit_feed_max_tray_num);


        horizontalLayout_50->addLayout(horizontalLayout_49);

        horizontalLayout_50->setStretch(0, 9);
        horizontalLayout_50->setStretch(1, 1);
        horizontalLayout_50->setStretch(2, 9);

        verticalLayout_5->addLayout(horizontalLayout_50);

        groupBox = new QGroupBox(SystemWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 230, 431, 110));
        groupBox->setMinimumSize(QSize(0, 110));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(85, 0));
        label->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(label);

        lineEdit_lowSpeed = new QLineEdit(groupBox);
        lineEdit_lowSpeed->setObjectName(QStringLiteral("lineEdit_lowSpeed"));
        lineEdit_lowSpeed->setMinimumSize(QSize(60, 0));
        lineEdit_lowSpeed->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(lineEdit_lowSpeed);


        horizontalLayout_35->addLayout(horizontalLayout_3);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_35->addItem(horizontalSpacer_14);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(85, 0));
        label_2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_4->addWidget(label_2);

        lineEdit_midSpeed = new QLineEdit(groupBox);
        lineEdit_midSpeed->setObjectName(QStringLiteral("lineEdit_midSpeed"));
        lineEdit_midSpeed->setMinimumSize(QSize(60, 0));
        lineEdit_midSpeed->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(lineEdit_midSpeed);


        horizontalLayout_35->addLayout(horizontalLayout_4);

        horizontalLayout_35->setStretch(0, 9);
        horizontalLayout_35->setStretch(1, 1);
        horizontalLayout_35->setStretch(2, 9);

        verticalLayout->addLayout(horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(85, 0));
        label_3->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_5->addWidget(label_3);

        lineEdit_hightSpeed = new QLineEdit(groupBox);
        lineEdit_hightSpeed->setObjectName(QStringLiteral("lineEdit_hightSpeed"));
        lineEdit_hightSpeed->setMinimumSize(QSize(60, 0));
        lineEdit_hightSpeed->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_5->addWidget(lineEdit_hightSpeed);


        horizontalLayout_36->addLayout(horizontalLayout_5);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_36->addItem(horizontalSpacer_13);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(85, 0));
        label_6->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(label_6);

        lineEdit_saveZ = new QLineEdit(groupBox);
        lineEdit_saveZ->setObjectName(QStringLiteral("lineEdit_saveZ"));
        lineEdit_saveZ->setMinimumSize(QSize(60, 0));
        lineEdit_saveZ->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(lineEdit_saveZ);


        horizontalLayout_36->addLayout(horizontalLayout_2);

        horizontalLayout_36->setStretch(0, 9);
        horizontalLayout_36->setStretch(1, 1);
        horizontalLayout_36->setStretch(2, 9);

        verticalLayout->addLayout(horizontalLayout_36);

        groupBox_13 = new QGroupBox(SystemWidget);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(20, 110, 431, 101));
        groupBox_13->setMinimumSize(QSize(0, 0));
        groupBox_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        verticalLayout_8 = new QVBoxLayout(groupBox_13);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_54 = new QHBoxLayout();
        horizontalLayout_54->setSpacing(6);
        horizontalLayout_54->setObjectName(QStringLiteral("horizontalLayout_54"));
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_41 = new QLabel(groupBox_13);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setMinimumSize(QSize(80, 0));

        horizontalLayout_27->addWidget(label_41);

        lineEdit_tray_row_space = new QLineEdit(groupBox_13);
        lineEdit_tray_row_space->setObjectName(QStringLiteral("lineEdit_tray_row_space"));
        lineEdit_tray_row_space->setMinimumSize(QSize(60, 0));
        lineEdit_tray_row_space->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_27->addWidget(lineEdit_tray_row_space);


        horizontalLayout_54->addLayout(horizontalLayout_27);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_54->addItem(horizontalSpacer_29);

        horizontalLayout_55 = new QHBoxLayout();
        horizontalLayout_55->setSpacing(6);
        horizontalLayout_55->setObjectName(QStringLiteral("horizontalLayout_55"));
        label_43 = new QLabel(groupBox_13);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setMinimumSize(QSize(80, 0));

        horizontalLayout_55->addWidget(label_43);

        lineEdit_tray_col_space = new QLineEdit(groupBox_13);
        lineEdit_tray_col_space->setObjectName(QStringLiteral("lineEdit_tray_col_space"));
        lineEdit_tray_col_space->setMinimumSize(QSize(60, 0));
        lineEdit_tray_col_space->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_55->addWidget(lineEdit_tray_col_space);


        horizontalLayout_54->addLayout(horizontalLayout_55);

        horizontalLayout_54->setStretch(0, 9);
        horizontalLayout_54->setStretch(1, 1);
        horizontalLayout_54->setStretch(2, 9);

        verticalLayout_8->addLayout(horizontalLayout_54);

        horizontalLayout_56 = new QHBoxLayout();
        horizontalLayout_56->setSpacing(6);
        horizontalLayout_56->setObjectName(QStringLiteral("horizontalLayout_56"));
        horizontalLayout_57 = new QHBoxLayout();
        horizontalLayout_57->setSpacing(6);
        horizontalLayout_57->setObjectName(QStringLiteral("horizontalLayout_57"));
        label_44 = new QLabel(groupBox_13);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setMinimumSize(QSize(80, 0));

        horizontalLayout_57->addWidget(label_44);

        lineEdit_tray_row_num = new QLineEdit(groupBox_13);
        lineEdit_tray_row_num->setObjectName(QStringLiteral("lineEdit_tray_row_num"));
        lineEdit_tray_row_num->setMinimumSize(QSize(60, 0));
        lineEdit_tray_row_num->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_57->addWidget(lineEdit_tray_row_num);


        horizontalLayout_56->addLayout(horizontalLayout_57);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_56->addItem(horizontalSpacer_30);

        horizontalLayout_58 = new QHBoxLayout();
        horizontalLayout_58->setSpacing(6);
        horizontalLayout_58->setObjectName(QStringLiteral("horizontalLayout_58"));
        label_45 = new QLabel(groupBox_13);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setMinimumSize(QSize(80, 0));

        horizontalLayout_58->addWidget(label_45);

        lineEdit_tray_col_num = new QLineEdit(groupBox_13);
        lineEdit_tray_col_num->setObjectName(QStringLiteral("lineEdit_tray_col_num"));
        lineEdit_tray_col_num->setMinimumSize(QSize(60, 0));
        lineEdit_tray_col_num->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_58->addWidget(lineEdit_tray_col_num);


        horizontalLayout_56->addLayout(horizontalLayout_58);

        horizontalLayout_56->setStretch(0, 9);
        horizontalLayout_56->setStretch(1, 1);
        horizontalLayout_56->setStretch(2, 9);

        verticalLayout_8->addLayout(horizontalLayout_56);

        groupBox_5 = new QGroupBox(SystemWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(470, 20, 431, 136));
        verticalLayout_2 = new QVBoxLayout(groupBox_5);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        checkBox_safeBar = new QCheckBox(groupBox_5);
        checkBox_safeBar->setObjectName(QStringLiteral("checkBox_safeBar"));
        checkBox_safeBar->setMinimumSize(QSize(0, 20));

        horizontalLayout_10->addWidget(checkBox_safeBar);

        checkBox_safeDoor = new QCheckBox(groupBox_5);
        checkBox_safeDoor->setObjectName(QStringLiteral("checkBox_safeDoor"));
        checkBox_safeDoor->setMinimumSize(QSize(0, 20));

        horizontalLayout_10->addWidget(checkBox_safeDoor);

        checkBox_enbleBuzzing = new QCheckBox(groupBox_5);
        checkBox_enbleBuzzing->setObjectName(QStringLiteral("checkBox_enbleBuzzing"));

        horizontalLayout_10->addWidget(checkBox_enbleBuzzing);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 1);
        horizontalLayout_10->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        checkBox_wipeNozzleModule = new QCheckBox(groupBox_5);
        checkBox_wipeNozzleModule->setObjectName(QStringLiteral("checkBox_wipeNozzleModule"));
        checkBox_wipeNozzleModule->setMinimumSize(QSize(0, 20));

        horizontalLayout_11->addWidget(checkBox_wipeNozzleModule);

        checkBox_visionProtect = new QCheckBox(groupBox_5);
        checkBox_visionProtect->setObjectName(QStringLiteral("checkBox_visionProtect"));

        horizontalLayout_11->addWidget(checkBox_visionProtect);

        checkBox_XYAngleAffine = new QCheckBox(groupBox_5);
        checkBox_XYAngleAffine->setObjectName(QStringLiteral("checkBox_XYAngleAffine"));

        horizontalLayout_11->addWidget(checkBox_XYAngleAffine);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 1);
        horizontalLayout_11->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_66 = new QHBoxLayout();
        horizontalLayout_66->setSpacing(6);
        horizontalLayout_66->setObjectName(QStringLiteral("horizontalLayout_66"));
        checkBox_showTrack = new QCheckBox(groupBox_5);
        checkBox_showTrack->setObjectName(QStringLiteral("checkBox_showTrack"));

        horizontalLayout_66->addWidget(checkBox_showTrack);

        checkBox_dryrun = new QCheckBox(groupBox_5);
        checkBox_dryrun->setObjectName(QStringLiteral("checkBox_dryrun"));

        horizontalLayout_66->addWidget(checkBox_dryrun);

        checkBox_enableMakeBar = new QCheckBox(groupBox_5);
        checkBox_enableMakeBar->setObjectName(QStringLiteral("checkBox_enableMakeBar"));

        horizontalLayout_66->addWidget(checkBox_enableMakeBar);

        horizontalLayout_66->setStretch(0, 1);
        horizontalLayout_66->setStretch(1, 1);
        horizontalLayout_66->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_66);

        groupBox_6 = new QGroupBox(SystemWidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(470, 180, 431, 71));
        verticalLayout_3 = new QVBoxLayout(groupBox_6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        checkBox_enableV0Command = new QCheckBox(groupBox_6);
        checkBox_enableV0Command->setObjectName(QStringLiteral("checkBox_enableV0Command"));
        checkBox_enableV0Command->setMinimumSize(QSize(0, 20));

        horizontalLayout_12->addWidget(checkBox_enableV0Command);

        checkBox_enableRCommand = new QCheckBox(groupBox_6);
        checkBox_enableRCommand->setObjectName(QStringLiteral("checkBox_enableRCommand"));
        checkBox_enableRCommand->setMinimumSize(QSize(0, 20));

        horizontalLayout_12->addWidget(checkBox_enableRCommand);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 1);
        horizontalLayout_12->setStretch(2, 1);

        verticalLayout_3->addLayout(horizontalLayout_12);

        groupBox_7 = new QGroupBox(SystemWidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(470, 270, 431, 71));
        verticalLayout_4 = new QVBoxLayout(groupBox_7);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(85, 0));
        label_7->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(label_7);

        comboBox_laser_version = new QComboBox(groupBox_7);
        comboBox_laser_version->setObjectName(QStringLiteral("comboBox_laser_version"));

        horizontalLayout_6->addWidget(comboBox_laser_version);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 1);

        horizontalLayout_8->addLayout(horizontalLayout_6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(85, 0));
        label_8->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(label_8);

        comboBox_vision_version = new QComboBox(groupBox_7);
        comboBox_vision_version->setObjectName(QStringLiteral("comboBox_vision_version"));

        horizontalLayout_7->addWidget(comboBox_vision_version);


        horizontalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_8->setStretch(0, 9);
        horizontalLayout_8->setStretch(1, 1);
        horizontalLayout_8->setStretch(2, 9);

        verticalLayout_4->addLayout(horizontalLayout_8);


        retranslateUi(SystemWidget);
        QObject::connect(pushButton_edit, SIGNAL(clicked()), SystemWidget, SLOT(onEdit()));
        QObject::connect(pushButton_save, SIGNAL(clicked()), SystemWidget, SLOT(onSave()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), SystemWidget, SLOT(onCancel()));
        QObject::connect(pushButton_reload, SIGNAL(clicked()), SystemWidget, SLOT(onReload()));

        QMetaObject::connectSlotsByName(SystemWidget);
    } // setupUi

    void retranslateUi(QWidget *SystemWidget)
    {
        SystemWidget->setWindowTitle(QApplication::translate("SystemWidget", "SystemWidget", Q_NULLPTR));
        pushButton_edit->setText(QApplication::translate("SystemWidget", "Edit", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("SystemWidget", "Save", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("SystemWidget", "Cancel", Q_NULLPTR));
        pushButton_reload->setText(QApplication::translate("SystemWidget", "Reload", Q_NULLPTR));
        groupBox_12->setTitle(QApplication::translate("SystemWidget", "\344\270\212\346\226\231\346\250\241\345\235\227\345\217\202\346\225\260", Q_NULLPTR));
        label_35->setText(QApplication::translate("SystemWidget", "\344\276\233\346\226\231\345\201\217\347\247\273\351\207\217", Q_NULLPTR));
        label_36->setText(QApplication::translate("SystemWidget", "\346\234\200\345\244\247\346\226\231\347\233\230\346\225\260\351\207\217", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SystemWidget", "Motion settings", Q_NULLPTR));
        label->setText(QApplication::translate("SystemWidget", "Manual low speed (mm/s)", Q_NULLPTR));
        label_2->setText(QApplication::translate("SystemWidget", "Manual medium speed(mm/s)", Q_NULLPTR));
        label_3->setText(QApplication::translate("SystemWidget", "Manual high speed(mm/s)", Q_NULLPTR));
        label_6->setText(QApplication::translate("SystemWidget", "Z axis safe pos", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("SystemWidget", "\346\226\231\347\233\230\345\217\202\346\225\260", Q_NULLPTR));
        label_41->setText(QApplication::translate("SystemWidget", "\350\241\214\351\227\264\350\267\235", Q_NULLPTR));
        label_43->setText(QApplication::translate("SystemWidget", "\345\210\227\351\227\264\350\267\235", Q_NULLPTR));
        label_44->setText(QApplication::translate("SystemWidget", "\350\241\214\346\225\260\351\207\217", Q_NULLPTR));
        label_45->setText(QApplication::translate("SystemWidget", "\345\210\227\346\225\260\351\207\217", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("SystemWidget", "Options", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_safeBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_safeBar->setText(QApplication::translate("SystemWidget", "Raster", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_safeDoor->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_safeDoor->setText(QApplication::translate("SystemWidget", "Door", Q_NULLPTR));
        checkBox_enbleBuzzing->setText(QApplication::translate("SystemWidget", "Ban buzzer", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_wipeNozzleModule->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_wipeNozzleModule->setText(QApplication::translate("SystemWidget", "Wipe glue module", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_visionProtect->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_visionProtect->setText(QApplication::translate("SystemWidget", "Vision protect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_XYAngleAffine->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_XYAngleAffine->setText(QApplication::translate("SystemWidget", "Angle compensation", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_showTrack->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_showTrack->setText(QApplication::translate("SystemWidget", "Show Track", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_dryrun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_dryrun->setText(QApplication::translate("SystemWidget", "Dry run", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_enableMakeBar->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_enableMakeBar->setText(QApplication::translate("SystemWidget", "\345\220\257\347\224\250\346\211\223\346\240\207", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("SystemWidget", "\346\214\207\344\273\244\351\200\211\346\213\251", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_enableV0Command->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_enableV0Command->setText(QApplication::translate("SystemWidget", "V0\346\214\207\344\273\244", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_enableRCommand->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        checkBox_enableRCommand->setText(QApplication::translate("SystemWidget", "\345\215\212\345\276\204\346\214\207\344\273\244", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("SystemWidget", "\347\211\210\346\234\254\351\200\211\346\213\251", Q_NULLPTR));
        label_7->setText(QApplication::translate("SystemWidget", "\346\211\223\346\240\207\347\250\213\345\272\217\345\217\267", Q_NULLPTR));
        label_8->setText(QApplication::translate("SystemWidget", "\350\247\206\350\247\211\347\250\213\345\272\217\345\217\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SystemWidget: public Ui_SystemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMWIDGET_H
