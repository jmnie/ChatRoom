#include "view/client_widget.h"
#include "ui_client_widget.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include<QCheckBox>

//client_widget::client_widget(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::client_widget)
//{
//    ui->setupUi(this);
//}

client_widget::client_widget(QWidget *parent) :
    QWidget(parent)
{
    //ui->setupUi(this);
    initIMLoginWidget();
}


client_widget::~client_widget()
{
    //delete ui;
}

void client_widget::initIMLoginWidget()
{

      QVBoxLayout *vLayoutMidTop   = new QVBoxLayout;
      QVBoxLayout *vLayoutRightTop = new QVBoxLayout;
      QHBoxLayout *hLayoutTop      = new QHBoxLayout;

      QHBoxLayout *hLayoutMid  = new QHBoxLayout;
      QHBoxLayout *hLayoutBtm  = new QHBoxLayout;
      QVBoxLayout *vLayoutMain = new QVBoxLayout;

      QLabel *labelHeadLine = new QLabel(tr("Login to the system"));
      labelHeadLine->setAlignment(Qt::AlignCenter);
      QPalette pa;
      pa.setColor(QPalette::WindowText, Qt::black);
      labelHeadLine->setPalette(pa);
      QFont ft;
      ft.setPointSize(17);
      labelHeadLine->setFont(ft);

      // set the login layout
       m_leUserID = new QLineEdit;
       m_leUserID->setPlaceholderText(tr("Account"));
       m_leUserPwd = new QLineEdit;
       m_leUserPwd->setPlaceholderText(tr("Password"));
       m_leUserPwd->setEchoMode(QLineEdit::Password);
       vLayoutMidTop->addWidget(m_leUserID);
       vLayoutMidTop->addWidget(m_leUserPwd);

       m_labelRegister = new IMClickLabel;
       m_labelRegister->setText(tr("Register Account"));
       m_labelForgotPwd = new IMClickLabel;
       m_labelForgotPwd->setText(tr("Foget Password"));
       vLayoutRightTop->addWidget(m_labelRegister);
       vLayoutRightTop->addWidget(m_labelForgotPwd);

       hLayoutTop->addLayout(vLayoutMidTop);
       hLayoutTop->addLayout(vLayoutRightTop);
       hLayoutTop->setMargin(10);

       m_cbKeepPwd = new QCheckBox(tr("Remember Password"));
       m_cbAutoLogin = new QCheckBox(tr("Login Automatically"));
       hLayoutMid->addWidget(m_cbKeepPwd);
        hLayoutMid->addWidget(m_cbAutoLogin);




      vLayoutMain->addWidget(labelHeadLine);
      setLayout(vLayoutMain);




}

void client_widget::showMainWidget()
{

}
