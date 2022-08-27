/********************************************************************************
** Form generated from reading UI file 'CommuniWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNIWIDGET_H
#define UI_COMMUNIWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommuniWidget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *tableWidget_tcp;
    QLineEdit *lineEdit_send_tcp;
    QPushButton *pushButton_5;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_save_tcp;
    QPushButton *pushButton_cancel_tcp;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_6;
    QTextEdit *textEdit_recv_tcp;
    QWidget *tab_2;
    QLineEdit *lineEdit_send_com;
    QPushButton *pushButton_send_com;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_save_com;
    QPushButton *pushButton_cancel_com;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableWidget_com;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QTextEdit *textEdit_recv_com;

    void setupUi(QWidget *CommuniWidget)
    {
        if (CommuniWidget->objectName().isEmpty())
            CommuniWidget->setObjectName(QStringLiteral("CommuniWidget"));
        CommuniWidget->resize(942, 612);
        tabWidget = new QTabWidget(CommuniWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(6, 14, 921, 593));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(6, 10, 581, 505));
        horizontalLayout_4 = new QHBoxLayout(groupBox);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tableWidget_tcp = new QTableWidget(groupBox);
        tableWidget_tcp->setObjectName(QStringLiteral("tableWidget_tcp"));

        horizontalLayout_4->addWidget(tableWidget_tcp);

        lineEdit_send_tcp = new QLineEdit(tab);
        lineEdit_send_tcp->setObjectName(QStringLiteral("lineEdit_send_tcp"));
        lineEdit_send_tcp->setGeometry(QRect(602, 18, 203, 31));
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(824, 18, 71, 31));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(6, 528, 833, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_save_tcp = new QPushButton(layoutWidget);
        pushButton_save_tcp->setObjectName(QStringLiteral("pushButton_save_tcp"));
        pushButton_save_tcp->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_save_tcp);

        pushButton_cancel_tcp = new QPushButton(layoutWidget);
        pushButton_cancel_tcp->setObjectName(QStringLiteral("pushButton_cancel_tcp"));
        pushButton_cancel_tcp->setMinimumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_cancel_tcp);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(600, 62, 297, 451));
        horizontalLayout_6 = new QHBoxLayout(groupBox_4);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        textEdit_recv_tcp = new QTextEdit(groupBox_4);
        textEdit_recv_tcp->setObjectName(QStringLiteral("textEdit_recv_tcp"));

        horizontalLayout_6->addWidget(textEdit_recv_tcp);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        lineEdit_send_com = new QLineEdit(tab_2);
        lineEdit_send_com->setObjectName(QStringLiteral("lineEdit_send_com"));
        lineEdit_send_com->setGeometry(QRect(648, 22, 177, 25));
        pushButton_send_com = new QPushButton(tab_2);
        pushButton_send_com->setObjectName(QStringLiteral("pushButton_send_com"));
        pushButton_send_com->setGeometry(QRect(842, 20, 71, 25));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 530, 839, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton_save_com = new QPushButton(layoutWidget1);
        pushButton_save_com->setObjectName(QStringLiteral("pushButton_save_com"));
        pushButton_save_com->setMinimumSize(QSize(80, 30));

        horizontalLayout_2->addWidget(pushButton_save_com);

        pushButton_cancel_com = new QPushButton(layoutWidget1);
        pushButton_cancel_com->setObjectName(QStringLiteral("pushButton_cancel_com"));
        pushButton_cancel_com->setMinimumSize(QSize(80, 30));

        horizontalLayout_2->addWidget(pushButton_cancel_com);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 611, 511));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tableWidget_com = new QTableWidget(groupBox_2);
        tableWidget_com->setObjectName(QStringLiteral("tableWidget_com"));

        horizontalLayout_3->addWidget(tableWidget_com);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(640, 66, 273, 455));
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        textEdit_recv_com = new QTextEdit(groupBox_3);
        textEdit_recv_com->setObjectName(QStringLiteral("textEdit_recv_com"));

        horizontalLayout_5->addWidget(textEdit_recv_com);

        tabWidget->addTab(tab_2, QString());

        retranslateUi(CommuniWidget);
        QObject::connect(pushButton_save_com, SIGNAL(clicked()), CommuniWidget, SLOT(onComBtnClicked()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), CommuniWidget, SLOT(onTcpBtnClicked()));
        QObject::connect(pushButton_cancel_com, SIGNAL(clicked()), CommuniWidget, SLOT(onComBtnClicked()));
        QObject::connect(pushButton_save_tcp, SIGNAL(clicked()), CommuniWidget, SLOT(onTcpBtnClicked()));
        QObject::connect(pushButton_cancel_tcp, SIGNAL(clicked()), CommuniWidget, SLOT(onTcpBtnClicked()));
        QObject::connect(pushButton_send_com, SIGNAL(clicked()), CommuniWidget, SLOT(onComBtnClicked()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CommuniWidget);
    } // setupUi

    void retranslateUi(QWidget *CommuniWidget)
    {
        CommuniWidget->setWindowTitle(QApplication::translate("CommuniWidget", "CommuniWidget", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("CommuniWidget", "Network List", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("CommuniWidget", "Send", Q_NULLPTR));
        pushButton_save_tcp->setText(QApplication::translate("CommuniWidget", "Confirm ", Q_NULLPTR));
        pushButton_cancel_tcp->setText(QApplication::translate("CommuniWidget", "Cancel", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("CommuniWidget", "Receive", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("CommuniWidget", "Network", Q_NULLPTR));
        pushButton_send_com->setText(QApplication::translate("CommuniWidget", "Send", Q_NULLPTR));
        pushButton_save_com->setText(QApplication::translate("CommuniWidget", "Confirm ", Q_NULLPTR));
        pushButton_cancel_com->setText(QApplication::translate("CommuniWidget", "Cancel", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("CommuniWidget", "Serial port list", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("CommuniWidget", "Receive", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("CommuniWidget", "Serial port", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CommuniWidget: public Ui_CommuniWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNIWIDGET_H
