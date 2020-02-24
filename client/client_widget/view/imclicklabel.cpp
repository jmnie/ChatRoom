
#include"imclicklabel.h"
#include <QMouseEvent>

IMClickLabel::IMClickLabel(QWidget * parent):
    QLabel (parent)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
}

IMClickLabel::IMClickLabel(const QString &text, QWidget *parent) :
    QLabel(parent)
{
    setText(text);
}

// mark: protected:------------------------------------------------
void IMClickLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit clicked();//(this);
}

void IMClickLabel::enterEvent(QEvent * )
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::blue);
    setPalette(pa);
}

void IMClickLabel::leaveEvent(QEvent *)
{
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::darkGreen);
    setPalette(pa);
}
