#include "clientwidget.h"
#include "ui_clientwidget.h"


clientWidget::clientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientWidget)
{
    ui->setupUi(this);

    //simple example
    char *data="hello qt!";
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);
    client->write(data);

}

clientWidget::~clientWidget()
{
    delete ui;
}
