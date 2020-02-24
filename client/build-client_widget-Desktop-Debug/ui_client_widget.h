/********************************************************************************
** Form generated from reading UI file 'client_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_WIDGET_H
#define UI_CLIENT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client_widget
{
public:
    QLabel *label;

    void setupUi(QWidget *client_widget)
    {
        if (client_widget->objectName().isEmpty())
            client_widget->setObjectName(QString::fromUtf8("client_widget"));
        client_widget->resize(400, 300);
        label = new QLabel(client_widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 20, 171, 41));

        retranslateUi(client_widget);

        QMetaObject::connectSlotsByName(client_widget);
    } // setupUi

    void retranslateUi(QWidget *client_widget)
    {
        client_widget->setWindowTitle(QApplication::translate("client_widget", "client_widget", nullptr));
        label->setText(QApplication::translate("client_widget", "Login to the System", nullptr));
    } // retranslateUi

};

namespace Ui {
    class client_widget: public Ui_client_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_WIDGET_H
