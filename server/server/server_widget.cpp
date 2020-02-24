#include "server_widget.h"
#include "ui_server_widget.h"

server_widget::server_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::server_widget)
{
    ui->setupUi(this);
}

server_widget::~server_widget()
{
    delete ui;
}
