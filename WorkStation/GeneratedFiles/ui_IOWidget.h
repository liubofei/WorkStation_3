/********************************************************************************
** Form generated from reading UI file 'IOWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOWIDGET_H
#define UI_IOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IOWidget
{
public:
    QHBoxLayout *horizontalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_in;
    QWidget *widget_out;
    QWidget *tab_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_in;
    QRadioButton *radioButton_out;
    QListWidget *listWidget_IO;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_name;
    QComboBox *comboBox_cardtype;
    QComboBox *comboBox_cardindex;
    QComboBox *comboBox_card_node;
    QComboBox *comboBox_IOIndex;
    QComboBox *comboBox_sense;
    QComboBox *comboBox_group;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_11;

    void setupUi(QWidget *IOWidget)
    {
        if (IOWidget->objectName().isEmpty())
            IOWidget->setObjectName(QStringLiteral("IOWidget"));
        IOWidget->resize(916, 826);
        horizontalLayout_4 = new QHBoxLayout(IOWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tabWidget = new QTabWidget(IOWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 890, 781));
        horizontalLayout_6 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        widget_in = new QWidget(scrollAreaWidgetContents);
        widget_in->setObjectName(QStringLiteral("widget_in"));
        widget_in->setMinimumSize(QSize(408, 546));
        widget_in->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(widget_in);

        widget_out = new QWidget(scrollAreaWidgetContents);
        widget_out->setObjectName(QStringLiteral("widget_out"));
        widget_out->setMinimumSize(QSize(403, 546));
        widget_out->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(widget_out);

        horizontalLayout_5->setStretch(0, 5);
        horizontalLayout_5->setStretch(1, 10);

        horizontalLayout_6->addLayout(horizontalLayout_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(scrollArea);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        layoutWidget = new QWidget(tab_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(408, 490, 223, 37));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_save = new QPushButton(layoutWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(pushButton_save);

        pushButton_cancel = new QPushButton(layoutWidget);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(pushButton_cancel);

        layoutWidget1 = new QWidget(tab_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(408, 30, 233, 21));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_in = new QRadioButton(layoutWidget1);
        radioButton_in->setObjectName(QStringLiteral("radioButton_in"));

        horizontalLayout_2->addWidget(radioButton_in);

        radioButton_out = new QRadioButton(layoutWidget1);
        radioButton_out->setObjectName(QStringLiteral("radioButton_out"));

        horizontalLayout_2->addWidget(radioButton_out);

        listWidget_IO = new QListWidget(tab_3);
        listWidget_IO->setObjectName(QStringLiteral("listWidget_IO"));
        listWidget_IO->setGeometry(QRect(96, 22, 237, 511));
        listWidget_IO->setContextMenuPolicy(Qt::CustomContextMenu);
        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(508, 70, 135, 375));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_name = new QLineEdit(layoutWidget2);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        verticalLayout->addWidget(lineEdit_name);

        comboBox_cardtype = new QComboBox(layoutWidget2);
        comboBox_cardtype->setObjectName(QStringLiteral("comboBox_cardtype"));

        verticalLayout->addWidget(comboBox_cardtype);

        comboBox_cardindex = new QComboBox(layoutWidget2);
        comboBox_cardindex->setObjectName(QStringLiteral("comboBox_cardindex"));

        verticalLayout->addWidget(comboBox_cardindex);

        comboBox_card_node = new QComboBox(layoutWidget2);
        comboBox_card_node->setObjectName(QStringLiteral("comboBox_card_node"));

        verticalLayout->addWidget(comboBox_card_node);

        comboBox_IOIndex = new QComboBox(layoutWidget2);
        comboBox_IOIndex->setObjectName(QStringLiteral("comboBox_IOIndex"));

        verticalLayout->addWidget(comboBox_IOIndex);

        comboBox_sense = new QComboBox(layoutWidget2);
        comboBox_sense->setObjectName(QStringLiteral("comboBox_sense"));

        verticalLayout->addWidget(comboBox_sense);

        comboBox_group = new QComboBox(layoutWidget2);
        comboBox_group->setObjectName(QStringLiteral("comboBox_group"));

        verticalLayout->addWidget(comboBox_group);

        layoutWidget3 = new QWidget(tab_3);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(407, 71, 86, 373));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_4);

        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_6);

        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_5);

        label_10 = new QLabel(layoutWidget3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_10);

        label_11 = new QLabel(layoutWidget3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label_11);

        tabWidget->addTab(tab_3, QString());

        horizontalLayout_4->addWidget(tabWidget);


        retranslateUi(IOWidget);
        QObject::connect(pushButton_save, SIGNAL(clicked()), IOWidget, SLOT(onBtnSaveClicked()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), IOWidget, SLOT(onBtnCancelClicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(IOWidget);
    } // setupUi

    void retranslateUi(QWidget *IOWidget)
    {
        IOWidget->setWindowTitle(QApplication::translate("IOWidget", "IOWidget", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("IOWidget", "IO Status", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("IOWidget", "Save", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("IOWidget", "Cancel", Q_NULLPTR));
        radioButton_in->setText(QApplication::translate("IOWidget", "Input", Q_NULLPTR));
        radioButton_out->setText(QApplication::translate("IOWidget", "Output", Q_NULLPTR));
        label_2->setText(QApplication::translate("IOWidget", "IO Name", Q_NULLPTR));
        label_3->setText(QApplication::translate("IOWidget", "Card Type", Q_NULLPTR));
        label_4->setText(QApplication::translate("IOWidget", "Card No", Q_NULLPTR));
        label_6->setText(QApplication::translate("IOWidget", "Node No\357\274\210Can\357\274\211", Q_NULLPTR));
        label_5->setText(QApplication::translate("IOWidget", "IO Index", Q_NULLPTR));
        label_10->setText(QApplication::translate("IOWidget", "Sense", Q_NULLPTR));
        label_11->setText(QApplication::translate("IOWidget", "Group", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("IOWidget", "Setting", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IOWidget: public Ui_IOWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOWIDGET_H
