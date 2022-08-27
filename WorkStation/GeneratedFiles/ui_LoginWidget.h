/********************************************************************************
** Form generated from reading UI file 'LoginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton_login;
    QLabel *label;
    QRadioButton *radioButton_admin;
    QRadioButton *radioButton_config;
    QPushButton *pushButton_changePW;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->resize(200, 280);
        LoginWidget->setMinimumSize(QSize(200, 280));
        LoginWidget->setMaximumSize(QSize(200, 280));
        lineEdit = new QLineEdit(LoginWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(28, 102, 145, 43));
        QFont font;
        font.setPointSize(15);
        font.setKerning(true);
        lineEdit->setFont(font);
        lineEdit->setEchoMode(QLineEdit::Password);
        lineEdit->setAlignment(Qt::AlignCenter);
        pushButton_login = new QPushButton(LoginWidget);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setGeometry(QRect(30, 210, 61, 39));
        label = new QLabel(LoginWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 166, 83, 25));
        label->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);
        radioButton_admin = new QRadioButton(LoginWidget);
        radioButton_admin->setObjectName(QStringLiteral("radioButton_admin"));
        radioButton_admin->setGeometry(QRect(46, 66, 65, 16));
        radioButton_admin->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        radioButton_admin->setChecked(true);
        radioButton_admin->setAutoRepeat(true);
        radioButton_config = new QRadioButton(LoginWidget);
        radioButton_config->setObjectName(QStringLiteral("radioButton_config"));
        radioButton_config->setGeometry(QRect(116, 66, 65, 16));
        radioButton_config->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        radioButton_config->setChecked(false);
        radioButton_config->setAutoRepeat(true);
        pushButton_changePW = new QPushButton(LoginWidget);
        pushButton_changePW->setObjectName(QStringLiteral("pushButton_changePW"));
        pushButton_changePW->setGeometry(QRect(114, 212, 61, 41));

        retranslateUi(LoginWidget);
        QObject::connect(pushButton_login, SIGNAL(clicked()), LoginWidget, SLOT(login()));

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "LoginWidget", Q_NULLPTR));
        lineEdit->setText(QString());
        pushButton_login->setText(QApplication::translate("LoginWidget", "\347\231\273\351\231\206", Q_NULLPTR));
        label->setText(QApplication::translate("LoginWidget", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
        radioButton_admin->setText(QApplication::translate("LoginWidget", "\347\256\241\347\220\206\345\221\230", Q_NULLPTR));
        radioButton_config->setText(QApplication::translate("LoginWidget", "\345\224\256\345\220\216", Q_NULLPTR));
        pushButton_changePW->setText(QApplication::translate("LoginWidget", "\344\277\256\346\224\271\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
