#ifndef VARYINGRESTITUTION_H
#define VARYINGRESTITUTION_H

#include <qbox2dworld.h>

class VaryingRestitution : public QBox2DWorld
{
    Q_OBJECT
public:
    explicit VaryingRestitution(const b2Vec2& gravity, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // VARYINGRESTITUTION_H
