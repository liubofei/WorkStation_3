/********************************************************************************
** Form generated from reading UI file 'MessageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOX_H
#define UI_MESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessageBox
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_icon;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_message;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *MessageBox)
    {
        if (MessageBox->objectName().isEmpty())
            MessageBox->setObjectName(QStringLiteral("MessageBox"));
        MessageBox->resize(417, 152);
        verticalLayout = new QVBoxLayout(MessageBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        groupBox = new QGroupBox(MessageBox);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_icon = new QLabel(groupBox);
        label_icon->setObjectName(QStringLiteral("label_icon"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_icon->sizePolicy().hasHeightForWidth());
        label_icon->setSizePolicy(sizePolicy);
        label_icon->setMinimumSize(QSize(60, 60));
        label_icon->setMaximumSize(QSize(60, 60));

        verticalLayout_2->addWidget(label_icon);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_message = new QLabel(groupBox);
        label_message->setObjectName(QStringLiteral("label_message"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label_message->setFont(font);
        label_message->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_message->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_message->setWordWrap(true);

        verticalLayout_3->addWidget(label_message);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_ok = new QPushButton(groupBox);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        sizePolicy.setHeightForWidth(pushButton_ok->sizePolicy().hasHeightForWidth());
        pushButton_ok->setSizePolicy(sizePolicy);
        pushButton_ok->setMinimumSize(QSize(75, 30));
        pushButton_ok->setMaximumSize(QSize(75, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        pushButton_ok->setFont(font1);

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(groupBox);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        sizePolicy.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy);
        pushButton_cancel->setMinimumSize(QSize(75, 30));
        pushButton_cancel->setMaximumSize(QSize(75, 30));
        pushButton_cancel->setFont(font1);

        horizontalLayout->addWidget(pushButton_cancel);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_3->setStretch(0, 10);

        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout->addWidget(groupBox);


        retranslateUi(MessageBox);
        QObject::connect(pushButton_ok, SIGNAL(clicked()), MessageBox, SLOT(onOKClicked()));
        QObject::connect(pushButton_cancel, SIGNAL(clicked()), MessageBox, SLOT(onCancelClicked()));

        QMetaObject::connectSlotsByName(MessageBox);
    } // setupUi

    void retranslateUi(QWidget *MessageBox)
    {
        MessageBox->setWindowTitle(QApplication::translate("MessageBox", "Hint", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_icon->setText(QString());
        label_message->setText(QString());
        pushButton_ok->setText(QApplication::translate("MessageBox", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("MessageBox", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MessageBox: public Ui_MessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOX_H
