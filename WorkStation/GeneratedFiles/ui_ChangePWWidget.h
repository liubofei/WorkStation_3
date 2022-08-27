/********************************************************************************
** Form generated from reading UI file 'ChangePWWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPWWIDGET_H
#define UI_CHANGEPWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangePWWidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_oldPW;
    QLabel *label_2;
    QLineEdit *lineEdit_newPW;
    QLineEdit *lineEdit_checkNewPW;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_changePW;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ChangePWWidget)
    {
        if (ChangePWWidget->objectName().isEmpty())
            ChangePWWidget->setObjectName(QStringLiteral("ChangePWWidget"));
        ChangePWWidget->resize(400, 300);
        layoutWidget = new QWidget(ChangePWWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(75, 60, 237, 166));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(72, 0));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_oldPW = new QLineEdit(layoutWidget);
        lineEdit_oldPW->setObjectName(QStringLiteral("lineEdit_oldPW"));
        lineEdit_oldPW->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_oldPW, 0, 1, 1, 2);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(78, 0));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_newPW = new QLineEdit(layoutWidget);
        lineEdit_newPW->setObjectName(QStringLiteral("lineEdit_newPW"));
        lineEdit_newPW->setMinimumSize(QSize(143, 20));
        lineEdit_newPW->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_newPW, 1, 1, 1, 2);

        lineEdit_checkNewPW = new QLineEdit(layoutWidget);
        lineEdit_checkNewPW->setObjectName(QStringLiteral("lineEdit_checkNewPW"));
        lineEdit_checkNewPW->setMinimumSize(QSize(143, 20));
        lineEdit_checkNewPW->setMaximumSize(QSize(143, 20));
        lineEdit_checkNewPW->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_checkNewPW, 2, 2, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 3);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 1, 1, 1, 1);

        pushButton_changePW = new QPushButton(layoutWidget);
        pushButton_changePW->setObjectName(QStringLiteral("pushButton_changePW"));
        pushButton_changePW->setMinimumSize(QSize(75, 40));
        pushButton_changePW->setMaximumSize(QSize(75, 40));

        gridLayout_2->addWidget(pushButton_changePW, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 1, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 40));
        pushButton_2->setMaximumSize(QSize(75, 40));

        gridLayout_2->addWidget(pushButton_2, 2, 2, 1, 1);


        retranslateUi(ChangePWWidget);

        QMetaObject::connectSlotsByName(ChangePWWidget);
    } // setupUi

    void retranslateUi(QWidget *ChangePWWidget)
    {
        ChangePWWidget->setWindowTitle(QApplication::translate("ChangePWWidget", "ChangePWWidget", Q_NULLPTR));
        label->setText(QApplication::translate("ChangePWWidget", "\346\227\247\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("ChangePWWidget", "\346\226\260\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("ChangePWWidget", "\346\226\260\345\257\206\347\240\201\347\241\256\350\256\244\357\274\232", Q_NULLPTR));
        pushButton_changePW->setText(QApplication::translate("ChangePWWidget", "\347\241\256\350\256\244\344\277\256\346\224\271", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ChangePWWidget", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChangePWWidget: public Ui_ChangePWWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPWWIDGET_H
