#ifndef VARYINGFRICTION_H
#define VARYINGFRICTION_H

#include <qbox2dtest.h>

class VaryingFriction : public QBox2DTest
{
    Q_OBJECT
public:
    explicit VaryingFriction(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // VARYINGFRICTION_H
