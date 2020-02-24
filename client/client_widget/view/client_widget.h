#ifndef CLIENT_WIDGET_H
#define CLIENT_WIDGET_H

#include <QWidget>
#include<QLabel>
#include"imclicklabel.h"

class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class IMClickLabel;
class IMLoginCtrl;
struct UserInformation;


namespace Ui {
class client_widget;
}

class client_widget : public QWidget
{
    Q_OBJECT

public:
   client_widget(QWidget *parent = nullptr);
    ~client_widget();

private:
    Ui::client_widget *ui;
    void initIMLoginWidget();

public slots:
    //display the MainWindow
    void showMainWidget();

private:
    QLineEdit *m_leUserID;
    QLineEdit *m_leUserPwd;   // password
    IMClickLabel *m_labelRegister;  // register account
    IMClickLabel *m_labelForgotPwd; // forget password
    QCheckBox *m_cbKeepPwd;   // remember password
    QCheckBox *m_cbAutoLogin; // login automatically
    QComboBox *m_cbxStatus;   // login status
    QPushButton *m_btnLogin;  // login button

    QPushButton *m_moreButton;// expand button
    QWidget *m_extendedWidget;// expand interface
    QLineEdit *m_hostAddress; // server  ip address
    QLineEdit *m_hostPort;    // server ip port

    QLabel *m_labelStatus;    // status label
    bool m_isLogin;           // login
    IMLoginCtrl *m_loginCtrl; // used to control

    int m_timerID;            // timer ID
    bool m_closeTimer;        // whether time is closed
    int m_counter;            // counter
    bool m_isAutoLogin;         // automatic login

    int m_status;


};

#endif // CLIENT_WIDGET_H
