/********************************************************************************
** Form generated from reading UI file 'serverwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWIDGET_H
#define UI_SERVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverWidget
{
public:
    QLabel *label;

    void setupUi(QWidget *serverWidget)
    {
        if (serverWidget->objectName().isEmpty())
            serverWidget->setObjectName(QString::fromUtf8("serverWidget"));
        serverWidget->resize(656, 438);
        label = new QLabel(serverWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 251, 17));

        retranslateUi(serverWidget);

        QMetaObject::connectSlotsByName(serverWidget);
    } // setupUi

    void retranslateUi(QWidget *serverWidget)
    {
        serverWidget->setWindowTitle(QApplication::translate("serverWidget", "IMQT_Server", nullptr));
        label->setText(QApplication::translate("serverWidget", "Accounts connected to the server:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serverWidget: public Ui_serverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWIDGET_H
