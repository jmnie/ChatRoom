#include "serverwidget.h"
#include "ui_serverwidget.h"

serverWidget::serverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverWidget)
{
    ui->setupUi(this);
}

serverWidget::~serverWidget()
{
    delete ui;
}


