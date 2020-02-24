#ifndef SERVER_WIDGET_H
#define SERVER_WIDGET_H

#include <QWidget>

namespace Ui {
class server_widget;
}

class server_widget : public QWidget
{
    Q_OBJECT

public:
    explicit server_widget(QWidget *parent = nullptr);
    ~server_widget();

private:
    Ui::server_widget *ui;
};

#endif // SERVER_WIDGET_H
