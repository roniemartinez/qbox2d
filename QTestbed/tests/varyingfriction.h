#ifndef VARYINGFRICTION_H
#define VARYINGFRICTION_H

#include <qbox2dworld.h>
#include <qbox2dbody.h>

class VaryingFriction : public QBox2DWorld
{
    Q_OBJECT
public:
    explicit VaryingFriction(const b2Vec2 &gravity, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // VARYINGFRICTION_H
