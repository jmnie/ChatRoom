#include <QApplication>
#include"view/client_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client_widget w;
    w.show();

    return a.exec();
}
