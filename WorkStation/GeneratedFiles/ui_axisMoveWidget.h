/********************************************************************************
** Form generated from reading UI file 'axisMoveWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AXISMOVEWIDGET_H
#define UI_AXISMOVEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AxisMoveWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton_laserXP;
    QPushButton *pushButton_laserYP;
    QPushButton *pushButton_laserYN;
    QPushButton *pushButton_laserXN;
    QPushButton *pushButton_carryXP;
    QPushButton *pushButton_carryXN;
    QPushButton *pushButton_feedZP;
    QPushButton *pushButton_feedZN;
    QPushButton *pushButton_unloadZP;
    QPushButton *pushButton_unloadZN;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox_move_step;
    QCheckBox *checkBox_pmove;
    QRadioButton *radioButton_speed_low;
    QRadioButton *radioButton_speed_normal;
    QRadioButton *radioButton_speed_fast;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *AxisMoveWidget)
    {
        if (AxisMoveWidget->objectName().isEmpty())
            AxisMoveWidget->setObjectName(QStringLiteral("AxisMoveWidget"));
        AxisMoveWidget->resize(465, 397);
        AxisMoveWidget->setMinimumSize(QSize(340, 280));
        AxisMoveWidget->setMaximumSize(QSize(1000, 1000));
        verticalLayout = new QVBoxLayout(AxisMoveWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_laserXP = new QPushButton(AxisMoveWidget);
        pushButton_laserXP->setObjectName(QStringLiteral("pushButton_laserXP"));
        pushButton_laserXP->setMinimumSize(QSize(70, 45));
        pushButton_laserXP->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(14);
        pushButton_laserXP->setFont(font);

        gridLayout->addWidget(pushButton_laserXP, 0, 0, 1, 1);

        pushButton_laserYP = new QPushButton(AxisMoveWidget);
        pushButton_laserYP->setObjectName(QStringLiteral("pushButton_laserYP"));
        pushButton_laserYP->setMinimumSize(QSize(70, 45));
        pushButton_laserYP->setFont(font);

        gridLayout->addWidget(pushButton_laserYP, 0, 1, 1, 1);

        pushButton_laserYN = new QPushButton(AxisMoveWidget);
        pushButton_laserYN->setObjectName(QStringLiteral("pushButton_laserYN"));
        pushButton_laserYN->setMinimumSize(QSize(70, 45));
        pushButton_laserYN->setFont(font);

        gridLayout->addWidget(pushButton_laserYN, 1, 1, 1, 1);

        pushButton_laserXN = new QPushButton(AxisMoveWidget);
        pushButton_laserXN->setObjectName(QStringLiteral("pushButton_laserXN"));
        pushButton_laserXN->setMinimumSize(QSize(70, 45));
        pushButton_laserXN->setMaximumSize(QSize(16777215, 16777215));
        pushButton_laserXN->setFont(font);

        gridLayout->addWidget(pushButton_laserXN, 1, 0, 1, 1);

        pushButton_carryXP = new QPushButton(AxisMoveWidget);
        pushButton_carryXP->setObjectName(QStringLiteral("pushButton_carryXP"));
        pushButton_carryXP->setMinimumSize(QSize(70, 45));
        pushButton_carryXP->setFont(font);

        gridLayout->addWidget(pushButton_carryXP, 0, 2, 1, 1);

        pushButton_carryXN = new QPushButton(AxisMoveWidget);
        pushButton_carryXN->setObjectName(QStringLiteral("pushButton_carryXN"));
        pushButton_carryXN->setMinimumSize(QSize(70, 45));
        pushButton_carryXN->setFont(font);

        gridLayout->addWidget(pushButton_carryXN, 1, 2, 1, 1);

        pushButton_feedZP = new QPushButton(AxisMoveWidget);
        pushButton_feedZP->setObjectName(QStringLiteral("pushButton_feedZP"));
        pushButton_feedZP->setMinimumSize(QSize(70, 45));
        pushButton_feedZP->setFont(font);

        gridLayout->addWidget(pushButton_feedZP, 2, 0, 1, 1);

        pushButton_feedZN = new QPushButton(AxisMoveWidget);
        pushButton_feedZN->setObjectName(QStringLiteral("pushButton_feedZN"));
        pushButton_feedZN->setMinimumSize(QSize(70, 45));
        pushButton_feedZN->setFont(font);

        gridLayout->addWidget(pushButton_feedZN, 3, 0, 1, 1);

        pushButton_unloadZP = new QPushButton(AxisMoveWidget);
        pushButton_unloadZP->setObjectName(QStringLiteral("pushButton_unloadZP"));
        pushButton_unloadZP->setMinimumSize(QSize(70, 45));
        pushButton_unloadZP->setFont(font);

        gridLayout->addWidget(pushButton_unloadZP, 2, 1, 1, 1);

        pushButton_unloadZN = new QPushButton(AxisMoveWidget);
        pushButton_unloadZN->setObjectName(QStringLiteral("pushButton_unloadZN"));
        pushButton_unloadZN->setMinimumSize(QSize(70, 45));
        pushButton_unloadZN->setFont(font);

        gridLayout->addWidget(pushButton_unloadZN, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        comboBox_move_step = new QComboBox(AxisMoveWidget);
        comboBox_move_step->setObjectName(QStringLiteral("comboBox_move_step"));

        gridLayout_3->addWidget(comboBox_move_step, 0, 5, 1, 1);

        checkBox_pmove = new QCheckBox(AxisMoveWidget);
        checkBox_pmove->setObjectName(QStringLiteral("checkBox_pmove"));

        gridLayout_3->addWidget(checkBox_pmove, 0, 4, 1, 1);

        radioButton_speed_low = new QRadioButton(AxisMoveWidget);
        radioButton_speed_low->setObjectName(QStringLiteral("radioButton_speed_low"));

        gridLayout_3->addWidget(radioButton_speed_low, 0, 0, 1, 1);

        radioButton_speed_normal = new QRadioButton(AxisMoveWidget);
        radioButton_speed_normal->setObjectName(QStringLiteral("radioButton_speed_normal"));

        gridLayout_3->addWidget(radioButton_speed_normal, 0, 1, 1, 1);

        radioButton_speed_fast = new QRadioButton(AxisMoveWidget);
        radioButton_speed_fast->setObjectName(QStringLiteral("radioButton_speed_fast"));

        gridLayout_3->addWidget(radioButton_speed_fast, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 3, 1, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 1);
        gridLayout_3->setColumnStretch(3, 2);
        gridLayout_3->setColumnStretch(4, 1);
        gridLayout_3->setColumnStretch(5, 2);

        verticalLayout->addLayout(gridLayout_3);


        retranslateUi(AxisMoveWidget);

        QMetaObject::connectSlotsByName(AxisMoveWidget);
    } // setupUi

    void retranslateUi(QWidget *AxisMoveWidget)
    {
        AxisMoveWidget->setWindowTitle(QApplication::translate("AxisMoveWidget", "AxisMoveWidget", Q_NULLPTR));
        pushButton_laserXP->setText(QApplication::translate("AxisMoveWidget", "\351\225\255\347\240\201X+", Q_NULLPTR));
        pushButton_laserYP->setText(QApplication::translate("AxisMoveWidget", "\351\225\255\347\240\201Y+", Q_NULLPTR));
        pushButton_laserYN->setText(QApplication::translate("AxisMoveWidget", "\351\225\255\347\240\201Y-", Q_NULLPTR));
        pushButton_laserXN->setText(QApplication::translate("AxisMoveWidget", "\351\225\255\347\240\201X-", Q_NULLPTR));
        pushButton_carryXP->setText(QApplication::translate("AxisMoveWidget", "\346\220\254\350\277\220X+", Q_NULLPTR));
        pushButton_carryXN->setText(QApplication::translate("AxisMoveWidget", "\346\220\254\350\277\220X-", Q_NULLPTR));
        pushButton_feedZP->setText(QApplication::translate("AxisMoveWidget", "\344\270\212\346\226\231Z+", Q_NULLPTR));
        pushButton_feedZN->setText(QApplication::translate("AxisMoveWidget", "\344\270\212\346\226\231Z-", Q_NULLPTR));
        pushButton_unloadZP->setText(QApplication::translate("AxisMoveWidget", "\344\270\213\346\226\231Z+", Q_NULLPTR));
        pushButton_unloadZN->setText(QApplication::translate("AxisMoveWidget", "\344\270\213\346\226\231Z-", Q_NULLPTR));
        checkBox_pmove->setText(QApplication::translate("AxisMoveWidget", "\347\202\271\345\212\250", Q_NULLPTR));
        radioButton_speed_low->setText(QApplication::translate("AxisMoveWidget", "\346\205\242\351\200\237", Q_NULLPTR));
        radioButton_speed_normal->setText(QApplication::translate("AxisMoveWidget", "\344\270\255\351\200\237", Q_NULLPTR));
        radioButton_speed_fast->setText(QApplication::translate("AxisMoveWidget", "\345\277\253\351\200\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AxisMoveWidget: public Ui_AxisMoveWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AXISMOVEWIDGET_H
