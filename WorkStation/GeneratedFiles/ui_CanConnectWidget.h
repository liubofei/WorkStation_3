/********************************************************************************
** Form generated from reading UI file 'CanConnectWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANCONNECTWIDGET_H
#define UI_CANCONNECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CanConnectWidget
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QSpinBox *spinBox_CANCardNo;
    QSpinBox *spinBox_CANNodeNum;
    QLabel *label_1;
    QLabel *label_3;
    QComboBox *comboBox_CANState;
    QLabel *label_4;
    QComboBox *comboBox_CANBaud;
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *lineEdit_CANState;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_CAN_OK;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_CAN_Cancel;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *CanConnectWidget)
    {
        if (CanConnectWidget->objectName().isEmpty())
            CanConnectWidget->setObjectName(QStringLiteral("CanConnectWidget"));
        CanConnectWidget->resize(440, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CanConnectWidget->sizePolicy().hasHeightForWidth());
        CanConnectWidget->setSizePolicy(sizePolicy);
        CanConnectWidget->setMinimumSize(QSize(440, 300));
        CanConnectWidget->setMaximumSize(QSize(440, 300));
        verticalLayout = new QVBoxLayout(CanConnectWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        groupBox_2 = new QGroupBox(CanConnectWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBox_CANCardNo = new QSpinBox(groupBox_2);
        spinBox_CANCardNo->setObjectName(QStringLiteral("spinBox_CANCardNo"));
        spinBox_CANCardNo->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox_CANCardNo->sizePolicy().hasHeightForWidth());
        spinBox_CANCardNo->setSizePolicy(sizePolicy1);
        spinBox_CANCardNo->setMinimumSize(QSize(100, 0));
        spinBox_CANCardNo->setMaximumSize(QSize(60, 16777215));
        spinBox_CANCardNo->setMouseTracking(false);
        spinBox_CANCardNo->setMinimum(0);
        spinBox_CANCardNo->setMaximum(999);
        spinBox_CANCardNo->setValue(0);

        gridLayout->addWidget(spinBox_CANCardNo, 0, 1, 1, 1);

        spinBox_CANNodeNum = new QSpinBox(groupBox_2);
        spinBox_CANNodeNum->setObjectName(QStringLiteral("spinBox_CANNodeNum"));
        sizePolicy1.setHeightForWidth(spinBox_CANNodeNum->sizePolicy().hasHeightForWidth());
        spinBox_CANNodeNum->setSizePolicy(sizePolicy1);
        spinBox_CANNodeNum->setMinimumSize(QSize(0, 0));
        spinBox_CANNodeNum->setMaximumSize(QSize(100, 16777215));
        spinBox_CANNodeNum->setMouseTracking(false);
        spinBox_CANNodeNum->setMinimum(1);
        spinBox_CANNodeNum->setMaximum(8);

        gridLayout->addWidget(spinBox_CANNodeNum, 1, 1, 1, 1);

        label_1 = new QLabel(groupBox_2);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setMinimumSize(QSize(100, 0));
        label_1->setMaximumSize(QSize(85, 16777215));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(100, 0));
        label_3->setMaximumSize(QSize(85, 16777215));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        comboBox_CANState = new QComboBox(groupBox_2);
        comboBox_CANState->setObjectName(QStringLiteral("comboBox_CANState"));
        sizePolicy1.setHeightForWidth(comboBox_CANState->sizePolicy().hasHeightForWidth());
        comboBox_CANState->setSizePolicy(sizePolicy1);
        comboBox_CANState->setMinimumSize(QSize(0, 0));
        comboBox_CANState->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(comboBox_CANState, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(100, 0));
        label_4->setMaximumSize(QSize(85, 16777215));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        comboBox_CANBaud = new QComboBox(groupBox_2);
        comboBox_CANBaud->setObjectName(QStringLiteral("comboBox_CANBaud"));
        sizePolicy1.setHeightForWidth(comboBox_CANBaud->sizePolicy().hasHeightForWidth());
        comboBox_CANBaud->setSizePolicy(sizePolicy1);
        comboBox_CANBaud->setMinimumSize(QSize(100, 0));
        comboBox_CANBaud->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(comboBox_CANBaud, 3, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(85, 16777215));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(100, 0));
        label_5->setMaximumSize(QSize(85, 16777215));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_CANState = new QLineEdit(groupBox_2);
        lineEdit_CANState->setObjectName(QStringLiteral("lineEdit_CANState"));
        lineEdit_CANState->setEnabled(false);
        lineEdit_CANState->setMinimumSize(QSize(100, 0));
        lineEdit_CANState->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(lineEdit_CANState, 4, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);

        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_CAN_OK = new QPushButton(CanConnectWidget);
        pushButton_CAN_OK->setObjectName(QStringLiteral("pushButton_CAN_OK"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_CAN_OK->sizePolicy().hasHeightForWidth());
        pushButton_CAN_OK->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(pushButton_CAN_OK);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_CAN_Cancel = new QPushButton(CanConnectWidget);
        pushButton_CAN_Cancel->setObjectName(QStringLiteral("pushButton_CAN_Cancel"));
        sizePolicy2.setHeightForWidth(pushButton_CAN_Cancel->sizePolicy().hasHeightForWidth());
        pushButton_CAN_Cancel->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(pushButton_CAN_Cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 2);

        retranslateUi(CanConnectWidget);

        QMetaObject::connectSlotsByName(CanConnectWidget);
    } // setupUi

    void retranslateUi(QWidget *CanConnectWidget)
    {
        CanConnectWidget->setWindowTitle(QApplication::translate("CanConnectWidget", "CanConnectWidget", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("CanConnectWidget", "\350\256\276\347\275\256CAN\351\200\232\350\256\257\347\212\266\346\200\201", Q_NULLPTR));
        label_1->setText(QApplication::translate("CanConnectWidget", "\346\216\247\345\210\266\345\215\241\345\215\241\345\217\267\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("CanConnectWidget", "\351\200\232\350\256\257\347\212\266\346\200\201\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("CanConnectWidget", "\346\263\242 \347\211\271 \347\216\207\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("CanConnectWidget", "CAN\350\212\202\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("CanConnectWidget", "\345\275\223\345\211\215\347\212\266\346\200\201\357\274\232", Q_NULLPTR));
        pushButton_CAN_OK->setText(QApplication::translate("CanConnectWidget", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_CAN_Cancel->setText(QApplication::translate("CanConnectWidget", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CanConnectWidget: public Ui_CanConnectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANCONNECTWIDGET_H
