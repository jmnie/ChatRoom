#include "addfriends.h"
#include "command.h"

#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <iostream>

AddFriends::AddFriends(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Add Friend"));
    this->setFixedSize(300,200);

    nameLabel = new QLabel(tr("Name:"));
    nameLineEdit = new QLineEdit();
    enterBtn = new QPushButton("Enter");

    tcpSocket = new QTcpSocket(this);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLineEdit, 0, 1);
    mainLayout->addWidget(enterBtn, 1, 1);

    //Connect to Port
    port = 2019;
    serverIP = new QHostAddress();
    QString ip = SERVER_IP;
    serverIP->setAddress(ip);

    connect(enterBtn, SIGNAL(clicked()), this, SLOT(slotEnter()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
}


AddFriends::~AddFriends()
{
    tcpSocket->disconnectFromHost();
}
//Disconnect from server before stopping all events
void AddFriends::closeEvent(QCloseEvent *event)
{
    tcpSocket->disconnectFromHost();
    tcpSocket->waitForDisconnected();
    event->accept();
}
void AddFriends::slotEnter()
{
    tcpSocket->connectToHost(*serverIP, port);
    if(nameLineEdit->text() == "")
    {
        QMessageBox::warning(this, tr("Name is empty"), tr("Name is empty"));
        return;
    }
    QString msg = tr(ADDFRIENDS);
    toname=nameLineEdit->text();
    msg += username+"+"+toname;
    int length=tcpSocket->write(msg.toUtf8(), msg.toUtf8().length());
    if(length != msg.toUtf8().length())
    {
        return;
    }
    this->hide();
}

void AddFriends::dataReceived()
{
    QByteArray datagram;
    datagram.resize(tcpSocket->bytesAvailable());
    tcpSocket->read(datagram.data(), datagram.size());
    QString msg = datagram.data();

    if(msg == "The name is wrong")
    {
        QMessageBox::warning(this, tr("the message from server..."), tr("The name is wrong"));
        this->show();
    }
    else if(msg == "message has been sended")
    {
        QMessageBox::information(this, tr("the message from server..."), tr("message has been sended"));
        tcpSocket->disconnectFromHost();
    }
    else if(msg=="you are have been friends!")
    {
        QMessageBox::information(this, tr("the message from server..."), tr("you are have been friends!"));
        this->show();
    }
}
