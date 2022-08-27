/********************************************************************************
** Form generated from reading UI file 'ModuleDebug.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULEDEBUG_H
#define UI_MODULEDEBUG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModuleDebug
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_carry_reset;
    QPushButton *pushButton_carry_start;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_scan_reset;
    QPushButton *pushButton_scan_start;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_sort_reset;
    QPushButton *pushButton_sort_start;
    QWidget *layoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_unload_reset;
    QPushButton *pushButton_unload_start;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_feed_reset;
    QPushButton *pushButton_feed_start;

    void setupUi(QWidget *ModuleDebug)
    {
        if (ModuleDebug->objectName().isEmpty())
            ModuleDebug->setObjectName(QStringLiteral("ModuleDebug"));
        ModuleDebug->resize(423, 274);
        layoutWidget = new QWidget(ModuleDebug);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 50, 101, 81));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_carry_reset = new QPushButton(layoutWidget);
        pushButton_carry_reset->setObjectName(QStringLiteral("pushButton_carry_reset"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_carry_reset->sizePolicy().hasHeightForWidth());
        pushButton_carry_reset->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(pushButton_carry_reset);

        pushButton_carry_start = new QPushButton(layoutWidget);
        pushButton_carry_start->setObjectName(QStringLiteral("pushButton_carry_start"));
        sizePolicy.setHeightForWidth(pushButton_carry_start->sizePolicy().hasHeightForWidth());
        pushButton_carry_start->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(pushButton_carry_start);

        layoutWidget_2 = new QWidget(ModuleDebug);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(290, 50, 101, 81));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_scan_reset = new QPushButton(layoutWidget_2);
        pushButton_scan_reset->setObjectName(QStringLiteral("pushButton_scan_reset"));
        sizePolicy.setHeightForWidth(pushButton_scan_reset->sizePolicy().hasHeightForWidth());
        pushButton_scan_reset->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(pushButton_scan_reset);

        pushButton_scan_start = new QPushButton(layoutWidget_2);
        pushButton_scan_start->setObjectName(QStringLiteral("pushButton_scan_start"));
        sizePolicy.setHeightForWidth(pushButton_scan_start->sizePolicy().hasHeightForWidth());
        pushButton_scan_start->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(pushButton_scan_start);

        layoutWidget_3 = new QWidget(ModuleDebug);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(30, 160, 101, 81));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_sort_reset = new QPushButton(layoutWidget_3);
        pushButton_sort_reset->setObjectName(QStringLiteral("pushButton_sort_reset"));
        sizePolicy.setHeightForWidth(pushButton_sort_reset->sizePolicy().hasHeightForWidth());
        pushButton_sort_reset->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(pushButton_sort_reset);

        pushButton_sort_start = new QPushButton(layoutWidget_3);
        pushButton_sort_start->setObjectName(QStringLiteral("pushButton_sort_start"));
        sizePolicy.setHeightForWidth(pushButton_sort_start->sizePolicy().hasHeightForWidth());
        pushButton_sort_start->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(pushButton_sort_start);

        layoutWidget_4 = new QWidget(ModuleDebug);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(160, 160, 101, 81));
        verticalLayout_5 = new QVBoxLayout(layoutWidget_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButton_unload_reset = new QPushButton(layoutWidget_4);
        pushButton_unload_reset->setObjectName(QStringLiteral("pushButton_unload_reset"));
        sizePolicy.setHeightForWidth(pushButton_unload_reset->sizePolicy().hasHeightForWidth());
        pushButton_unload_reset->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(pushButton_unload_reset);

        pushButton_unload_start = new QPushButton(layoutWidget_4);
        pushButton_unload_start->setObjectName(QStringLiteral("pushButton_unload_start"));
        sizePolicy.setHeightForWidth(pushButton_unload_start->sizePolicy().hasHeightForWidth());
        pushButton_unload_start->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(pushButton_unload_start);

        layoutWidget1 = new QWidget(ModuleDebug);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 50, 101, 81));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_feed_reset = new QPushButton(layoutWidget1);
        pushButton_feed_reset->setObjectName(QStringLiteral("pushButton_feed_reset"));
        sizePolicy.setHeightForWidth(pushButton_feed_reset->sizePolicy().hasHeightForWidth());
        pushButton_feed_reset->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_feed_reset);

        pushButton_feed_start = new QPushButton(layoutWidget1);
        pushButton_feed_start->setObjectName(QStringLiteral("pushButton_feed_start"));
        sizePolicy.setHeightForWidth(pushButton_feed_start->sizePolicy().hasHeightForWidth());
        pushButton_feed_start->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_feed_start);


        retranslateUi(ModuleDebug);

        QMetaObject::connectSlotsByName(ModuleDebug);
    } // setupUi

    void retranslateUi(QWidget *ModuleDebug)
    {
        ModuleDebug->setWindowTitle(QApplication::translate("ModuleDebug", "OpticalFiberTeachWidget", Q_NULLPTR));
        pushButton_carry_reset->setText(QApplication::translate("ModuleDebug", "\346\220\254\350\277\220\346\250\241\347\273\204\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_carry_start->setText(QApplication::translate("ModuleDebug", "\346\220\254\350\277\220\346\250\241\347\273\204\345\220\257\345\212\250", Q_NULLPTR));
        pushButton_scan_reset->setText(QApplication::translate("ModuleDebug", "\346\211\253\347\240\201\346\250\241\347\273\204\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_scan_start->setText(QApplication::translate("ModuleDebug", "\346\211\253\347\240\201\346\250\241\347\273\204\345\220\257\345\212\250", Q_NULLPTR));
        pushButton_sort_reset->setText(QApplication::translate("ModuleDebug", "\345\210\206\346\226\231\346\250\241\347\273\204\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_sort_start->setText(QApplication::translate("ModuleDebug", "\345\210\206\346\226\231\346\250\241\347\273\204\345\220\257\345\212\250", Q_NULLPTR));
        pushButton_unload_reset->setText(QApplication::translate("ModuleDebug", "\344\270\213\346\226\231\346\250\241\347\273\204\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_unload_start->setText(QApplication::translate("ModuleDebug", "\344\270\213\346\226\231\346\250\241\347\273\204\345\220\257\345\212\250", Q_NULLPTR));
        pushButton_feed_reset->setText(QApplication::translate("ModuleDebug", "\344\270\212\346\226\231\346\250\241\347\273\204\345\244\215\344\275\215", Q_NULLPTR));
        pushButton_feed_start->setText(QApplication::translate("ModuleDebug", "\344\270\212\346\226\231\346\250\241\347\273\204\345\220\257\345\212\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ModuleDebug: public Ui_ModuleDebug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULEDEBUG_H
