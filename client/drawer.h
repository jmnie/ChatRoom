#ifndef DRAWER_H
#define DRAWER_H

#include <QToolButton>
#include <QTableWidget>
#include <QWidget>
#include <QPushButton>
#include <QToolBox>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QQueue>
#include <QTimer>
#include <QPoint>
#include <QApplication>
#include "tcpclient.h"
#include "addfriends.h"
#include "friendslist.h"
#include "onlinestate.h"
#include "command.h"
class Drawer : public QToolBox
{
    Q_OBJECT
public:
    Drawer(QWidget *parent = 0, Qt::WindowFlags f = 0);

    QString username;
    QString fromname;
    QString toname;
    QString onlinename;
    QTabWidget *tabWidget;
    QToolButton *toolBtn1;
    QToolButton *toolBtn2;
    QPushButton *addFriendsBtn;
    QComboBox *SelectMapStytle;
    QWidget *myFriends;
    QVBoxLayout *friLayout;
    //QLabel *picSelect;
    bool addflag;
    bool refuseflag;
    bool changefunc;
    bool PicChangeflag;
    QQueue<QString> friendList;
    QTimer *havedoneTimer;
    QToolButton **friendsListButtons;
    int friendsNum;
    AddFriends *addFriends;
private slots:
    void showChatWidget1();
    void slotAddFriends();
    void showaddfriendWidget();
    void MapStytleSet();
    void getFDL();
    void CheckFlag();
    void CheckonlineState();
    void Quit();
private:
    QPoint windowPos; //Position of Window
    QPoint mousePos; // Position of Mouse
    QPoint dPos;//Position of Mouse after moving
    void mousePressEvent(QMouseEvent *event);//Mouse Clicked Event
    void mouseMoveEvent(QMouseEvent *event);//Mouse Moving Eevnt
    void initialMapstylestring();
    void initialfriendsList();
    QString MapStytle[11];
    TcpClient *chat1;
    friendsList *getFriendsList;
    onlineState *checkOnlineState;
    QTimer *getfdlTimer;
    QTimer *onlineStateTimer;
    struct userInfo *users;
};

#endif // DRAWER_H
