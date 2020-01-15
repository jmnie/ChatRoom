/********************************************************************************
** Form generated from reading UI file 'clientwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_clientWidget
{
public:

    void setupUi(QWidget *clientWidget)
    {
        if (clientWidget->objectName().isEmpty())
            clientWidget->setObjectName(QString::fromUtf8("clientWidget"));
        clientWidget->resize(400, 300);

        retranslateUi(clientWidget);

        QMetaObject::connectSlotsByName(clientWidget);
    } // setupUi

    void retranslateUi(QWidget *clientWidget)
    {
        clientWidget->setWindowTitle(QApplication::translate("clientWidget", "clientWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class clientWidget: public Ui_clientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
