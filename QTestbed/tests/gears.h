#ifndef GEARS_H
#define GEARS_H

#include <qbox2dtest.h>

class Gears : public QBox2DTest
{
    Q_OBJECT
public:
    explicit Gears(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GEARS_H
