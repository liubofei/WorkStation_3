/********************************************************************************
** Form generated from reading UI file 'ParamWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMWIDGET_H
#define UI_PARAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamWidget
{
public:
    QTabWidget *tabWidget;

    void setupUi(QWidget *ParamWidget)
    {
        if (ParamWidget->objectName().isEmpty())
            ParamWidget->setObjectName(QStringLiteral("ParamWidget"));
        ParamWidget->resize(1000, 820);
        ParamWidget->setMinimumSize(QSize(1000, 820));
        ParamWidget->setMaximumSize(QSize(1000, 820));
        tabWidget = new QTabWidget(ParamWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 961, 801));
        tabWidget->setMinimumSize(QSize(0, 0));

        retranslateUi(ParamWidget);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ParamWidget);
    } // setupUi

    void retranslateUi(QWidget *ParamWidget)
    {
        ParamWidget->setWindowTitle(QApplication::translate("ParamWidget", "ParamWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParamWidget: public Ui_ParamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMWIDGET_H
