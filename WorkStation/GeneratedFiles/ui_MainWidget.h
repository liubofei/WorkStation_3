/********************************************************************************
** Form generated from reading UI file 'MainWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_system;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_sysStatus;
    QLabel *label_time;
    QPushButton *pushButton_start_up;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_continue;
    QPushButton *pushButton_laserCalib;
    QPushButton *pushButton_unload_tray_taked;
    QTabWidget *tabWidget_tray_status;
    QTextEdit *textEdit_log;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QStringLiteral("MainWidget"));
        MainWidget->resize(957, 635);
        verticalLayout_2 = new QVBoxLayout(MainWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_system = new QGroupBox(MainWidget);
        groupBox_system->setObjectName(QStringLiteral("groupBox_system"));
        groupBox_system->setMinimumSize(QSize(150, 0));
        groupBox_system->setMaximumSize(QSize(150, 16777215));
        groupBox_system->setAlignment(Qt::AlignCenter);
        verticalLayout_6 = new QVBoxLayout(groupBox_system);
        verticalLayout_6->setSpacing(7);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(9, 9, 9, 9);
        label_sysStatus = new QLabel(groupBox_system);
        label_sysStatus->setObjectName(QStringLiteral("label_sysStatus"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_sysStatus->sizePolicy().hasHeightForWidth());
        label_sysStatus->setSizePolicy(sizePolicy);
        label_sysStatus->setMinimumSize(QSize(0, 0));
        label_sysStatus->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(24);
        label_sysStatus->setFont(font);
        label_sysStatus->setStyleSheet(QStringLiteral("color: rgb(255, 85, 0);"));
        label_sysStatus->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_sysStatus);

        label_time = new QLabel(groupBox_system);
        label_time->setObjectName(QStringLiteral("label_time"));
        sizePolicy.setHeightForWidth(label_time->sizePolicy().hasHeightForWidth());
        label_time->setSizePolicy(sizePolicy);
        label_time->setMinimumSize(QSize(0, 30));
        label_time->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setPointSize(11);
        label_time->setFont(font1);
        label_time->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_time);

        pushButton_start_up = new QPushButton(groupBox_system);
        pushButton_start_up->setObjectName(QStringLiteral("pushButton_start_up"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_start_up->sizePolicy().hasHeightForWidth());
        pushButton_start_up->setSizePolicy(sizePolicy1);
        pushButton_start_up->setMinimumSize(QSize(0, 35));
        pushButton_start_up->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        pushButton_start_up->setFont(font2);
        pushButton_start_up->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_6->addWidget(pushButton_start_up);

        pushButton_reset = new QPushButton(groupBox_system);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        sizePolicy1.setHeightForWidth(pushButton_reset->sizePolicy().hasHeightForWidth());
        pushButton_reset->setSizePolicy(sizePolicy1);
        pushButton_reset->setMinimumSize(QSize(0, 35));
        pushButton_reset->setMaximumSize(QSize(16777215, 16777215));
        pushButton_reset->setFont(font2);
        pushButton_reset->setFlat(false);

        verticalLayout_6->addWidget(pushButton_reset);

        pushButton_stop = new QPushButton(groupBox_system);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        sizePolicy1.setHeightForWidth(pushButton_stop->sizePolicy().hasHeightForWidth());
        pushButton_stop->setSizePolicy(sizePolicy1);
        pushButton_stop->setMinimumSize(QSize(0, 35));
        pushButton_stop->setMaximumSize(QSize(16777215, 16777215));
        pushButton_stop->setFont(font2);

        verticalLayout_6->addWidget(pushButton_stop);

        pushButton_continue = new QPushButton(groupBox_system);
        pushButton_continue->setObjectName(QStringLiteral("pushButton_continue"));
        sizePolicy1.setHeightForWidth(pushButton_continue->sizePolicy().hasHeightForWidth());
        pushButton_continue->setSizePolicy(sizePolicy1);
        pushButton_continue->setMinimumSize(QSize(0, 35));
        pushButton_continue->setMaximumSize(QSize(16777215, 16777215));
        pushButton_continue->setFont(font2);

        verticalLayout_6->addWidget(pushButton_continue);

        pushButton_laserCalib = new QPushButton(groupBox_system);
        pushButton_laserCalib->setObjectName(QStringLiteral("pushButton_laserCalib"));
        sizePolicy1.setHeightForWidth(pushButton_laserCalib->sizePolicy().hasHeightForWidth());
        pushButton_laserCalib->setSizePolicy(sizePolicy1);
        pushButton_laserCalib->setMinimumSize(QSize(0, 35));
        pushButton_laserCalib->setMaximumSize(QSize(16777215, 16777215));
        pushButton_laserCalib->setFont(font2);

        verticalLayout_6->addWidget(pushButton_laserCalib);

        pushButton_unload_tray_taked = new QPushButton(groupBox_system);
        pushButton_unload_tray_taked->setObjectName(QStringLiteral("pushButton_unload_tray_taked"));
        sizePolicy1.setHeightForWidth(pushButton_unload_tray_taked->sizePolicy().hasHeightForWidth());
        pushButton_unload_tray_taked->setSizePolicy(sizePolicy1);
        pushButton_unload_tray_taked->setMinimumSize(QSize(0, 35));
        pushButton_unload_tray_taked->setMaximumSize(QSize(16777215, 16777215));
        pushButton_unload_tray_taked->setFont(font2);

        verticalLayout_6->addWidget(pushButton_unload_tray_taked);

        verticalLayout_6->setStretch(0, 2);
        verticalLayout_6->setStretch(1, 2);
        verticalLayout_6->setStretch(2, 1);
        verticalLayout_6->setStretch(3, 1);
        verticalLayout_6->setStretch(4, 1);
        verticalLayout_6->setStretch(5, 1);

        horizontalLayout->addWidget(groupBox_system);

        tabWidget_tray_status = new QTabWidget(MainWidget);
        tabWidget_tray_status->setObjectName(QStringLiteral("tabWidget_tray_status"));

        horizontalLayout->addWidget(tabWidget_tray_status);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout);

        textEdit_log = new QTextEdit(MainWidget);
        textEdit_log->setObjectName(QStringLiteral("textEdit_log"));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(10);
        textEdit_log->setFont(font3);
        textEdit_log->setContextMenuPolicy(Qt::CustomContextMenu);
        textEdit_log->setStyleSheet(QStringLiteral("color: rgb(85, 85, 127);"));
        textEdit_log->setReadOnly(true);

        verticalLayout->addWidget(textEdit_log);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MainWidget);

        tabWidget_tray_status->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", Q_NULLPTR));
        groupBox_system->setTitle(QApplication::translate("MainWidget", "System Control", Q_NULLPTR));
        label_sysStatus->setText(QApplication::translate("MainWidget", " UnHome", Q_NULLPTR));
        label_time->setText(QApplication::translate("MainWidget", "09/21 17\357\274\23214", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_start_up->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_start_up->setText(QApplication::translate("MainWidget", "Start up", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_reset->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_reset->setText(QApplication::translate("MainWidget", "Reset", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_stop->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_stop->setText(QApplication::translate("MainWidget", "Stop", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_continue->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_continue->setText(QApplication::translate("MainWidget", "Continue", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_laserCalib->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_laserCalib->setText(QApplication::translate("MainWidget", "\351\225\255\347\240\201\346\240\207\345\256\232", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_unload_tray_taked->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButton_unload_tray_taked->setText(QApplication::translate("MainWidget", "\344\270\213\346\226\231\346\250\241\347\273\204\346\226\231\347\233\230\345\267\262\345\217\226\350\265\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
