#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
    class serverWidget;
}

class serverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit serverWidget(QWidget *parent = nullptr);
    ~serverWidget();

private slots:
    void acceptConnection();
    void readClient();


private:
    Ui::serverWidget *ui;


};

#endif // SERVERWIDGET_H
