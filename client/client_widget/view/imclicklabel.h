#ifndef IMCLICKLABEL_H
#define IMCLICKLABEL_H

#include<QLabel>

class IMClickLabel : public QLabel
{
        Q_OBJECT
public:
    explicit IMClickLabel(QWidget *parent = 0);
    IMClickLabel(const QString &text, QWidget *parent=0);
signals:
    void clicked();
protected:
        void mouseReleaseEvent(QMouseEvent *);
        void enterEvent(QEvent *);
        void leaveEvent(QEvent *);
    public slots:
};

#endif // IMCLICKLABEL_H
