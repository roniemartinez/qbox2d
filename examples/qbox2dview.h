#ifndef QBOX2DVIEW_H
#define QBOX2DVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <qmath.h>

class QBox2DView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QBox2DView(QWidget *parent = 0);

signals:

private:
    void scaleBy(double factor) {
        scale(factor, factor);
    }

protected:
    void wheelEvent(QWheelEvent *event) {
        scaleBy(qPow(4.0 / 3.0, (event->delta() / 240.0)));
    }
    
};

#endif // QBOX2DVIEW_H
