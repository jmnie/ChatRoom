#include "onlinestate.h"

onlineState::onlineState(QWidget *parent) : QWidget(parent)
{

    port = 2019;
    serverIP = new QHostAddress();
    QString ip = SERVER_IP;
    serverIP->setAddress(ip);
    tcpSocket=new QTcpSocket(this);
    tcpSocket->connectToHost(*serverIP, port);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    sendRQ();
    StateUpdateDone=false;
    SendRqTimer=new QTimer(this);
    connect(SendRqTimer,SIGNAL(timeout()),this,SLOT(senRq()));
    SendRqTimer->start(1000);
}
void onlineState::sendRQ()
{
    QString msg = tr(ONLINESTATE);
    tcpSocket->write(msg.toLatin1(), msg.toLatin1().length());
}
void onlineState::senRq()
{
    tcpSocket->connectToHost(*serverIP, port);
    sendRQ();
}
void onlineState::dataReceived()
{
    QByteArray datagram;
    datagram.resize(tcpSocket->bytesAvailable());
    tcpSocket->read(datagram.data(), datagram.size());
    QString msg = datagram.data();
    //qDebug()<<"online State msg:"<<msg;
    count=msg.section('#',1,1).toInt();
    //qDebug()<<"count:"<<count;
    users=new userInfo[count];
    int i;
    QString str;
    for(i=0;i<count;i++)
     {
        str=msg.section(':',i,i);
        users[i].name=str.section(',',0,0).toStdString();
        users[i].online=str.section(',',1,1).toInt();
        users[i].pic=str.section(',',2,2).toInt();
    }
    StateUpdateDone=true;
//    for(i=0;i<count;i++)
//    {
//        qDebug()<<users[i].name.c_str()<<" "<<users[i].online<<" "<<users[i].pic;
//    }
    tcpSocket->disconnectFromHost();
}
