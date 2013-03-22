#ifndef QBOX2DVIEW_H
#define QBOX2DVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <qmath.h>
#include <QPainter>
#include <QLabel>

class QBox2DView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QBox2DView(QWidget *parent = 0);

public slots:
    void setText(QString text) {
        q_label->setText(text);
        q_label->adjustSize();
    }

signals:

private:
    void scaleBy(double factor) {
        scale(factor, factor);
    }
    QLabel *q_label;

protected:
    void wheelEvent(QWheelEvent *event) {
        scaleBy(qPow(4.0 / 3.0, (event->delta() / 240.0)));
    }
    
};

#endif // QBOX2DVIEW_H
