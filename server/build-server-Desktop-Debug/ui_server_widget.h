/********************************************************************************
** Form generated from reading UI file 'server_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_WIDGET_H
#define UI_SERVER_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_server_widget
{
public:

    void setupUi(QWidget *server_widget)
    {
        if (server_widget->objectName().isEmpty())
            server_widget->setObjectName(QString::fromUtf8("server_widget"));
        server_widget->resize(400, 300);

        retranslateUi(server_widget);

        QMetaObject::connectSlotsByName(server_widget);
    } // setupUi

    void retranslateUi(QWidget *server_widget)
    {
        server_widget->setWindowTitle(QApplication::translate("server_widget", "server_widget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class server_widget: public Ui_server_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_WIDGET_H
