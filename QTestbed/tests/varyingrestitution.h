#ifndef VARYINGRESTITUTION_H
#define VARYINGRESTITUTION_H

#include <qbox2dtest.h>

class VaryingRestitution : public QBox2DTest
{
    Q_OBJECT
public:
    explicit VaryingRestitution(const b2Vec2& gravity = b2Vec2_zero, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // VARYINGRESTITUTION_H
